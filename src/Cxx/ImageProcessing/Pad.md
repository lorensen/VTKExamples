### Description
An important point about the discrete Fourier transform is that it treats the image as a periodic function. This means the pixels on the right border are adjacent to pixels on the left border. Since there is usually no physical relationship between these pixels, the artificial horizontal and vertical edges can distort the frequency spectrum and subsequent processing. To reduce these artifacts, the original image can be multiplied by a window function that becomes zero at the borders.

Another approach removes these artificial edges by smoothing only along the borders.

In both of these approaches, a portion of the original image is lost, so only the central portion of an image can be processed. If this is unacceptable, another solution is to double the dimensions of the original image with a mirror-padding filter. The intermediate image is periodic and continuous.

The lower-left image has been padded with a constant (800). On the right, mirror padding has been used to remove artificial edges introduced by borders.
