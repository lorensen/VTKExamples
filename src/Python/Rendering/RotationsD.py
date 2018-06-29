#!/usr/bin/env python

"""
Rotations, VTK Textbook figure 3-31d.

Note: Make sure Rotations.py is in the same directory as this program.
"""

import Rotations


def main():
    file_name, figure, book_color = Rotations.get_program_parameters()
    # First a rotation about the x-axis, then six rotations about the y-axis.
    figure = 4
    book_color = True
    Rotations.rotate(file_name, figure, book_color)


if __name__ == '__main__':
    main()
