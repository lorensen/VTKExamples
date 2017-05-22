### Description

This example demonstrates how to use a slider that is drawn in window coordinates - so if you move the scene the slider is not affected. Contrast this with the [3D slider widget](/Cxx/Widgets/Slider) that remains at a fixed location in the world coordinates.

If the callback is connected to *InteractionEvent*, the scene will update immediately.
This is not ideal if the re-rendering takes significant time as it will make the interaction very choppy.
If you want to move the slider and have the scene update when the mouse button is released, connect the callback to *EndInteractionEvent* instead.
