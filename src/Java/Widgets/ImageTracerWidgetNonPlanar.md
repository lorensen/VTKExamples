### Description

vtkImageTracerWidget object is designed for manually tracing over image data. 

The button actions and key modifiers are as follows for controlling the widget: 

1) Left button click over the image, hold and drag draws a free hand line. 

2) Left button click and release erases the widget line, if it exists, and repositions the first handle. 

3) Middle button click starts a snap drawn line. The line is terminated by clicking the middle button while depressing the ctrl key. 

4) When tracing a continuous or snap drawn line, if the last cursor position is within a specified tolerance to the first handle, the widget line will form a closed loop. 

5) Right button clicking and holding on any handle that is part of a snap drawn line allows handle dragging: existing line segments are updated accordingly. If the path is open and AutoClose is set to On, the path can be closed by repositioning the first and last points over one another. 

6) Ctrl key + right button down on any handle will erase it: existing snap drawn line segments are updated accordingly. If the line was formed by continuous tracing, the line is deleted leaving one handle. 

7) Shift key + right button down on any snap drawn line segment will insert a handle at the cursor position. The line segment is split accordingly.
