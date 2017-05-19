### Description
The idea of this example is to navigate levels of a uniform spatial tree (vtkPointLocator) using a slider. 

!!! note
    It is not desirable to have PointsPerBucket set "too small". This is because at some point, refining a bucket will result in each cell in that bucket to also be in the bucket's children.  This only wastes memory and computation.  The value that is "too small" is dependent on the grid but in general a value between 10 and 100 should work well (the default value is 25).
