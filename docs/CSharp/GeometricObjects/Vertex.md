[VTKExamples](/index/)/[CSharp](/CSharp)/GeometricObjects/Vertex

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/GeometricObjects/TestVertex.png?raw=true" width="256" />

### Description
A tutorial on how to setup a Windows Forms Application utilizing ActiViz.NET can be found here: [Setup a Windows Forms Application to use ActiViz.NET](http://www.vtk.org/Wiki/VTK/CSharp/ActiViz.NET)

**Vertex.cs**
```csharp
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Windows.Forms;
using System.Diagnostics;

using Kitware.VTK;

namespace ActiViz.Examples {
   public partial class Form1 : Form {
      public Form1() {
         InitializeComponent();
      }


      private void renderWindowControl1_Load(object sender, EventArgs e) {
         try {
            Vertex();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void Vertex() {
         vtkPoints points = vtkPoints.New();
         points.InsertNextPoint(0, 0, 0);

         vtkVertex vertex = vtkVertex.New();
         vertex.GetPointIds().SetId(0, 0);

         vtkCellArray vertices = vtkCellArray.New();
         vertices.InsertNextCell(vertex);

         vtkPolyData polydata = vtkPolyData.New();
         polydata.SetPoints(points);
         polydata.SetVerts(vertices);

         // Visualize
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInputConnection(polydata.GetProducerPort());
         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);
         actor.GetProperty().SetPointSize(10);
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         renderer.SetBackground(0.2, 0.3, 0.4);
         // Add the actor to the scene
         renderer.AddActor(actor);
      }
   }
}
```
