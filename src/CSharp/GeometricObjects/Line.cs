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
