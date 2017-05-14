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
            WindowedSincPolyDataFilter();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void WindowedSincPolyDataFilter() {
         vtkSphereSource sphereSource = vtkSphereSource.New();
         sphereSource.Update();

         vtkWindowedSincPolyDataFilter smoother = vtkWindowedSincPolyDataFilter.New();
         smoother.SetInputConnection(sphereSource.GetOutputPort());
         smoother.SetNumberOfIterations(15);
         smoother.BoundarySmoothingOff();
         smoother.FeatureEdgeSmoothingOff();
         smoother.SetFeatureAngle(120.0);
         smoother.SetPassBand(.001);
         smoother.NonManifoldSmoothingOn();
         smoother.NormalizeCoordinatesOn();
         smoother.Update();

         vtkPolyDataMapper smoothedMapper = vtkPolyDataMapper.New();
#if VTK_MAJOR_VERSION_5
         smoothedMapper.SetInputConnection(smoother.GetOutputPort());
#else
         smoothedMapper.SetInputData(smoother);
#endif
         vtkActor smoothedActor = vtkActor.New();
         smoothedActor.SetMapper(smoothedMapper);

         vtkPolyDataMapper inputMapper = vtkPolyDataMapper.New();
#if VTK_MAJOR_VERSION_5
         inputMapper.SetInputConnection(sphereSource.GetOutputPort());
#else
         inputMapper.SetInputData(sphereSource);
#endif
         vtkActor inputActor = vtkActor.New();
         inputActor.SetMapper(inputMapper);

         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         this.Size = new System.Drawing.Size(612, 352);

         // Define viewport ranges
         // (xmin, ymin, xmax, ymax)
         double[] leftViewport = new double[] { 0.0, 0.0, 0.5, 1.0 };
         double[] rightViewport = new double[] { 0.5, 0.0, 1.0, 1.0 };

         // Setup both renderers
         vtkRenderer leftRenderer = vtkRenderer.New();
         renderWindow.AddRenderer(leftRenderer);
         leftRenderer.SetViewport(leftViewport[0], leftViewport[1], leftViewport[2], leftViewport[3]);
         leftRenderer.SetBackground(.6, .5, .4);

         vtkRenderer rightRenderer = vtkRenderer.New();
         renderWindow.AddRenderer(rightRenderer);
         rightRenderer.SetViewport(rightViewport[0], rightViewport[1], rightViewport[2], rightViewport[3]);
         rightRenderer.SetBackground(.4, .5, .6);

         // Add the sphere to the left and the cube to the right
         leftRenderer.AddActor(inputActor);
         rightRenderer.AddActor(smoothedActor);
         leftRenderer.ResetCamera();
         rightRenderer.ResetCamera();
         renderWindow.Render();
      }
   }
}
