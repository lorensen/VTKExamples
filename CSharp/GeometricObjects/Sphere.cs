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
            Sphere();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void Sphere() {
         // Create a sphere.  
         vtkSphereSource sphereSource = vtkSphereSource.New();
         sphereSource.SetRadius(0.5);
         // a more smoother sphere
         //sphereSource.SetPhiResolution(36);
         //sphereSource.SetThetaResolution(36);

         //not a complete sphere, only a spherical shell
         //sphereSource.SetEndPhi(120);
         //sphereSource.SetEndTheta(90);

         // Visualize
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInputConnection(sphereSource.GetOutputPort());
         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         renderer.SetBackground(0.3, 0.2, 0.1);
         renderer.AddActor(actor);
      }
   }
}
