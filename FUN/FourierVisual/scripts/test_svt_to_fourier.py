from svgmodules import *
import re
import sys, pdb
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np
from funcFourier import generate_artists, generate_background
import argparse

parser = argparse.ArgumentParser(description='A simple function to visualize fourier transforms')
parser.add_argument('-s', '--save', action='store_true',      help='save if true else show)')
parser.add_argument('-f', '--figure',   type=str,             help='example figure (cicle/ellipse/lissajous/love)')
parser.add_argument('-i', '--interval', type=int, default=1,  help='interval in milliseconds')
parser.add_argument('-a', '--artists',  type=int, default=10, help='number of artists/rotating circles/vectors')
args = parser.parse_args()

def init():
    """
    initialization function: plots the background of each frame
    
    Arguments:
        None
    Returns:
        point - point initialized
        trace - trace initialized
    """
    trace.set_data([], [])
    point.set_data([], [])
    return trace, point 

def update_fourier(frame):
    """
    Update function for the animation
    This function is for the transformed
    version of the parametric curve
    
    Arguments:
        frame - frame count
    Returns:
        circ  - updated coordinates of the circle
        arrow - updated coordinates of the arrows
        point - updated coordinate of point 
        trace - updated coordinates of trace
    """
    global estimator_zero, x_history, y_history
    offset = estimator_zero
    for ii, frequency in enumerate(range(1-no_of_artists, no_of_artists)):
        if frequency == 0: continue                                                # Constant term without rotation. Already computed
        rotation_vector = np.exp(2j * np.pi * frequency * frame / N)        # Rotation vector at current timestep
        estimator       = artists[ii]
        radius          = np.round(abs(estimator), 4)                       # Circle radius
        if radius == 0.: continue
        center          = offset 
        center_xy       = (np.real(center), np.imag(center))                # Circle center
        circ[ii - ii // no_of_artists].set_center(center_xy)
        circ[ii - ii // no_of_artists].set_radius(radius)
        offset          = offset + estimator * rotation_vector              # f(t) = Sum{Cn * e^(2i * pi * n * t)}
        end             = (np.real(offset), np.imag(offset))                # end-point of arrow 
        start           = center_xy                                         # start-point of arrow
        arrow[ii - ii // no_of_artists].xy  = end
        arrow[ii - ii // no_of_artists].set_position(start)
    x_history.append(np.real(offset))
    y_history.append(np.imag(offset))
    trace.set_data(x_history, y_history)
    point.set_data([np.real(offset)], [np.imag(offset)])
    return [trace] + [point] + circ + arrow

f = args.figure
t = 10
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
#fig, axes = plt.subplots(1, figsize=(3.5,4))
curve = np.zeros(((len(commands) - 2) * t + 1,  2), dtype=float)
for ii, command in enumerate(commands[:-1]):
#    print(f'count: {ii}, command: {command}')
    start_char = commands[ii]
    end_char   = commands[ii+1]
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
#    print(f'parsed string: {coords}')
    if scale:
        coords = transform_scale(coords, sx, -sy)
    else:
        coords = transform_scale(coords, 1, -1)
#        print(f'Scaled coords: {coords}')
#    if translate:
#        coords = transform_translate(coords, tx, ty)
    
    if command == 'M':
        x, y = moveto(*coords)
        origin_x, origin_y = x, y
        xr, yr = x, y
        curve[0, 0] = x
        curve[0, 1] = y
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
#    print(f'x: {x}')
#    print(f'y: {y}')
#    if not command == 'H':axes.scatter(coords[0::2], coords[1::2], s=100, c='r', linewidths=0.8)
#    axes.scatter(x, y, c='k', linewidths=0.8)
    if not command == 'M' and not command == 'm':
        curve[(ii-1)*t + 1:ii * t + 1, 0] = x
        curve[(ii-1)*t + 1:ii * t + 1, 1] = y
#    if ii == 2:
#        plt.tight_layout()
#        plt.show()
#        sys.exit()
x, y = lineto(xr, yr, origin_x, origin_y, t)
#axes.scatter(x, y, c='k', linewidth=0.8)
#axes.plot(curve[:, 0], curve[:, 1], linewidth=0.8)
#axes.set_xticks([])
#axes.set_yticks([])
#plt.show()


plt.style.use('dark_background')
x_history     = []
y_history     = []
N             = len(curve)
interval      = args.interval
no_of_artists = args.artists
xMax, yMax    = np.max(curve, axis=0)
xMin, yMin    = np.min(curve, axis=0)
xMax          = xMax + 0.1 * abs(xMax)
yMax          = yMax + 0.5 * abs(yMax)
xMin          = xMin - 0.5 * abs(xMin)
yMin          = yMin - 0.1 * abs(yMin)
print(f"xMax:{xMax}, yMax:{yMax}, xMin:{xMin}, yMin:{yMin}")
z                                  = curve[:, 0] + 1j * curve[:, 1]
tsteps                             = np.linspace(0, 1, N)
artists                            = generate_artists(z, no_of_artists, tsteps)
radius_sum                         = np.sum(np.round(abs(artists)))
fig, ax, circ, arrow, trace, point = generate_background(no_of_artists, xMax, xMin, yMax, yMin) 

# Treat the constant non-rotating vector first
estimator_zero                     = artists[no_of_artists - 1]
end_coord                          = (np.real(estimator_zero), np.imag(estimator_zero))
length                             = np.round(abs(estimator_zero))

if length > 0.:
    ax.annotate('',
                xy=end_coord,
                xytext=(0, 0),
                arrowprops=dict(facecolor='black', shrink=0.0, width=0.01, headwidth=1, alpha=0.1)
                )
frames = N + 1
ani    = FuncAnimation(fig, update_fourier, frames=frames, init_func=init, interval=interval, repeat=False, blit=True)
plt.tight_layout()
if args.save:
    ani.save(f'anim_{no_of_artists}.mp4', fps=300, extra_args=['-vcodec', 'libx264'])
else:
    plt.show()
