### Description
This example generates a set of points aligned with an XY grid with random heights (z values). The Delaunay2D filter "magically" knows how to triangulate this type of point set because it projects the points by default onto the XY axis and then performs a 2D Delaunay triangulation. The result is a mesh on the input points.
