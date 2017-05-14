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
            ContoursFromPolyData(null);
            //ContoursFromPolyData(@"c:\vtk\vtkdata-5.8.0\Data\bunny.vtp");
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }

      private void ContoursFromPolyData(string filePath) {
         vtkPolyData inputPolyData;
         if(filePath != null) {
            vtkXMLPolyDataReader reader = vtkXMLPolyDataReader.New();
            reader.SetFileName(filePath);
            reader.Update();
            inputPolyData = reader.GetOutput();
         }
         else {
            vtkSphereSource sphereSource = vtkSphereSource.New();
            sphereSource.SetThetaResolution(30);
            sphereSource.SetPhiResolution(15);
            sphereSource.Update();
            inputPolyData = sphereSource.GetOutput();
         }

         vtkPolyDataMapper inputMapper = vtkPolyDataMapper.New();
#if VTK_MAJOR_VERSION_5
         inputMapper.SetInput(inputPolyData);
#else
         inputMapper.SetInputData(inputPolyData);
#endif

         // Create a plane to cut
         vtkPlane plane = vtkPlane.New();
         double[] center = inputPolyData.GetCenter();
         double[] bounds = inputPolyData.GetBounds();
         plane.SetOrigin(center[0], center[1], center[2]);
         plane.SetNormal(1, 1, 1);


         float[] centerf = new float[] { (float)center[0], (float)center[1], (float)center[2] };
         float[] minBoundf = new float[] { (float)bounds[0], (float)bounds[2], (float)bounds[4] };
         float[] maxBoundf = new float[] { (float)bounds[1], (float)bounds[3], (float)bounds[5] };
         IntPtr pCenter = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(float)) * 3);
         IntPtr pMinBound = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(float)) * 3);
         IntPtr pMaxBound = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(float)) * 3);
         Marshal.Copy(centerf, 0, pCenter, 3);
         Marshal.Copy(minBoundf, 0, pMinBound, 3);
         Marshal.Copy(maxBoundf, 0, pMaxBound, 3);

         // vtkMath.Distance2BetweenPoints accepts floats only
         double distanceMin = Math.Sqrt(vtkMath.Distance2BetweenPoints(pMinBound, pCenter));
         double distanceMax = Math.Sqrt(vtkMath.Distance2BetweenPoints(pMaxBound, pCenter));

         Marshal.FreeHGlobal(pCenter);
         Marshal.FreeHGlobal(pMinBound);
         Marshal.FreeHGlobal(pMaxBound);
         // Create cutter
         vtkCutter cutter = vtkCutter.New();
         cutter.SetCutFunction(plane);
#if VTK_MAJOR_VERSION_5
         cutter.SetInput(inputPolyData);
#else
         cutter.SetInputData(inputPolyData);
#endif
         cutter.GenerateValues(20, -distanceMin, distanceMax);
         vtkPolyDataMapper cutterMapper = vtkPolyDataMapper.New();
         cutterMapper.SetInputConnection(cutter.GetOutputPort());
         cutterMapper.ScalarVisibilityOff();

         // Create plane actor
         vtkActor planeActor = vtkActor.New();
         planeActor.GetProperty().SetColor(1.0, 0.0, 0.0);
         planeActor.GetProperty().SetLineWidth(3);
         planeActor.SetMapper(cutterMapper);

         // Create input actor
         vtkActor inputActor = vtkActor.New();
         inputActor.GetProperty().SetColor(1.0, 0.8941, 0.7686); // bisque
         inputActor.SetMapper(inputMapper);

         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(.2, .3, .4);
         renderer.AddActor(inputActor); 
         renderer.AddActor(planeActor); //display the contour lines
      }
   }
}
