### Description

This example samples a "terrain map" using two approaches.

- Creates an image from the x,y points of the terrain and then uses vtkProbeFilter to interpolate the heights.
- Uses vtkCellLocator to directly interpolate the terrain polydata.

Note that the results differ when the point is not one of the original terrain points. This is because the image has quadrilateral elements and the polydata has triangles. As the resolution of the grid increases, the two results converge.
