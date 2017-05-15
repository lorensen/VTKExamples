### Description
When a cube is created, it has 24 vertices (4 for each face). This is done because 
the normal at each face is very different. Often we would want a cube to only have 8 vertices. The vtkCleanPolyData filter removes coincident points, resulting in the cube we would expect.
