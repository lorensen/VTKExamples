### Description

vtkImageFFT object implements a fast Fourier transform. 

The input can have real or complex data in any components and data types, but the output is always complex doubles with real values in component0, and imaginary values in component1. 

The filter is fastest for images that have power of two sizes. The filter uses a butterfly diagram for each prime factor of the dimension. 

This makes images with prime number dimensions (i.e. 17x17) much slower to compute. Multi dimensional (i.e volumes) FFT's are decomposed so that each axis executes serially.
