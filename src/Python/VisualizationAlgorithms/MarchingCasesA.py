#!/usr/bin/env python

"""
Marching cubes cases for 3D isosurface generation.
The 256 possible cases have been reduced to 15 cases using symmetry.
Dark vertices are greater than the selected isosurface value.

Note: Make sure MarchingCases.py is in the same directory as this program.
"""

import MarchingCases


def main():
    mc_cases = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14]
    MarchingCases.marching_cubes(mc_cases)


if __name__ == '__main__':
    main()
