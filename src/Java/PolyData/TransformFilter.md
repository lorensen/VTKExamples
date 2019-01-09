### Description 

vtkTransformFilter is an object to transform point coordinates, and associated point normals and vectors, as well as cell normals and vectors.

Transformed data array will be stored in a float array or a double array. Other point and cel data are passed through the filter, unless TransformAllInputVectors is set to true, in this case all other 3 components arrays from point and cell data will be transformed as well.
