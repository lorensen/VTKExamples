### Description

This example visualizes a Lorenz strange attractor by integrating the Lorenz equations in a volume. The number of visits in each voxel is recorded as a scalar function. The surface is extracted via vtkMarchingCubes using a visit value of 50. The number of integration steps is 10 million, in a volume of dimensions 200^3. The surface roughness is caused by the discrete nature of the evaluation function.

!!! info
    See [Figure 6-25](/VTKBook/06Chapter6/#Figure%206-25) in [Chapter 6](/VTKBook/06Chapter6) the [VTK Textbook](/VTKBook/01Chapter1).
