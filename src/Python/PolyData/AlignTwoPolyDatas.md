### Description

This example shows how to align two vtkPolyData's. Typically, the two datasets are related. For example, aligning a CT head isosurface with an MRI head isosurface of the same patient. Or two steps in a time series of an evolving surface. These cases usually reside in the same coordinate system, and the initial alignment is "close" to the desired results.

Another case is when the two datasets are from the "same" family of objects — for example, running the example with two types of sharks that exist in different coordinate systems.

The algorithm proceeds as follows:

1. Read the two vtkPolyData's that exist in the example's command line. The first file contains the source vtkPolyData to be aligned with the second file's vtkPolyData called the target. Another naming convention is moving and fixed.

2. Compute a measure of fit of the two original files. We use the recently added vtkHausdorffDistancePointSetFilter to compute the measure. See [Hausdorff Distance](https://en.wikipedia.org/wiki/Hausdorff_distance).

3. Align the bounding boxes of the two datasets. Here we use a vtkOBBTree locator to create oriented bounding boxes. See [Oriented Bounding Boxes](https://en.wikipedia.org/wiki/Minimum_bounding_box). Use the bounding box corner coordinates to create source and target vtkLandmarkTransform's. vtkTransformPolyData uses this transform to create a new source vtkPolyData. Since the orientations of the bounding boxes may differ, the AlignBoundingBoxes function tries ten different rotations. For each rotation, it computes the Hausdorff distance between the target's OBB corners and the transformed source's OBB corners. Finally, transform the original source using the smallest distance.

4. Improve the alignment with vtkIterativeClosestPointTransform with a RigidBody transform. Compute the distance metric again.

5. Using the transform that has the best distance metric, do a final, and display the source and target vtkPolyData's.

!!! info
    The example is run with [Grey_Nurse_Shark.stl](https://github.com/lorensen/VTKExamples/raw/master/src/Testing/Data/thingiverse/Grey_Nurse_Shark.stl) and [shark.ply](https://raw.githubusercontent.com/lorensen/VTKExamples/master/src/Testing/Data/shark.ply)

!!! info
    You may need to orient the target using vtkTransformPolyDataFilter to get a better fit, for example when using  [Grey_Nurse_Shark.stl](https://github.com/lorensen/VTKExamples/raw/master/src/Testing/Data/thingiverse/Grey_Nurse_Shark.stl) and [greatWhite.stl](https://raw.githubusercontent.com/lorensen/VTKExamples/master/src/Testing/Data/greatWhite.stl), uncommenting the two rotations in vtkTransform will provide an excellent alignment.

