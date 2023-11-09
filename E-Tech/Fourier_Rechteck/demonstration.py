#!/usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt
import math

approx = lambda y: lambda x: [sum([math.sin(n * v) / n for n in [2 * m + 1 for m in range(y)]]) for v in x]
X = np.linspace(0, 10*math.pi, 100000)
plt.plot(X, approx(20)(X))
plt.show()
