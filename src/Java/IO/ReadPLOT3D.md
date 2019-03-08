### Description

vtkMultiBlockPLOT3DReader is a reader object that reads PLOT3D formatted files and generates structured grid(s) on output. 

PLOT3D is a computer graphics program designed to visualize the grids and solutions of computational fluid dynamics.

PLOT3D files consist of a grid file (also known as XYZ file), an optional solution file (also known as a Q file), and an optional function file that contains user created data (currently unsupported). 

The Q file contains solution information as follows: the four parameters free stream mach number (Fsmach), angle of attack (Alpha), Reynolds number (Re), and total integration time (Time). This information is stored in an array called Properties in the FieldData of each output (tuple 0: fsmach, tuple 1: alpha, tuple 2: re, tuple 3: time). In addition, the solution file contains the flow density (scalar), flow momentum (vector), and flow energy (scalar).
