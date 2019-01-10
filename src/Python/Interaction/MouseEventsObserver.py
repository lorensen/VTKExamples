#!/usr/bin/env python
from __future__ import print_function

import vtk


def main():
    colors = vtk.vtkNamedColors()


    source = vtk.vtkSphereSource()
    source.SetCenter(0, 0, 0)
    source.SetRadius(1)
    source.Update()

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(source.GetOutputPort())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetColor(colors.GetColor3d('AliceBlue'))

    renderer = vtk.vtkRenderer()
    renderer.SetBackground(colors.GetColor3d('Silver'))
    renderer.AddActor(actor)

    renwin = vtk.vtkRenderWindow()
    renwin.AddRenderer(renderer)

    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetInteractorStyle(vtk.vtkInteractorStyleTrackballCamera())
    interactor.SetRenderWindow(renwin)


    def DummyFunc1(obj, ev):
        print("Before Event")


    def DummyFunc2(obj, ev):
        print("After Event")

    # Print interator gives you a list of registered observers of the current
    # interactor style
    # print(interactor)


    # adding priorities allow to control the order of observer execution
    # (highest value first! if equal the first added observer is called first)
    interactor.RemoveObservers('LeftButtonPressEvent')
    interactor.AddObserver('LeftButtonPressEvent', DummyFunc1, 1.0)
    interactor.AddObserver('LeftButtonPressEvent', DummyFunc2, -1.0)
    interactor.Initialize()
    renwin.Render()
    WriteImage('TestMouseEventsObserver', renwin, rgba=False)
    interactor.Start()

def WriteImage(fileName, renWin, rgba=True):
    """
    Write the render window view to an image file.

    Image types supported are:
     BMP, JPEG, PNM, PNG, PostScript, TIFF.
    The default parameters are used for all writers, change as needed.

    :param fileName: The file name, if no extension then PNG is assumed.
    :param renWin: The render window.
    :param rgba: Used to set the buffer type.
    :return:
    """

    import os

    if fileName:
        # Select the writer to use.
        path, ext = os.path.splitext(fileName)
        ext = ext.lower()
        if not ext:
            ext = '.png'
            fileName = fileName + ext
        if ext == '.bmp':
            writer = vtk.vtkBMPWriter()
        elif ext == '.jpg':
            writer = vtk.vtkJPEGWriter()
        elif ext == '.pnm':
            writer = vtk.vtkPNMWriter()
        elif ext == '.ps':
            if rgba:
                rgba = False
            writer = vtk.vtkPostScriptWriter()
        elif ext == '.tiff':
            writer = vtk.vtkTIFFWriter()
        else:
            writer = vtk.vtkPNGWriter()

        windowto_image_filter = vtk.vtkWindowToImageFilter()
        windowto_image_filter.SetInput(renWin)
        windowto_image_filter.SetScale(1)  # image quality
        if rgba:
            windowto_image_filter.SetInputBufferTypeToRGBA()
        else:
            windowto_image_filter.SetInputBufferTypeToRGB()
            # Read from the front buffer.
            windowto_image_filter.ReadFrontBufferOff()
            windowto_image_filter.Update()

        writer.SetFileName(fileName)
        writer.SetInputConnection(windowto_image_filter.GetOutputPort())
        writer.Write()
    else:
        raise RuntimeError('Need a filename.')
if __name__ == '__main__':
    main()
