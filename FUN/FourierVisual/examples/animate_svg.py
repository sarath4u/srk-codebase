import matplotlib.pyplot as plt
import numpy as np
import argparse

from fouriersartists import svg_to_curve
from fouriersartists import generate_artists
from fouriersartists import EpicycleAnimator

parser = argparse.ArgumentParser(description='A simple function to visualize fourier transforms')
parser.add_argument('-s', '--save', action='store_true',      help='save if true else show)')
parser.add_argument('-f', '--figure',   type=str,             help='example figure (cicle/ellipse/lissajous/love)')
parser.add_argument('-i', '--interval', type=int, default=1,  help='interval in milliseconds')
parser.add_argument('-a', '--artists',  type=int, default=10, help='number of artists/rotating circles/vectors')
args = parser.parse_args()

curve    = svg_to_curve(args.figure)
N        = len(curve)
xMax, yMax    = np.max(curve, axis=0)
xMin, yMin    = np.min(curve, axis=0)
xMax          = xMax + 0.1 * abs(xMax)
yMax          = yMax + 0.5 * abs(yMax)
xMin          = xMin - 0.5 * abs(xMin)
yMin          = yMin - 0.1 * abs(yMin)
z        = curve[:, 0] + 1j * curve[:, 1]
tsteps   = np.linspace(0, 1, N)
artists  = generate_artists(z, args.artists, tsteps)
animator = EpicycleAnimator(artists, curve, interval=args.interval)
animator.initialize_artists()
animator.generate_background()
animator.run(frames=N+1, save=args.save)

