### Description

* Contributed by: Lars Friedrich

This is a C++-port of the VTK example '''DepthSort.py''' found in
[VTKSourceDir/Examples/VisualizationAlgorithms/Python(https://gitlab.kitware.com/vtk/vtk/blob/master/Examples/VisualizationAlgorithms/Python/DepthSort.py). It
was slightly modified. It generates 5 spheres with configurable PHI
and THETA resolution. The spheres overlap. Therefore, correct blending
and visualization in general requires depth sorting of the underlying
polygons which will not happen when simply using a poly data
mapper. Depth sorting can be achieved by connecting a
*vtkDepthSortPolyData* filter to the mapper instead of the pure poly
data.

### Program Usage

```
Usage: ./DepthSortPolyData DepthSortFlag ThetaResolution  PhiResolution ScalarVisibilityFlag*

DepthSortFlag ... activate/deactivate the depth sorting algorithm

ThetaResolution ... THETA resolution for the spheres

PhiResolution ... PHI resolution for the spheres

ScalarVisibilityFlag ... show/hide the found depth values as scalars
```

*Example calls:*

```
./DepthSortPolyData 0 100 100 0
... will render the spheres 'as usual' (without depth sorting); in general you will be confronted with situations (specific view directions) where you cannot determine whether a small sphere is behind or in front of the big center sphere
```
```
./DepthSortPolyData 1 100 100 0
... will render the spheres using depth sorting; the sphere depth order should now be visually traceable
```
```
./DepthSortPolyData 1 100 100 1
... will render the spheres using depth sorting; the depth values are mapped to the spheres and renderd on the surfaces
```
Using higher PHI/THETA resolutions shows how depth sorting reduces the frame rate.
