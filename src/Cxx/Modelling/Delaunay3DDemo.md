### Description
This example creates a tetrahedral mesh from unorganized points. The example uses the vtkDelaunay3D filter. The resulting mesh will be a solid convex hull of the original points. The example takes the points from a XML PolyData file (.vtp) produces the 3D Delaunay tetrahedralization (both with alpha = 0 and a non-zero alpha), and displays the result on the screen.

For alpha != 0 (right window), the tetra are yellow, the lines are blue and the triangles are red.

Alpha can be changed interactively to see its affect on the resulting surface.
