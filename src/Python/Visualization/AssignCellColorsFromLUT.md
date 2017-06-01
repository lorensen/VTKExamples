### Description
Demonstrates how to assign colors to cells in a vtkPolyData structure using lookup tables.

Two techniques are demonstrated:

1. Using a lookup table of predefined colors.

2. Using a lookup table generated from a color transfer function.
 
The resultant display shows in the left-hand column, the cells in a plane
colored by the two lookup tables and in the right-hand column, the same
polydata that has been read in from a file demonstrating that the structures
are identical.
 
The top row of the display uses the color transfer function to create a
green to tan transition in a diverging color space.
Note that the central square is white indicating the midpoint.

The bottom row of the display uses a lookup table of predefined colors.
