[VTKExamples](Home)/[CSharp](CSharp)/GeometricObjects/Pyramid

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/GeometricObjects/TestPyramid.png" width="256" />

### Description
A tutorial on how to setup a Windows Forms Application utilizing ActiViz.NET can be found here: [Setup a Windows Forms Application to use ActiViz.NET](http://www.vtk.org/Wiki/VTK/CSharp/ActiViz.NET)

**Pyramid.cs**
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
            Pyramid();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void Pyramid() {
         vtkPoints points = vtkPoints.New();
         double[,] p = new double[,] {
            { 1.0,  1.0, 1.0 },
            {-1.0,  1.0, 1.0 },
            {-1.0, -1.0, 1.0 },
            { 1.0, -1.0, 1.0 },
            { 0.0,  0.0, 0.0 }};

         for(int i = 0; i < 5; i++)
            points.InsertNextPoint(p[i, 0], p[i, 1], p[i, 2]);

         vtkPyramid pyramid = vtkPyramid.New();
         for(int i = 0; i < 5; i++)
            pyramid.GetPointIds().SetId(i, i);

         vtkCellArray cells = vtkCellArray.New();
         cells.InsertNextCell(pyramid);

         vtkUnstructuredGrid ug = vtkUnstructuredGrid.New();
         ug.SetPoints(points);
         ug.InsertNextCell(pyramid.GetCellType(), pyramid.GetPointIds());

         //Create an actor and mapper
         vtkDataSetMapper mapper = vtkDataSetMapper.New();
         mapper.SetInput(ug);
         vtkActor actor = vtkActor.New();
         actor.RotateX(105.0);
         actor.RotateZ(-36.0);
         actor.SetMapper(mapper);
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         renderer.SetBackground(0.2, 0.3, 0.4);
         renderer.AddActor(actor);
         renderer.ResetCamera();
      }
   }
}
```
