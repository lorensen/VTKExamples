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
            LongLine();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void LongLine() {
         // Create five points 
         double[,] p = new double[,] { 
            { 0.0, 0.0, 0.0 }, 
            { 1.0, 0.0, 0.0 },
            { 0.0, 1.0, 0.0 },
            { 0.0, 1.0, 2.0 },
            { 1.0, 2.0, 3.0 }
         };

         // Create a vtkPoints object and store the points in it
         vtkPoints points = vtkPoints.New();
         for(int i = 0; i < 5; i++)
            points.InsertNextPoint(p[i, 0], p[i, 1], p[i, 2]);

         // Create a cell array to store the lines in and add the lines to it
         vtkCellArray lines = vtkCellArray.New();

         for(int i = 0; i < 4; i++) {
            vtkLine line = vtkLine.New();
            line.GetPointIds().SetId(0, i);
            line.GetPointIds().SetId(1, i + 1);
            lines.InsertNextCell(line);
         }

         // Create a polydata to store everything in
         vtkPolyData linesPolyData = vtkPolyData.New();

         // Add the points to the dataset
         linesPolyData.SetPoints(points);

         // Add the lines to the dataset
         linesPolyData.SetLines(lines);
         // Visualize
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInput(linesPolyData);
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
