import re
def moveto(x, y):
    """
    Move to (x, y)
    """
    xc = x
    yc = y
    return xc, yc

def lineto(x0, y0, x, y, t):
    """
    Draw line to (x, y) from (x0, y0)
    """
    xc = []
    yc = []
    dx = (x-x0) / t
    dy = (y-y0) / t
    for ii in range(t):
        xc.append(x0 + (ii+1) * dx)
        yc.append(y0 + (ii+1) * dy)
    return xc, yc

def hlineto(x0, y0, x, t):
    """
    Draw horizontal line to (x, y0) from (x0, y0)
    """
    xc = []
    yc = []
    dx = (x-x0) / t
    for ii in range(t):
        xc.append(x0 + (ii+1) * dx)
        yc.append(y0)
    return xc, yc

def vlineto(x0, y0, y, t):
    """
    Draw vertical line to (x0, y) from (x0, y0)
    """
    xc = []
    yc = []
    dy = (y-y0) / t
    for ii in range(t):
        xc.append(x0)
        yc.append(y0 + (ii+1) * dy)
    return xc, yc

def quadbez(x0, y0, x1, y1, x2, y2, t):
    """
    Quadratic Bezier from (x0, y0) to (x2, y2)
    with control point (x1, y1)
    """
    xc = []
    yc = []
    for ii in range(1, t+1):
        xc.append((1 - ii/t) * ((1 - ii/t) * x0 + (ii/t) * x1) + (ii/t) * ((1 - ii/t) * x1 + (ii/t) * x2))
        yc.append((1 - ii/t) * ((1 - ii/t) * y0 + (ii/t) * y1) + (ii/t) * ((1 - ii/t) * y1 + (ii/t) * y2))
    return xc, yc

def cubicbez(x0, y0, x1, y1, x2, y2, x3, y3, t):
    """
    Cubic Bezier from (x0, y0) to (x3, y3)
    with control points (x1, y1) and (x2, y2)
    """
    xc = []
    yc = []
    for ii in range(1, t+1):
        xc.append((1 - ii/t) * ((1 - ii/t) * ((1 - ii/t) * x0 + (ii/t) * x1) + (ii/t) * ((1 - ii/t) * x1 + (ii/t) * x2)) +
            (ii/t) * ((1 - ii/t) * ((1 - ii/t) * x1 + (ii/t) * x2) + (ii/t) * ((1 - ii/t) * x2 + (ii/t) * x3)))
        yc.append((1 - ii/t) * ((1 - ii/t) * ((1 - ii/t) * y0 + (ii/t) * y1) + (ii/t) * ((1 - ii/t) * y1 + (ii/t) * y2)) +
            (ii/t) * ((1 - ii/t) * ((1 - ii/t) * y1 + (ii/t) * y2) + (ii/t) * ((1 - ii/t) * y2 + (ii/t) * y3)))
    return xc, yc

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

def transform_scale(coords, sx, sy):
    """
    Function to scale the coordinates
    """
    coords[0::2] *= sx 
    coords[1::2] *= sy 
    return coords

def transform_translate(coords, tx, ty):
    """
    Function to translate the coordinates
    """
    coords[0::2] += tx 
    coords[1::2] -= ty 
    return coords
