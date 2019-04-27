### Description

Test the VTK Version.

To use the snippet, click the *Copy to clipboard* at the upper left of the code blocks.

### Implementation

``` python

def vtk_check_version(major, minor=0, build=0):
    """
    Check the version number of VTK.

    :param major: Major version
    :param minor: Minor version
    :param build: Build version
    :return: True if the version number is the same or greater
    """
    ver = vtk.vtkVersion()
    if major > ver.GetVTKMajorVersion():
        return True
    elif major == ver.GetVTKMajorVersion() and minor > ver.GetVTKMinorVersion():
        return True
    elif major == ver.GetVTKMajorVersion() and minor == ver.GetVTKMinorVersion() and build >= ver.GetVTKBuildVersion():
        return True
    else:
        return False

```

### Typical usage

``` python

    if vtk_check_version(8, 90):
        print('Version  8.90.00')
        # Do 8.90 and greater specific stuff here.
    else:
        print('Version < 8.90.00')
        # Do older stuff here that changed in 8.90 and greater.

```