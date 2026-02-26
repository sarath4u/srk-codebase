from svgmodules import *
import re
import sys, pdb
import matplotlib.pyplot as plt
import numpy as np

f = sys.argv[1]
t = 100
translate_tuple, scale_tuple, data = svgparser(f)
if data.count('M') > 1:
    index = data[1:].find('M')
    data  = data[:index]
if translate_tuple: 
    translate = True
    tx, ty = translate_tuple
else:
    translate = False
if scale_tuple: 
    scale = True
    sx, sy = scale_tuple
else:
    scale = False
commands = re.findall(r'[a-zA-Zz]', data)
#print(commands)
fig, axes = plt.subplots(1, figsize=(3.5,4))
for ii, command in enumerate(commands[:-1]):
#    print(f'count: {ii}, command: {command}')
    start_char = commands[ii]
    end_char   = commands[ii+1]
    if command == 'Z': pdb.set_trace()
#    print(start_char, end_char)
#    if ii == 4:
#        import pdb
#        pdb.set_trace()
    pattern = rf"{re.escape(start_char)}(.*?){re.escape(end_char)}"
    coords = re.findall(pattern, data)[0]
#    print(f'actual string: {coords}')
    data = data[len(coords)+1:]
    if ',' in coords:
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
    elif '-' in coords:
        coords = coords.split('-')
        if coords[0] == '':
            coords[1] = '-' + coords[1]
            coords.pop(0)
        for kk in range(1, len(coords)):
            coords[kk] = '-' + coords[kk]
#    import pdb
#    pdb.set_trace()
#    if ii == 4:
#        import pdb
#        pdb.set_trace()
    else:
        coords = coords.split()
    if type(coords) != list:
        coords = [coords]
    coords = np.array(list(map(float, coords)))
    print(f'parsed string: {coords}')
    if scale:
        coords = transform_scale(coords, sx, -sy)
    else:
        coords = transform_scale(coords, 1, -1)
        print(f'Scaled coords: {coords}')
#    if translate:
#        coords = transform_translate(coords, tx, ty)
    if command == 'M':
        x, y = moveto(*coords)
        origin_x, origin_y = x, y
        xr, yr = x, y
    elif command == 'm':
        coords[0] += xr
        coords[1] += yr
        x, y = moveto(*coords)
        xr, yr = x, y
    elif command == 'L':
        x, y = lineto(xr, yr, *coords, t)
        xr, yr = coords
    elif command == 'l':
        coords[0] += xr
        coords[1] += yr
        x, y = lineto(xr, yr, *coords, t)
        xr, yr = coords
    elif command == 'H':
        x, y = hlineto(xr, yr, *coords, t)
        xr = coords.item()
    elif command == 'h':
        coords[0] += xr
        x, y = hlineto(xr, yr, *coords, t)
        xr = coords.item()
    elif command == 'V':
        coords[0] = yr
        x, y = vlineto(xr, yr, coords, t)
        yr = coords.item()
    elif command == 'v':
        coords[0] += yr
        x, y = vlineto(xr, yr, *coords, t)
        yr = coords.item()
    elif command == 'C':
        x, y = cubicbez(xr, yr,*coords, t)
        xr, yr = coords[-2:]
    elif command == 'c':
#        import pdb
#        pdb.set_trace()
        coords[0::2,] += xr 
        coords[1::2,] += yr 
        x, y = cubicbez(xr, yr,*coords, t)
        xr, yr = coords[-2:]
#    print(f'xr: {xr}, yr: {yr}')
    if command == 'h':
        print(f'x: {x}')
        print(f'y: {y}')
#    if not command == 'H':axes.scatter(coords[0::2], coords[1::2], s=100, c='r', linewidths=0.8)
    axes.scatter(x, y, c='k', linewidths=0.8)
#    if ii == 2:
#        plt.tight_layout()
#        plt.show()
#        sys.exit()
x, y = lineto(xr, yr, origin_x, origin_y, t)
axes.scatter(x, y, c='k', linewidth=0.8)
axes.set_xticks([])
axes.set_yticks([])
plt.tight_layout()
plt.show()

