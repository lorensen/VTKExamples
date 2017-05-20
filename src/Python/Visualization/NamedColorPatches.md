### Description
This example shows how to produce a HTML page called [VTKNamedColorPatches](http://htmlpreview.github.com/?https://github.com/lorensen/VTKExamples/blob/master/src/Python/Visualization/VTKNamedColorPatches.html) showing the available
colors in [vtkNamedColors](http://www.vtk.org/doc/nightly/html/classvtkNamedColors.html).

It also shows how to select the text color based on luminance.
In this case Digital CCIR601 is used which gives less weight to the
red and blue components of a color.

In the class HTMLTableMaker there are four methods that generate the HTML tables:

 * MakeWebColorPage() -- Makes a page of just the colors and names known to Web Browsers.
 * MakeVTKColorPage() -- Makes a page of colors and names corresponding to those in vtkColors.txt.
 * MakeSynonymColorPage() -- Makes a page of color names and their synonyms.
 * MakeCombinedColorPage() -- Makes an indexed page with all the colors and names in the class [vtkNamedColors](http://www.vtk.org/doc/nightly/html/classvtkNamedColors.html).