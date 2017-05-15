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
            vtkPolyDataConnectivityFilter_LargestRegion();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void vtkPolyDataConnectivityFilter_LargestRegion() {
         // Small sphere
         vtkSphereSource sphereSource1 = vtkSphereSource.New();
         sphereSource1.Update();

         // Large sphere
         vtkSphereSource sphereSource2 = vtkSphereSource.New();
         sphereSource2.SetRadius(10);
         sphereSource2.SetCenter(25, 0, 0);
         sphereSource2.SetThetaResolution(10);
         sphereSource2.SetPhiResolution(10);
         sphereSource2.Update();

         vtkAppendPolyData appendFilter = vtkAppendPolyData.New();
         appendFilter.AddInputConnection(sphereSource1.GetOutputPort());
         appendFilter.AddInputConnection(sphereSource2.GetOutputPort());
         appendFilter.Update();

         vtkPolyDataConnectivityFilter connectivityFilter = vtkPolyDataConnectivityFilter.New();
         connectivityFilter.SetInputConnection(appendFilter.GetOutputPort());
         connectivityFilter.SetExtractionModeToLargestRegion();
         connectivityFilter.Update();

         // Create a mapper and actor for original data
         vtkPolyDataMapper originalMapper = vtkPolyDataMapper.New();
         originalMapper.SetInputConnection(appendFilter.GetOutputPort());
         originalMapper.Update();

         vtkActor originalActor = vtkActor.New();
         originalActor.SetMapper(originalMapper);

         // Create a mapper and actor for extracted data
         vtkPolyDataMapper extractedMapper = vtkPolyDataMapper.New();
         extractedMapper.SetInputConnection(connectivityFilter.GetOutputPort());
         extractedMapper.Update();

         vtkActor extractedActor = vtkActor.New();
         extractedActor.GetProperty().SetColor(1, 0, 0);
         extractedActor.SetMapper(extractedMapper);
         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(0.2, 0.3, 0.4);
         // add our actor to the renderer
         renderer.AddActor(originalActor);
         renderer.AddActor(extractedActor);
      }
   }
}
