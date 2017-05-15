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
            Planes();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void Planes() {
         // in this example we need the renderer first to retrieve the active camera
         // in order to get camera's frustum planes and renderer's aspectratio
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         vtkRenderer renderer = vtkRenderer.New();
         renderer = renderWindow.GetRenderers().GetFirstRenderer();
         vtkCamera camera = renderer.GetActiveCamera();
         double[] aspect = renderer.GetAspect();
         double aspectRatio = aspect[0] / aspect[1];

         vtkPlanes planes = vtkPlanes.New();
         // one way
         {
            // allocate memory for 24 unmanaged doubles
            int size = Marshal.SizeOf(typeof(double)) * 24;
            IntPtr ptr = Marshal.AllocHGlobal(size);
            camera.GetFrustumPlanes(aspectRatio, ptr);
            // in case we would need this values diectly we could copy 
            // the unmanaged double array to a managed array like so:

            // double[] planesArray = new double[24];
            // Marshal.Copy(ptr, planesArray, 0, 24);

            // but fortunately we can forward the IntPtr directly to the function 
            // SetFrustumPlanes()
            planes.SetFrustumPlanes(ptr);
            // free unmanaged memory
            Marshal.FreeHGlobal(ptr);
         }
         // another way
         {
            vtkSphereSource sphereSource = vtkSphereSource.New();
            sphereSource.Update();
            double[] bounds = new double[6];
            bounds = sphereSource.GetOutput().GetBounds();
            planes.SetBounds(bounds[0], bounds[1], bounds[2], bounds[3], bounds[4], bounds[5]);
         }
         // nothing to visualize
      }
   }
}
