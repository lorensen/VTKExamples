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
            ColoredLines();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void ColoredLines() {
         // Create three points. Join (Origin and P0) with a red line and
         // (Origin and P1) with a green line
         double[] origin = new double[] { 0.0, 0.0, 0.0 };
         double[] p0 = new double[] { 1.0, 0.0, 0.0 };
         double[] p1 = new double[] { 0.0, 1.0, 0.0 };

         // Create a vtkPoints object and store the points in it
         vtkPoints pts = vtkPoints.New();
         pts.InsertNextPoint(origin[0], origin[1], origin[2]);
         pts.InsertNextPoint(p0[0], p0[1], p0[2]);
         pts.InsertNextPoint(p1[0], p1[1], p1[2]);

         // Setup two colors - one for each line
         byte[] red = new byte[] { 255, 0, 0 };
         byte[] green = new byte[] { 0, 255, 0 };

         // Setup the colors array
         vtkUnsignedCharArray colors = vtkUnsignedCharArray.New();
         colors.SetNumberOfComponents(3);
         colors.SetName("Colors");

         // Add the colors we created to the colors array
         colors.InsertNextValue(red[0]);
         colors.InsertNextValue(red[1]);
         colors.InsertNextValue(red[2]);

         colors.InsertNextValue(green[0]);
         colors.InsertNextValue(green[1]);
         colors.InsertNextValue(green[2]);

         // Create the first line (between Origin and P0)
         vtkLine line0 = vtkLine.New();
         line0.GetPointIds().SetId(0, 0); //the second 0 is the index of the Origin in the vtkPoints
         line0.GetPointIds().SetId(1, 1); //the second 1 is the index of P0 in the vtkPoints

         // Create the second line (between Origin and P1)
         vtkLine line1 = vtkLine.New();
         line1.GetPointIds().SetId(0, 0); //the second 0 is the index of the Origin in the vtkPoints
         line1.GetPointIds().SetId(1, 2); //2 is the index of P1 in the vtkPoints

         // Create a cell array to store the lines in and add the lines to it
         vtkCellArray lines = vtkCellArray.New();
         lines.InsertNextCell(line0);
         lines.InsertNextCell(line1);

         // Create a polydata to store everything in
         vtkPolyData linesPolyData = vtkPolyData.New();

         // Add the points to the dataset
         linesPolyData.SetPoints(pts);

         // Add the lines to the dataset
         linesPolyData.SetLines(lines);

         // Color the lines - associate the first component (red) of the
         // colors array with the first component of the cell array (line 0)
         // and the second component (green) of the colors array with the
         // second component of the cell array (line 1)
         linesPolyData.GetCellData().SetScalars(colors);

         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInput(linesPolyData);
         // create an actor
         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);

         // a renderer and render window
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         renderer.SetBackground(0.2, 0.3, 0.4);

         // add the actors to the scene
         renderer.AddActor(actor);
      }
   }
}
