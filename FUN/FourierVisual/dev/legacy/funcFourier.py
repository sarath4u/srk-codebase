import numpy as np
import matplotlib.pyplot as plt

def generate_curve(name='love', steps=100):
	"""
	A function that generates the parameteric curve

	Arguments: 
		name  - name of the figure
		steps - discreization steps	   
	Returns:
		x - x coordinate
		y - y coordinate
		t - time
	"""
	t = np.linspace(0, 1, steps)
	if name == 'circle':
		r = 10
		x = r * np.cos(2*t*np.pi)
		y = r * np.sin(2*t*np.pi)
	elif name == 'ellipse':
		a, b = 10, 15
		x = a * np.cos(2*t*np.pi)
		y = b * np.sin(2*t*np.pi)
	elif name == 'lissajous':
		r = 15
		x = r * np.cos(2*13*t*np.pi)
		y = r * np.sin(2*11*t*np.pi + np.pi/2)
	elif name == 'love':
		a = 16
		b = 13
		x = a * np.sin(2 * np.pi * t)**3
		y = b * np.cos(2 * np.pi * t) - 5 * np.cos(2 * 2 * np.pi * t) - 2 * np.cos(3 * 2 * np.pi *  t) - np.cos(4 * 2 * np.pi * t)
	return x, y, t

def generate_artists(path, no_of_artists, t):
	"""
	This function computes the coefficients of the 
	fourier transfrom using the formula 
	Integral_0^t{e^(-i2pint)f(t)}, n ranging 
	from -N to N
	
	Arguments: 
		path		  - co-ordinates of the figure as a 
						complex function
		no_of_artists - number of coefficients. It is 
						half of the actual number + 1
		t			  - time steps for integration
	Returns:
		artists - computed coefficients
	"""
	frequency_components = np.arange(1 - no_of_artists, no_of_artists)[:, np.newaxis]
	integrand			= path * np.exp(-2j * np.pi * t * frequency_components) 
	artists			  = np.round(np.trapezoid(integrand, t, axis=-1), 4) 
	return artists

def generate_background(no_of_artists, xMax, xMin, yMax, yMin, fourier=True):
	"""
	This function creates the canvas for the drawing

	Arguments: 
		no_of_artists - half the total number of artists
        xMax          - maximum value of x
        xMin          - minimum value of x
        yMax          - maximum value of y
        yMin          - minimum value of y
		fourier       - Boolean to check if the transformed
						version or actual version is drawn
	Returns:
		fig   - Figure object
		ax    - axes
		circ  - list of circles for the fourier version
		arrow - list of arrows for the fourier version
		point - the point that traces the path 
		trace - locus of the point
	"""
	# Set up figure and axes
	fig, ax = plt.subplots(figsize=(8, 6))
	ax.set_xlim(xMin, xMax)
	ax.set_ylim(yMin, yMax)
	ax.set_xticks([])
	ax.set_yticks([])
	ax.set_xticklabels([])
	ax.set_yticklabels([])
	ax.autoscale_view()
	ax.set_aspect('equal', adjustable='box')
	
	if fourier:
		# Initialize the artists
		circ   = [0.0]*(2 * (no_of_artists - 1))
		arrow  = [0.0]*(2 * (no_of_artists - 1))
		trace, = ax.plot([], [], 'y-', lw=2)
		point, = ax.plot([], [], 'go', markersize=8)
		for ii in range(2 * (no_of_artists - 1)):
			# circles
			circ[ii]  = plt.Circle((0,0), 0., color='cyan', fill=False, linewidth=1, alpha=0.2)
			ax.add_patch(circ[ii])

			#arrows
			arrow[ii] = ax.annotate('',
								xy=(0,0),
								xytext=(0.,0.),
								arrowprops=dict(facecolor='white', shrink=0.0, width=0.01, headwidth=1.5, alpha=0.2)
								   )
		return fig, ax, circ, arrow, trace, point
	else:
		trace, = ax.plot([], [], 'y-', lw=2)
		point, = ax.plot([], [], 'go', markersize=8)
		return fig, ax, trace, point

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

def update_true(frame):
	"""
	Update function for the animation
	This function is for the true
	parametric curve
	
	Arguments:
		frame - frame count
	Returns:
		point - updated coordinate of point 
		trace - updated coordinates of trace
	"""
	trace.set_data(x[:frame], y[:frame])
	point.set_data([x[frame]], [y[frame]])
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
		if ii == 0: continue												# Constant term without rotation. Already computed
		rotation_vector = np.exp(2j * np.pi * frequency * frame / N)		# Rotation vector at current timestep
		estimator	   = artists[ii]
		radius		  = np.round(abs(estimator), 4)					        # Circle radius
		if radius == 0.: continue
		center		  = offset 
		center_xy	   = (np.real(center), np.imag(center))				    # Circle center
		circ[ii-1].set_center(center_xy)
		circ[ii-1].set_radius(radius)
		offset		  = offset + estimator * rotation_vector			    # f(t) = Sum{Cn * e^(2i * pi * n * t)}
		end			 = (np.real(offset), np.imag(offset))				    # end-point of arrow 
		start		   = center_xy										    # start-point of arrow
		arrow[ii-1].xy  = end
		arrow[ii-1].set_position(start)
	x_history.append(np.real(offset))
	y_history.append(np.imag(offset))
	trace.set_data(x_history, y_history)
	point.set_data([np.real(offset)], [np.imag(offset)])
	return [trace] + [point] + circ + arrow
