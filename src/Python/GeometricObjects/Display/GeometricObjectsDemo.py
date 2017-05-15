#!/usr/bin/env python

import vtk

class GeometricObjects():
    
    def GeometricObjects(self):
        
        GeometricObjects = list()
        GeometricObjects.append(vtk.vtkArrowSource())
        GeometricObjects.append(vtk.vtkConeSource())
        GeometricObjects.append(vtk.vtkCubeSource())
        GeometricObjects.append(vtk.vtkCylinderSource())
        GeometricObjects.append(vtk.vtkDiskSource())
        GeometricObjects.append(vtk.vtkLineSource())
        GeometricObjects.append(vtk.vtkRegularPolygonSource())
        GeometricObjects.append(vtk.vtkSphereSource())
        
        renderers = list()
        mappers = list()
        actors = list()
        textmappers = list()
        textactors = list()
        
        # Create a common text property.
        textProperty = vtk.vtkTextProperty()
        textProperty.SetFontSize(10)
        textProperty.SetJustificationToCentered()
        
        # Create a parametric function source, renderer, mapper 
        # and actor for each object.
        for idx, item in enumerate(GeometricObjects):
            GeometricObjects[idx].Update()
            
            mappers.append(vtk.vtkPolyDataMapper())
            mappers[idx].SetInputConnection(GeometricObjects[idx].GetOutputPort())
            
            actors.append(vtk.vtkActor())
            actors[idx].SetMapper(mappers[idx])
            
            textmappers.append(vtk.vtkTextMapper())
            textmappers[idx].SetInput(item.GetClassName())
            textmappers[idx].SetTextProperty(textProperty)
            
            textactors.append(vtk.vtkActor2D())
            textactors[idx].SetMapper(textmappers[idx])
            textactors[idx].SetPosition(150, 16)
            
            renderers.append(vtk.vtkRenderer())
            
        gridDimensions = 3
        
        for idx in range(len(GeometricObjects)):
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
                                
                if idx > (len(GeometricObjects) - 1):
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
    po = GeometricObjects()
    po.GeometricObjects()
