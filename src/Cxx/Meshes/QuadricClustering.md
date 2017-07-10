### Description
The algorithm used is the one described by Peter Lindstrom in his Siggraph
2000 paper, ["Out-of-Core Simplification of Large Polygonal Models."](https://www.researchgate.net/publication/2915018_Out-of-Core_Simplification_of_Large_Polygonal_Models)  The general approach of the algorithm is to cluster vertices in a uniform binning of space, accumulating the quadric of each triangle (pushed out to  the triangles vertices) within each bin, and then determining an optimal position for a single vertex in a bin by using the accumulated quadric.

!!! seealso
    [QuadricDecimation](/Cxx/Meshes/QuadricDecimation) and [Decimation](/Cxx/Meshes/Decimation).
