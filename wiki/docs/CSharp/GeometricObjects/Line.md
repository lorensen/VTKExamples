[VTKExamples](/home/)/[CSharp](/CSharp)/GeometricObjects/Line

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/GeometricObjects/TestLine.png?raw=true" width="256" />

### Description
A tutorial on how to setup a Windows Forms Application utilizing ActiViz.NET can be found here: [Setup a Windows Forms Application to use ActiViz.NET](http://www.vtk.org/Wiki/VTK/CSharp/ActiViz.NET)

**Line.cs**
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
            Line();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void Line() {
         // Create a line.  
         vtkLineSource lineSource = vtkLineSource.New();
         // Create two points, P0 and P1
         double[] p0 = new double[] { 1.0, 0.0, 0.0 };
         double[] p1 = new double[] { 0.0, 1.0, 0.0 };

         lineSource.SetPoint1(p0[0], p0[1], p0[2]);
         lineSource.SetPoint2(p1[0], p1[1], p1[2]);

         // Visualize
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInputConnection(lineSource.GetOutputPort());
         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);
         actor.GetProperty().SetLineWidth(4);
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         renderer.SetBackground(0.2, 0.3, 0.4);
         renderer.AddActor(actor);
         renderer.ResetCamera();
      }
   }
}
```
