### Description

vtkPlaneSource object creates an m x n array of quadrilaterals arranged as a regular tiling in a plane. 

The plane is defined by specifying an origin point, and then two other points that, together with the origin, define two axes for the plane. These axes do not have to be orthogonal - so you can create a parallelogram. (The axes must not be parallel.) The resolution of the plane (i.e., number of subdivisions) is controlled by the ivars XResolution and YResolution.

By default, the plane is centered at the origin and perpendicular to the z-axis, with width and height of length 1 and resolutions set to 1.
