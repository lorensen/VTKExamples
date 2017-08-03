### Description
This example creates two spheres and combines them together into one polydata. The vtkPolyDataConnectivityFilter is used to find the two spheres as they are separate regions (disconnected). If region 0 is selected, the small sphere is extracted. If region 1 is selected, the large sphere is extracted.

The original vtkPolyData is red, on top. The extracted region is yellow, on the bottom.

!!! note
    Contrast this with [PolyDataConnectivityFilter_LargestRegion](/Cxx/PolyData/PolyDataConnectivityFilter_LargestRegion).

!!! note
    Contributed by: Jinyoung Hwang
