### Description
This example creates a volume (convex hull-ish) out of a mesh object. It then uses FindCell (which determines if a point is inside of a cell) to determine if a point is inside of any of the 3D cells created by Delaunay3D or not. This could potentially lead to false positives - that is, points that are outside the mesh but inside the convex hull.
