[VTKExamples](/index/)/[Python](/Python)/Graphs/EdgeWeights

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Graphs/TestEdgeWeights.png?raw=true" width="256" />

### Description
[]([File:VTK_Examples_Python_Graphs_EdgeWeights.png])

* Contributed by Jim McCusker

**EdgeWeights.py**
```python
#!/usr/bin/env python

import vtk

g = vtk.vtkMutableDirectedGraph()

# Create 3 vertices
v1 = g.AddVertex()
v2 = g.AddVertex()
v3 = g.AddVertex()

# Create a fully connected graph
g.AddGraphEdge(v1, v2)
g.AddGraphEdge(v2, v3)
g.AddGraphEdge(v1, v3)
 
# Create the edge weight array
weights = vtk.vtkDoubleArray()
weights.SetNumberOfComponents(1)
weights.SetName("Weights")

# Set the edge weights
weights.InsertNextValue(1.0)
weights.InsertNextValue(1.0)
weights.InsertNextValue(2.0)
 
# Add the edge weight array to the graph
g.GetEdgeData().AddArray(weights);

graphLayoutView = vtk.vtkGraphLayoutView()
graphLayoutView.AddRepresentationFromInput(g)
graphLayoutView.SetLayoutStrategy("Simple 2D")
graphLayoutView.GetLayoutStrategy().SetEdgeWeightField("Weights")
graphLayoutView.GetLayoutStrategy().SetWeightEdges(1)
graphLayoutView.SetEdgeLabelArrayName("Weights")
graphLayoutView.SetEdgeLabelVisibility(1)
graphLayoutView.ResetCamera()
graphLayoutView.Render()

graphLayoutView.GetLayoutStrategy().SetRandomSeed(0)

graphLayoutView.GetInteractor().Start()
```
