### Description

This examples uses vtkCollisionDetectionFilter to find the intersection between a fixed (solid white) and moving (red wireframe) sphere. The animation places the moving spgere some distance from the fixed sphere and moves the moving sphere untikl it contacts the fixed sphere.

Three collision modes are avaiable and can be set as the first argument on the command line.

1. All contacts (0) finds all the contacting cell pairs with two points per collision.
2. First contact (1) quickly find the first contact point.
3. Half contacts (2) finds all the contacting cell pairs with one points per collision.

The animation pauses between each frame. The total animation should be 3 seconds.
