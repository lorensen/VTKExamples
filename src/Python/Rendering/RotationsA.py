#!/usr/bin/env python

"""
Rotations, VTK Textbook figure 3-31a.

Note: Make sure Rotations.py is in the same directory as this program.
"""

import Rotations


def main():
    file_name, figure, book_color = Rotations.get_program_parameters()
    # Set up for six rotations about the x-axis.
    figure = 1
    book_color = True
    Rotations.rotate(file_name, figure, book_color)


if __name__ == '__main__':
    main()
