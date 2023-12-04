#!/usr/bin/env python3
# -*- encoding: utf8 -*-

class add(int):
    def __call__(self, value):
        return type(self)(self + value)


print(add(3))
print(add(3)(4))
print(add(3)(4)(5))
