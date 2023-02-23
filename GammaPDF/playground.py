#!/usr/bin/env python3
# -*- encoding: utf-8 -*-

"""
tested with matplotlib version 3.7.0
"""

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider
from scipy.stats import gamma

## set default values
x_lim_init = 15
shape_init = 2
loc_init = 0
scale_init = 2
x = None
y = None

# generate initial curve
x = np.linspace(0, x_lim_init, num=1000)
y = gamma.pdf(x, shape_init, loc_init, scale_init)


## set up matplotlib window basics
fig, ax = plt.subplots()
line, = ax.plot(x, y)

fig.subplots_adjust(left=0.30)


## the shape Slider
shape_ax = fig.add_axes([0.05, 0.1, 0.02, 0.8])
shape_slider = Slider(
    ax=shape_ax,
    label="Shape",
    valmin=0,
    valmax=5,
    valinit=shape_init,
    orientation="vertical"
)
## the location Slider
loc_ax = fig.add_axes([0.1, 0.1, 0.02, 0.8])
loc_slider = Slider(
    ax=loc_ax,
    label="Location",
    valmin=0,
    valmax=5,
    valinit=loc_init,
    orientation="vertical"
)
## the scale Slider
scale_ax = fig.add_axes([0.15, 0.1, 0.02, 0.8])
scale_slider = Slider(
    ax=scale_ax,
    label="Scale",
    valmin=0,
    valmax=5,
    valinit=scale_init,
    orientation="vertical"
)
## the x-limit Slider
x_lim_ax = fig.add_axes([0.20, 0.1, 0.02, 0.8])
x_lim_slider = Slider(
    ax=x_lim_ax,
    label="X-Limit",
    valmin=5,
    valmax=50,
    valinit=x_lim_init,
    orientation="vertical"
)

## fuction call to update the x and y values of the function
def update(val):
    global x
    global y
    x = np.linspace(0, x_lim_slider.val, num=1000)
    y = gamma.pdf(x, shape_slider.val, loc_slider.val, scale_slider.val)
    line.set_xdata(x)
    line.set_ydata(y)
    ax.relim()
    ax.autoscale_view()

## register the updates when a slider changes
shape_slider.on_changed(update)
loc_slider.on_changed(update)
scale_slider.on_changed(update)
x_lim_slider.on_changed(update)

plt.show()
