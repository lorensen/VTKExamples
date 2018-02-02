#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import print_function

import os
import re
from collections import defaultdict


def path_splitter(path):
    """
    Split a path into its constituent parts.
    Might be better written as a recursive function.
    :param path: The path to split.
    :return: A list of the path's constituent parts.
    """
    res = []
    while True:
        p = os.path.split(path)
        if p[0] == path:
            # Were done, this is an absolute path.
            res.insert(0, p[0])
            break
        elif p[1] == path:
            # Were done, this is a relative path.
            res.insert(0, p[0])
            break
        else:
            path = p[0]
            res.insert(0, p[1])
    return res


def get_program_parameters():
    import argparse
    description = 'Produce a list of examples that are not mentioned in the src/*.md files.'
    epilogue = '''
Typical usage:
   To produce a list of examples that are not mentioned in the src/*.md files:
      FindMissingExamples.py some_path/VTKExamples/src
   Where: some_path/VTKExamples/src is the path to the source files for the VTK examples.
'''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument('vtk_examples', help='The path to the VTK example source files.')

    args = parser.parse_args()
    return args.vtk_examples


class UndocumentedExamples(object):
    """
    Find undocumented examples.
    """

    def __init__(self, base_directory):
        """
        :param base_directory: The path to the VTK Examples sources, usually some_path/VTKExamples/src
        """
        self.example_types = ['CSharp', 'Cxx', 'Java', 'Python']
        self.excluded_dirs = ['Cxx/CMakeTechniques', 'Cxx/Developers', 'Cxx/Untested', 'Cxx/Untested/Video']
        self.base_directory = base_directory
        # A dictionary consisting of [example type][directory name][example name ...]
        self.all_examples = defaultdict(lambda: defaultdict(set))
        self.extras = defaultdict(lambda: defaultdict(set))
        self.documented_examples = defaultdict(lambda: defaultdict(set))
        self.undocumented_examples = defaultdict(lambda: defaultdict(set))

    def get_all_examples(self):
        """
        For each example, get the example file paths and the example file names.
        """
        for eg in self.example_types:
            # Get the paths to the examples in a particular sub directory e.g Cxx.
            directory = os.path.join(self.base_directory, eg)
            # Does the directory exist?
            if not os.path.isdir(directory):
                raise RuntimeError('Non-existent folder: {:s}'.format(directory))
            if eg == 'CSharp':
                fn_pattern = re.compile(r'^[0-9a-zA-Z_\-]+\.cs$')
            elif eg == 'Cxx':
                fn_pattern = re.compile(
                    r'^[0-9a-zA-Z_\-]+\.(hxx|HXX|hpp|HPP|[hH]\+\+|[hH]|cpp|CPP|cxx|CXX|[cC]\+\+|txx|TXX)$')

            elif eg == 'Java':
                fn_pattern = re.compile(r'^[0-9a-zA-Z_\-]+\.java$')
            elif eg == 'Python':
                fn_pattern = re.compile(r'^[0-9a-zA-Z_\-]+\.py$')
            else:
                raise RuntimeError('Unknown example type.')

            # Walk the tree.
            for root, directories, files in os.walk(directory):
                sp = path_splitter(root)
                idx = sp.index(eg)
                key = '/'.join(sp[idx:])
                examples = set()
                if key in self.excluded_dirs:
                    continue
                for filename in files:
                    m = fn_pattern.match(filename)
                    if m:
                        examples.add(os.path.splitext(filename)[0])
                self.all_examples[eg][key] = examples

    def get_extras(self):
        for eg in self.example_types:
            # Get the paths to the examples in a particular sub directory e.g Cxx.
            directory = os.path.join(self.base_directory, eg)
            # Does the directory exist?
            if not os.path.isdir(directory):
                raise RuntimeError('Non-existent folder: {:s}'.format(directory))
            fn_pattern = re.compile(r'^[0-9a-zA-Z_\-]+\.extras$')
            if eg not in self.example_types:
                raise RuntimeError('Unknown example type.')
            # Walk the tree.
            for root, directories, files in os.walk(directory):
                sp = path_splitter(root)
                idx = sp.index(eg)
                key = '/'.join(sp[idx:])
                examples = set()
                if key in self.excluded_dirs:
                    continue
                for filename in files:
                    m = fn_pattern.match(filename)
                    if m:
                        with open(os.path.join(root, filename), 'r') as f:
                            for line in f:
                                examples.add(os.path.splitext(line)[0])
                self.extras[eg][key] = examples

    def parse_markdown_files(self):
        """
        Parse the markdown files looking for the examples.
        :return:
        """
        # Go up one level.
        row = re.compile(r'(^[^|]+[|])([^|]*[|])([^|]*[^|])?$')
        row_key = re.compile(r'\[(.*?)\].*\((.*?)\)')

        for eg in self.example_types:
            curr_file = os.path.join(self.base_directory, eg + '.md')
            with open(curr_file) as f:
                for line in f:
                    if row.match(line):
                        kv = line.split('|')[0]
                        m = row_key.match(kv)
                        if m:
                            res = m.group(2)
                            key = res[1:res.rfind('/')]
                            val = res[res.rfind('/') + 1:]
                            self.documented_examples[eg][key].add(val)
                f.close()

    def make_undocumented_examples(self):
        for k in self.all_examples.keys():
            for k1 in self.all_examples[k].keys():
                self.undocumented_examples[k][k1] = self.all_examples[k][k1] - self.documented_examples[k][k1] - \
                                                    self.extras[k][k1]

    def print_tables(self):
        self.get_all_examples()
        self.get_extras()
        self.parse_markdown_files()
        self.make_undocumented_examples()
        if self.undocumented_examples:
            for k in sorted(self.undocumented_examples.keys()):
                if self.undocumented_examples[k]:
                    print(k)
                    for k1 in sorted(self.undocumented_examples[k].keys()):
                        if self.undocumented_examples[k][k1]:
                            print('  ', k1)
                            for v in sorted(self.undocumented_examples[k][k1]):
                                print('    ', v)
            print()
        return


def main():
    example_source = get_program_parameters()
    UndocumentedExamples(example_source).print_tables()


if __name__ == '__main__':
    main()
