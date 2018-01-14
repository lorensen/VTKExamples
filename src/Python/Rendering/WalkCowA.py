#!/usr/bin/env python

"""
WalkCow, VTK Textbook figure 3-33a.

Note: Make sure WalkCow.py is in the same directory as this program.
"""

import WalkCow


def main():
    file_name, figure = WalkCow.get_program_parameters()
    figure = 1
    WalkCow.walk_cow(file_name, figure)


if __name__ == '__main__':
    main()
