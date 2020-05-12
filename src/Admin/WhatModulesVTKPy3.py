#!/usr/bin/env python

import os
import re
import sys

def get_program_parameters():
    import argparse
    description = 'Generate a FindPackage(VTK COMPONENTS) that lists all modules referenced by a set of files.'
    epilogue = '''
For example:
  Running from the VTK source,
    ./Utilities/Maintenance/WhatModulesVTK.py . Filters/Modeling/Testing/Cxx/TestRotationalExtrusion.cxx
  Produces
    All modules referenced in the files:
    find_package(VTK COMPONENTS
      vtkCommonCore
      vtkFiltersCore
      vtkFiltersModeling
      vtkFiltersSources
      vtkInteractionStyle
      vtkRenderingContextOpenGL2
      vtkRenderingCore
      vtkRenderingFreeType
      vtkRenderingGL2PSOpenGL2
      vtkRenderingOpenGL2
      vtkTestingCore
      vtkTestingRendering
    )
    Your application code includes 12 of 216 vtk modules.
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('-p', '--path', help='The path to the VTK source tree.')
    parser.add_argument('-s', '--source', nargs='+', help='The path to the application file or folder.')
    args = parser.parse_args()
    return args.path, args.source

def IncludesToPaths(path):
    """
    Build a dict that maps include files to paths.
    """
    includeToPath = dict()
    prog = re.compile(r"((?:vtk|QVTK).*\.h)")
    for root, dirs, files in os.walk(path):
        for f in files:
            if prog.match(f):
                includeFile = prog.findall(f)[0]
                includeToPath[includeFile] = root
    return includeToPath


def FindModules(path):
    """
    Build a dict that maps paths to modules.
    """
    pathToModule = dict()
    fileProg = re.compile(r"vtk\.module$")
    for root, dirs, files in os.walk(path):
        for f in files:
            if fileProg.match(f):
                with open(os.path.join(root, f), "r") as fid:
                    contents = fid.read()
                args = contents.split()
                try:
                    idx = args.index('NAME')
                except ValueError:
                    raise RuntimeError('%s is missing a NAME field' % os.path.join(root, f))
                pathToModule[root] = args[idx + 1]
    return pathToModule


def FindIncludes(path):
    """
    Build a set that contains vtk includes.
    """
    includes = set()
    includeProg = re.compile(r"((?:vtk|QVTK).*\.h)")
    with open(path, "r") as fid:
        contents = fid.read()
    incs = includeProg.findall(contents)
    includes.update(incs)
    return includes


def FindModuleFiles(path):
    """
    Get a list of module files in the VTK directory.
    """
    moduleFiles = [os.path.join(root, name)
                   for root, dirs, files in os.walk(path)
                   for name in files
                   if name == "vtk.module"]
    return moduleFiles


def MakeFindPackage(modules):
    """
    Make a useful find_package command.
    """
    # Print a useful cmake command
    res = "find_package(VTK COMPONENTS\n"
    for module in sorted(modules):
        res += "  " + module.replace('VTK::', 'vtk') + "\n"
    res += ")"
    return res


def main():
    vtkSourceDir, sourceFiles = get_program_parameters()
    # Generate dict's for mapping includes to modules
    includesToPaths = IncludesToPaths(vtkSourceDir + "/")
    pathsToModules = FindModules(vtkSourceDir + "/")

    # Test to see if VTK source is provided
    if len(pathsToModules) == 0:
        raise IOError(vtkSourceDir + \
                      " is not a VTK source directory. It does not contain any vtk.module files.")

    # Parse the module files making a dictionary of each module and its
    # dependencies or what it implements.
    # moduleFiles = FindModuleFiles(vtkSourceDir + "/")

    # Build a set of includes for all command line files
    allIncludes = set()
    for f in sourceFiles:
        if os.path.isfile(f):
            allIncludes.update(FindIncludes(f))
        else:
            # We have a folder so look through all the files.
            for path, dirs, files in os.walk(f):
                for fn in files:
                    allIncludes.update(FindIncludes(os.path.join(path, fn)))
    if len(allIncludes) == 0:
        return

    # Build a set that contains all modules referenced in command line files
    optionalModules = set()
    allModules = set()
    for inc in allIncludes:
        if inc in includesToPaths:
            module = includesToPaths[inc]
            if module in pathsToModules:
                allModules.add(pathsToModules[includesToPaths[inc]])

    if "VTK::RenderingCore" in allModules:
        allModules.add("VTK::RenderingOpenGL2")
        allModules.add("VTK::InteractionStyle")
        allModules.add("VTK::RenderingFreeType")
        allModules.add("VTK::RenderingGL2PSOpenGL2")
        allModules.add("VTK::RenderingContextOpenGL2")
    if "VTK::DomainsChemistry" in allModules:
        allModules.add("VTK::DomainsChemistryOpenGL2")
    if "VTK::RenderingVolume" in allModules:
        allModules.add("VTK::RenderingVolumeOpenGL2")
    if "VTK::RenderingContext2D" in allModules:
        allModules.add("VTK::RenderingContextOpenGL2")
    if "VTK::IOExport" in allModules:
        allModules.add("VTK::RenderingContextOpenGL2")
        allModules.add("VTK::IOExportOpenGL2")
        allModules.add("VTK::IOExportPDF")
        allModules.add("VTK::RenderingContextOpenGL2")
    optionalModules.add("VTK::TestingRendering")

    modules = {'All modules referenced in the files:': allModules,
               }
    for k, v in modules.items():
        print(k)
        print(MakeFindPackage(v))
        print("Your application code includes " + str(len(v)) + \
              " of " + str(len(pathsToModules)) + " vtk modules.")


if __name__ == '__main__':
    # if len(sys.argv) < 3:
    #     displayHelp()
    #     exit(0)
    main()
