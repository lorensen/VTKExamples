### Description

Demonstrates how to create a capped sphere.

Firstly a line is created in the x-z plane corresponding to an arc from +z to -z in the +x direction in the x-z plane, the length of the arc is specified in degrees.

Then the line is extended by dropping a perpendicular to the x-axis.

The points generated are then converted to a line and passed through to the vtkRotationalExtrusionFilter to generate the resultant 3D surface.

The parameters are:

- angle - the arc length in degrees default 90° (a hemisphere)
- step -the step size of the arc in degrees, default 1°
- radius - the radius of the arc default 1

Options are provided to:

- Uncap the sphere (**-u, --uncapped**)
- Display the line that was rotationally extruded (**-s, --show_line**)

!!! Note
    The coordinate system for specifying the arc is left-handed with 0° aligned with the positive z-axis, 90° aligned with the positive x-axis.

!!! Note
    You can substitute different parametric equations for x and z in the line generating function to get other shapes.
