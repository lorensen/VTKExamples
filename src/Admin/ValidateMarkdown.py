#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
"""

import os
import re
from collections import defaultdict


def eliminate_duplicate_lines(lines):
    lines_seen = set()
    no_duplicates = list()
    for l in lines:
        if l not in lines_seen:
            no_duplicates.append(l)
            lines_seen.add(l)
    return no_duplicates


def remove_consecutive_duplicates(lines):
    ncd = list()
    for l in lines:
        if len(ncd):
            if ncd[-1] != l:
                ncd.append(l)
        else:
            ncd.append(l)
    return ncd


def split_file_name(full_path):
    """
    Split the file name into path, file name and extension.
    :param full_path: The full path.
    :return: a list [path, filename, extension]
    """
    res = list(os.path.split(full_path))
    if res[1].rfind('.') > 0:
        fn = res[1][:res[1].rfind('.')]
        ext = res[1][res[1].rfind('.') + 1:]
        res[1] = fn
    else:
        ext = None
    res.append(ext)
    return res


def main():
    ifn = get_program_parameters()
    ifn = os.path.abspath(ifn)
    allowed_files = {'CSharp': ['CSharp', 'cs'], 'Cxx': ['Cxx', 'cxx'], 'Java': ['Java', 'java'],
                     'Python': ['Python', 'py'], 'VTKBookFigures': ['Cxx', 'cxx']}
    # Split the input file name into [path, file name, extension, [sub directory, language]].
    file_parameters = split_file_name(ifn)
    if not (file_parameters[1] in allowed_files.keys() and file_parameters[2] == 'md'):
        print('Wrong file:', ifn)
        print('These files can only be validated:')
        print(', '.join(s + '.md' for s in sorted(allowed_files.keys())))
        return
    else:
        file_parameters.append(allowed_files[file_parameters[1]])

    #  These regular expressions are for VTKExamples.
    title = re.compile(r'^[#]+[ ]*\w')
    title_line = re.compile(r'^([#]+)\s*(.*)$')
    info_line = re.compile(r'^[!]{3}[ ]+info$')
    header = re.compile(r'(^\|[^|]+)(\|[^|]+)(\|[^|]+)(\|[^|]+)\|')
    row = re.compile(r'(^[^|]+[|])([^|]*[|])([^|]*[^|])?$')
    row_key = re.compile(r'\[(.*?)\].*\((.*?)\)')

    with open(ifn) as f:
        """
        We expect:
        [title] [text] [[title][text]] [header][rows][text]
        """
        lines = remove_consecutive_duplicates(f.read().split('\n'))
        tbl = defaultdict()
        find_rows = False
        indent_next_line = False
        header_line_no = 0
        res = list()
        problems = defaultdict(lambda: defaultdict(list))

        for line in lines:
            ls = line.strip()
            if find_rows:
                # Process the rows.
                if not (title.match(ls) or header.match(ls)) and ls:
                    if row.match(ls):
                        sl = [x.strip() for x in ls.split('|')]
                        match = re.search(row_key, sl[0])
                        if match:
                            # Check the link to see if it is valid.
                            k = match.group(1).strip()
                            v = match.group(2).strip()
                            if v.strip('/').split('/')[0] != file_parameters[3][0]:
                                problems['link - wrong language'][last_title].append(ls)
                                continue
                            if not os.path.isfile(
                                    os.path.join(file_parameters[0], '.'.join((v, file_parameters[3][1]))[1:])):
                                problems['link - target not found'][last_title].append(ls)
                                continue
                            sl[0] = '[' + k + ']' + '(' + v + ')'
                            tbl[k] = sl
                        else:
                            problems['No key'][last_title].append(ls)
                            continue
                    else:
                        problems['Bad row'][last_title].append(ls)
                        continue
                    continue
                else:
                    find_rows = False
                    keys = sorted(tbl.keys())
                    for k in keys:
                        res.append((' | '.join(tbl[k])).strip())
                    res.append('')
                    tbl.clear()
                    continue

            if title.match(ls):
                match = re.search(title_line, ls)
                if match:
                    new_line = match.group(1) + ' ' + match.group(2)
                    res.append(new_line)
                    last_title = new_line
                    res.append('')
                else:
                    res.append(ls)
                    problems['Bad title'][''].append(ls)
                continue

            if not (title.match(line) or header.match(line) or row.match(line)):
                if indent_next_line:
                    res.append(' ' * 4 + ls)
                    indent_next_line = False
                else:
                    res.append(ls)
                if info_line.match(ls):
                    indent_next_line = True
                continue

            if header.match(line):
                sl = [x.strip() for x in ls.split('|')]
                res.append((' | '.join(sl)).strip())
                header_line_no += 1
                if header_line_no > 1:
                    header_line_no = 0
                    find_rows = True

    res = remove_consecutive_duplicates(res)
    lines = '\n'.join(res)
    if not problems:
        backup_file = os.path.abspath(os.path.join(ifn + '.back'))
        try:
            os.rename(ifn, backup_file)
            with open(ifn, 'w') as f:
                f.write(lines)
        except IOError as e:
            print(e)
        print('Reformatted Ok.')
    else:
        ofn = os.path.abspath(os.path.join(ifn + '.errors'))
        res = list()
        res.append('There are problems.')
        res.append('The file:\n' + ifn + '\n    will not be updated.')
        res.append('The problems are:')
        for i in problems.keys():
            res.append(i)
            for j, v in problems[i].items():
                res.append('    ' + j)
                for k in v:
                    res.append('        ' + k)
        lines = '\n'.join(res)
        with open(ofn, 'w') as f:
            f.write(lines)
        print('There are problems.')
        print('Please see:\n', ofn)


def get_program_parameters():
    import argparse
    description = 'This program parses a markdown file that is used to generate the web page.'
    epilogue = '''
    Assume that the file you are checking is called Cxx.md.
    1) If errors are found a log file called Cxx.md.log is written and the markdown file being parsed is not updated.
    2) If there are no errors then the markdown file is renamed to Cxx.md.backup.
       Then a new file is created with the original name Cxx.md.
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('ifn', help='Input filename.')
    args = parser.parse_args()
    return args.ifn


if __name__ == "__main__":
    main()
