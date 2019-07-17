### Description

This example adds interaction to [FireFlow](/Cxx/VisualizationAlgorithms/FireFlow).

The example uses vtkSliderWidget's to manipulate the center of the vtkPointSource that provides seed for the streamlines. As the X, Y, or Z center corrdiantes change, the streamlines are changed. The range of the x, y, and z coordinates are limited to the bounds of the solution dataset. There is a built in delay of 500 milliseconds to make the animation between selections consistent.

[Watch this video](https://www.youtube.com/watch?v=qWjAbxzDhWE&feature=youtu.be) showing the interactive movement o the seeding sphere.

!!! cite
    The solution and geometry data is from the [Mayavi ](https://docs.enthought.com/mayavi/mayavi/) project. Mayavi is a python application that provides an easy to use interface to many vtk filters. Both a command-line and GUI interface are provided. If you use the Mayavi data or the Mayavi application, please use the following citation in any published work:
     **Ramachandran, P. and Varoquaux, G., `Mayavi: 3D Visualization of Scientific Data` IEEE Computing in Science & Engineering, 13 (2), pp. 40-51 (2011).**

 LocalWords:  corrdiantes
