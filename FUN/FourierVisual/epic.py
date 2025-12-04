#form presentation import *
#form pptx import Presentation
import numpy as np
import sys
import math

img = sys.argv[1]
## Parametrize image as closed loop function

time_table, x_table, y_table = create_close_loop(img)

## Calculate DFT coefficients

order = 5
coef = coef_list(time_table, x_table, y_table, order)
print(coef)

## Evaluate fourier transform

space = np.linspace(0, math.tau, 300)
x_DFT = [DFT(t, coef, order)[0] for t in space]
y_DFT = [DFT(t, coef, order)[1] for t in space]

## Visualise

fig.ax = plt.subplots(figsize = (5, 5))
ax.plot(x_DFT, y_DFT, 'r--')
ax.plot(x_table, y_table, 'k--')
ax.set_aspect('equal', 'datalim')
xmin, xmax = xlim()
ymin, ymax = ylim()

## Create epicycle animation

anim = visulaze(x_DFT, y_DFT, coef, order, space, [xmin, xmax, ymin, ymax])
Writer = animation.writers('html')
writer =  Writer(fps = 60)
anim.save('bman.html', write=writer, dpi =150)


