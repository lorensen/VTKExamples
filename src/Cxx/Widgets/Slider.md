### Description

This example demonstrates how to use a 3D slider widget. Here, the slider controls the resolution of the sphere. The slider is positioned in world coordinates - so if you rotate/translate/scale the scene, the slider will change orientation/position/size. Contrast this with [Slider2D](/Cxx/Widgets/Slider2D) that remains at a fixed location in the window.

If the callback is connected to InteractionEvent, the scene will update whenever the mouse is moved on the slider. This is not ideal if the re-rendering takes significant time as it will make the interaction very choppy. If you want to move the slider and have the scene update when the mouse button is released, connect the callback to EndInteractionEvent instead.

!!! note
    This original source code for this example is [here](https://gitlab.kitware.com/vtk/vtk/blob/395857190c8453508d283958383bc38c9c2999bf/Examples/Widgets/Cxx/Slider.cxx).
