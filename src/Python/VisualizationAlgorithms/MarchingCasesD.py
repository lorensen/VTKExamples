#!/usr/bin/env python

"""
Marching cubes cases.

Case 7 is rotated 180 degrees about the y-axis with no label.

Note: Make sure MarchingCases.py is in the same directory as this program.
"""

import MarchingCases


def main():
    mc_cases = [7]
    rotation = 2
    label = False
    MarchingCases.marching_cubes(mc_cases, rotation, label)


if __name__ == '__main__':
    main()
