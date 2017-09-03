### Description

vtkVRMLImporter imports multiple vtkActor models. Sometimes the vtkPolyData require modifications. For example [the data in this example](http://alexei.nfshost.com/3d/grasshop.wrl) does not have normals. The example uses vtkActorCollection to walk each model's vtkPolyData and inserts a vtkPolyDataNormals if the normals do not exist.

!!! bug
    vtkVRMLImporter files use a shininess between 0 and 1, while vtk's vtkProperty has a specular power between 0 and 128. The example corrects this if the specular power is <= 1.0.

!!! bug
    vtkVRMLImporter incorrectly creates a vtkLookupTable for colorPerVertex. This example converts the vtkLookupTable to vtkPointData.

!!! tip
    [The Virtual Insect](http://alexei.nfshost.com/3d/virtual.html) website has lots of cool wrl models of insects.
