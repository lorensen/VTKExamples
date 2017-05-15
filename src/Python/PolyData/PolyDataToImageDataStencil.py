import vtk
from vtk.util.misc import vtkGetDataRoot

VTK_DATA_ROOT = vtkGetDataRoot()

# A script to test the stencil filter with a polydata stencil.
# Image pipeline
reader = vtk.vtkPNGReader()
reader.SetDataSpacing(0.8, 0.8, 1.5)
reader.SetDataOrigin(0.0, 0.0, 0.0)
reader.SetFileName("" + str(VTK_DATA_ROOT) + "/Data/fullhead15.png")
sphere = vtk.vtkSphereSource()
sphere.SetPhiResolution(12)
sphere.SetThetaResolution(12)
sphere.SetCenter(102, 102, 0)
sphere.SetRadius(60)
triangle = vtk.vtkTriangleFilter()
if vtk.VTK_MAJOR_VERSION <= 5:
    triangle.SetInput(sphere.GetOutput())
else:
    triangle.SetInputConnection(sphere.GetOutputPort())

stripper = vtk.vtkStripper()
if vtk.VTK_MAJOR_VERSION <= 5:
    stripper.SetInput(triangle.GetOutput())
else:
    stripper.SetInputConnection(triangle.GetOutputPort())
dataToStencil = vtk.vtkPolyDataToImageStencil()
if vtk.VTK_MAJOR_VERSION <= 5:
    dataToStencil.SetInput(stripper.GetOutput())
else:
    dataToStencil.SetInputConnection(stripper.GetOutputPort())
dataToStencil.SetOutputSpacing(0.8, 0.8, 1.5)
dataToStencil.SetOutputOrigin(0.0, 0.0, 0.0)

stencil = vtk.vtkImageStencil()
if vtk.VTK_MAJOR_VERSION <= 5:
    stencil.SetInput(reader.GetOutput())
    stencil.SetStencil(dataToStencil.GetOutput())
else:
    stencil.SetInputConnection(reader.GetOutputPort())
    stencil.SetStencilConnection(dataToStencil.GetOutputPort())
stencil.ReverseStencilOn()
stencil.SetBackgroundValue(500)

# test again with a contour
reader2 = vtk.vtkPNGReader()
reader2.SetDataSpacing(0.8, 0.8, 1.5)
reader2.SetDataOrigin(0.0, 0.0, 0.0)
reader2.SetFileName("" + str(VTK_DATA_ROOT) + "/Data/fullhead15.png")
plane = vtk.vtkPlane()
plane.SetOrigin(0, 0, 0)
plane.SetNormal(0, 0, 1)
cutter = vtk.vtkCutter()
if vtk.VTK_MAJOR_VERSION <= 5:
    cutter.SetInput(sphere.GetOutput())
else:
    cutter.SetInputConnection(sphere.GetOutputPort())
cutter.SetCutFunction(plane)
stripper2 = vtk.vtkStripper()
if vtk.VTK_MAJOR_VERSION <= 5:
    stripper2.SetInput(cutter.GetOutput())
else:
    stripper2.SetInputConnection(cutter.GetOutputPort())
dataToStencil2 = vtk.vtkPolyDataToImageStencil()
if vtk.VTK_MAJOR_VERSION <= 5:
    dataToStencil2.SetInput(stripper2.GetOutput())
else:
    dataToStencil2.SetInputConnection(stripper2.GetOutputPort())
dataToStencil2.SetOutputSpacing(0.8, 0.8, 1.5)
dataToStencil2.SetOutputOrigin(0.0, 0.0, 0.0)
stencil2 = vtk.vtkImageStencil()
if vtk.VTK_MAJOR_VERSION <= 5:
    stencil2.SetInput(reader2.GetOutput())
    stencil2.SetStencil(dataToStencil2.GetOutput())
else:
    stencil2.SetInputConnection(reader2.GetOutputPort())
    stencil2.SetStencilConnection(dataToStencil2.GetOutputPort())
stencil2.SetBackgroundValue(500)

imageAppend = vtk.vtkImageAppend()
if vtk.VTK_MAJOR_VERSION <= 5:
    imageAppend.SetInput(stencil.GetOutput())
    imageAppend.AddInput(stencil2.GetOutput())
else:
    imageAppend.SetInputConnection(stencil.GetOutputPort())
    imageAppend.AddInputConnection(stencil2.GetOutputPort())

viewer = vtk.vtkImageViewer()
interator = vtk.vtkRenderWindowInteractor()
if vtk.VTK_MAJOR_VERSION <= 5:
    viewer.SetInput(imageAppend.GetOutput())
else:
    viewer.SetInputConnection(imageAppend.GetOutputPort())
viewer.SetupInteractor(interator)
viewer.SetZSlice(0)
viewer.SetColorWindow(2000)
viewer.SetColorLevel(1000)
viewer.Render()

interator.Start()
