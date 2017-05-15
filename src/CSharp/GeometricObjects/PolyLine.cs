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
            PolyLine();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void PolyLine() {
         // Create five points
         double[,] p = new double[,] { 
            { 0.0, 0.0, 0.0 }, 
            { 1.0, 0.0, 0.0 },
            { 0.0, 1.0, 0.0 },
            { 0.0, 1.0, 2.0 },
            { 0.0, 3.0, 3.0 }
         };

         // Create the points
         vtkPoints points = vtkPoints.New();
         for(int i = 0; i < 5; i++)
            points.InsertNextPoint(p[i, 0], p[i, 1], p[i, 2]);


         vtkPolyLine polyLine = vtkPolyLine.New();
         polyLine.GetPointIds().SetNumberOfIds(5);
         for(int i = 0; i < 5; i++)
            polyLine.GetPointIds().SetId(i, i);

         // Create a cell array to store the lines in and add the lines to it
         vtkCellArray cells = vtkCellArray.New();
         cells.InsertNextCell(polyLine);

         // Create a polydata to store everything in
         vtkPolyData polyData = vtkPolyData.New();

         // Add the points to the dataset
         polyData.SetPoints(points);

         // Add the lines to the dataset
         polyData.SetLines(cells);
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
