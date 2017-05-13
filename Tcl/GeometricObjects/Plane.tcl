package require vtk

vtkXMLPolyDataWriter writer

#Generate a synthetic plane
vtkPlaneSource plane
plane SetCenter 1.0 0.0 0.0
plane SetNormal 1.0 0.0 0.0

set data [ plane GetOutput ]

# Write the polydata file 
writer SetInput $data
writer SetFileName "plane.vtp"
writer Write
