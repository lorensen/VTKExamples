[VTKExamples](/index/)/[CSharp](/CSharp)/PolyData/ColorDisconnectedRegions

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestColorDisconnectedRegions.png?raw=true" width="256" />

### Description
A tutorial on how to setup a Windows Forms Application utilizing ActiViz.NET can be found here: [Setup a Windows Forms Application to use ActiViz.NET](http://www.vtk.org/Wiki/VTK/CSharp/ActiViz.NET)

**ColorDisconnectedRegions.cs**
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
            ColorDisconnectedRegions();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void ColorDisconnectedRegions() {
         // Create some spheres
         vtkSphereSource sphereSource1 = vtkSphereSource.New();
         sphereSource1.Update();

         vtkSphereSource sphereSource2 = vtkSphereSource.New();
         sphereSource2.SetCenter(5, 0, 0);
         sphereSource2.Update();

         vtkSphereSource sphereSource3 = vtkSphereSource.New();
         sphereSource3.SetCenter(10, 0, 0);
         sphereSource3.Update();

         vtkAppendPolyData appendFilter = vtkAppendPolyData.New();
         appendFilter.AddInputConnection(sphereSource1.GetOutputPort());
         appendFilter.AddInputConnection(sphereSource2.GetOutputPort());
         appendFilter.AddInputConnection(sphereSource3.GetOutputPort());

         vtkPolyDataConnectivityFilter connectivityFilter = vtkPolyDataConnectivityFilter.New();
         connectivityFilter.SetInputConnection(appendFilter.GetOutputPort());
         connectivityFilter.SetExtractionModeToAllRegions();
         connectivityFilter.ColorRegionsOn();
         connectivityFilter.Update();

         // Visualize
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInputConnection(connectivityFilter.GetOutputPort());
         double[] range = connectivityFilter.GetOutput().GetPointData().GetArray("RegionId").GetRange();
         mapper.SetScalarRange(range[0], range[1] );

         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);
         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(0.0, 0.0, 0.0);
         // add our actor to the renderer
         renderer.AddActor(actor);
      }
   }
}
```
