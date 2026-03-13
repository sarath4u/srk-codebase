import re
import numpy as np
from ..utils.geometry import moveto, lineto, hlineto, vlineto, quadbez, cubicbez, transform_scale
def svgparser(f):
    """
    A function to parse the svg file to get the
    information for generating the figure
    """
    translate_tuple = None
    scale_tuple     = None
    path_found      = False
    with open(f, "r") as fhandle:
        for row in fhandle:
            line = row.strip()
            if 'path' in line or path_found:
                if not 'd=' in line: 
                    if path_found:
                        curve_data = curve_data + line
                    else:
                        path_found = True
                        continue
                if path_found:
                    if 'd=' in line:
                        curve_data = line.split('d=')[1]
                    else:
                        curve_data = curve_data + ' ' + line
                else:
                    if 'transform' in line:
                        transform_info  = line.split('"')[1].split()
                        translate_tuple = tuple(map(float, re.findall(r'\(([^)]+)\)', transform_info[0])[0].split(',')))
                        scale_tuple     = tuple(map(float, re.findall(r'\(([^)]+)\)', transform_info[1])[0].split(',')))
                    curve_data = line.split('d=')[1]
                    path_found = True
                    if 'z' or 'Z' in curve_data: break
            else:
                continue
    return translate_tuple, scale_tuple, curve_data.split('"')[1]

def svg_to_curve(filename, resolution=10):
    """
    Convert SVG path into Nx2 numpy array curve
    """
    translate_tuple, scale_tuple, data = svgparser(filename)
    if data.count('M') > 1:
        index = data[1:].find('M')
        data  = data[:index]
    if translate_tuple: 
        translate = True
        tx, ty    = translate_tuple
    else:
        translate = False
    if scale_tuple: 
        scale  = True
        sx, sy = scale_tuple
    else:
        scale = False
    commands = re.findall(r'[a-zA-Zz]', data)
    curve    = np.zeros(((len(commands) - 2) * resolution + 1,  2), dtype=float)
    for ii, command in enumerate(commands[:-1]):
        start_char = commands[ii]
        end_char   = commands[ii+1]
        pattern    = rf"{re.escape(start_char)}(.*?){re.escape(end_char)}"
        coords     = re.findall(pattern, data)[0]
        data       = data[len(coords)+1:]
        if ',' in coords:
            if not ' ' in coords:
                coords = coords.split(',')
                for jj, each in enumerate(coords):
                    if '-' in each:
                        splits = each.split('-')
                        if splits[0] == '' and len(splits) == 2: continue
                        if splits[0] == '':
                            splits[1] = '-' + splits[1]
                            splits.pop(0)
                        to_save = coords[jj+1:jj+len(splits)]
                        for kk in range(1, len(splits)):
                            splits[kk] = '-' + splits[kk] 
                        coords[jj : jj + len(splits)] = splits
                        if to_save:
                            coords[jj + len(splits): jj + len(splits)] = to_save
                        else:
                            break
            else:
                coords = coords.split()
                coords = ','.join(coords)
                coords = coords.split(',')
    
        elif '-' in coords:
            coords = coords.split('-')
            if coords[0] == '':
                coords[1] = '-' + coords[1]
                coords.pop(0)
            for kk in range(1, len(coords)):
                coords[kk] = '-' + coords[kk]
        else:
            coords = coords.split()
        if type(coords) != list:
            coords = [coords]
        coords = np.array(list(map(float, coords)))
        if scale:
            coords = transform_scale(coords, sx, -sy)
        else:
            coords = transform_scale(coords, 1, -1)
        if command == 'M':
            x, y = moveto(*coords)
            xr, yr = x, y
            curve[0, 0] = x
            curve[0, 1] = y
        elif command == 'm':
            coords[0] += xr
            coords[1] += yr
            x, y = moveto(*coords)
            xr, yr = x, y
        elif command == 'L':
            x, y = lineto(xr, yr, *coords, resolution)
            xr, yr = coords
        elif command == 'l':
            coords[0] += xr
            coords[1] += yr
            x, y = lineto(xr, yr, *coords, resolution)
            xr, yr = coords
        elif command == 'H':
            x, y = hlineto(xr, yr, *coords, resolution)
            xr = coords.item()
        elif command == 'h':
            coords[0] += xr
            x, y = hlineto(xr, yr, *coords, resolution)
            xr = coords.item()
        elif command == 'V':
            coords[0] = yr
            x, y = vlineto(xr, yr, coords, resolution)
            yr = coords.item()
        elif command == 'v':
            coords[0] += yr
            x, y = vlineto(xr, yr, *coords, resolution)
            yr = coords.item()
        elif command == 'C':
            x, y = cubicbez(xr, yr,*coords, resolution)
            xr, yr = coords[-2:]
        elif command == 'c':
            coords[0::2,] += xr 
            coords[1::2,] += yr 
            x, y = cubicbez(xr, yr,*coords, resolution)
            xr, yr = coords[-2:]
        if not command == 'M' and not command == 'm':
            curve[(ii-1)*resolution + 1:ii * resolution + 1, 0] = x
            curve[(ii-1)*resolution + 1:ii * resolution + 1, 1] = y
    return curve
