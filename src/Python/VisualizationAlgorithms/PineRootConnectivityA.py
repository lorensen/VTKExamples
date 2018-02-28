#!/usr/bin/env python

"""
PineRootConnectivityA

Note: Make sure PineRootConnectivity.py is in the same directory as this program.
"""

import PineRootConnectivity


def main():
    fileName, noConnectivity = PineRootConnectivity.get_program_parameters()
    noConnectivity = 1
    PineRootConnectivity.pine_root_connectivity(fileName, noConnectivity)


if __name__ == '__main__':
    main()
