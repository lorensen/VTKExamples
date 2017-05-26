### Description
There are two ways to convert images to greyscale:

* vtkImageLuminance uses the [luminance equation](http://www.wikipedia.org/wiki/Luma_(video)) for properly weighting the R, G, and B components;

* vtkImageMagnitude does a simple sum-of-squares computation of the components (i.e. the [Euclidean norm](http://www.wikipedia.org/wiki/Magnitude_(mathematics)#Euclidean_vector_space) -- not the [quadratic mean](http://www.wikipedia.org/wiki/Root_mean_square)!), and is meant for vector data.

For an example of usage of the vtkImageMagnitude filter, see [ImageMagnitude](/Cxx/Images/ImageMagnitude).
