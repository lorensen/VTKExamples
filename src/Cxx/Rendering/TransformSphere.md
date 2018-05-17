### Description

This example extends the pipeline of the [ColoredSphere.cxx](/Cxx/Rendering/ColoredSphere) example and shows the effects of type checking on the connectivity of process objects. We add a transform filter (vtkTransformFilter) to nonuniformly scale the sphere in the x-y-z directions. The transform filter only operates on objects with explicit point coordinate representation (i.e., a subclass of vtkPointSet ). However, the elevation filter generates the more general form vtkDataSet as output. Hence we cannot connect the transform filter to the elevation filter. But we can connect the transform filter to the sphere source, and then the elevation filter to the transform filter. (Note: an alternative method is to use vtkCastToConcrete to perform run-time casting.)

!!! info
    See [Figure 4-20](/VTKBook/04Chapter4/#Figure%204-20) in [Chapter 4](/VTKBook/04Chapter4) the [VTK Textbook](/VTKBook/01Chapter1).
