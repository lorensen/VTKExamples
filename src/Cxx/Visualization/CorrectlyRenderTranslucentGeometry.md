### Description

* Contributed by: Lars Friedrich

Correctly rendering translucent geometry with OpenGL-functionality in
the background (as in the case of VTK) requires non-intersecting
polygons and depth-sorted traversal. In general these requirements are
not satisfied as the inherent order of scene traversal is
object-based. Using a method, namely depth peeling, presented by
NVIDIA in 2001 [Interactive Order-Independent Transparency](http://www.nvidia.com/attach/6545), shadow
mapping (multi-pass rendering) in conjunction with alpha test can be
consulted to achieve correct blending of the rendered objects in the
frame buffer.

VTK implements this feature since November 2006 as described in the
[VTK WIKI](http://www.vtk.org/Wiki/VTK/Depth_Peeling) (Francois
Bertel). Unfortunately depth peeling has several OpenGL extension,
context and driver requirements (but also runs on Mesa) which restrict
the approach's usage to modern GPUs. Usually this feature slows down
the rendering process depending on the configuration (occlusion ratio
and maximum number of iterative peels).

However if depth peeling is not available on a certain machine, depth
sorting can be accomplished on the CPU using
[DepthSortPolyData](/Cxx/Visualization/DepthSortPolyData). This
is usually much slower than the GPU-implementation and furthermore
brings additional restrictions with it (e.g. poly data must be merged
within one set).

This example program generates a set of intersecting (overlapping)
spheres that have transparency properties. The program automatically
checks whether depth peeling is supported or not. If depth peeling is
not supported, CPU-based depth sorting is used. In addition the
program tries to determine an average frame rate for the scene.

The following image shows the spheres arrangement (and view position)
and compares the different render modes: no special translucency
treatment, CPU depth sorting and GPU depth peeling.

###Program Usage
./CorrectlyRenderTranslucentGeometry Theta Phi MaximumPeels OcclusionRatio ForceDepthSortingFlag DoNotUseAnyDepthRelatedAlgorithmFlag

Theta ... spheres' THETA resolution

Phi ... spheres' PHI resolution

MaximumPeels ... maximum number of depth peels (multi-pass rendering) for depth peeling mode

OcclusionRatio ... occlusion ratio for depth peeling mode (0.0 for a perfect rendered image, >0.0 for a non-perfect image which is expected to be slower)

ForceDepthSortingFlag ... force depth sorting even if depth peeling is supported

DoNotUseAnyDepthRelatedAlgorithmFlag ... neither use depth peeling nor depth sorting - just render as usual


***Example calls***:

./CorrectlyRenderTranslucentGeometry 100 100 50 0.1 0 0 ... will render the spheres using depth peeling if available (depth sorting otherwise)

./CorrectlyRenderTranslucentGeometry 100 100 50 0.1 1 0 ... will render the spheres using depth sorting even if depth peeling is available

./CorrectlyRenderTranslucentGeometry 100 100 50 0.1 0 1 ... will render the spheres using neither depth peeling nor depth sorting


***Resultant frame rates show that depth peeling is usually much faster than the CPU-implementation, however, it will slow down the rendering process due to internal multi-pass rendering.***
