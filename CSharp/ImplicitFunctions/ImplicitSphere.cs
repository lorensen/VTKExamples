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
            ImplicitSphere();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void ImplicitSphere() {
         vtkSphere sphere = vtkSphere.New();

         // Sample the function
         vtkSampleFunction sample = vtkSampleFunction.New();
         sample.SetSampleDimensions(50, 50, 50);
         sample.SetImplicitFunction(sphere);
         double value = 2.0;
         double xmin = -value, xmax = value,
                ymin = -value, ymax = value,
                zmin = -value, zmax = value;
         sample.SetModelBounds(xmin, xmax, ymin, ymax, zmin, zmax);

         // Create the 0 isosurface
         vtkContourFilter contours = vtkContourFilter.New();
#if VTK_MAJOR_VERSION_5
         contours.SetInputConnection(sample.GetOutputPort());
#else
         contours.SetInputData(sample);
#endif
         contours.GenerateValues(1, 1, 1);

         // Map the contours to graphical primitives
         vtkPolyDataMapper contourMapper = vtkPolyDataMapper.New();
#if VTK_MAJOR_VERSION_5
         contourMapper.SetInputConnection(contours.GetOutputPort());
#else
         contourMapper.SetInputData(contours);
#endif
         contourMapper.ScalarVisibilityOff();

         // Create an actor for the contours
         vtkActor contourActor = vtkActor.New();
         contourActor.SetMapper(contourMapper);

         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(.2, .3, .4);
         // add our actor to the renderer
         renderer.AddActor(contourActor);
      }
   }
}
