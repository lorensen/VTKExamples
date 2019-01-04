#!/usr/bin/env python
import vtk

def MakeScalars(dims, origin, spacing, scalars):
    # Implicit function used to compute scalars
    sphere = vtk.vtkSphere()
    sphere.SetRadius(3)
    sphere.SetCenter(5, 5, 5)
    scalars.SetNumberOfTuples(dims[0]*dims[1]*dims[2])
    for k in range(0, dims[2]):
        z = origin[2] + spacing[2]*k
        for j in range(0, dims[1]):
    	    y = origin[1] + spacing[1]*j
            for i in range(0,dims[0]):
                x = origin[0] + spacing[0]*i
                scalars.SetValue(k*dims[0]*dims[1] + j*dims[0] + i, sphere.EvaluateFunction(x, y, z))

def main():  
    # Create and populate the AMR dataset
    # The dataset should look like
    # Level 0
    #   uniform grid, dimensions 11, 11, 11, AMR box (0, 0, 0) - (9, 9, 9) 
    # Level 1 - refinement ratio : 2
    #   uniform grid, dimensions 11, 11, 11, AMR box (0, 0, 0) - (9, 9, 9)
    #   uniform grid, dimensions 11, 11, 11, AMR box (10, 10, 10) - (19, 19, 19)
    # Use MakeScalars() above to fill the scalar arrays
    
    amr = vtk.vtkOverlappingAMR()
    blocksPerLevel = [1, 2]
    amr.Initialize(2, blocksPerLevel)
    
    origin = [0.0, 0.0, 0.0]
    spacing = [1.0, 1.0, 1.0]
    dims = [11, 11, 11]
   
    ug1 = vtk.vtkUniformGrid()
    # Geometry
    ug1.SetOrigin(origin)
    ug1.SetSpacing(spacing)
    ug1.SetDimensions(dims)
    
    # Data
    scalars = vtk.vtkFloatArray() 
    ug1.GetPointData().SetScalars(scalars)
    MakeScalars(dims, origin, spacing, scalars)
    
    lo = [0, 0, 0]
    hi = [9, 9, 9]
    box1 = vtk.vtkAMRBox()
    amr.SetAMRBox(0, 0, box1)
    amr.SetDataSet(0, 0, ug1)
    
    spacing2 = [0.5, 0.5, 0.5]
    ug2 = vtk.vtkUniformGrid()
    # Geometry
    ug2.SetOrigin(origin)
    ug2.SetSpacing(spacing2)
    ug2.SetDimensions(dims)
    
    # Data
    scalars = vtk.vtkFloatArray() 
    ug2.GetPointData().SetScalars(scalars)
    MakeScalars(dims, origin, spacing2, scalars)
    
    lo2 = [0, 0, 0]
    hi2 = [9, 9, 9]
    box2 = vtk.vtkAMRBox()
    amr.SetAMRBox(1, 0, box2)
    amr.SetDataSet(1, 0, ug2)
    
    origin3 = [5, 5, 5]
    ug3 = vtk.vtkUniformGrid()
 
    # Geometry
    ug3.SetOrigin(origin3)
    ug3.SetSpacing(spacing2)
    ug3.SetDimensions(dims)
    
    # Data
    scalars = vtk.vtkFloatArray() 
    ug3.GetPointData().SetScalars(scalars)
    MakeScalars(dims, origin3, spacing2, scalars)
    
    lo3 = [10, 10, 10]
    hi3 = [19, 19, 19]
    box3 = vtk.vtkAMRBox()
    amr.SetAMRBox(1, 1, box3)
    amr.SetDataSet(1, 1, ug3)
    amr.SetRefinementRatio(0, 2)
    
    # Render the amr data here.
    of = vtk.vtkOutlineFilter()
    of.SetInputData(amr)
    
    geomFilter = vtk.vtkCompositeDataGeometryFilter()
    geomFilter.SetInputConnection(of.GetOutputPort())
    
    # Create an iso-surface - at 10.
    cf = vtk.vtkContourFilter()
    cf.SetInputData(amr)
    cf.SetNumberOfContours(1)
    cf.SetValue(0, 10.0)
    
    geomFilter2 = vtk.vtkCompositeDataGeometryFilter()
    geomFilter2.SetInputConnection(cf.GetOutputPort())
    
    # Create the render window, renderer, and interactor.
    aren =  vtk.vtkRenderer()
    renWin  = vtk.vtkRenderWindow()
    renWin.AddRenderer(aren)
    
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)
    
    # Associate the geometry with a mapper and the mapper to an actor.
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(geomFilter.GetOutputPort())
    actor1 = vtk.vtkActor()
    actor1.SetMapper(mapper)
    
    # Associate the geometry with a mapper and the mapper to an actor.
    mapper2 = vtk.vtkPolyDataMapper()
    mapper2.SetInputConnection(geomFilter2.GetOutputPort())
    actor2 = vtk.vtkActor()
    actor2.SetMapper(mapper2)
    
    # Add the actor to the renderer and start handling events.
    aren.AddActor(actor1)
    aren.AddActor(actor2)
    renWin.Render()
    iren.Start()

if __name__ == '__main__':
    main()
