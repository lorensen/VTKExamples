### Description
In this example a mesh is read from a file and then subdivided using linear subdivision.  The SetNumberOfSubdivisions(n) function controls how many times the mesh is subdivided. For each n, the number of triangles will increase by approximately a factor of 4. For example, if n=2, the number of triangles in the resulting mesh will be 16x the number of triangles in the original mesh. 

Different types of subdivisions can be obtained by replacing vtkLinearSubdivisionFilter with either vtkLoopSubdivisionFilter or vtkButterflySubdivisionFilter.
