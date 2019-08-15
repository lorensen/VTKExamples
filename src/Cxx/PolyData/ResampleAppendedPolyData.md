### Description

The example populates a level terrain with randomly positioned and scaled objects selected from vtkPlatonicSolidSource.

The example proceeds as follows:

1. Create a terrain using vtkPlaneSource.
2. Generate objects using vtkPlatonicSolidSource, randomly selecting the type of solid.
3. Randomly scale and place the object using [std::random](http://www.cplusplus.com/reference/random/).
4. Use vtkAppendPolyDatato to append the object to the terrain and other objects.
5. Create a higher or lower resolution terrain.
6. For each point in the new terrain, create a long line, through the point.
7. Use vtkCellLocator::IntersectWithLine to find the intersection of the line and use its z value as the new terrain height.
8. Display original and resampled terrain in side-by-side viewports.

!!! note
    The example was motivated on [this question](https://discourse.vtk.org/t/how-to-probe-a-polygonal-mesh-on-a-polydata/1323)  on [VTK's Discourse](https://discourse.vtk.org/).
 LocalWords:  Creata
