#!/usr/bin/env python

"""
"""

import vtk


def main():
    # colors = vtk.vtkNamedColors()

    fileName1, fileName2, sliceNumber = get_program_parameters()

    sliceOrder = SliceOrder()

    # Now create the RenderWindow, Renderer and Interactor
    #
    ren1 = vtk.vtkRenderer()
    ren2 = vtk.vtkRenderer()
    ren3 = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren1)
    renWin.AddRenderer(ren2)
    renWin.AddRenderer(ren3)

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    greyReader = vtk.vtkMetaImageReader()
    greyReader.SetFileName(fileName1)
    greyReader.Update()

    greyPadder = vtk.vtkImageConstantPad()
    greyPadder.SetInputConnection(greyReader.GetOutputPort())
    greyPadder.SetOutputWholeExtent(0, 511, 0, 511, sliceNumber, sliceNumber)
    greyPadder.SetConstant(0)

    greyPlane = vtk.vtkPlaneSource()

    greyTransform = vtk.vtkTransformPolyDataFilter()
    greyTransform.SetTransform(sliceOrder["hfsi"])
    greyTransform.SetInputConnection(greyPlane.GetOutputPort())

    greyNormals = vtk.vtkPolyDataNormals()
    greyNormals.SetInputConnection(greyTransform.GetOutputPort())
    greyNormals.FlipNormalsOff()

    wllut = vtk.vtkWindowLevelLookupTable()
    wllut.SetWindow(255)
    wllut.SetLevel(128)
    wllut.SetTableRange(0, 255)
    wllut.Build()

    greyMapper = vtk.vtkPolyDataMapper()
    greyMapper.SetInputConnection(greyPlane.GetOutputPort())

    greyTexture = vtk.vtkTexture()
    greyTexture.SetInputConnection(greyPadder.GetOutputPort())
    greyTexture.SetLookupTable(wllut)
    greyTexture.SetColorModeToMapScalars()
    greyTexture.InterpolateOn()

    greyActor = vtk.vtkActor()
    greyActor.SetMapper(greyMapper)
    greyActor.SetTexture(greyTexture)

    segmentReader = vtk.vtkMetaImageReader()
    segmentReader.SetFileName(fileName2)
    segmentReader.Update()

    segmentPadder = vtk.vtkImageConstantPad()
    segmentPadder.SetInputConnection(segmentReader.GetOutputPort())
    segmentPadder.SetOutputWholeExtent(0, 511, 0, 511, sliceNumber, sliceNumber)
    segmentPadder.SetConstant(0)

    segmentPlane = vtk.vtkPlaneSource()

    segmentTransform = vtk.vtkTransformPolyDataFilter()
    segmentTransform.SetTransform(sliceOrder["hfsi"])
    segmentTransform.SetInputConnection(segmentPlane.GetOutputPort())

    segmentNormals = vtk.vtkPolyDataNormals()
    segmentNormals.SetInputConnection(segmentTransform.GetOutputPort())
    segmentNormals.FlipNormalsOn()

    colorLut = CreateFrogLut()

    segmentMapper = vtk.vtkPolyDataMapper()
    segmentMapper.SetInputConnection(segmentPlane.GetOutputPort())

    segmentTexture = vtk.vtkTexture()
    segmentTexture.SetInputConnection(segmentPadder.GetOutputPort())
    segmentTexture.SetLookupTable(colorLut)
    segmentTexture.SetColorModeToMapScalars()
    segmentTexture.InterpolateOff()

    segmentActor = vtk.vtkActor()
    segmentActor.SetMapper(segmentMapper)
    segmentActor.SetTexture(segmentTexture)

    segmentOverlayActor = vtk.vtkActor()
    segmentOverlayActor.SetMapper(segmentMapper)
    segmentOverlayActor.SetTexture(segmentTexture)

    segmentOverlayActor.GetProperty().SetOpacity(.5)
    ren1.SetBackground(0, 0, 0)
    ren1.SetViewport(0, .5, .5, 1)
    renWin.SetSize(640, 480)
    ren1.AddActor(greyActor)

    ren2.SetBackground(0, 0, 0)
    ren2.SetViewport(.5, .5, 1, 1)
    ren2.AddActor(segmentActor)

    cam1 = vtk.vtkCamera()
    cam1.SetViewUp(0, -1, 0)
    cam1.SetPosition(0, 0, -1)
    ren1.SetActiveCamera(cam1)
    ren1.ResetCamera()
    cam1.SetViewUp(0, -1, 0)
    cam1.SetPosition(0.0554068, -0.0596001, -0.491383)
    cam1.SetFocalPoint(0.0554068, -0.0596001, 0)
    ren1.ResetCameraClippingRange()

    ren3.AddActor(greyActor)
    ren3.AddActor(segmentOverlayActor)
    segmentOverlayActor.SetPosition(0, 0, -.01)

    ren3.SetBackground(0, 0, 0)
    ren3.SetViewport(0, 0, 1, .5)

    ren2.SetActiveCamera(ren1.GetActiveCamera())
    ren3.SetActiveCamera(ren1.GetActiveCamera())

    renWin.Render()
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'Visualization of a frog.'
    epilogue = '''
    Photographic slice of frog (upper left), segmented frog (upper right) and
     composite of photo and segmentation (bottom).
    The purple color represents the stomach and the kidneys are yellow.
    If slice = 39 it matches Figure 12-6 in the VTK Book.
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename1', help='frog.mhd.')
    parser.add_argument('filename2', help='frogtissue.mhd.')
    parser.add_argument('slice_number', default=39, type=int, nargs='?', help='Slice number.')
    args = parser.parse_args()
    return args.filename1, args.filename2, args.slice_number


def CreateFrogLut():
    colors = vtk.vtkNamedColors()

    colorLut = vtk.vtkLookupTable()
    colorLut.SetNumberOfColors(17)
    colorLut.SetTableRange(0, 16)
    colorLut.Build()

    colorLut.SetTableValue(0, 0, 0, 0, 0)
    colorLut.SetTableValue(1, colors.GetColor4d("salmon"))  # blood
    colorLut.SetTableValue(2, colors.GetColor4d("beige"))  # brain
    colorLut.SetTableValue(3, colors.GetColor4d("orange"))  # duodenum
    colorLut.SetTableValue(4, colors.GetColor4d("misty_rose"))  # eye_retina
    colorLut.SetTableValue(5, colors.GetColor4d("white"))  # eye_white
    colorLut.SetTableValue(6, colors.GetColor4d("tomato"))  # heart
    colorLut.SetTableValue(7, colors.GetColor4d("raspberry"))  # ileum
    colorLut.SetTableValue(8, colors.GetColor4d("banana"))  # kidney
    colorLut.SetTableValue(9, colors.GetColor4d("peru"))  # l_intestine
    colorLut.SetTableValue(10, colors.GetColor4d("pink"))  # liver
    colorLut.SetTableValue(11, colors.GetColor4d("powder_blue"))  # lung
    colorLut.SetTableValue(12, colors.GetColor4d("carrot"))  # nerve
    colorLut.SetTableValue(13, colors.GetColor4d("wheat"))  # skeleton
    colorLut.SetTableValue(14, colors.GetColor4d("violet"))  # spleen
    colorLut.SetTableValue(15, colors.GetColor4d("plum"))  # stomach

    return colorLut


def SliceOrder():
    #
    # These transformations permute medical image data to maintain proper orientation
    # regardless of the acquisition order. After applying these transforms with
    # vtkTransformFilter, a view up of 0,-1,0 will result in the body part
    # facing the viewer.
    # NOTE: some transformations have a -1 scale factor for one of the components.
    #       To ensure proper polygon orientation and normal direction, you must
    #       apply the vtkPolyDataNormals filter.
    #
    # Naming:
    # si - superior to inferior (top to bottom)
    # is - inferior to superior (bottom to top)
    # ap - anterior to posterior (front to back)
    # pa - posterior to anterior (back to front)
    # lr - left to right
    # rl - right to left
    #

    sliceOrder = dict()

    siMatrix = [1, 0, 0, 0, 0, 0, 1, 0, 0, -1, 0, 0, 0, 0, 0, 1]
    si = vtk.vtkTransform()
    si.SetMatrix(siMatrix)
    sliceOrder["si"] = si

    isMatrix = [1, 0, 0, 0, 0, 0, -1, 0, 0, -1, 0, 0, 0, 0, 0, 1]
    i_s = vtk.vtkTransform()  # 'is' is a keyword in Python, changed to 'i_s'
    i_s.SetMatrix(isMatrix)
    sliceOrder["is"] = i_s

    ap = vtk.vtkTransform()
    ap.Scale(1, -1, 1)
    sliceOrder["ap"] = ap

    pa = vtk.vtkTransform()
    pa.Scale(1, -1, -1)
    sliceOrder["pa"] = pa

    lrMatrix = [0, 0, -1, 0, 0, -1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1]
    lr = vtk.vtkTransform()
    lr.SetMatrix(lrMatrix)
    sliceOrder["lr"] = lr

    rlMatrix = [0, 0, 1, 0, 0, -1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1]
    rl = vtk.vtkTransform()
    rl.SetMatrix(rlMatrix)
    sliceOrder["rl"] = rl

    #
    # The previous transforms assume radiological views of the slices (viewed from the feet). other
    # modalities such as physical sectioning may view from the head. these transforms modify the original
    # with a 180 rotation about y
    #
    hfMatrix = [-1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1]
    hf = vtk.vtkTransform()
    hf.SetMatrix(hfMatrix)
    sliceOrder["hf"] = hf

    hfsi = vtk.vtkTransform()
    hfsi.Concatenate(hf.GetMatrix())
    hfsi.Concatenate(si.GetMatrix())
    sliceOrder["hfsi"] = hfsi

    hfis = vtk.vtkTransform()
    hfis.Concatenate(hf.GetMatrix())
    hfis.Concatenate(i_s.GetMatrix())
    sliceOrder["hfis"] = hfis

    hfap = vtk.vtkTransform()
    hfap.Concatenate(hf.GetMatrix())
    hfap.Concatenate(ap.GetMatrix())
    sliceOrder["hfap"] = hfap

    hfpa = vtk.vtkTransform()
    hfpa.Concatenate(hf.GetMatrix())
    hfpa.Concatenate(pa.GetMatrix())
    sliceOrder["hfpa"] = hfpa

    hflr = vtk.vtkTransform()
    hflr.Concatenate(hf.GetMatrix())
    hflr.Concatenate(lr.GetMatrix())
    sliceOrder[""] = hflr

    hfrl = vtk.vtkTransform()
    hfrl.Concatenate(hf.GetMatrix())
    hfrl.Concatenate(rl.GetMatrix())
    sliceOrder["hfrl"] = hfrl

    return sliceOrder


if __name__ == '__main__':
    main()
