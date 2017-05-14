#!/usr/bin/python

from vtk import *

def Sphere():
    # create the quadric function definition
    quadric = vtkQuadric()
    quadric.SetCoefficients(1,1,1,0,0,0,0,0,0,0)
    
    # F(x,y,z) = a0*x^2 + a1*y^2 + a2*z^2 + a3*x*y + a4*y*z + a5*x*z + a6*x + a7*y + a8*z + a9
    # F(x,y,z) = 1*x^2 + 1*y^2 + 1*z^2
 
    PlotFunction(quadric, 1.0)
 
def EllipticParaboloid():
    # create the quadric function definition
    quadric = vtkQuadric()
    quadric.SetCoefficients(1,1,0,0,0,0,0,0,-1,0)
 
    # F(x,y,z) = a0*x^2 + a1*y^2 + a2*z^2 + a3*x*y + a4*y*z + a5*x*z + a6*x + a7*y + a8*z + a9
    # F(x,y,z) = 1*x^2 + 1*y^2
 
    PlotFunction(quadric, 0.0)
 
def HyperbolicParaboloid():
    # create the quadric function definition
    quadric = vtkQuadric()
    quadric.SetCoefficients(1,-1,0,0,0,0,0,0,0,0)
    
    # F(x,y,z) = a0*x^2 + a1*y^2 + a2*z^2 + a3*x*y + a4*y*z + a5*x*z + a6*x + a7*y + a8*z + a9
    # F(x,y,z) = 1*x^2 - 1*y^2
 
    PlotFunction(quadric, 1.0)
 
def Cylinder():
    # create the quadric function definition
    quadric = vtkQuadric()
    quadric.SetCoefficients(1,1,0,0,0,0,0,0,0,0)
 
    # F(x,y,z) = a0*x^2 + a1*y^2 + a2*z^2 + a3*x*y + a4*y*z + a5*x*z + a6*x + a7*y + a8*z + a9
    # F(x,y,z) = 1*x^2 + 1*y^2
 
    PlotFunction(quadric, 1.0)
 
def HyperboloidOneSheet():
    # create the quadric function definition
    quadric = vtkQuadric()
    quadric.SetCoefficients(1,1,-1,0,0,0,0,0,0,0)
 
    # F(x,y,z) = a0*x^2 + a1*y^2 + a2*z^2 + a3*x*y + a4*y*z + a5*x*z + a6*x + a7*y + a8*z + a9
    # F(x,y,z) = 1*x^2 + 1*y^2
 
    PlotFunction(quadric, 1.0)
 
def HyperboloidTwoSheets():
    # create the quadric function definition
    quadric = vtkQuadric()
    quadric.SetCoefficients(1,1,-1,0,0,0,0,0,0,0)
 
    # F(x,y,z) = a0*x^2 + a1*y^2 + a2*z^2 + a3*x*y + a4*y*z + a5*x*z + a6*x + a7*y + a8*z + a9
    # F(x,y,z) = 1*x^2 + 1*y^2
 
    PlotFunction(quadric, -1.0)
 
def Ellipsoid():
    # create the quadric function definition
    quadric = vtkQuadric()
    quadric.SetCoefficients(1,1,2,0,0,0,0,0,0,0)
 
    # F(x,y,z) = a0*x^2 + a1*y^2 + a2*z^2 + a3*x*y + a4*y*z + a5*x*z + a6*x + a7*y + a8*z + a9
    # F(x,y,z) = 1*x^2 + 1*y^2 + 1*z^2
    
    PlotFunction(quadric, 1.0)
 
def Cone():
    # create the quadric function definition
    quadric = vtkQuadric()
    quadric.SetCoefficients(1,1,-1,0,0,0,0,0,0,0)
    
    # F(x,y,z) = a0*x^2 + a1*y^2 + a2*z^2 + a3*x*y + a4*y*z + a5*x*z + a6*x + a7*y + a8*z + a9
    # F(x,y,z) = 1*x^2 + 1*y^2 - 1*z^2
    PlotFunction(quadric, 0.0)
 
 
def Other():
    # create the quadric function definition
    quadric = vtkQuadric()
    quadric.SetCoefficients(.5,1,.2,0,.1,0,0,.2,0,0)
    
    # F(x,y,z) = a0*x^2 + a1*y^2 + a2*z^2 + a3*x*y + a4*y*z + a5*x*z + a6*x + a7*y + a8*z + a9
    # F(x,y,z) = 0.5*x^2 + 1*y^2 + 0.2*z^2 + 0*x*y + 0.1*y*z + 0*x*z + 0*x + 0.2*y + 0*z + 0
    PlotFunction(quadric, 1.0)
 
def PlotFunction(quadric, value):
    # sample the quadric function
    sample = vtkSampleFunction()
    sample.SetSampleDimensions(50,50,50)
    sample.SetImplicitFunction(quadric)
    #double xmin = 0, xmax=1, ymin=0, ymax=1, zmin=0, zmax=1
    xmin = -10
    xmax=11
    ymin=-10
    ymax=10
    zmin=-10
    zmax=10
    sample.SetModelBounds(xmin, xmax, ymin, ymax, zmin, zmax)
 
    #create the 0 isosurface
    contours = vtkContourFilter()
    contours.SetInput(sample.GetOutput())
    contours.GenerateValues(1, value, value)
 
    # map the contours to graphical primitives
    contourMapper = vtkPolyDataMapper()
    contourMapper.SetInput(contours.GetOutput())
    contourMapper.SetScalarRange(0.0, 1.2)
 
    # create an actor for the contours
    contourActor = vtkActor()
    contourActor.SetMapper(contourMapper)
 
    # -- create a box around the function to indicate the sampling volume --
 
    # create outline
    outline = vtkOutlineFilter()
    outline.SetInput(sample.GetOutput())
 
    # map it to graphics primitives
    outlineMapper = vtkPolyDataMapper()
    outlineMapper.SetInput(outline.GetOutput())
 
    # create an actor for it
    outlineActor = vtkActor()
    outlineActor.SetMapper(outlineMapper)
    outlineActor.GetProperty().SetColor(0,0,0)
 
    # setup the window
    ren1 = vtkRenderer()
    renWin = vtkRenderWindow()
    renWin.AddRenderer(ren1)
    iren = vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)
 
    # add the actors to the scene
    ren1.AddActor(contourActor)
    ren1.AddActor(outlineActor)
    ren1.SetBackground(1,1,1) # Background color white
 
    # render and interact
    renWin.Render()
    iren.Start()

Other()
Sphere()
Cone()
Ellipsoid()
Cylinder()
HyperboloidOneSheet()
HyperboloidTwoSheets()
HyperbolicParaboloid()
EllipticParaboloid()
