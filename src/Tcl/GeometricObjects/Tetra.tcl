package require vtk

vtkUnstructuredGridWriter writer

#Generate a synthetic Tetrahedron
vtkPoints points
points SetDataTypeToDouble
points InsertNextPoint 0 -1 -1
points InsertNextPoint -1 -1 1
points InsertNextPoint 1 1 1
points InsertNextPoint 0 1 0
		
vtkTetra tetra
[tetra GetPointIds] SetId 0 0
[tetra GetPointIds] SetId 1 1
[tetra GetPointIds] SetId 2 2
[tetra GetPointIds] SetId 3 3

set cellType [tetra GetCellType]
vtkUnstructuredGrid tetraGrid
tetraGrid SetPoints points
tetraGrid InsertNextCell $cellType [tetra GetPointIds]

vtkDelaunay3D tetraMesh
tetraMesh SetInput tetraGrid
tetraMesh Update

#Write unstructured grid file
set filename "tetra.vtu"
writer SetInput [ tetraMesh GetOutput ]
writer SetFileName $filename
writer Update
