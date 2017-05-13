[VTKExamples](Home)/[Tcl](Tcl)/GeometricObjects/Cube

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/GeometricObjects/TestCube.png" width="256" />

**Cube.tcl**
```tcl
package require vtk

vtkUnstructuredGridWriter writer

#Generate a synthetic cube
vtkCubeSource cube
cube SetCenter 0.0 0.0 0.0
cube SetXLength 0.5
cube SetYLength 0.5
cube SetZLength 0.5
cube Update

vtkDelaunay3D cubeMesh
cubeMesh SetInput [ cube GetOutput ]
cubeMesh Update

#Write unstructured grid file
writer SetInput [ cubeMesh GetOutput ]
set filename "cube.vtu"
writer SetFileName $filename
writer Update
```
