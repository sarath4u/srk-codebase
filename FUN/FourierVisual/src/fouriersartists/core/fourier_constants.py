import numpy as np
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
	integrand			 = path * np.exp(-2j * np.pi * t * frequency_components) 
	artists			     = np.round(np.trapezoid(integrand, t, axis=-1), 4) 
	return artists
