### Description
Demonstrates how to apply the decimation filter to get a reduced data size and then the connectivity filter to remove noisy isosurfaces. The data is from the root system of a pine tree.

To count the number of triangles in the polydata we do the following:
#### C++
We use a lambda function
``` c++
auto NumberofTriangles = [](auto *pd)
```
#### Python
We just implement:
``` python
def NumberOfTriangles(pd):
```
within the scope of the calling function.
