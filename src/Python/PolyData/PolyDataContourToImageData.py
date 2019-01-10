import math

import vtk


def main():
    # 3D source sphere
    sphereSource = vtk.vtkSphereSource()
    sphereSource.SetPhiResolution(30)
    sphereSource.SetThetaResolution(30)
    sphereSource.SetCenter(40, 40, 0)
    sphereSource.SetRadius(20)

    # generate circle by cutting the sphere with an implicit plane
    # (through its center, axis-aligned)
    circleCutter = vtk.vtkCutter()
    circleCutter.SetInputConnection(sphereSource.GetOutputPort())
    cutPlane = vtk.vtkPlane()
    cutPlane.SetOrigin(sphereSource.GetCenter())
    cutPlane.SetNormal(0, 0, 1)
    circleCutter.SetCutFunction(cutPlane)

    stripper = vtk.vtkStripper()
    stripper.SetInputConnection(circleCutter.GetOutputPort())  # valid circle
    stripper.Update()

    # that's our circle
    circle = stripper.GetOutput()

    # write circle out
    polyDataWriter = vtk.vtkXMLPolyDataWriter()
    polyDataWriter.SetInputData(circle)

    polyDataWriter.SetFileName("circle.vtp")
    polyDataWriter.SetCompressorTypeToNone()
    polyDataWriter.SetDataModeToAscii()
    polyDataWriter.Write()

    # prepare the binary image's voxel grid
    whiteImage = vtk.vtkImageData()
    bounds = [0] * 6
    circle.GetBounds(bounds)
    spacing = [0] * 3  # desired volume spacing
    spacing[0] = 0.5
    spacing[1] = 0.5
    spacing[2] = 0.5
    whiteImage.SetSpacing(spacing)

    # compute dimensions
    dim = [0] * 3
    for i in range(3):
        dim[i] = int(math.ceil((bounds[i * 2 + 1] - bounds[i * 2]) / spacing[i])) + 1
        if dim[i] < 1:
            dim[i] = 1
    whiteImage.SetDimensions(dim)
    whiteImage.SetExtent(0, dim[0] - 1, 0, dim[1] - 1, 0, dim[2] - 1)
    origin = [0] * 3
    # NOTE: I am not sure whether or not we had to add some offset!
    origin[0] = bounds[0]  # + spacing[0] / 2
    origin[1] = bounds[2]  # + spacing[1] / 2
    origin[2] = bounds[4]  # + spacing[2] / 2
    whiteImage.SetOrigin(origin)
    whiteImage.AllocateScalars(vtk.VTK_UNSIGNED_CHAR, 1)

    # fill the image with foreground voxels:
    inval = 255
    outval = 0
    count = whiteImage.GetNumberOfPoints()
    # for (vtkIdType i = 0 i < count ++i)
    for i in range(count):
        whiteImage.GetPointData().GetScalars().SetTuple1(i, inval)

    # sweep polygonal data (this is the important thing with contours!)
    extruder = vtk.vtkLinearExtrusionFilter()
    extruder.SetInputData(circle)
    extruder.SetScaleFactor(1.0)
    # extruder.SetExtrusionTypeToNormalExtrusion()
    extruder.SetExtrusionTypeToVectorExtrusion()
    extruder.SetVector(0, 0, 1)
    extruder.Update()

    # polygonal data -. image stencil:
    pol2stenc = vtk.vtkPolyDataToImageStencil()
    pol2stenc.SetTolerance(0)  # important if extruder.SetVector(0, 0, 1) !!!
    pol2stenc.SetInputConnection(extruder.GetOutputPort())
    pol2stenc.SetOutputOrigin(origin)
    pol2stenc.SetOutputSpacing(spacing)
    pol2stenc.SetOutputWholeExtent(whiteImage.GetExtent())
    pol2stenc.Update()

    # cut the corresponding white image and set the background:
    imgstenc = vtk.vtkImageStencil()
    imgstenc.SetInputData(whiteImage)
    imgstenc.SetStencilConnection(pol2stenc.GetOutputPort())
    imgstenc.ReverseStencilOff()
    imgstenc.SetBackgroundValue(outval)
    imgstenc.Update()

    imageWriter = vtk.vtkMetaImageWriter()
    imageWriter.SetFileName("labelImage.mhd")
    imageWriter.SetInputConnection(imgstenc.GetOutputPort())
    imageWriter.Write()

    imageWriter = vtk.vtkPNGWriter()
    imageWriter.SetFileName("labelImage.png")
    imageWriter.SetInputConnection(imgstenc.GetOutputPort())
    imageWriter.Write()


if __name__ == '__main__':
    main()
