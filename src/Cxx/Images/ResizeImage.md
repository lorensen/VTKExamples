### Description
Resize an image using a sinc interpolator. Without command line arguments, the example resize a synthetic image. A jpeg file can be passed on the command lines. The new dimensions can also be passed as well as an integer specifying the sinc interpolator. See {{VTKDoxygenURL|vtkImageSincInterpolator}} for details. A -1 turns off interpolation.

ImageResize maintains the physical size of the image.

!!! note
    This example was inspired by a question asked by *Qiang Wang*.
