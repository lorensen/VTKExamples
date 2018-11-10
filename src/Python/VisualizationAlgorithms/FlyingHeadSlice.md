### Description

This example generates 2D contour lines on one CT slice through the head. The contours correspond to density values of the tissues and are colored according to density value.

This example is a modification of [HeadSlice](https://lorensen.github.io/VTKExamples/site/Python/VisualizationAlgorithms/HeadSlice/) using [vtkFlyingEdges2D](https://www.vtk.org/doc/nightly/html/classvtkFlyingEdges2D.html) for contouring. However there is an option to use [vtkContourFilter](https://www.vtk.org/doc/nightly/html/classvtkContourFilter.html) instead.

!!! info
    See [Figure 6-11a](/VTKBook/06Chapter6/#Figure%206-11a) in [Chapter 6](/VTKBook/06Chapter6) of the [VTK Textbook](/VTKBook/01Chapter1/).
