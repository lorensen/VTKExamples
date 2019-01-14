### Description
This example shows how to produce a HTML page called [VTKNamedColorPatches](http://htmlpreview.github.com/?https://github.com/lorensen/VTKExamples/blob/master/src/Python/Visualization/VTKNamedColorPatches.html) showing the available
colors in vtkNamedColors.

It also shows how to select the text color based on luminance.
In this case Digital CCIR601 is used which gives less weight to the
red and blue components of a color.

This program produces identical output to [NamedColorPatches.py](/Python/Visualization/NamedColorPatches).

The logic is largely similar to that in [NamedColorPatches.py](/Python/Visualization/NamedColorPatches),
however the Python dictionaries and lists defining the various color names by type and the starting and ending conditions are stored as strings and then parsed into the corresponding C++ maps and vectors. This is done in one of the helper classes. Other helper classes extend the STL and provide conversions between RGB colors and HTML color strings.

Three helper classes are also used, these are defined and instantiated in an anonymous namespace in *NamedColorPatches.cxx*.

In the class HTMLTableMaker there are four public methods:

 * MakeWebColorPage() -- Makes a page of just the colors and names known to Web Browsers.
 * MakeVTKColorPage() -- Makes a page of colors and names corresponding to those in vtkColors.txt.
 * MakeSynonymColorPage() -- Makes a page of color names and their synonyms.
 * MakeCombinedColorPage() -- Makes an indexed page with all the colors and names in the class vtkNamedColors.
