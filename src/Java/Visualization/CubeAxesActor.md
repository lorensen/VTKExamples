### Description

vtkCubeAxesActor object is a composite actor that draws axes of the bounding box of an input dataset. 

The axes include labels and titles for the x-y-z axes. The algorithm selects which axes to draw based on the user-defined 'fly' mode. (STATIC is default). 'STATIC' constructs axes from all edges of the bounding box. 'CLOSEST_TRIAD' consists of the three axes x-y-z forming a triad that lies closest to the specified camera. 'FURTHEST_TRIAD' consists of the three axes x-y-z forming a triad that lies furthest from the specified camera. 'OUTER_EDGES' is constructed from edges that are on the "exterior" of the bounding box, exterior as determined from examining outer edges of the bounding box in projection (display) space.
