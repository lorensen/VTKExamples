#!/usr/bin/env python

"""
Marching cubes cases for 3D isosurface generation.
The 256 possible cases have been reduced to 14 cases using symmetry.
Dark vertices are greater than the selected isosurface value.

Note: Make sure MarchingCases.py is in the same directory as this program.
"""

import PineRootConnectivity


def main():
    fileName, noConnectivity = PineRootConnectivity.get_program_parameters()
    noConnectivity = 1
    PineRootConnectivity.pine_root_connectivity(fileName, noConnectivity)


if __name__ == '__main__':
    main()
