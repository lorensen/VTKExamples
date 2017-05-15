#!/usr/bin/env python

'''
The purpose of this is to demonstrate how to get the Gaussian and Mean curvatures of a surface.

Two different surfaces are used in this demonstration with each surface coloured according
 to its Gaussian and Mean curvatures.

The first surface is a superquadric surface, this demonstrates the use of extra filters
 that are needed to get a nice smooth surface.
 
The second surface is a parametric surface, in this case the surface has already been triangulated
so no extra processing is necessary.

In order to get a nice coloured image, a vtkColorTransferFunction has been used to generate
 a set of colours for the vtkLookUp tables. We have used a diverging colour space similar 
 to that in ParaView.
Because of the symmetry of the ranges selected for the lookup tables, the white colouration
 represents a midpoint value whilst the blue represents values less than the midopoint value
 and red represents colours greater than the midpoint value.
  
In the case of the Random Hills Gaussian Curvature surface, this colouration shows the nature 
 of the surface quite nicely. The blue areas are saddle points (negative Gaussian curvature) 
 and the red areas have a positive Gaussian curvature.  In the case of the mean curvature the 
 blue colouration is representing negative curvature perpendicular to one of the principal axes.
  
This example also demonstrates the use of lists and the linking of the elements of the 
 lists together to form a pipeline. 
  
'''
import vtk

class CurvaturesDemo():
    
    def CurvaturesDemo(self):
        
        # We are going to handle two different sources.
        # The first source is a superquadric source.
        torus = vtk.vtkSuperquadricSource();
        torus.SetCenter(0.0, 0.0, 0.0)
        torus.SetScale(1.0, 1.0, 1.0)
        torus.SetPhiResolution (64)
        torus.SetThetaResolution(64)
        torus.SetThetaRoundness (1)
        torus.SetThickness (0.5)
        torus.SetSize(0.5)
        torus.SetToroidal(1) 
        
        # Rotate the torus towards the observer (around the x-axis)
        torusT = vtk.vtkTransform()
        torusT.RotateX(55)
        
        torusTF = vtk.vtkTransformFilter()
        torusTF.SetInputConnection(torus.GetOutputPort())
        torusTF.SetTransform(torusT)
              
        # The quadric is made of strips, so pass it through a triangle filter as
        # the curvature filter only operates on polys
        tri = vtk.vtkTriangleFilter()
        tri.SetInputConnection(torusTF.GetOutputPort())
         
        # The quadric has nasty discontinuities from the way the edges are generated
        # so let's pass it though a CleanPolyDataFilter and merge any points which
        # are coincident, or very close
        
        cleaner = vtk.vtkCleanPolyData()
        cleaner.SetInputConnection(tri.GetOutputPort())
        cleaner.SetTolerance(0.005)

        # The next source will be a parametric function
        rh = vtk.vtkParametricRandomHills()
        rhFnSrc = vtk.vtkParametricFunctionSource()
        rhFnSrc.SetParametricFunction(rh)
    
        # Now we have the sources, lets put them into a list.
        sources = list()
        sources.append(cleaner)
        sources.append(cleaner)
        sources.append(rhFnSrc)
        sources.append(rhFnSrc)
        
        # Colour transfer function.
        ctf = vtk.vtkColorTransferFunction()
        ctf.SetColorSpaceToDiverging()
        ctf.AddRGBPoint(0.0, 0.230, 0.299, 0.754)
        ctf.AddRGBPoint(1.0, 0.706, 0.016, 0.150)
        cc = list()
        for i in range(256):
            cc.append(ctf.GetColor(float(i) / 255.0)) 
                   
        # Lookup table.
        lut = list()
        for idx in range(len(sources)):
            lut.append(vtk.vtkLookupTable())
            lut[idx].SetNumberOfColors(256)
            for i, item in enumerate(cc):
                lut[idx].SetTableValue(i, item[0], item[1], item[2], 1.0)
            if idx == 0:
                lut[idx].SetRange(-10, 10)
            if idx == 1:
                lut[idx].SetRange(0, 4)
            if idx == 2:
                lut[idx].SetRange(-1, 1)
            if idx == 3:
                lut[idx].SetRange(-1, 1)
            lut[idx].Build()

        curvatures = list()        
        for idx in range(len(sources)):
            curvatures.append(vtk.vtkCurvatures())
            if idx % 2 == 0:
                curvatures[idx].SetCurvatureTypeToGaussian()
            else:
                curvatures[idx].SetCurvatureTypeToMean()
        
        renderers = list()
        mappers = list()
        actors = list()
        textmappers = list()
        textactors = list()
        
        # Create a common text property.
        textProperty = vtk.vtkTextProperty()
        textProperty.SetFontSize(10)
        textProperty.SetJustificationToCentered()
        
        names = ['Torus - Gaussian Curvature', 'Torus - Mean Curvature', 'Random Hills - Gaussian Curvature', 'Random Hills - Mean Curvature']

        # Link the pipeline together. 
        for idx, item in enumerate(sources):
            sources[idx].Update()
            
            curvatures[idx].SetInputConnection(sources[idx].GetOutputPort())
            
            mappers.append(vtk.vtkPolyDataMapper())
            mappers[idx].SetInputConnection(curvatures[idx].GetOutputPort())
            mappers[idx].SetLookupTable(lut[idx])
            mappers[idx].SetUseLookupTableScalarRange(1)

            actors.append(vtk.vtkActor())
            actors[idx].SetMapper(mappers[idx])
            
            textmappers.append(vtk.vtkTextMapper())
            textmappers[idx].SetInput(names[idx])
            textmappers[idx].SetTextProperty(textProperty)
            
            textactors.append(vtk.vtkActor2D())
            textactors[idx].SetMapper(textmappers[idx])
            textactors[idx].SetPosition(150, 16)
            
            renderers.append(vtk.vtkRenderer())
            
        gridDimensions = 2
        
        for idx in range(len(sources)):
            if idx < gridDimensions * gridDimensions:
                renderers.append(vtk.vtkRenderer)
        
        rendererSize = 300
        
        # Create the RenderWindow
        #
        renderWindow = vtk.vtkRenderWindow()
        renderWindow.SetSize(rendererSize * gridDimensions, rendererSize * gridDimensions)
        
        # Add and position the renders to the render window.
        viewport = list()
        for row in range(gridDimensions):
            for col in range(gridDimensions):
                idx = row * gridDimensions + col
                
                viewport[:] = []
                viewport.append(float(col) * rendererSize / (gridDimensions * rendererSize))
                viewport.append(float(gridDimensions - (row+1)) * rendererSize / (gridDimensions * rendererSize))
                viewport.append(float(col+1)*rendererSize / (gridDimensions * rendererSize))
                viewport.append(float(gridDimensions - row) * rendererSize / (gridDimensions * rendererSize))
                                
                if idx > (len(sources) - 1):
                    continue

                renderers[idx].SetViewport(viewport)
                renderWindow.AddRenderer(renderers[idx])
                
                renderers[idx].AddActor(actors[idx])
                renderers[idx].AddActor(textactors[idx])
                renderers[idx].SetBackground(0.4,0.3,0.2)
        
        interactor = vtk.vtkRenderWindowInteractor()
        interactor.SetRenderWindow(renderWindow)
        
        renderWindow.Render()

        interactor.Start()
    
if __name__ == "__main__":
    po = CurvaturesDemo()
    po.CurvaturesDemo()
