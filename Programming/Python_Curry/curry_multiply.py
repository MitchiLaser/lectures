#!/usr/bin/env python3
# -*- encoding: utf8 -*-

class multiply(int):
    def __call__(self, value):
        return type(self)(self * value)


print(multiply(3))
print(multiply(3)(4))
print(multiply(3)(4)(5))

a = multiply(1)(2)(3)
print(a(4))
