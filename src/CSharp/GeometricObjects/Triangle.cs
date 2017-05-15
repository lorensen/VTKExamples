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
            Triangle();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void Triangle() {
         // Create a triangle
         vtkPoints points = vtkPoints.New();
         points.InsertNextPoint(1.0, 0.0, 0.0);
         points.InsertNextPoint(0.0, 0.0, 0.0);
         points.InsertNextPoint(0.0, 1.0, 0.0);

         vtkTriangle triangle = vtkTriangle.New();
         triangle.GetPointIds().SetId(0, 0);
         triangle.GetPointIds().SetId(1, 1);
         triangle.GetPointIds().SetId(2, 2);

         // Create a cell array to store the triangle in and add the triangle to it
         vtkCellArray cells = vtkCellArray.New();
         cells.InsertNextCell(triangle);

         // Create a polydata to store everything in
         vtkPolyData polyData = vtkPolyData.New();

         // Add the points to the dataset
         polyData.SetPoints(points);

         // Add the quad to the dataset
         polyData.SetPolys(cells);

         //Create an actor and mapper
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInput(polyData);
         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         renderer.SetBackground(0.2, 0.3, 0.4);
         renderer.AddActor(actor);
      }
   }
}
