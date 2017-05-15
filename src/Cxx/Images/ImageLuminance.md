### Description
There are two ways to convert images to greyscale:
* {{class|vtkImageLuminance}} uses the [(video)|luminance equation]]([wikipedia:Luma) for properly weighting the R, G, and B components;
* {{class|vtkImageMagnitude}} does a simple sum-of-squares computation of the components (i.e. the [(mathematics)#Euclidean vector space|Euclidean norm]] -- not the [[wikipedia:Root mean square|quadratic mean]]([wikipedia:Magnitude)!), and is meant for vector data.

For an example of usage of the vtkImageMagnitude filter, see []([../ImageMagnitude]).
