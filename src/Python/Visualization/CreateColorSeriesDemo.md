### Description

This example demonstrates how to create a custom vtkColorSeries. The examples produces a vtkLookupTable explicitly. The vtkLookupTable is populated with colors from the vtkColorSeries using GetColorRepeating, since the size of the vtkLookupTable may be larger than the colors in the vtkColorSeries.

A vtkPlaneSource generates the geometry. The vtkCellData is populated with increasing integers starting at 1.

Nine different color series are generated from VTK color names in vtkNamedColors. The first argument of the example is one of "Blue", "Brown", "Red", "Orange", "White", "Grey", "Magenta", "Cyan", and "Yellow".

The colors are added from left to right, row by row, from the bottom left-hand corner of the table.