### Description

This example shows how to add user functions to a VTK shader. The example's fragment shader uses an implementation of [Ken Perlin's noise function](https://www.semanticscholar.org/paper/An-image-synthesizer-Perlin/e04d7772b91a83a901408eb0876bbb7814b1d4b5). Perlin received a Technical Achievement Academy Award for his work procedural texture.

The file for the shader code is [here](https://github.com/lorensen/VTKExamples/blob/master/src/Testing/Data/Shaders/PerlinNoise.glsl)..

!!! example "Usage"
    MarbleShader PerlnNoise.glsl
     [polydataFile]
     [veincolor(1,1,1)]
     [veinfreq(10)]
     [veinlevels(2)]
     [warpfreq(1)]
     [warping(.5)]
     [sharpness(8)]

!!! cite
    [Perlin's original Siggraph Paper](Perlin, K. 1985. "An Image Synthesizer." Computer Graphics 19(3)).

!!! cite
    This shader is inspired by Larry Gritz's veined marble shader.

