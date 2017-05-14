### Description
The perspective transform automatically appends the "homogeneous 1" to the point before it is multiplied by the matrix. It then divides the first 3 coordinates of the result by the 4th coordinate of the result. For comparison, the standard projection (vtkTransform) is also performed with the same matrix and the same point. Note that the results are much different.
