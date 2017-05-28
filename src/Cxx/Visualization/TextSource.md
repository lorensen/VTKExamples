### Description
This example displays a 3D polygonal text saying "Hello", using the
9x15 font from [X Windows](http://www.wikipedia.org/wiki/X_Window_System). That is a raster
(pixelized) font, so characters are formed by converting the pixels on
each character into quadrilaterals. vtkVectorText generates
higher quality polygonal representations of text, so it is recommended
instead -- see [VectorText](/Cxx/Visualization/VectorText) for an example of this.
