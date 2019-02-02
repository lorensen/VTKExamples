#!/usr/bin/env python
import vtk

def main():
    g = vtk.vtkMutableUndirectedGraph()
    
    v1 = g.AddVertex()
    v2 = g.AddVertex()
    
    g.AddEdge(v1, v2)
    g.AddEdge(v1, v2)
    
    scales = vtk.vtkFloatArray()
    scales.SetNumberOfComponents(1)
    scales.SetName("Scales")
    scales.InsertNextValue(1.0)
    scales.InsertNextValue(4.0)
    
    g.GetVertexData().AddArray(scales)
    
    layoutView = vtk.vtkGraphLayoutView()
    layoutView.AddRepresentationFromInput(g)
    layoutView.ScaledGlyphsOn()
    layoutView.SetScalingArrayName("Scales")
    rGraph = vtk.vtkRenderedGraphRepresentation()
    gGlyph = vtk.vtkGraphToGlyphs()
    rGraph.SafeDownCast(layoutView.GetRepresentation()).SetGlyphType(gGlyph.CIRCLE)
    layoutView.ResetCamera()
    layoutView.Render()
    layoutView.GetInteractor().Start()

if __name__ == '__main__':
    main()
