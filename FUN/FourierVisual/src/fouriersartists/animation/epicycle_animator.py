import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

class EpicycleAnimator:

	def __init__(self, artists, curve, interval=1):
		"""
		Parameters
		----------
		artists : list
			Fourier artists (co-coefficients) returned by
			Fourier generator
		curve   : Nx2 numpy array
			Regrenerated image coordinates of the curve 
			returned after parsing the svg image.
		interval: int
			Animation frame interval in milliseconds
		"""
		self.artists     = artists
		self.curve       = curve
		self.interval    = interval
		self.frequencies = np.arange(-(len(artists) // 2), 1 + len(artists) // 2)
		
		self.fig, self.ax = plt.subplots(figsize=(8, 6))

		self.x_history = []
		self.y_history = []

	def initialize_artists(self):
		"""
        Initializes the variables for animation
		Arguments: 
			None
		Returns:
            None
		"""
		no_of_artists = len(self.artists)
		self.circ     = [0.0]*(no_of_artists)
		self.arrow    = [0.0]*(no_of_artists)
		self.trace,   = self.ax.plot([], [], 'y-', lw=2)
		self.point,   = self.ax.plot([], [], 'go', markersize=8)
		for ii in range(no_of_artists):
			# circles
			self.circ[ii]  = plt.Circle((0,0), 0., color='cyan', fill=False, linewidth=1, alpha=0.2)
			self.ax.add_patch(self.circ[ii])

			#arrows
			self.arrow[ii] = self.ax.annotate('',
								xy=(0,0),
								xytext=(0.,0.),
								arrowprops=dict(facecolor='white', shrink=0.0, width=1, headwidth=3, alpha=0.2)
								   )
		if np.round(abs(self.artists[len(self.artists) // 2])) > 0.:
			self.ax.annotate('',
						xy=(np.real(self.artists[no_of_artists // 2]), np.imag(self.artists[no_of_artists // 2])),
						xytext=(0, 0),
						arrowprops=dict(facecolor='white', shrink=0.0, width=1, headwidth=3, alpha=0.2)
						)

	def init(self):
		"""
		initialization function: plots the background of each frame
		
		Arguments:
			None
		Returns:
			point - point initialized
			trace - trace initialized
		"""
		self.trace.set_data([], [])
		self.point.set_data([], [])
		return self.trace, self.point 
	
	def generate_background(self):
		"""
		This function creates the canvas for the drawing
	
		Arguments: 
			None
		Returns:
            None
		"""
		# Set up figure and axes
		xMax, yMax 	= np.max(self.curve, axis=0)
		xMin, yMin 	= np.min(self.curve, axis=0)
		xMax		= xMax + 0.1 * abs(xMax)
		yMax		= yMax + 0.5 * abs(yMax)
		xMin		= xMin - 0.5 * abs(xMin)
		yMin		= yMin - 0.1 * abs(yMin)
		self.ax.set_xlim(xMin, xMax)
		self.ax.set_ylim(yMin, yMax)
		self.ax.set_xticks([])
		self.ax.set_yticks([])
		self.ax.set_xticklabels([])
		self.ax.set_yticklabels([])
		self.ax.autoscale_view()
		self.ax.set_aspect('equal', adjustable='box')
		self.ax.set_facecolor('black')
		self.ax.figure.set_facecolor('black')
		self.ax.figure.tight_layout()
		for spine in self.ax.spines.values():
			spine.set_color('white')

	def update(self, frame):
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
		N	    = len(self.curve)  
		offset	= self.artists[len(self.artists) // 2]
		for ii, frequency in enumerate(self.frequencies):
			if frequency == 0: continue										 # Constant term without rotation. Already computed
			rotation_vector = np.exp(2j * np.pi * frequency * frame / N)     # Rotation vector at current timestep
			estimator	    = self.artists[ii]
			radius		    = np.round(abs(estimator), 4)				     # Circle radius
			if radius == 0.: continue
			center    = offset 
			center_xy = (np.real(center), np.imag(center))				     # Circle center
			self.circ[ii].set_center(center_xy)
			self.circ[ii].set_radius(radius)
			offset            = offset + estimator * rotation_vector	     # f(t) = Sum{Cn * e^(2i * pi * n * t)}
			end	              = (np.real(offset), np.imag(offset))	 	     # end-point of arrow 
			start             = center_xy									 # start-point of arrow
			self.arrow[ii].xy = end
			self.arrow[ii].set_position(start)
		self.x_history.append(np.real(offset))
		self.y_history.append(np.imag(offset))
		self.trace.set_data(self.x_history, self.y_history)
		self.point.set_data([np.real(offset)], [np.imag(offset)])
		return [self.trace] + [self.point] + self.circ + self.arrow

	def run(self, frames=100, save=False):
		"""
        Function to run the animation

        Arguments:
            frames - Number of frames for the animation
            save   - If true saves the animation
        Returns:
            None
        """
        ani = FuncAnimation(self.fig, self.update, frames=frames, init_func=self.init, interval=self.interval, repeat=False, blit=True)
		if save:
			ani.save(f'anim_{no_of_artists}.mp4', fps=300, extra_args=['-vcodec', 'libx264'])
		else:
			plt.show()
