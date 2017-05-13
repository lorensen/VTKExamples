[VTKExamples](/home/)/[Tcl](/Tcl)/GeometricObjects/Sphere

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/GeometricObjects/TestSphere.png?raw=true" width="256" />

**Sphere.tcl**
```tcl
package require vtk

vtkXMLPolyDataWriter writer

#Generate a synthetic sphere
vtkSphereSource sphere
sphere SetThetaResolution 12
sphere SetPhiResolution 12
sphere SetRadius 5.0
sphere Update

#Write polydata file
writer SetInput [sphere GetOutput]
set filename "sphere.vtp"
writer SetFileName $filename
writer Update
```
