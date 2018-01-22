#!/usr/bin/env python

"""
ViewFrogA

Note: Make sure ViewFrog.py is in the same directory as this program.
"""

import ViewFrog


def main():
    fileName = get_program_parameters()
    tissues = ['blood', 'brain', 'duodenum', 'eyeRetina', 'eyeWhite', 'heart', 'ileum', 'kidney', 'intestine', 'liver',
               'lung', 'nerve', 'spleen', 'stomach']
    ViewFrog.view_frog(fileName, tissues)


def get_program_parameters():
    import argparse
    description = 'The complete frog without skin or skeleton.'
    epilogue = '''
    For Figure 12-9c in the VTK Book:
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='frogtissue.mhd.')
    args = parser.parse_args()
    return args.filename


if __name__ == '__main__':
    main()
