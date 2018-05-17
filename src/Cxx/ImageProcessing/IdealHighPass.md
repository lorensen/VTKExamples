### Description
Low-pass and high-pass filtering become trivial in the frequency domain. A portion of the pixels are simply masked or attenuated. This example shows a high pass Butterworth filter that attenuates the frequency domain image with the function  `out(i, j) = 1 / (1 + pow(CutOff/Freq(i,j), 2*Order))`.

The gradual attenuation of the filter is important. The ideal high-pass filter, shown in the same exaample, simply masks a set of pixels in the frequency domain. The abrupt transition causes a ringing effect in the spatial domain.

!!! info
    See [this figure](/VTKBook/10Chapter10/#Figure%2010-11) in [Chapter 10](/VTKBook/10Chapter10) the [VTK Textbook](/VTKBook/01Chapter1).

