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
            ShrinkPolyData();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void ShrinkPolyData() {
         vtkSphereSource sphereSource = vtkSphereSource.New();
         sphereSource.SetRadius(10);
         sphereSource.SetPhiResolution(12);
         sphereSource.SetThetaResolution(12);
         sphereSource.Update();

         vtkShrinkPolyData shrinkFilter = vtkShrinkPolyData.New();
         shrinkFilter.SetInputConnection(sphereSource.GetOutputPort());
         shrinkFilter.Update();

         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInputConnection(shrinkFilter.GetOutputPort());

         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);

         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(.2, .3, .4);
         //Add the actors to the renderer, set the background and size 
         renderer.AddActor(actor);
      }
   }
}
