### Description

vtkConeSource object creates a cone centered at a specified point and pointing in a specified direction. (By default, the center is the origin and the direction is the x-axis.) 

Depending upon the resolution of this object, different representations are created. If resolution=0 a line is created; if resolution=1, a single triangle is created; if resolution=2, two crossed triangles are created. 

For resolution > 2, a 3D cone (with resolution number of sides) is created. 

It also is possible to control whether the bottom of the cone is capped with a (resolution-sided) polygon, and to specify the height and radius of the cone.

The example shows cones with resolutions 0, 1, 2, and 3.

!!! tip "Style"
    This example collects all of the color definition in the beginning of the example. This makes it easier to make changes to the colors without having to search the code.
