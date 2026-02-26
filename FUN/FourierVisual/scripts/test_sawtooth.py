import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation

## Set up figure, axis and the plot element we want to animate

xs   = 10.0 
ys   = 5.0
ar   = ys/xs
fig  = plt.figure(figsize = (xs,ys))
ax   = plt.axes()
xlim = 6.0
ylim = xlim * ar
plt.xlim(-xlim,xlim)
plt.ylim(-ylim,ylim)

xproj = -xlim + 2.0
div   = 1000                    # No of divisions
order = 20                      # No of estimators/circles
line, = ax.plot([], [], lw=2)
circ  = [0.0]*(order + 3)
for c in range(order + 3):
    circ[c], = ax.plot([], [], lw=2)

## initialization function: plots the background of each frame

def init():
    line.set_data([], [])
    for c in range(order + 3):
        circ[c].set_data([], [])
    circ.append(line)
    return circ 

## animation function; called sequentially
def animate(t):
    x     = np.linspace(0, xlim, div+1)
    y     = 0.0 
    xc    = np.zeros(len(x))
    yc    = np.zeros(len(x))
    xcum  = np.zeros(len(x))
    ycum  = np.zeros(len(x))
    xco   = np.zeros(2)
    yco   = np.zeros(2)
    xr    = np.zeros(order + 1)
    yr    = np.zeros(order + 1)
    xcent = xproj
    ycent = 0.0
    for jj in range(order):
        y        = y + np.sin(2*(jj+1)*np.pi*(x - 0.01*t))/(1+jj)       ## yCords of the curve
        xcum     = xcum + np.cos(2*(jj+1)*np.pi*(x - 0.01*t))/(1+jj)    ## xCords of the cumulative curve 
        ycum     = ycum + np.sin(2*(jj+1)*np.pi*(x - 0.01*t))/(1+jj)    ## yCords of the cumulative curve
        xc       = np.cos(2*(jj+1)*np.pi*(x - 0.01*t))/(1+jj) + xcent
        yc       = np.sin(2*(jj+1)*np.pi*(x - 0.01*t))/(1+jj) + ycent
        xr[jj]   = xcent
        yr[jj]   = ycent
        xr[jj+1] = xc[0]
        yr[jj+1] = yc[0]
        xcent    = xc[0] 
        ycent    = yc[0]
        circ[jj].set_data(xc,yc)                                    ## setting the circles
    circ[order].set_data(xr,yr)                                     ## setting the radii
    xcum = xcum + xproj
    xco[0] = x[0]
    xco[1] = xc[0]
    yco[0] = y[0]
    yco[1] = yc[0]
    circ[order + 2].set_data(xco,yco)                               ## setting the connector line
    circ[order + 3].set_data(x,y)                                   ## setting the curve
    return circ

## call the animator; blit=True means only re-draw the parts that have changed.

anim = animation.FuncAnimation(fig, animate, init_func=init, frames=div, interval = 20 , blit=True)

## save animation 

#anim.save('sawtooth_%d.mp4'%order, fps=30, extra_args=['-vcodec', 'libx264'])
ax.set_xticks([])
ax.set_yticks([])
ax.set_xticklabels([])
plt.tight_layout()
plt.show()
