### Description
Given a filename, render window and optionally a rgba value, itakes a screen shot from the render window and writes it to a png file.

To use the snippet, click the *Copy to clipboard* at the upper left of the code blocks.

### Implementation
``` python

def WritePNG(fileName, ren_win, rgba = True):
    """
    Write the render window view to a png file.
    :param fileName:
    :param ren_win: The render window.
    :param rgba: Used to det the buffer type.
    :return:
    """
    """
    Save a screenshot.
    :param fileName:
    :param renWin:
    :return:
    """
    windowto_image_filter = vtk.vtkWindowToImageFilter()
    windowto_image_filter.SetInput(ren_win)
    windowto_image_filter.SetScale(1)  # image quality
    if rgba:
        windowto_image_filter.SetInputBufferTypeToRGBA()
    else:
        windowto_image_filter.SetInputBufferTypeToRGB()
    # Read from the front buffer.
        windowto_image_filter.ReadFrontBufferOff()
        windowto_image_filter.Update()

    writer = vtk.vtkPNGWriter()
    writer.SetFileName(fileName)
    writer.SetInputConnection(windowto_image_filter.GetOutputPort())
    writer.Write()


```
