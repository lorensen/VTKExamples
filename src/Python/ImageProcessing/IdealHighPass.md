### Description
Low-pass and high-pass filtering become trivial in the frequency domain. A portion of the pixels are simply masked or attenuated. This example shows a high pass Butterworth filter that attenuates the frequency domain image with the function  `out(i, j) = 1 / (1 + pow(CutOff/Freq(i,j), 2*Order))`.

The gradual attenuation of the filter is important. The ideal high-pass filter, shown in the same exaample, simply masks a set of pixels in the frequency domain. The abrupt transition causes a ringing effect in the spatial domain.