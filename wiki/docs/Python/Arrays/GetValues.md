[VTKExamples](Home)/[Python](Python)/Arrays/GetValues

### Description
Seems to work, but segfaults at the end? 

Tested: No segfault in Python 2.7 and Python 3.4.

**GetValues.py**
```python
from __future__ import print_function
import vtk
from vtk import *

#setup sphere
sphereSource = vtk.vtkSphereSource()
sphereSource.Update()

polydata = vtk.vtkPolyData()
polydata.ShallowCopy(sphereSource.GetOutput())

normals = polydata.GetPointData().GetNormals();
normal0 = normals.GetTuple3(0);

print("Normal0: {:3.1f} {:3.1f} {:3.1f}".format(normal0[0], normal0[1], normal0[2]))
```
