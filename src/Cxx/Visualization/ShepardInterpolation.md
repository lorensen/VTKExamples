### Description

Use vtkShephardMethod to interpolate the scalars of a vtkPolyData. The zero-contour of the original and interpoltated scalars are extracted with vtkContourFilter. The original data is shown in red and the interpolated data in shown in yellow.

```
 Usage: SheohardInterpolation polydata [resolution]
      where
        polydata is a polydata file with scalar data.
        resolution is the sampling resoluton, default 100.
```
