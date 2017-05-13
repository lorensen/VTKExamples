[VTKExamples](Home)/[CSharp](CSharp)/GeometricObjects/Frustum

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/GeometricObjects/TestFrustum.png" width="256" />

### Description
This example gets the frustum from a camera and displays it on the screen. <br />
A tutorial on how to setup a Windows Forms Application utilizing ActiViz.NET can be found here: [Setup a Windows Forms Application to use ActiViz.NET](http://www.vtk.org/Wiki/VTK/CSharp/ActiViz.NET)

**Frustum.cs**
```csharp
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
            Frustum();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void Frustum() {
         // Create a frustum.  
         // in this example we need the renderer first to retrieve the active camera
         // in order to get camera's frustum planes
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         vtkCamera camera = renderer.GetActiveCamera();
         double[] aspect = renderer.GetAspect();
         double aspectRatio = aspect[0] / aspect[1];

         // allocate memory for 24 unmanaged doubles
         int size = Marshal.SizeOf(typeof(double)) * 24;
         IntPtr ptr = Marshal.AllocHGlobal(size);
         camera.GetFrustumPlanes(aspectRatio, ptr);
         // in case we would need this values directly we could copy 
         // the unmanaged double array to a managed array like so:

         // double[] planesArray = new double[24];
         // Marshal.Copy(ptr, planesArray, 0, 24);

         // but fortunately we can forward the IntPtr directly to the function 
         // SetFrustumPlanes()
         vtkPlanes planes = vtkPlanes.New();
         planes.SetFrustumPlanes(ptr);
         // free unmanaged memory
         Marshal.FreeHGlobal(ptr);

         vtkFrustumSource frustumSource = vtkFrustumSource.New();
         frustumSource.SetPlanes(planes);
         frustumSource.Update();

         vtkPolyData frustum = frustumSource.GetOutput();
         // Visualize
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInput(frustum);
         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);

         renderer.SetBackground(.2, .1, .3); // Background color dark purple
         renderer.AddActor(actor);
         renderer.ResetCamera();
      }
   }
}
```
