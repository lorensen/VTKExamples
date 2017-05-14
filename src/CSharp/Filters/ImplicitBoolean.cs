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
            ImplicitBoolean();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void ImplicitBoolean() {
         vtkSphere sphere1 = vtkSphere.New();
         sphere1.SetCenter(.9, 0, 0);
         vtkSphere sphere2 = vtkSphere.New();
         sphere2.SetCenter(-.9, 0, 0);

         vtkImplicitBoolean implicitBoolean = vtkImplicitBoolean.New();
         implicitBoolean.AddFunction(sphere1);
         implicitBoolean.AddFunction(sphere2);
         implicitBoolean.SetOperationTypeToUnion();
         //implicitBoolean.SetOperationTypeToIntersection();

         // Sample the function
         vtkSampleFunction sample = vtkSampleFunction.New();
         sample.SetSampleDimensions(50, 50, 50);
         sample.SetImplicitFunction(implicitBoolean);
         double value = 3.0;
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
         renderer.AddActor(contourActor);
      }
   }
}
