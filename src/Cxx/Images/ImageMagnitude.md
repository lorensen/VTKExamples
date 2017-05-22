### Description

There are two ways to convert images to greyscale:
* [vtkImageLuminance](http://www.vtk.org/doc/nightly/html/classvtkImageLuminance.html) uses the [luminance equation](http://www.wikipedia.org/wiki/Luma_(video) for properly weighting the R, G, and B components;
* [vtkImageMagnitude](http://www.vtk.org/doc/nightly/html/classvtkImageMagnitude.html) does a simple sum-of-squares computation of the components (i.e. the [Euclidean norm](http://www.wikipedia.org/wiki/Magnitude_(mathematics)#Euclidean_vector_space) -- not the [quadratic mean](http://www.wikipedia.org/wiki/Root_mean_square), and is meant for vector data.

For an example of usage of the vtkImageLuminance filter, see [ImageLuminance](/Cxx/Images/ImageLuminance).
