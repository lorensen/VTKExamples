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
            Hexahedron();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void Hexahedron() {
         // Setup the coordinates of eight points 
         // (faces must be in counter clockwise order as viewed from the outside)
         double[,] p = new double[,] { 
            { 0.0, 0.0, 0.0 }, 
            { 1.0, 0.0, 0.0 },
            { 1.0, 1.0, 0.0 },
            { 0.0, 1.0, 0.0 },
            { 0.0, 0.0, 1.0 },
            { 1.0, 0.0, 1.0 },
            { 1.0, 1.0, 1.0 },
            { 0.0, 1.0, 1.0 }
         };

         // Create the points
         vtkPoints points = vtkPoints.New();
         for(int i = 0; i < 8; i++)
            points.InsertNextPoint(p[i, 0], p[i, 1], p[i, 2]);

         // Create a hexahedron from the points
         vtkHexahedron hex = vtkHexahedron.New();
         for(int i = 0; i < 8; i++)
            hex.GetPointIds().SetId(i, i);

         // Add the hexahedron to a cell array
         vtkCellArray hexs = vtkCellArray.New();
         hexs.InsertNextCell(hex);

         // Add the points and hexahedron to an unstructured grid
         vtkUnstructuredGrid uGrid = vtkUnstructuredGrid.New();
         uGrid.SetPoints(points);
         uGrid.InsertNextCell(hex.GetCellType(), hex.GetPointIds());

         // Visualize
         vtkDataSetMapper mapper = vtkDataSetMapper.New();
         mapper.SetInput(uGrid);
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
