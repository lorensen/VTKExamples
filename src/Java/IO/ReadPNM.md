### Description

vtkPNMReader is a source object that reads pnm (portable anymap) files. This includes .pbm (bitmap), .pgm (grayscale), and .ppm (pixmap) files. (Currently this object only reads binary versions of these files.)

PNMReader creates structured point datasets. The dimension of the dataset depends upon the number of files read. Reading a single file results in a 2D image, while reading more than one file results in a 3D volume.
