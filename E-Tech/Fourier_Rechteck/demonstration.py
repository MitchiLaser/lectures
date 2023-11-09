#!/usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider
import math

# set slider default values
approx_depth = 5
X_Start = 0
X_End = 2 * math.pi
X_Resolution = 1000


# the approximation function
approx = lambda y: lambda x: [sum([math.sin(n * v) / n for n in [2 * m + 1 for m in range(y)]]) for v in x]  # noqa: E731


# generate X and Y Values to plot
def data():
    global X, Y
    X = np.linspace(X_Start, X_End, X_Resolution)
    Y = approx(approx_depth)(X)


data()  # generate the inital data


# create matplotlib window layout
fig, ax = plt.subplots()
line, = ax.plot(X, Y)

fig.subplots_adjust(left=.1)

# slider definition
slider_ax = fig.add_axes([.05, .1, .02, .8])
slider = Slider(
    ax=slider_ax,
    label="n",
    valmin=0,
    valmax=200,
    valinit=approx_depth,
    orientation="vertical",
)


# update values when slider changes
def update(val):
    global X, Y, approx_depth, slider
    approx_depth = round(slider.val)
    data()
    line.set_xdata(X)
    line.set_ydata(Y)
    ax.relim()
    ax.autoscale_view()


slider.on_changed(update)
ax.set_title(r"$\sum_{n} \frac{ \sin(n \cdot x) }{n}$")
plt.show()
