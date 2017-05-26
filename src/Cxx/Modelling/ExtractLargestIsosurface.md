### Description
* Contributed by: Jinyoung Hwang

This example reads a structured points dataset stored in a .vtk file and constructs a 3D model using vtkMarchingCubes.
vtkPolyDataConnectivityFilter is used to extract the largest isosurface.

Data is available at:

1. test.vtk: http://web.kaist.ac.kr/~hjy/test.vtk

2. brainweb.img: http://web.kaist.ac.kr/~hjy/brainweb.img

3. brainweb.hdr: http://web.kaist.ac.kr/~hjy/brainweb.hdr

Second and third datasets can be downloaded from [BrainWeb](http://www.bic.mni.mcgill.ca/brainweb/), which is free of charge in use for a research.
"test.vtk" was converted from "brainweb.img" using a program by Erik Vidholm (http://www.cb.uu.se/~erik/vtk/rawToVTK.cpp).

The examples expects 2 or 3 argments:

``` bash
 ExtractLargestIsosurface InputFilename Threshold (ExtractLargest)
```

  if ExtractLargest is omitted or 1, the largest isosurface is extracted

  if ExtractLargest is 0, all of the isosurfaces are extracted

Try

 ExtractLargestIsosurface test.vtk 50 1

and compare the results to

 ExtractLargestIsosurface test.vtk 50 0
