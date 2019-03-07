### Description

vtkBMPReader is a source object that reads Windows BMP files. This includes indexed and 24 bit bitmaps Usually, all BMPs are converted to 24 bit RGB, but BMPs may be output as 8 bit images with a LookupTable if they allow 8 bit BMP flag is set.

BMPReader creates structured point datasets. The dimension of the dataset depends upon the number of files read. Reading a single file results in a 2D image, while reading more than one file results in a 3D volume.
