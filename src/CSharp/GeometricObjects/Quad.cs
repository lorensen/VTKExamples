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
            Quad();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void Quad() {
         double[,] p = new double[,] { 
            { 0.0, 0.0, 0.0 }, 
            { 1.0, 0.0, 0.0 },
            { 1.0, 1.0, 0.0 },
            { 0.0, 1.0, 0.0 }
         };

         // Create the points
         vtkPoints points = vtkPoints.New();
         for(int i = 0; i < 4; i++)
            points.InsertNextPoint(p[i, 0], p[i, 1], p[i, 2]);


         vtkQuad quad = vtkQuad.New();
         quad.GetPointIds().SetNumberOfIds(4);
         for(int i = 0; i < 4; i++)
            quad.GetPointIds().SetId(i, i);

         // Create a cell array to store the quad in and add the quad to it
         vtkCellArray cells = vtkCellArray.New();
         cells.InsertNextCell(quad);

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
