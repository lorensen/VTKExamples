### Description
An artifact called aliasing occurs when sub-sampling and is often associated with stair-stepping edges. Sampling theory proves that discrete sampled signals with spacing S, completely describe continuous functions composed of frequencies less than S/2. When a signal is sub-sampled, its capacity to hold high frequency information is reduced. However, the high frequency energy does not disappear. It wraps around the frequency spectrum appearing as a low frequency alias artifact. The solution, which eliminates this artifact, is to low-pass filter before sub-sampling.

Low-pass smoothing reduces the high frequency range of an image that would cause aliasing. The same aliasing phenomena occurs when acquiring data. If a signal from an analog source contains high frequencies, saving the analog data in a discrete form requires sub-sampling that will introduce alias artifacts. For this reason, it is common practice to acquire data at high resolutions,then smooth and subsample to reduce the image to a manageable size.

This example demonstrates aliasing that occurs when a high-frequency signal is sub-sampled. High frequencies appear as low frequency artifacts. The left image is an isosurface of a skull after sub-sampling. The right image used a low-pass filter before sub-sampling to reduce aliasing.

!!! note
    This example uses the [FullHead.mhd](https://github.com/lorensen/VTKExamples/blob/master/src/Testing/Data/FullHead.mhd), [FullHead.raw.gz](https://github.com/lorensen/VTKExamples/blob/master/src/Testing/Data/FullHead.raw.gz) dataset.