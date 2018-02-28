#!/usr/bin/env python

"""
OfficeA.

Note: Make sure Office.py is in the same directory as this program.
"""

import Office


def main():
    file_name, center = Office.get_program_parameters()
    center = 0
    Office.office(file_name, center)


if __name__ == '__main__':
    main()
