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
    We do this by:
     1) Generate sets of all example names keyed on [example type][directory name]
     2) Generate a set of all example names keyed on  [example type].
     3) Parse  the markdown files  [example type].md generating example names keyed on [example type]
     4) Then use set differencing to find the examples not in the [example type].md files.
    """

    def __init__(self, base_directory):
        """
        :param base_directory: The path to the VTK Examples sources, usually some_path/VTKExamples/src
        """
        self.example_types = ['CSharp', 'Cxx', 'Java', 'Python']
        self.base_directory = base_directory
        # A dictionary consisting of [example type][directory name][example name ...]
        self.all_examples = dict()
        self.documented_examples = dict()
        # A dictionary consisting of [example type][directory name][file name ...]
        self.example_file_paths = dict()

    def get_all_examples(self):
        """
        For each example, get the example file paths and the example file names.
        """
        for eg in self.example_types:
            # Get the paths to the examples in a particular sub directory e.g Cxx.
            file_paths = defaultdict(set)
            examples = set()
            directory = os.path.join(self.base_directory, eg)
            # Does the directory exist?
            if not os.path.isdir(directory):
                raise RuntimeError('Non-existent folder: {:s}'.format(directory))
            exclude_dirs = None
            if eg == 'CSharp':
                fn_pattern = re.compile(r'^[0-9a-zA-Z_\-]+\.cs$')
            elif eg == 'Cxx':
                fn_pattern = re.compile(
                    r'^[0-9a-zA-Z_\-]+\.(hxx|HXX|hpp|HPP|[hH]\+\+|[hH]|cpp|CPP|cxx|CXX|[cC]\+\+|txx|TXX)$')
                exclude_dirs = ['CMakeTechniques', 'Untested']
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
                if exclude_dirs:
                    if sp[idx] in exclude_dirs:
                        continue
                for filename in files:
                    m = fn_pattern.match(filename)
                    if m:
                        example_name = os.path.splitext(filename)[0]
                        file_paths[key].add(example_name)
                        examples.add(example_name)
            self.example_file_paths[eg] = file_paths
            self.all_examples[eg] = examples

    def parse_markdown_files(self):
        """
        Parse the markdown files looking for the examples.
        :return:
        """
        # Go up one level.
        eg_pattern = re.compile(r'^.*\[ *([a-zA-Z][[a-zA-Z0-9\-_]+) *]')
        for eg in self.example_types:
            examples = set()
            curr_file = os.path.join(self.base_directory, eg + '.md')
            with open(curr_file) as f:
                for line in f:
                    m = eg_pattern.match(line)
                    if m:
                        examples.add(m.group(1))
            self.documented_examples[eg] = examples

    def print_tables(self):
        self.get_all_examples()
        self.parse_markdown_files()
        for eg in self.example_types:
            undocumented_examples = self.all_examples[eg] - self.documented_examples[eg]
            if undocumented_examples:
                print(eg)
                file_paths = self.example_file_paths[eg]
                lst = sorted(undocumented_examples)
                for l in lst:
                    for p in file_paths.keys():
                        if l in self.example_file_paths[eg][p]:
                            print('\t', p, l)
            print()
        return


def main():
    example_source = get_program_parameters()
    UndocumentedExamples(example_source).print_tables()


if __name__ == '__main__':
    main()
