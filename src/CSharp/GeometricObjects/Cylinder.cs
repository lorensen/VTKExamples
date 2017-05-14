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
            Cylinder();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void Cylinder() {
         // Create a cylinder.  
         vtkCylinderSource cylinderSource = vtkCylinderSource.New();
         cylinderSource.SetCenter(0.0, 0.0, 0.0);
         cylinderSource.SetRadius(5.0);
         cylinderSource.SetHeight(7.0);
         cylinderSource.SetResolution(36);
         // Visualize
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInputConnection(cylinderSource.GetOutputPort());
         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         renderer.SetBackground(0.1, 0.3, 0.2);
         renderer.AddActor(actor);
         renderer.ResetCamera();
      }
   }
}
