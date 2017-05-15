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
            WeightedTransformFilter();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void WeightedTransformFilter() { 
         // Use a sphere as a basis of the shape
         vtkSphereSource sphere = vtkSphereSource.New();
         sphere.SetPhiResolution(40);
         sphere.SetThetaResolution(40);
         sphere.Update();

         vtkPolyData sphereData = sphere.GetOutput();

         // Create a data array to hold the weighting coefficients
         vtkFloatArray tfarray = vtkFloatArray.New();
         int npoints = sphereData.GetNumberOfPoints();
         tfarray.SetNumberOfComponents(2);
         tfarray.SetNumberOfTuples(npoints);

         // Parameterize the sphere along the z axis, and fill the weights
         // with (1.0-a, a) to linearly interpolate across the shape
         IntPtr pPoint = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(double)) * 3);
         double[] point = new double[3];
         for(int i = 0; i < npoints; i++) {
            sphereData.GetPoint(i, pPoint);
            Marshal.Copy(pPoint, point, 0, 3);
            double x = point[0];
            double y = point[1];
            double z = point[2];

            double zn = z + 0.5;
            double zn1 = 1.0 - zn;
            if(zn > 1.0)
               zn = 1.0;
            if(zn1 < 0.0)
               zn1 = 0.0;

            tfarray.SetComponent(i, 0, zn1);
            tfarray.SetComponent(i, 1, zn);
         }
         Marshal.FreeHGlobal(pPoint);

         // Create field data to hold the array, and bind it to the sphere
         vtkFieldData fd = vtkFieldData.New();
         tfarray.SetName("weights");
         sphereData.GetPointData().AddArray(tfarray);

         // Use an ordinary transform to stretch the shape
         vtkTransform stretch = vtkTransform.New();
         stretch.Scale(1, 1, 3.2);

         vtkTransformFilter stretchFilter = vtkTransformFilter.New();
         stretchFilter.SetInputConnection(sphereData.GetProducerPort());
         stretchFilter.SetTransform(stretch);

         // Now, for the weighted transform stuff
         vtkWeightedTransformFilter weightedTrans = vtkWeightedTransformFilter.New();

         // Create two transforms to interpolate between
         vtkTransform identity = vtkTransform.New();
         identity.Identity();

         vtkTransform rotated = vtkTransform.New();
         double rotatedAngle = 45;
         rotated.RotateX(rotatedAngle);

         weightedTrans.SetNumberOfTransforms(2);
         weightedTrans.SetTransform(identity, 0);
         weightedTrans.SetTransform(rotated, 1);
         // which data array should the filter use ?
         weightedTrans.SetWeightArray("weights");

         weightedTrans.SetInputConnection(stretchFilter.GetOutputPort());

         vtkPolyDataMapper weightedTransMapper = vtkPolyDataMapper.New();
         weightedTransMapper.SetInputConnection(weightedTrans.GetOutputPort());
         vtkActor weightedTransActor = vtkActor.New();
         weightedTransActor.SetMapper(weightedTransMapper);
         weightedTransActor.GetProperty().SetDiffuseColor(0.8, 0.8, 0.1);
         weightedTransActor.GetProperty().SetRepresentationToSurface();

         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(0.2, 0.3, 0.4);
         // add our actor to the renderer
         renderer.AddActor(weightedTransActor);

         renderer.ResetCamera();
         renderer.GetActiveCamera().Azimuth(90);
         renderer.GetActiveCamera().Dolly(1);
      }
   }
}
