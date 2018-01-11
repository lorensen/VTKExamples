#!/usr/bin/env python

"""
Marching cubes complementary cases.

Note: Make sure MarchingCases.py is in the same directory as this program.
"""

import MarchingCases


def main():
    mc_cases = [-3, -6, -7, -10, -12, -13]
    MarchingCases.marching_cubes(mc_cases)


if __name__ == '__main__':
    main()
