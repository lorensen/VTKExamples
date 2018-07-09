#!/usr/bin/env python

"""
Marching cubes complementary cases.

Cases 3c, 6c, 7c, 10c, 12c and 13c are displayed.

Note: Make sure MarchingCases.py is in the same directory as this program.
"""

import MarchingCases


def main():
    mc_cases = [-3, -6, -7, -10, -12, -13]
    MarchingCases.marching_cubes(mc_cases)


if __name__ == '__main__':
    main()
