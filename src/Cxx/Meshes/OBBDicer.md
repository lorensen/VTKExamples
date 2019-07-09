### Description
The vtkOBBDicer filter breaks up an input mesh into a number of pieces. The resulting mesh contains scalar point data that can be used to extract the individual pieces with a filter like vtkThresholdFilter. This examples displays the output of vtkOBBDicer with a different color for each piece.

The first argument is a filename for a vtkPolyData reader. If not specified, then a vtkSphereSource generates the vtkPolyData. The second argument is the number of pieces and is optional. The default is 4.

The example was run with these arguments:

```bash
   OBBDicer Armadill0 20
```