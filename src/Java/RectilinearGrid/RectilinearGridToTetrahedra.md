### Description

vtkRectilinearGridToTetrahedra object forms a mesh of Tetrahedra from a vtkRectilinearGrid. 

The tetrahedra can be 5 per cell, 6 per cell, or a mixture of 5 or 12 per cell. The resulting mesh is consistent, meaning that there are no edge crossings and that each tetrahedron face is shared by two tetrahedra, except those tetrahedra on the boundary. All tetrahedra are right handed.
