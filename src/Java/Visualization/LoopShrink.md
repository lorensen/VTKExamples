### Description

vtkShrinkFilter object shrinks cells composing an arbitrary data set towards their centroid. 

The centroid of a cell is computed as the average position of the cell points. Shrinking results in disconnecting the cells from one another. The output of this filter is of general dataset type vtkUnstructuredGrid.
