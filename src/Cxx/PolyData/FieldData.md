### Description
Three types of data can be stored in a vtkPolyData object - PointData, CellData, and FieldData. For PointData, there must be a piece of data associated with each point (e.g. a temperature data array with the temperature at each point). For CellData, there must be a piece of data associated with each cell (e.g. the area of each triangle). For data that does not align with either points or cells, FieldData should be used. This is typically data that describes the dataset as a whole. An example could be the name of the dataset, or the center of mass of the points, etc.

This demo adds general data to a polydata (not at each point or cell). In this example, the center of mass of the data is stored.
