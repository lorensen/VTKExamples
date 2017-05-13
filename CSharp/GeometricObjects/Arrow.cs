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
            Arrow();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void Arrow() {
         // Create two arrows.  
         vtkArrowSource arrowSource01 = vtkArrowSource.New();
         vtkArrowSource arrowSource02 = vtkArrowSource.New();
         arrowSource02.SetShaftResolution(24);   // default = 6
         arrowSource02.SetTipResolution(36);     // default = 6

         // Visualize
         vtkPolyDataMapper mapper01 = vtkPolyDataMapper.New();
         vtkPolyDataMapper mapper02 = vtkPolyDataMapper.New();
         mapper01.SetInputConnection(arrowSource01.GetOutputPort());
         mapper02.SetInputConnection(arrowSource02.GetOutputPort());
         vtkActor actor01= vtkActor.New();
         vtkActor actor02 = vtkActor.New();
         actor01.SetMapper(mapper01);
         actor02.SetMapper(mapper02);
         actor01.SetPosition(0.0,  0.25, 0.0);
         actor02.SetPosition(0.0, -0.25, 0.0);
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         renderer.SetBackground(0.2, 0.3, 0.4);
         renderer.AddActor(actor01);
         renderer.AddActor(actor02);
         renderer.ResetCamera();
      }
   }
}
