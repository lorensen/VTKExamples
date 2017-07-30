### Description
Resize an image using a sinc interpolator. Without command line arguments, the example resizes a synthetic image. An image file can be passed on the command lines. The new dimensions can also be passed as well as an integer specifying the window for sinc interpolator. See vtkImageSincInterpolator for details. A -1 turns off interpolation.

Several window functions are provided. See [this article](https://en.wikipedia.org/wiki/Window_function) for a description og window functions.

vtkImageResize maintains the physical size of the image.

!!! note
    This example was inspired by a question asked by *Qiang Wang*.

!!! seealso
    The paper ["Some windows with very good sidelobe behavior"](http://mwlab.pmo.ac.cn/~lzh/about_work/dspfftpaper/Some_Windows_with_Very_Good_Sidelobe_Behavior.pdf) describes the windows implemented in vtkImageSincInterpolator.