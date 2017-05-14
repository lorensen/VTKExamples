[VTKExamples](/index/)/[Python](/Python)/Arrays/RenameArray

### Description
Works, but segfaults at the end?

**RenameArray.py**
```python
import vtk
from vtk import *

#setup sphere
sphereSource = vtk.vtkSphereSource()
sphereSource.Update()

polydata = vtk.vtkPolyData()
polydata.ShallowCopy(sphereSource.GetOutput())

normals = polydata.GetPointData().GetNormals();
normals.SetName("TestN")

writer = vtk.vtkXMLPolyDataWriter();
writer.SetFileName("Test.vtp");
writer.SetInput(polydata);
writer.Write();
```
