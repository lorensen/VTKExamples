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
            TriangleStrip();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void TriangleStrip() {
         vtkPoints points = vtkPoints.New();
         points.InsertNextPoint(0, 0, 0);
         points.InsertNextPoint(0, 1, 0);
         points.InsertNextPoint(1, 0, 0);
         points.InsertNextPoint(1.5, 1, 0);

         vtkTriangleStrip triangleStrip = vtkTriangleStrip.New();
         triangleStrip.GetPointIds().SetNumberOfIds(4);
         triangleStrip.GetPointIds().SetId(0, 0);
         triangleStrip.GetPointIds().SetId(1, 1);
         triangleStrip.GetPointIds().SetId(2, 2);
         triangleStrip.GetPointIds().SetId(3, 3);

         vtkCellArray cells = vtkCellArray.New();
         cells.InsertNextCell(triangleStrip);
         // Create a polydata to store everything in
         vtkPolyData polyData = vtkPolyData.New();

         // Add the points to the dataset
         polyData.SetPoints(points);
         // Add the strip to the dataset
         polyData.SetStrips(cells);

         //Create an actor and mapper
         vtkDataSetMapper mapper = vtkDataSetMapper.New();
         mapper.SetInput(polyData);
         vtkActor actor = vtkActor.New();
         actor.GetProperty().SetRepresentationToWireframe();

         actor.SetMapper(mapper);
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         renderer.SetBackground(0.2, 0.3, 0.4);
         renderer.AddActor(actor);
      }
   }
}
