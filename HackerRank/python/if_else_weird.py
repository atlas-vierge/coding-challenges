#!/bin/python3

import math
import os
import random
import re
import sys

def is_weird(n : int):
    if (n%2 == 0): # Even
        if n in range(2, 5+1): # [2..5]
            print("Not Weird")
        elif n in range(6, 20+1): # [6..20]
            print("Weird")
        elif n > 20:
            print("Not Weird")
    else: # Odd
        print("Weird")


if __name__ == '__main__':
    n = int(input().strip())
    is_weird(n)

    # for i in range (0, 2):
    #     print(f"{i} -> {is_weird(i)}")
