### Description

This example uses vtkKdTreePointLocator to find all points within a given radius. The example generates "n" spheres and finds all the points within the radius of the spheres. The input vtkPolyData's vtkPointData is set the the radius value of each sphere.

The example takes one or two arguments. The first argument specifies the input file that contains vtkPolyData. The second optional argument specifies the number of radii use. If the number is < 6, the vtkSphereSource will be displayed as concentric translucent spheres.

The image was produced with this command:
```
KDTreeFindPointsWithinRadius dragon.ply 10
```
To see the translucent spheres run:
```
KDTreeFindPointsWithinRadius dragon.ply
```

!!! info
    See other locator demos:
    [OctreeFindPointsWithinRadiusDemo](/Cxx/DataStructures/OctreeFindPointsWithinRadiusDemo),
    [StaticLocatorFindPointsWithinRadiusDemo](/Cxx/DataStructures/StaticLocatorFindPointsWithinRadiusDemo),
    [PointLocatorFindPointsWithinRadiusDemo](/Cxx/DataStructures/PointLocatorFindPointsWithinRadiusDemo)
