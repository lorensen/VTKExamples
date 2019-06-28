### Description

Generates a cube using vtkCubeSource, then a shrink filter is applied.

vtkShrinkFilter object shrinks cells composing an arbitrary data set towards their centroid. The centroid of a cell is computed as the average position of the cell points. Shrinking results in disconnecting the cells from one another.

!!! seealso
    [TessellatedBoxSource](/Python/GeometricObjects/TessellatedBoxSource) generates multiple quads or triangles per side.
    
!!! info
    See [Figure 5-17](/VTKBook/05Chapter5/#Figure%205-17) in [Chapter 5](/VTKBook/05Chapter5) the [VTK Textbook](/VTKBook/01Chapter1).
