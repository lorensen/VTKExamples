### Description
This example displays a vtkUnstructuredGrid that contains eleven linear cells. We use a number of techniques to visualize the cells.

1. vtkUnstructuredGridReader reads the file [VTKCellTypes.vtk](https://raw.githubusercontent.com/lorensen/VTKExamples/master/src/Testing/Data/VTKCellTypes.vtk).
2. vtkExtractEdges extracts the edges of the 2 and 3 dimensional cells. vtkTubeFilter wraps each edge with tubes.
3. vtkGlyph3DMapper displays each point as a vtkSphere.
4. vtkShrinkFilter highlights the cell faces by pulling them in towards their centroid.
5. vtkLabeledDataMapper shows the point ids.
6. vtkProperty::EdgeVisibilityOn() shows the edges of the cells after shrinking.
7. vtkCellData colors each cell with a different color.

The example also shows how to add a vtkCategoryLegend to a visualization. The vtkCategoryLegend has a vtkLookupTable that **must** be Indexed for categorical data. Since the vtkDataSetMapper for the geometry uses the lookup table to color each cell, we use vtkLookupTable::DeepCopy to copy the input vtkLookupTable and apply vtkLookupTable::IndexedLookupOn().

The [sample file](https://raw.githubusercontent.com/lorensen/VTKExamples/master/src/Testing/Data/VTKCellTypes.vtk) is taken from the [VTKFileFormats](/VTKFileFormats#legacy-file-examples) document.
