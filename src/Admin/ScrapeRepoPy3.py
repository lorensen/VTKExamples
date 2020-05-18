#!/usr/bin/env python

# This is a currently untested Python 3 version of ScrapeRepo
# 
# concurrent.futures is used to set up a thread pool
#   to make processing of tiny urls faster

import concurrent.futures
import contextlib
# imports
import hashlib
import os
import re
import shutil
import subprocess
import tarfile
import tempfile
from urllib.parse import urlencode
from urllib.request import urlopen

try:
    import markdown
except ModuleNotFoundError:
    print("ScrapeRepo: " + "markdown package is required but not found.")
    print("ScrapeRepo: " + "install with `pip|conda install markdown`")
    exit(0)


def get_program_parameters():
    import argparse
    description = 'Creates site files from the source respository.'
    epilogue = '''
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('RepoDir', help='The local directory containing the VTK example source e.g. VTKExamples/src/')
    parser.add_argument('DocDir', help='The directory to receive the markdown pages e.g. VTKExamples/docs/')
    parser.add_argument('RepoURL',
                        help='RepoURL is the githib repo UR e.g. https::/github.com/**YOUR_NAME**/VTKExamples')
    parser.add_argument('VTKSrc', help='The local directory containing the VTK source')
    args = parser.parse_args()
    return args.RepoDir, args.DocDir, args.RepoURL, args.VTKSrc


def make_tiny(url):
    request_url = ('http://tinyurl.com/api-create.php?' +
                   urlencode({'url': url}))
    with contextlib.closing(urlopen(request_url)) as response:
        return response.read().decode('utf-8')


# copy a file

def CopyFile(fromFile, toFile):
    fromFn = make_path_name(fromFile)
    toFn = make_path_name(toFile)
    outFile = open(toFn, 'wb')
    with open(fromFn, 'rb') as f:
        outFile.write(f.read())
    outFile.close()


# create a list of html id's
def CreateHtmlIds(fromFile):
    global htmlIdSet
    fromFn = make_path_name(fromFile)
    with open(fromFn, 'r') as chapterLine:
        for line in chapterLine:
            idFound = re.findall(r'<figure[ ]*id="([^\"]*)">', line)
            if len(idFound) > 0:
                htmlIdSet.add(idFound[0])


# copy a file and add figure and doxygen links
# only add links to doxygen if we are outside code blocks
# delimited by ```
# only add links to a figure if the figure exists
def CopyChapterAndAddLinks(fromFile, toFile):
    global htmlIdSet
    fromFn = make_path_name(fromFile)
    toFn = make_path_name(toFile)
    inCode = False
    outFile = open(toFn, 'w')
    with open(fromFn, 'r') as chapterLine:
        for line in chapterLine:
            if line.count(r'```') % 2 != 0:
                inCode = not inCode
            if not inCode:
                line = AddDoxygen(line)
                figureFound = sorted(re.findall(r'\*\*(Figure[^\*]*)\*\*', line), reverse=True)
                if len(figureFound) > 0:
                    for figure in figureFound:
                        if figure in htmlIdSet:
                            line = line.replace(figure, r'<a href="#' + figure.replace("Figure",
                                                                                       "FIGURE") + '">**' + figure.replace(
                                "Figure", "FIGURE") + r'**</a>')
            line = line.replace("FIGURE", "Figure")
            outFile.write(line)
    outFile.close()


# load the component cache into a dictionary

def LoadComponentsCache(CacheFile, CacheDict):
    cf = open(CacheFile, 'r')
    for line in cf:
        words = line.split()
        CacheDict[words[0]] = ""
        for word in words[1:]:
            CacheDict[words[0]] += " " + word
    cf.close()


# if the source code components are not in the cache, find them

def GetComponents(CacheDict, VTKSrcDir, srcFile, src):
    global componentsCacheHits
    global componentsCacheMisses
    # compute sha of src
    sha = hashlib.sha256(str.encode(src)).hexdigest()
    if srcFile in list(CacheDict.keys()):
        words = CacheDict[srcFile].split()
        if str(sha) == words[0]:
            componentsCacheHits = componentsCacheHits + 1
            return words[1:]
    componentsCacheMisses = componentsCacheMisses + 1
    try:
        cmd = os.path.join(RepoDir, 'Admin', 'WhatModulesVTKPy3.py') + ' -p ' + VTKSrcDir + ' -s ' + srcFile
        process = subprocess.run(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, )
    except subprocess.CalledProcessError as err:
        print('ERROR:', err)
    if process.returncode != 0:
        print('returncode:', process.returncode)
        print('Have {} bytes in stdout:\n{}'.format(
            len(process.stdout),
            process.stdout.decode('utf-8'))
        )
        print('Have {} bytes in stderr:\n{}'.format(
            len(process.stderr),
            process.stderr.decode('utf-8'))
        )
    rawWhatOutput = process.stdout.decode('utf-8')
    components = ParseWhatModulesVTKOutput(rawWhatOutput)

    CacheDict[str(srcFile)] = sha
    for component in components:
        CacheDict[str(srcFile)] += " " + component
    print("cache miss: ", str(srcFile))
    return components


def ParseWhatModulesVTKOutput(rawWhatOutput):
    words = rawWhatOutput.split('\n')
    components = list()
    for word in words:
        if "find_package" in word:
            continue
        if ")" in word:
            continue
        if "Your" in word:
            continue
        if "All" in word:
            continue
        if word == "":
            continue
        components.append(word.strip())
    return components


# load the tinyurl cache into a dictionary

def LoadTinyUrlCache(CacheFile, CacheDict):
    cf = open(CacheFile, 'r')
    for line in cf:
        words = line.split()
        CacheDict[words[0]] = words[1]
    cf.close()


# if the url is not in the cache, get the tinyurl

def GetTinyUrl(CacheDict, Url):
    global cacheHits
    global cacheMisses
    if Url in list(CacheDict.keys()):
        cacheHits = cacheHits + 1
        return CacheDict[Url]
    tinyOne = make_tiny(Url)
    CacheDict[Url] = tinyOne
    cacheMisses = cacheMisses + 1
    print("cache miss: " + Url)
    return CacheDict[Url]


def tiny_url(k):
    return k, make_tiny(k)


def get_results(url):
    # The default value of max_workers is min(32, os.cpu_count() + 4) for Python 3.8 or greater
    with concurrent.futures.ThreadPoolExecutor() as executor:
        future_results = [executor.submit(tiny_url, k) for k in url]
        # Block execution until all the tasks are completed
        concurrent.futures.wait(future_results)
        for future in future_results:
            yield future.result()
            # try:
            #     yield future.result()
            # except:
            #     print_exc()


def UpdateUrlCache(CacheDict, lines):
    global cacheHits
    global cacheMisses
    #  Extract the lines that need tiny urls
    needUrls = dict()
    urlsToShorten = list()
    for k, v in lines.items():
        if v[0]:
            needUrls[k] = v
    for k, v in needUrls.items():
        if v[2] in list(CacheDict.keys()):
            cacheHits += 1
        else:
            cacheMisses += 1
            print("cache miss: " + v[2])
            urlsToShorten.append(v[2])
    res = get_results(urlsToShorten)
    #  Update the cache
    for r in res:
        CacheDict[r[0]] = r[1]


def MakeTinyUrls(CacheDict, lines):
    UpdateUrlCache(CacheDict, lines)
    for k, v in lines.items():
        if v[0]:
            img = '<img class="lazy" style="float:center" data-src="' + CacheDict[v[2]] + '?raw=true" width="64" />'
            s = ' | <a href="{}?raw=true target="_blank">{}\n</a>'.format(v[2], img)
            lines[k][2] = s
    return  # lines


# Is the example a Qt example

def IsQtExample(S):
    reg = re.compile(r".*Qt.*", re.DOTALL)
    return reg.match(S)


# Get the Qt CMake file

def GetVTKQtCMake(S):
    reg = re.compile(r"\{\{(VTKQtCMakeLists)\|(.*?)\}\}.*?", re.DOTALL)
    return [reg.findall(S)]


# Get the VTK CMake file
def GetVTKCMakelists(S):
    reg = re.compile(r"```cmake(.*?)```", re.DOTALL)
    return [''.join(reg.findall(S))]


# add header and code hilighting to c++ code

def WriteCxxCode(toFile, codeName, code):
    toFile.write("**" + codeName + "**" + "\n")
    toFile.write("```c++" + "\n")
    toFile.write(code)
    toFile.write("```" + "\n")


# Return hl_lines to highlight lines that have vtk classes mentiones

def FindLinesWithVTK(srcFileName):
    srcFile = open(srcFileName, 'r')
    lines = srcFile.readlines()
    lineNumber = 1
    reg = re.compile(r'(vtk[0-9a-zA-Z]*)')
    hl_lines = 'hl_lines="'
    for line in lines:
        if reg.search(line):
            hl_lines += str(lineNumber) + " "
        lineNumber += 1
    hl_lines += '"\n'
    srcFile.close()
    return hl_lines


# Add a link to an example in anpther language
def AddLanguage(S, link):
    reg = re.compile(r'(^\[[^\)]*\))')
    if reg.findall(S):
        return re.sub(r'(^\[[^\)]*\))', r'\1' + link, S)
    return S


# Given a lang example return a link to a Python example if it exists
def FindPythonGivenLang(repoDir, example, lang):
    if lang == "Python":
        return ""
    pythonLink = re.sub(r'/' + lang + r'/', r'/Python/', example)
    pythonPath = repoDir + pythonLink + ".py"
    if os.path.exists(pythonPath):
        return "([python](" + pythonLink + "))"
    return ""


# Given a lang example return a link to another example if it exists
def FindOtherGivenLang(repoDir, example, exampleLang, otherLang, otherExt):
    if otherLang == exampleLang:
        return ""
    otherLink = re.sub(r'/' + exampleLang + r'/', r'/' + otherLang + '/', example)
    otherPath = repoDir + otherLink + otherExt
    if os.path.exists(otherPath):
        return "([" + otherLang + "](" + otherLink + "))"
    return ""


# Given a Cxx example return a link to a Python example if it exists
def FindPythonGivenCxx(repoDir, cxxExample):
    pythonLink = re.sub(r'/Cxx/', r'/Python/', cxxExample)
    pythonPath = repoDir + pythonLink + ".py"
    if os.path.exists(pythonPath):
        return "([python](" + pythonLink + "))"
    return ""


# Given a Python example return a link to a Cxx example if it exists
def FindCxxGivenPython(repoDir, pythonExample):
    cxxLink = re.sub(r'/Python/', r'/Cxx/', pythonExample)
    cxxPath = repoDir + cxxLink + ".cxx"
    if os.path.exists(cxxPath):
        return "([cxx](" + cxxLink + "))"
    return ""


# If vtkXXXX is in the string, add a link to the doxygen file

def AddDoxygen(S):
    global doxyCount
    reg = re.compile(r'[^\./\[s\-](vtk[^ &][0-9a-zA-Z]*)')
    if reg.findall(S):
        doxyCount = doxyCount + 1
        return re.sub(r'[^\./\[-](vtk[0-9a-zA-Z]*)',
                      r' [\1](' + r'http://www.vtk.org/doc/nightly/html/class' + r'\1.html#details)', S)
    return S


# add doxygen links to a file

def AddDoxygens(repoDir, repoURL, fromFile, toFile):
    mdFile = open(fromFile, 'r')
    outFile = open(toFile, 'w')
    for line in mdFile:
        withDoxy = AddDoxygen(line)
        outFile.write(withDoxy.rstrip())
        outFile.write("\n")
    mdFile.close()
    outFile.close()


# add thumbnails to example tables

def FindThumbnail(S):
    reg = re.compile(r'^\[[^\(]*\]\(([^)]*)')
    if reg.match(S):
        return [''.join(reg.findall(S))]
    return ['']


# add thumbnails to a file

def AddThumbnailsAndLanguageLinks(repoDir, repoURL, fromFile, toFile):
    global thumbCount
    fromFn = make_path_name(fromFile)
    toFn = make_path_name(toFile)
    mdFile = open(fromFn, 'r')
    lines = dict()
    line_count = 0
    x = []
    for line in mdFile:
        exampleLine = FindThumbnail(line.strip())[0]
        startCxx = exampleLine.find("Cxx")
        if startCxx >= 0:
            pythonLink = FindPythonGivenCxx("src", exampleLine)
            if pythonLink != '':
                line = AddLanguage(line, pythonLink)

        startPython = exampleLine.find("Python")
        if startPython >= 0:
            cxxLink = FindCxxGivenPython("src", exampleLine)
            if cxxLink != '':
                line = AddLanguage(line, cxxLink)

        withDoxy = AddDoxygen(line)
        x.append(False)
        x.append(withDoxy.rstrip())
        if exampleLine != '':
            thumbCount = thumbCount + 1
            exampleName = os.path.split(exampleLine)[1]
            exampleDir = os.path.split(exampleLine)[0]
            baseline = make_path_name(RepoDir + "/Testing/Baseline" + exampleDir + "/Test" + exampleName + ".png")
            if os.path.exists(baseline):
                baselineURL = make_path_name(repoURL + "/blob/master/" + baseline)
                x[0] = True
                x.append(baselineURL)
        lines[line_count] = x
        line_count += 1
        x = []
    MakeTinyUrls(CacheDict, lines)
    mdFile.close()
    outFile = open(toFn, 'w')
    k = sorted(lines.keys())
    for kv in k:
        line = ''.join(lines[kv][1:])
        # print(lines[kv])
        # print(line)
        # if lines[kv][0]:
        #     print(line)
        outFile.write(line + '\n')
    outFile.close()


# Fill in the template parameters in a CMakeLists template file
# The output is a CMakeLists.txt file with Name substituted for {{{1}}}

def FillCMakeLists(S, Name, ExtraNames, Components):
    r1 = re.sub(r'XXX', Name, S)
    r2 = re.sub(r'YYY', ExtraNames, r1)
    reg = re.sub(r'ZZZ', Components, r1)
    return reg


def FillQtCMakeLists(S, Name, Components):
    r1 = re.sub(r'XXX', Name, S)
    reg = re.sub(r'ZZZ', Components, r1)
    return reg


def make_path_name(*args):
    """
    Return a path name
    :param args:
    :return:
    """
    components = []
    for a in args:
        components.append(a.split('/'))
    flat_list = [item for sublist in components for item in sublist]
    if flat_list[0] == '':
        flat_list[0] = '/'
    # Strip out remaining ''s
    list1 = [elem for elem in flat_list if elem]
    return os.path.join(*list1)


#####################################################################
# Initialize counts on these globals
cacheHits = 0
cacheMisses = 0
componentsCacheHits = 0
componentsCacheMisses = 0

cxxCount = 0
csCount = 0
pyCount = 0
javaCount = 0

thumbCount = 0
doxyCount = 0

# Other globals
CacheDict = dict()
ComponentsDict = dict()
htmlIdSet = set()

RepoDir= ''
DocDir = ''
RepoURL = ''
VTKSrcDir = ''

#####################################################################
#  This is the main module.
def main ():
    global cacheHits
    global cacheMisses
    global componentsCacheHits
    global componentsCacheMisses

    global cxxCount
    global csCount
    global pyCount
    global javaCount

    global thumbCount
    global doxyCount

    global CacheDict
    global ComponentsDict

    global RepoDir
    global DocDir
    global RepoURL
    global VTKSrcDir

    RepoDir, DocDir, RepoURL, VTKSrcDir = get_program_parameters()
    
    # Make sure the wiki docs folder exists
    if not os.path.exists(DocDir):
        os.makedirs(DocDir)
    
    # Baseline top level
    BaselineName = make_path_name(RepoDir, '/Testing/Baseline')
    
    # Load the TinyUrl cache
    CacheFile = make_path_name(RepoDir, '/Admin/TinyUrlCache')
    # CacheDict = dict()
    LoadTinyUrlCache(CacheFile, CacheDict)
    
    # Load the Component cache
    ComponentsCacheFile = make_path_name(RepoDir, '/Admin/ComponentsCache')
    # ComponentsDict = dict()
    LoadComponentsCache(ComponentsCacheFile, ComponentsDict)
    
    # Read the Wiki Templates
    with open(make_path_name(RepoDir, '/Admin/VTKCMakeLists'), 'r') as VTKTemplateFile:
        VTKTemplate = VTKTemplateFile.read()
    
    with open(make_path_name(RepoDir, '/Admin/VTKQtCMakeLists'), 'r') as VTKQtTemplateFile:
        VTKQtTemplate = VTKQtTemplateFile.read()
    
    # Make the reference mtime to be the most recent of the two CMakeLists templates
    refStat1 = os.stat(make_path_name(RepoDir, '/Admin/VTKQtCMakeLists'))
    refStat2 = os.stat(make_path_name(RepoDir, '/Admin/VTKCMakeLists'))
    refMtime = refStat1.st_mtime
    if refStat2.st_mtime > refStat1.st_mtime:
        refMtime = refStat2.st_mtime
    
    # Create a dict to hold code name and page name
    codeToPage = dict()
    
    # Create a dict to hold CMakeLists.txt file
    exampleToCMake = dict()
    
    # Create a dict to hold the file names for each example
    exampleToFileNames = dict()
    
    # Create Snippets directories for Cxx, Python and Java
    if not os.path.exists(make_path_name(DocDir, '/Cxx/Snippets')):
        os.makedirs(make_path_name(DocDir, '/Cxx/Snippets'))
    
    if not os.path.exists(make_path_name(DocDir, '/Python/Snippets')):
        os.makedirs(make_path_name(DocDir, '/Python/Snippets'))
    
    if not os.path.exists(make_path_name(DocDir, '/Java/Snippets')):
        os.makedirs(make_path_name(DocDir, '/Java/Snippets'))
    
    # Add thumbnails and language links to each of the language summary pages, Snippets and Book figures
    AddThumbnailsAndLanguageLinks(RepoDir, RepoURL, RepoDir + '/Cxx.md', DocDir + '/Cxx.md')
    AddThumbnailsAndLanguageLinks(RepoDir, RepoURL, RepoDir + '/Python.md', DocDir + '/Python.md')
    AddThumbnailsAndLanguageLinks(RepoDir, RepoURL, RepoDir + '/CSharp.md', DocDir + '/CSharp.md')
    AddThumbnailsAndLanguageLinks(RepoDir, RepoURL, RepoDir + '/Java.md', DocDir + '/Java.md')
    AddThumbnailsAndLanguageLinks(RepoDir, RepoURL, RepoDir + '/JavaScript.md', DocDir + '/JavaScript.md')
    
    AddThumbnailsAndLanguageLinks(RepoDir, RepoURL, RepoDir + '/Cxx/Snippets.md', DocDir + '/Cxx/Snippets.md')
    AddThumbnailsAndLanguageLinks(RepoDir, RepoURL, RepoDir + '/Python/Snippets.md', DocDir + '/Python/Snippets.md')
    AddThumbnailsAndLanguageLinks(RepoDir, RepoURL, RepoDir + '/Java/Snippets.md', DocDir + '/Java/Snippets.md')
    AddThumbnailsAndLanguageLinks(RepoDir, RepoURL, RepoDir + '/VTKBookFigures.md', DocDir + '/VTKBookFigures.md')
    AddThumbnailsAndLanguageLinks(RepoDir, RepoURL, RepoDir + '/VTKFileFormats.md', DocDir + '/VTKFileFormats.md')
    
    # C++ Snippets
    files = os.listdir(make_path_name(RepoDir + '/Cxx/Snippets'))
    for f in files:
        snippet = os.path.splitext(f)[0]
        fromPath = RepoDir + '/Cxx/Snippets/' + snippet + '.md'
        toPath = DocDir + '/Cxx/Snippets/' + snippet + '.md'
        CopyFile(fromPath, toPath)
    
    # Python Snippets
    files = os.listdir(make_path_name(RepoDir + '/Python/Snippets'))
    for f in files:
        snippet = os.path.splitext(f)[0]
        fromPath = RepoDir + '/Python/Snippets/' + snippet + '.md'
        toPath = DocDir + '/Python/Snippets/' + snippet + '.md'
        CopyFile(fromPath, toPath)
    
    # Java Snippets
    files = os.listdir(make_path_name(RepoDir + '/Java/Snippets'))
    for f in files:
        snippet = os.path.splitext(f)[0]
        fromPath = RepoDir + '/Java/Snippets/' + snippet + '.md'
        toPath = DocDir + '/Java/Snippets/' + snippet + '.md'
        CopyFile(fromPath, toPath)
    
    # Copy favicon.png
    fromPath = make_path_name(DocDir + '/assets')
    toPath = make_path_name(make_path_name(DocDir + '/assets/images'))
    if not os.path.exists(fromPath):
        os.makedirs(fromPath)
    if not os.path.exists(toPath):
        os.makedirs(toPath)
    CopyFile(RepoDir + '/Images/favicon.png', DocDir + '/assets/images/favicon.png')
    
    # Copy repo .md files
    CopyFile(RepoDir + '/index.md', DocDir + '/index.md')
    CopyFile(RepoDir + '/VTKBook.md', DocDir + '/VTKBook.md')
    
    # Copy coverage files
    if not os.path.exists(make_path_name(DocDir + '/Coverage')):
        os.makedirs(make_path_name(DocDir + '/Coverage'))
    
    # Get list of all  examples
    Languages = dict()
    Languages['Cxx'] = '.cxx'
    Languages['Python'] = '.py'
    Languages['Java'] = '.java'
    Languages['CSharp'] = '.cs'
    
    for k in Languages.keys():
        tmp = []
        tmp.append(RepoDir + '/Coverage/' + k + 'VTKClassesNotUsed.md')
        tmp.append(DocDir + '/Coverage/' + k + 'VTKClassesNotUsed.md')
        tmp.append(RepoDir + '/Coverage/' + k + 'VTKClassesUsed.md')
        tmp.append(DocDir + '/Coverage/' + k + 'VTKClassesUsed.md')
        CopyFile(tmp[0], tmp[1])
        CopyFile(tmp[2], tmp[3])
    
    # Copy Instructions files
    if not os.path.exists(make_path_name(DocDir + '/Instructions')):
        os.makedirs(make_path_name(DocDir + '/Instructions'))
    CopyFile(RepoDir + '/Instructions/ForUsers.md', DocDir + '/Instructions/ForUsers.md')
    CopyFile(RepoDir + '/Instructions/ForDevelopers.md', DocDir + '/Instructions/ForDevelopers.md')
    CopyFile(RepoDir + '/Instructions/ForAdministrators.md', DocDir + '/Instructions/ForAdministrators.md')
    CopyFile(RepoDir + '/Instructions/Guidelines.md', DocDir + '/Instructions/Guidelines.md')
    CopyFile(RepoDir + '/Instructions/ConvertingFiguresToExamples.md',
             DocDir + '/Instructions/ConvertingFiguresToExamples.md')
    
    # Copy VTKBook files
    if not os.path.exists(make_path_name(DocDir + '/VTKBook')):
        os.makedirs(make_path_name(DocDir + '/VTKBook'))
    # htmlIdSet = set()
    CreateHtmlIds(RepoDir + '/VTKBook/00Preface.md')
    CreateHtmlIds(RepoDir + '/VTKBook/01Chapter1.md')
    CreateHtmlIds(RepoDir + '/VTKBook/02Chapter2.md')
    CreateHtmlIds(RepoDir + '/VTKBook/03Chapter3.md')
    CreateHtmlIds(RepoDir + '/VTKBook/04Chapter4.md')
    CreateHtmlIds(RepoDir + '/VTKBook/05Chapter5.md')
    CreateHtmlIds(RepoDir + '/VTKBook/06Chapter6.md')
    CreateHtmlIds(RepoDir + '/VTKBook/07Chapter7.md')
    CreateHtmlIds(RepoDir + '/VTKBook/08Chapter8.md')
    CreateHtmlIds(RepoDir + '/VTKBook/09Chapter9.md')
    CreateHtmlIds(RepoDir + '/VTKBook/10Chapter10.md')
    CreateHtmlIds(RepoDir + '/VTKBook/11Chapter11.md')
    CreateHtmlIds(RepoDir + '/VTKBook/12Chapter12.md')
    CreateHtmlIds(RepoDir + '/VTKBook/13Glossary.md')
    
    print('Found', len(htmlIdSet), 'figures with html ids')
    CopyChapterAndAddLinks(RepoDir + '/VTKBook/00Preface.md', DocDir + '/VTKBook/00Preface.md')
    CopyChapterAndAddLinks(RepoDir + '/VTKBook/01Chapter1.md', DocDir + '/VTKBook/01Chapter1.md')
    CopyChapterAndAddLinks(RepoDir + '/VTKBook/02Chapter2.md', DocDir + '/VTKBook/02Chapter2.md')
    CopyChapterAndAddLinks(RepoDir + '/VTKBook/03Chapter3.md', DocDir + '/VTKBook/03Chapter3.md')
    CopyChapterAndAddLinks(RepoDir + '/VTKBook/04Chapter4.md', DocDir + '/VTKBook/04Chapter4.md')
    CopyChapterAndAddLinks(RepoDir + '/VTKBook/05Chapter5.md', DocDir + '/VTKBook/05Chapter5.md')
    CopyChapterAndAddLinks(RepoDir + '/VTKBook/06Chapter6.md', DocDir + '/VTKBook/06Chapter6.md')
    CopyChapterAndAddLinks(RepoDir + '/VTKBook/07Chapter7.md', DocDir + '/VTKBook/07Chapter7.md')
    CopyChapterAndAddLinks(RepoDir + '/VTKBook/08Chapter8.md', DocDir + '/VTKBook/08Chapter8.md')
    CopyChapterAndAddLinks(RepoDir + '/VTKBook/09Chapter9.md', DocDir + '/VTKBook/09Chapter9.md')
    CopyChapterAndAddLinks(RepoDir + '/VTKBook/10Chapter10.md', DocDir + '/VTKBook/10Chapter10.md')
    CopyChapterAndAddLinks(RepoDir + '/VTKBook/11Chapter11.md', DocDir + '/VTKBook/11Chapter11.md')
    CopyChapterAndAddLinks(RepoDir + '/VTKBook/12Chapter12.md', DocDir + '/VTKBook/12Chapter12.md')
    CopyChapterAndAddLinks(RepoDir + '/VTKBook/13Glossary.md', DocDir + '/VTKBook/13Glossary.md')
    
    # Copy VTKBookLaTeX files
    if not os.path.exists(make_path_name(DocDir + '/VTKBookLaTeX')):
        os.makedirs(make_path_name(DocDir + '/VTKBookLaTeX'))
    CopyFile(make_path_name(RepoDir + '/VTKBookLaTeX/VTKTextBook.md'),
             make_path_name(DocDir + '/VTKBookLaTeX/VTKTextBook.md'))
    
    # Scan all Cxx directories and look for extras
    allExtras = set()
    for root, dirs, files in os.walk(RepoDir):
        to_find = RepoDir + '/' + 'Cxx'
        start = root.find(to_find)
        if start < 0:
            continue
        for f in files:
            fileName = os.path.splitext(f)
            if fileName[1] == '.extras':
                ExtrasPath = root + '/' + f
                ExtrasFile = open(ExtrasPath, 'r')
                for line in ExtrasFile:
                    line = line.strip()
                    allExtras.add(line)
                ExtrasFile.close()
    
    for lang, langExt in list(Languages.items()):
        for root, dirs, files in os.walk(RepoDir):
            to_find = os.path.join(RepoDir, lang)
            start = root.find(to_find)
            if start:
                continue
            # Get the part of the file name that comes after RepoDir
            # e.g. if the file name is VTKExamples/Cxx/GeometricObjects/Line,
            # Path will be Cxx/GeometriObjects/Line
            KitName = root[start + 1 + len(to_find):]
            if KitName.find('Boneyard') >= 0:
                continue
            if KitName.find('Broken') >= 0:
                continue
            for f in files:
                otherLanguages = list()
                # skip files that are listed as extras
                if f in allExtras:
                    continue
                if f == 'CMakeLists.txt':
                    continue
                ExampleName = os.path.splitext(f)[0]
                ExampleExt = os.path.splitext(f)[1]
                if ExampleExt != langExt:
                    continue
                # Find examples in other languages
                fp = root + '/' + f
                for lLang, lExt in list(Languages.items()):
                    otherLink = FindOtherGivenLang('', os.path.splitext(fp)[0], lang, lLang, lExt)
                    if otherLink != '':
                        otherLink = re.sub(r'src', r'', otherLink)
                        otherLanguages.append(otherLink)
                #           otherLink = FindOtherGivenLang("", os.path.splitext(fp)[0], lang, "Cxx", ".cxx")
                #            if otherLink != '' :
                #                otherLink = re.sub(r'src',r'', otherLink)
                #                otherLanguages.append(otherLink)
                #            otherLink = FindOtherGivenLang("", os.path.splitext(fp)[0], lang, "Python", ".py")
                #            if otherLink != '' :
                #                otherLink = re.sub(r'src',r'', otherLink)
                #                otherLanguages.append(otherLink)
                #            otherLink = FindOtherGivenLang("", os.path.splitext(fp)[0], lang, "Java", ".java")
                #            if otherLink != '' :
                #                otherLink = re.sub(r'src',r'', otherLink)
                #                otherLanguages.append(otherLink)
                #            otherLink = FindOtherGivenLang("", os.path.splitext(fp)[0], lang, "CSharp", ".cs")
                #            if otherLink != '' :
                #                otherLink = re.sub(r'src',r'', otherLink)
                #                otherLanguages.append(otherLink)
                BaselinePath = os.path.join(RepoDir, 'Testing', 'Baseline', lang, KitName, 'Test', ExampleName + '.png')
                PathName = os.path.join(DocDir, lang, KitName)
                if not os.path.exists(PathName):
                    if PathName != '':
                        os.makedirs(PathName)
                OutputFile = os.path.join(DocDir, lang, KitName, ExampleName + '.md')
                MdFile = open(OutputFile, 'w')
                MdFile.write('[VTKExamples](/)/[' + lang + '](/' + lang + ')/' + KitName + '/' + ExampleName + '\n\n')
    
                if os.path.isfile(BaselinePath):
                    ImgUrl = RepoURL + '/blob/master/src/Testing/Baseline/' + lang + '/' + KitName + '/Test' + ExampleName + '.png?raw=true'
                    # href to open image in new tab
                    MdFile.write('<a href="' + ImgUrl + ' target="_blank">' + '\n')
                    MdFile.write(
                        '<img style="border:2px solid beige;float:center" src="' + ImgUrl + '" width="256" />' + '\n')
                    MdFile.write('</a>' + '\n')
                    MdFile.write('<hr>\n')
                    MdFile.write('\n')
                DescriptionPath = os.path.join(RepoDir, lang, KitName, ExampleName + ".md")
                # Add a description if a .md file exists for the example
                if os.path.isfile(DescriptionPath):
                    DescriptionFile = open(DescriptionPath, 'r')
                    description = DescriptionFile.read()
                    DescriptionFile.close()
                    description = AddDoxygen(description)
                    MdFile.write(description)
                # Add examples from other languages if they exist
                if len(otherLanguages) > 0:
                    seeAlso = '\n!!! Tip "Other Languages"\n'
                    see = '    See '
                    for other in otherLanguages:
                        seeAlso += see + other
                        see = ', '
                    seeAlso += '\n'
                    MdFile.write(seeAlso)
                    MdFile.write('\n')
    
                # Add email contact for questions
                question = '\n!!! question\n    If you have a simple question about this example contact us at <a href=mailto:VTKExamplesProject@gmail.com?subject=' + ExampleName + langExt + '&body=' + 'https://lorensen.github.io/VTKExamples/site/' + lang + '/' + KitName + '/' + ExampleName + '>VTKExamplesProject</a>\n    If your question is more complex and may require extended discussion, please use the [VTK Discourse Forum](https://discourse.vtk.org/)\n'
                MdFile.write(question)
                MdFile.write('\n')
    
                SrcFileName = os.path.join(RepoDir, lang, KitName, ExampleName + langExt)
                with open(SrcFileName, 'r') as SrcFile:
                    src = SrcFile.read()
                hiliteLines = FindLinesWithVTK(SrcFileName)
                MdFile.write('###Code\n')
                MdFile.write('**' + ExampleName + langExt + '**' + '\n')
                if langExt == '.cxx':
                    MdFile.write('``` c++ ' + hiliteLines + '\n')
                    # Get the components used in this example
                    components = GetComponents(ComponentsDict, VTKSrcDir, SrcFileName, src)
                    cxxCount = cxxCount + 1
                elif langExt == '.cs':
                    MdFile.write('```csharp' + hiliteLines + '\n')
                    csCount = csCount + 1
                elif langExt == '.py':
                    MdFile.write('```python' + hiliteLines + '\n')
                    pyCount = pyCount + 1
                elif langExt == '.java':
                    MdFile.write('```java' + hiliteLines + '\n')
                    javaCount = javaCount + 1
                MdFile.write(src)
                MdFile.write('```' + '\n')
    
                # Store the full file names for the example
                if ExampleName not in exampleToFileNames:
                    exampleToFileNames[ExampleName] = set()
                SrcFile = os.path.join(RepoDir, lang, KitName, ExampleName + ExampleExt)
                exampleToFileNames[ExampleName].add(SrcFile)
    
                ExtrasPath = os.path.join(RepoDir, lang, KitName, ExampleName + '.extras')
                ExtraNames = ''
                if os.path.isfile(ExtrasPath):
                    ExtrasFile = open(ExtrasPath, 'r')
                    for line in ExtrasFile:
                        line = line.strip()
                        if line == '':
                            continue
                        ExtraPath = os.path.join(RepoDir, lang, KitName, line)
                        SrcFile = os.path.join(RepoDir, lang, KitName, line)
    
                        exampleToFileNames[ExampleName].add(SrcFile)
                        ExtraFile = open(ExtraPath, 'r')
                        extraCode = ExtraFile.read()
                        ExtraFile.close()
                        WriteCxxCode(MdFile, line, extraCode)
                        extent = os.path.splitext(line)
                        if extent[1] == '.cxx':
                            ExtraNames += ' ' + line
                    ExtrasFile.close()
                CustomCMakePath = os.path.join(RepoDir, lang, KitName, ExampleName + '.cmake')
                if os.path.isfile(CustomCMakePath):
                    CustomCMakeFile = open(CustomCMakePath, 'r')
                    cmake = CustomCMakeFile.read()
                    CustomCMakeFile.close()
                else:
                    if IsQtExample(src):
                        CMakeFile = open(os.path.join(RepoDir, 'Admin', 'VTKQtCMakeLists'), 'r')
                        CMakeContents = CMakeFile.read()
                        CMakeFile.close()
                        # Create component lines
                        Components = ''
                        for component in components:
                            if 'vtk' in component:
                                Components += '\n  ' + component
                            else:
                                Components += '\n  ' + 'vtk' + component
                        # If there are no components found, assume we need then all
                        # This occurs when the source file includes another Cxx file
                        # print('Components: ' + Components)
                        cmake = FillQtCMakeLists(CMakeContents, ExampleName, Components)
                    else:
                        with open(os.path.join(RepoDir, 'Admin', 'VTKCMakeLists'), 'r') as CMakeFile:
                            CMakeContents = CMakeFile.read()
                        # Create component lines
                        Components = ''
                        for component in components:
                            if 'vtk' in component:
                                Components += '\n  ' + component
                            else:
                                Components += '\n  ' + 'vtk' + component
                        # If there are no components found, assume we need then all
                        # This occurs when the source file includes another Cxx file
                        # print('Components: ' + Components)
                        cmake = FillCMakeLists(CMakeContents, ExampleName, ExtraNames, Components)
                if lang == 'Cxx':
                    exampleToCMake[ExampleName] = GetVTKCMakelists(cmake)
                    MdFile.write(cmake)
                MdFile.close()
                codeToPage[ExampleName + langExt] = '/' + lang + '/' + KitName + '/' + ExampleName
    
    # Generate an html page that links each example code file to its Wiki Example page
    indexFile = open(os.path.join(DocDir, 'ExampleCodeToWikiPage.html'), 'w')
    indexFile.write('Navigate to the page that contains the source code of an example<br>')
    indexFile.write('\n')
    sortedByCode = sorted(codeToPage.items())
    for item in sortedByCode:
        indexFile.write("<A HREF=" + RepoURL + "/wikis" + re.sub(" ", "_", item[1]) + ">" + item[0] + "</A>")
        indexFile.write("<A HREF=" + RepoURL + "/blob/master" + re.sub(" ", "_", item[1]) + ".md" + ">" + "(md)" + "</A>")
        indexFile.write("<br>\n")
    indexFile.close()
    
    # Create tarballs for each example
    tmpDir = tempfile.mkdtemp(prefix='VTKTarballs') + '/'
    
    # Create the Tarballs directory in the source tree if not present
    # If it does not exist, assume the tarball repo has not been cloned
    # and we need to ignore tar files
    if not os.path.exists('src/Tarballs'):
        os.makedirs('src/Tarballs')
        ignoreFile = open('src/Tarballs/.gitignore', 'w')
        ignoreFile.write('*,tar\n')
        ignoreFile.close()
    
    # Create tarballs
    # For each example page, create a directory and copy that example's files
    # into the directory
    # If the example has a CMakeLists.txt file, copy that.
    # Also, create a subdir called build. This directory is handy when you want to
    # configure with CMake and build the example.
    for example in exampleToFileNames:
        if example not in exampleToCMake:
            continue
        # Make the directories for the example
        srcDir = tmpDir + example
        # codeFileName = srcDir + '/' + example + '.cxx'
        if not os.path.exists(srcDir):
            os.makedirs(srcDir)
    
            # An example may have multiple source files
            for exampleFileName in exampleToFileNames[example]:
                # Get the file name
                tarFileName = srcDir + '/' + os.path.split(exampleFileName)[1]
                # Copy the code for the example
                shutil.copy(exampleFileName, tarFileName)
                os.utime(tarFileName, (refMtime, refMtime))
    
        # Some examples do not have a CMakeLists.txt file
        if example in exampleToCMake:
            os.makedirs(srcDir + '/build')
            cmakeFileName = srcDir + '/' + 'CMakeLists.txt'
            cmakeFile = open(cmakeFileName, 'w')
            cmakeFile.write(exampleToCMake[example][0])
            cmakeFile.close()
            os.utime(cmakeFileName, (refMtime, refMtime))
    
        # Set the mtimes for the directories containing the example
        # Since the mtime is stored in the tar header for each file and directory,
        # we need a consistent time so that a tar of an unchanged example will be equal
        # to the one in the repo
        os.utime(srcDir, (refMtime, refMtime))
        os.utime(srcDir + '/build', (refMtime, refMtime))
    
        # Now create the tar file for the example
        # The tarballs are stored in the source tree
        tar = tarfile.open('src/Tarballs/' + example + '.tar', 'w')
        tar.add(srcDir, arcname=example)
        tar.close()
    
    os.utime(tmpDir, (0, refMtime))
    # Cleanup the temporary directories
    shutil.rmtree(tmpDir)
    
    # Update the tinyurl cache file if necessary
    if cacheMisses > 0:
        cf = open(CacheFile, 'w')
        for key in CacheDict:
            cf.write(key + ' ' + CacheDict[key] + '\n')
        cf.close()
    
    # Rewrite the components cache file if necessary
    if componentsCacheMisses > 0:
        cf = open(ComponentsCacheFile, 'w')
        for key, contents in list(ComponentsDict.items()):
            if os.path.exists(key):
                # add the vtk prefix to the component to support older versions of vtk
                cf.write(key + ' ' + contents + '\n')
        cf.close()
    
    # Report stats
    stats = list()
    stats.append('ScrapeRepo Summary')
    stats.append('    C++ examples: ' + str(cxxCount))
    stats.append('    CSharp examples: ' + str(csCount))
    stats.append('    Python examples: ' + str(pyCount))
    stats.append('    Java examples: ' + str(javaCount))
    stats.append('    Total examples: ' + str(cxxCount + csCount + pyCount + javaCount))
    stats.append('    Doxygen added: ' + str(doxyCount))
    stats.append('    Thumbnails added: ' + str(thumbCount))
    stats.append('    TinyUrl Cache hits: ' + str(cacheHits))
    stats.append('    TinyUrl Cache misses: ' + str(cacheMisses))
    stats.append('    Components Cache hits: ' + str(componentsCacheHits))
    stats.append('    Components Cache misses: ' + str(componentsCacheMisses))
    print('\n'.join(stats))

if __name__ == '__main__':
    main()
