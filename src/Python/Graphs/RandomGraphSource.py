#!/usr/bin/env python
import vtk

def main():
    randomGraphSource = vtk.vtkRandomGraphSource()
    randomGraphSource.SetNumberOfVertices(5)
    randomGraphSource.SetNumberOfEdges(4)
    randomGraphSource.SetSeed(0) # This ensures repeatable results for testing. Turn this off for real use.
    randomGraphSource.Update()
    
    graphLayoutView = vtk.vtkGraphLayoutView()
    graphLayoutView.AddRepresentationFromInput(randomGraphSource.GetOutput())
    graphLayoutView.ResetCamera()
    graphLayoutView.Render()
    graphLayoutView.GetInteractor().Start()

if __name__ == '__main__':
    main()
