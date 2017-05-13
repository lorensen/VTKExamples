[VTKExamples](/home/)/[Python](/Python)/Graphs/VisualizeGraph

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Graphs/TestVisualizeGraph.png?raw=true" width="256" />

### Description
[]([File:VTK_Examples_Python_Graphs_VisualizeGraph.png])

* Contributed by Jim McCusker

* Note: AddEdge() is not enabled through python, but AddGraphEdge() is.

**VisualizeGraph.py**
```python
#!/usr/bin/env python

import vtk

g = vtk.vtkMutableDirectedGraph()

v1 = g.AddVertex()
v2 = g.AddVertex()

g.AddGraphEdge(v1, v2)
g.AddGraphEdge(v1, v2)

graphLayoutView = vtk.vtkGraphLayoutView()
graphLayoutView.AddRepresentationFromInput(g)
graphLayoutView.SetLayoutStrategy("Simple 2D")
graphLayoutView.ResetCamera()
graphLayoutView.Render()

graphLayoutView.GetLayoutStrategy().SetRandomSeed(0)

graphLayoutView.GetInteractor().Start()
```
