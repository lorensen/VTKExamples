# !/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import print_function

import os


def get_program_parameters():
    import argparse
    description = 'Add prefix "Test" to test images if missing.'
    epilogue = '''
Typical usage:
   For each file in VTKExamples/src/Testing/Baseline look in the corresponding folder in
      VTKExamples/src/Testing/Baseline for an image file that does not have the Test prefix.
      Then rename the file so it has a TestPrefix.

   To produce a list of example files that should be renamed:
      AddTestPrefix.py some_path/VTKExamples/src/Testing/Baseline Python png

   To rename the example files:
      AddTestPrefix.py some_path/VTKExamples/src/Testing/Baseline Python png -p Test -r

'''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument('base_path', help='The base path.')
    parser.add_argument('folder', help='The subfolder to do the renaming in e.g. Python.')
    parser.add_argument('extension', help='The file extension e.g. png.')
    parser.add_argument('-p', '--prefix', help='The prefix of the renamed file.', nargs='?', const=None, type=str)
    parser.add_argument('-s', '--suffix', help='The suffix of the renamed file.', nargs='?', const=None, type=str)
    parser.add_argument('-r', '--rename', help='Rename files from <file_name>.png to <prefix><file_name><suffix>.png.',
                        action='store_true')

    args = parser.parse_args()
    return args.base_path, args.folder, args.extension, args.prefix, args.suffix, args.rename


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


class Renamer:
    """
    Rename all files in the folder.
    """

    def __init__(self, base_path, folder, ext, prefix, suffix, do_rename):
        """

        :param base_path: The base path.
        :param folder: The folder in the base path where files are to be renamed.
        :param ext: Extension
        :param prefix: The prefix of the new file name.
        :param suffix: The suffix of the new file name.
        :param do_rename: True if renaming is to occur.
        """
        self.base_path = base_path
        self.folder = folder
        self.ext = ext
        self.prefix = prefix  # '' if prefix is None else str(prefix)
        self.suffix = suffix  # '' if suffix is None else str(suffix)
        self.rename = do_rename
        self.files_to_rename = list()

    def get_all_test_images(self):
        """
        For each example, get the file paths and the file names to change.
        """
        # Get the paths to the examples in a particular sub directory e.g Cxx.
        directory = os.path.join(self.base_path, self.folder)
        # Does the directory exist?
        if not os.path.isdir(directory):
            raise RuntimeError('Non-existent folder: {:s}'.format(directory))
        prefix = '' if self.prefix is None else str(self.prefix)
        suffix = '' if self.suffix is None else str(self.suffix)
        # Walk the tree.
        for root, directories, files in os.walk(directory):
            if os.path.isabs(root):
                abs_path = root
            else:
                abs_path = os.path.abspath(root)
            ext = '.' + self.ext
            for filename in files:
                s = os.path.splitext(filename)
                if s[1] == ext:
                    idx = s[0].find(prefix)
                    if idx < 0:
                        to_fn = prefix + s[0] + suffix
                    else:
                        to_fn = prefix + s[0][len(prefix):] + suffix
                    if s[0] == to_fn:
                        continue
                    if not self.rename:
                        print(root, s[0] + s[1], '->', to_fn + s[1])
                    from_path = os.path.join(abs_path, s[0] + s[1])
                    to_path = os.path.join(abs_path, to_fn + s[1])
                    self.files_to_rename.append([from_path, to_path])

    def rename_all_test_images(self):
        """
        Rename the test images.
        """
        if not self.files_to_rename:
            self.get_all_test_images()
        if self.files_to_rename:
            not_renamed = list()
            for item in self.files_to_rename:
                try:
                    os.rename(item[0], item[1])
                    print(item[0], '->', item[1])
                except OSError as e:
                    print(e)
                    not_renamed.append(item)
                    continue
            print('Number of files:')
            print('  Renamed    :', len(self.files_to_rename) - len(not_renamed))
            print('  Not Renamed:', len(not_renamed))
            print('  Total      :', len(self.files_to_rename))


def main():
    baseline_path, folder, ext, prefix, suffix, do_rename = get_program_parameters()
    renamer = Renamer(baseline_path, folder, ext, prefix, suffix, do_rename)
    if do_rename:
        renamer.rename_all_test_images()
    else:
        print('Here are the files to rename:')
        renamer.get_all_test_images()
        print('To rename all these files, re-run this script with the -r option.')


if __name__ == '__main__':
    main()
