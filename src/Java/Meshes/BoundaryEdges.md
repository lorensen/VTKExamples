### Description

vtkFeatureEdges object is a filter to extract special types of edges from input polygonal data.

These edges are either 
1) boundary (used by one polygon) or a line cell
2) non-manifold (used by three or more polygons)
3) feature edges (edges used by two triangles and whose dihedral angle > FeatureAngle) or 
4) manifold edges (edges used by exactly two polygons). 

Edges may also be "colored" (i.e., scalar values assigned) based on edge type. The cell coloring is assigned to the cell data of the extracted edges.
