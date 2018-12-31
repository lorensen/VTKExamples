#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import print_function

import os
import re

try:
    from urllib.request import urlopen
except ImportError:
    # urllib.request does not exist in Python 2.7
    from urllib2 import urlopen
from collections import defaultdict


def get_program_parameters():
    import argparse
    description = 'Produce tables of VTK classes used in the examples.'
    epilogue = '''
Typical usage:
   To produce tables of classes used in some_path/VTKExamples/src:
      VTKClassesUsedInExamples.py some_path/VTKExamples/src
   To produce tables of classes used and those not used in some_path/VTKExamples/src:
      VTKClassesUsedInExamples.py some_path/VTKExamples/src -u

   The markdown tables are written to some_path/VTKExamples/src/Coverage

   Note:
      To add links to the VTK class documentation on the web, just add -a as a parameter.
      To vary the number of columns for unused classes to say 8, just add -c8 as a parameter.
'''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument('vtk_examples', help='The path to the VTK example source files.')
    parser.add_argument('-c', '--columns',
                        help='Specify the number of columns for unused VTK classes output, default is 5.', nargs='?',
                        const=5, type=int, default=5)
    parser.add_argument('-e', '--excluded_columns',
                        help='Specify the number of columns for excluded VTK classes output, default is 5.', nargs='?',
                        const=3, type=int, default=3)
    parser.add_argument('-u', '--unused_vtk',
                        help='Select unused VTK classes output in addition to the used VTK classes output.',
                        action='store_true')
    parser.add_argument('-a', '--add_vtk_html', help='Add html paths to the VTK classes.', action='store_true')

    args = parser.parse_args()
    return args.vtk_examples, args.columns, args.excluded_columns, args.unused_vtk, args.add_vtk_html


def print_table(table, filename):
    """
    The table is printed either to the console or to a file.
    :param table: The formatted data to print or save to a file.
    :param filename: File name to use (optional)
    :return:
    """
    if filename:
        path, ext = os.path.splitext(filename)
        if not ext.lower() in ['.md']:
            ext = '.md'
        fn = path + ext
        with open(fn, 'w') as f:
            f.writelines(table)
            f.close()
    else:
        for row in table:
            print(row)


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


class VTKClassesInExamples(object):
    """
    Determine what classes are being used or not used in the examples.
    """

    def __init__(self, base_directory, columns, excluded_columns, unused_vtk, add_vtk_html):
        """
        :param base_directory: The path to the VTK Examples sources, usually some_path/VTKExamples/src
        :param columns: When generating the classes not used table, the number of columns to use.
        :param excluded_columns: When generating the excluded classes table, the number of columns to use.
        :param unused_vtk: True if the unused VTK class tables are to be generated.
        :param add_vtk_html: True if the Doxygen documentation paths are to be added to the vtk classes in the tables.
        """
        self.example_types = ['CSharp', 'Cxx', 'Java', 'Python']
        # Classes common to most examples.
        self.excluded_classes = ['vtkActor', 'vtkCamera', 'vtkNamedColors', 'vtkPolyDataMapper', 'vtkProperty',
                                 'vtkRenderer', 'vtkRenderWindow', 'vtkRenderWindowInteractor', ]
        # Where to get the list of VTK classes from.
        self.vtk_class_url = 'https://www.vtk.org/doc/nightly/html/annotated.html'
        # This is the path to the details bookmark in the VTK class.
        self.vtk_html_fmt = '[{:s}](http://www.vtk.org/doc/nightly/html/{:s}#details)'

        self.base_directory = base_directory
        self.columns = columns
        self.excluded_columns = excluded_columns
        self.unused_vtk = unused_vtk
        self.add_vtk_html = add_vtk_html
        # A dictionary consisting of the class name as the key and the link class name as the value.
        self.vtk_classes = dict()
        # A dictionary consisting of [example type][directory name][full file paths of each example ...]
        self.example_file_paths = dict()
        # A dictionary consisting of [example type][vtk class][relative example path]{examples, ...}
        self.classes_used = dict()
        # Markdown tables of classes used keyed on [example type]
        self.classes_used_table = dict()
        # Markdown tables of classes not used keyed on [example type]
        self.classes_not_used_table = dict()

        # Used to signal if the tables have been built, see build_tables()
        self.used_tables_built = False
        self.not_used_tables_built = False

    def get_vtk_classes_from_html(self):
        """
        Parse the html file, getting a list of the classes.
        """
        # We want the first match, hence the use of ?.
        # Adding a ? on a quantifier (?, * or +) makes it non-greedy.
        # Selecting only objects marked as classes.
        vtk_class_pattern = re.compile(r'<span class=\"icon\">C.*?href=\"(.*?)\" target=\"_self\">(.*?)</a>')
        try:
            f = urlopen(self.vtk_class_url)
            for line in f:
                s = re.findall(vtk_class_pattern, line.decode('utf-8'))
                if s:
                    for item in s:
                        # Remove structs.
                        if item[0].startswith('struct'):
                            continue
                        self.vtk_classes[item[1]] = item[0]
            f.close()
        except IOError:
            print('Unable to open the URL: {:s}'.format(self.vtk_class_url))

    def get_example_file_paths(self):
        """
        For each example, get the example file paths.
        """
        for eg in self.example_types:
            # Get the paths to the examples in a particular sub directory e.g Cxx.
            file_paths = defaultdict(list)
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
                        file_paths[key].append(os.path.join(root, filename))
            self.example_file_paths[eg] = file_paths

    def vtk_classes_in_examples(self):
        """
        Find the vtk classes used in the examples.
        """
        for eg in self.example_types:
            res = defaultdict(lambda: defaultdict(set))
            if eg == 'CSharp':
                class_pattern = re.compile(r'^[A-Za-z0-9=. <>()\t]+(vtk[A-Za-z0-9]+)')
            elif eg == 'Cxx':
                class_pattern = re.compile(
                    r'^[ \t]*#include[ ]+<(vtk[A-Za-z0-9]+)+.h>$|'  # match: #include <vtkClass.h>
                    r'.*[< ]+(vtk[A-Za-z0-9]+)[> ]|'  # match: <vtkClass>
                    r'.*[= ]+(vtk[A-Za-z0-9]+)[ ]*::New'  # match: vtkClass::New()
                )
            elif eg == 'Java':
                class_pattern = re.compile(r'^[A-Za-z0-9=. \t]+new[ ]+(vtk[A-Za-z0-9]+)[ ]*\(')
            elif eg == 'Python':
                class_pattern = re.compile(r'^[A-Za-z0-9=. ()\t]+(vtk[A-Za-z0-9]+)[ ]*\(')
            else:
                raise RuntimeError('Unknown example type.')

            for k, v in self.example_file_paths[eg].items():
                for fn in v:
                    # Open and read the file building a list of classes.
                    with open(fn) as f:
                        for line in f:
                            m = class_pattern.match(line)
                            if m:
                                c = m.group(m.lastindex)
                                if c in self.vtk_classes:
                                    # Just get the file name
                                    sp = path_splitter(fn)
                                    res[c][k].add(sp[-1])
            self.classes_used[eg] = res

    def make_classes_used_table(self):
        """
        Make a table of classes used for each set of examples.
        """
        if self.add_vtk_html:
            vtk_html_fmt = self.vtk_html_fmt
        else:
            vtk_html_fmt = '{:s}'

        eg_fmt = '[{:s}]({:s})'
        h1 = '# VTK Classes used in the Examples\n\n'
        h2 = '## {:s}\n\n'
        h3 = '### {:s}\n\n'

        # Excluded classes columns.
        h1ec = ' VTK Class '
        h2ec = '-----------'
        r1ec = ' {:s} '
        th1ec = '|' + h1ec
        th2ec = '|' + h2ec
        trec = '|' + r1ec
        for i in range(1, self.excluded_columns):
            th1ec += '|' + h1ec
            th2ec += '|' + h2ec
            trec += '|' + r1ec
        th1ec += '|\n'
        th2ec += '|\n'
        trec += '|\n'

        # Classes and examples.
        th1 = '| VTK Class | Examples |\n'
        th2 = '|--------------|----------------------|\n'
        tr = '| {:s} | {:s} |\n'
        for eg in self.example_types:
            if eg == 'Cxx':
                excl_classes = self.excluded_classes + ['vtkSmartPointer', 'vtkNew']
            else:
                excl_classes = self.excluded_classes
            res = list()
            res.append(h1)
            res.append(h2.format(eg))
            res.append('Out of {:d} available VTK classes, {:d} are demonstrated here.\n\n'.format(
                len(self.vtk_classes), len(self.classes_used[eg])))
            # Excluded classes
            res.append(h3.format('Excluded classes'))
            res.append('These classes are excluded since they occur in the majority of the examples:\n\n')
            res.append(th1ec)
            res.append(th2ec)
            tmp = []
            for c in list(sorted(excl_classes, key=lambda x: (x.lower(), x.swapcase()))):
                tmp.append(vtk_html_fmt.format(c, self.vtk_classes[c]))
                if len(tmp) == self.excluded_columns:
                    res.append(trec.format(*tmp))
                    del tmp[:]
            if tmp:
                while len(tmp) < self.excluded_columns:
                    tmp.append('')
                res.append(trec.format(*tmp))
            res.append('\n')
            res.append(h3.format('Classes used'))
            res.append(th1)
            res.append(th2)
            vtk_keys = list(sorted(list(self.classes_used[eg].keys()), key=lambda x: (x.lower(), x.swapcase())))
            for vtk_class in vtk_keys:
                if vtk_class not in excl_classes:
                    html_class = vtk_html_fmt.format(vtk_class, self.vtk_classes[vtk_class])
                    paths = self.classes_used[eg][vtk_class]
                    f_list = ''
                    # Here we are assuming no two files have the same name.
                    # tmp will be used to generate a sorted list of files.
                    tmp = dict()
                    for path, fn in paths.items():
                        for f in fn:
                            # Remove the extension.
                            f1 = f[:f.rfind('.')]
                            # NOTE: Need leading '/'
                            tmp[f] = eg_fmt.format(f1, '/' + path + '/' + f1) + ' '
                    tmp_keys = list(sorted(list(tmp.keys()), key=lambda x: (x.lower(), x.swapcase())))
                    for k in tmp_keys:
                        f_list += tmp[k]
                    tmp.clear()
                    res.append(tr.format(html_class, f_list))
            self.classes_used_table[eg] = res

    def make_classes_not_used_table(self):
        """
        Make a table of classes that are not used for each set of examples.
        """
        if self.add_vtk_html:
            vtk_html_fmt = self.vtk_html_fmt
        else:
            vtk_html_fmt = '{:s}'

        h1 = '# VTK Classes not used in the Examples\n\n'
        h2 = '## {:s}\n\n'

        h1c = ' VTK Class '
        h2c = '-----------'
        r1c = ' {:s} '
        th1 = '|' + h1c
        th2 = '|' + h2c
        tr = '|' + r1c
        for i in range(1, self.columns):
            th1 += '|' + h1c
            th2 += '|' + h2c
            tr += '|' + r1c
        th1 += '|\n'
        th2 += '|\n'
        tr += '|\n'

        for eg in self.example_types:
            res = list()
            unused_classes = list()
            for vtk_class in sorted(self.vtk_classes):
                if vtk_class not in self.classes_used[eg]:
                    unused_classes.append(vtk_html_fmt.format(vtk_class, self.vtk_classes[vtk_class]))
            res.append(h1)
            res.append(h2.format(eg))
            res.append('Out of {:d} available VTK classes, {:d} have not been used.  \n'.format(
                len(self.vtk_classes), len(unused_classes)))
            res.append('\n')
            res.append(th1)
            res.append(th2)

            for i in range(len(unused_classes) % self.columns):
                unused_classes.append('')
            idx = 0
            tmp = [''] * self.columns
            for i in range(0, len(unused_classes)):
                tmp[idx] = unused_classes[i]
                idx += 1
                if idx % self.columns == 0:
                    idx = 0
                    res.append(tr.format(*tmp))
                    tmp = [''] * self.columns
            res.append(tr.format(*tmp))
            self.classes_not_used_table[eg] = res

    def build_tables(self):
        self.get_vtk_classes_from_html()
        self.get_example_file_paths()
        self.vtk_classes_in_examples()
        self.make_classes_used_table()
        self.used_tables_built = True
        if self.unused_vtk:
            self.make_classes_not_used_table()
            self.not_used_tables_built = True

    def print_tables(self):
        if not self.used_tables_built:
            raise RuntimeError('The classes used tables have not been built.')
        if self.unused_vtk and not self.not_used_tables_built:
            raise RuntimeError('The classes not used tables have not been built. Enable -u.')
        pth = os.path.join(self.base_directory, 'Coverage')
        for eg in self.example_types:
            fn = os.path.join(pth, eg + 'VTKClassesUsed')
            print_table(self.classes_used_table[eg], fn)
            if self.unused_vtk:
                fn = os.path.join(pth, eg + 'VTKClassesNotUsed')
                print_table(self.classes_not_used_table[eg], fn)


def main():
    example_source, columns, excluded_columns, unused_vtk, add_vtk_html = get_program_parameters()
    vtk_classes = VTKClassesInExamples(example_source, columns, excluded_columns, unused_vtk, add_vtk_html)
    vtk_classes.build_tables()
    vtk_classes.print_tables()


if __name__ == '__main__':
    main()
