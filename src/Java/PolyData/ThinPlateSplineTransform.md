### Description

vtkThinPlateSplineTransform object describes a nonlinear warp transform defined by a set of source and target landmarks. 

Any point on the mesh close to a source landmark will be moved to a place close to the corresponding target landmark. The points in between are interpolated smoothly using Bookstein's Thin Plate Spline algorithm.
