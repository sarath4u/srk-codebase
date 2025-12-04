import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation

## Set up figure, axis and the plot element we want to animate

fig = plt.figure(figsize=(8,8))
ax = plt.axes()
plt.xlim(-2,2)
plt.ylim(-2,2)
line, = ax.plot([], [], lw=2)
circ, = ax.plot([], [], lw=2)
conn, = ax.plot([], [], lw=2)
## initialization function: plots the background of each frame

def init():
	line.set_data([], [])
	circ.set_data([], [])
	conn.set_data([], [])
	return line,circ,conn

## animation function; called sequentially

def animate(t):
	x = np.linspace(0, 2, 1000)
	y = np.sin(2*np.pi*(x - 0.01*t))
	line.set_data(x,y)
	xc_ = np.cos(2*np.pi*(x - 0.01*t))
	yc_ = y
	xc = np.transpose(np.zeros(len(xc_)+1))
	yc = np.transpose(np.zeros(len(yc_)+1))
	xc[1:] = xc_
	xc = xc - np.transpose(1*np.ones(len(xc)))
	yc[1:] = yc_ 
	circ.set_data(xc,yc)
	xco = np.zeros(2)
	yco = np.zeros(2)
	xco[0] = x[0]
	xco[1] = xc[1]
	yco[0] = y[0]
	yco[1] = yc[1]
	conn.set_data(xco,yco)
	return line,circ,conn

## call the animator; blit=True means only re-draw the parts that have changed.

anim = animation.FuncAnimation(fig, animate, init_func=init, frames=200, interval = 20, blit=True)

## save animation 

#anim.save('sine.mp4', fps=30, extra_args=['-vcodec', 'libx264'])

plt.show()
