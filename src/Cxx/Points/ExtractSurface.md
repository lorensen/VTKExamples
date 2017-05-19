### Description
This example loosely follows the most excellent paper by Curless and Levoy: ["A Volumetric Method for Building Complex Models from Range Images."](https://graphics.stanford.edu/papers/volrange) First it estimates normals from the points, then creates a signed distance field, followed by surface extraction of the zero-level set of the distance field.

The image was created using the [Armadillo dataset](https://github.com/lorensen/VTKExamples/blob/master/src/Testing/Data/Armadillo.ply?raw=true)

!!! warning
    The classes used in this example require vtk 7.1 or later.
