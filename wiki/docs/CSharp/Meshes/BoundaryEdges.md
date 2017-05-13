[VTKExamples](/home/)/[CSharp](/CSharp)/Meshes/BoundaryEdges

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Meshes/TestBoundaryEdges.png?raw=true" width="256" />

### Description
<p>This filter will extract the boundary edges of a mesh. The original mesh is shown with the feature edges shown in red. </p>
A tutorial on how to setup a Windows Forms Application utilizing ActiViz.NET can be found here: [Setup a Windows Forms Application to use ActiViz.NET](http://www.vtk.org/Wiki/VTK/CSharp/ActiViz.NET)<br />
Note: As long as ActiViz.NET is not build with VTK version 6.0 or higher you must define the preprocessor directive VTK_MAJOR_VERSION_5.

**BoundaryEdges.cs**
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
            BoundaryEdges();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void BoundaryEdges() {
         vtkDiskSource diskSource = vtkDiskSource.New();
         diskSource.Update();

         vtkFeatureEdges featureEdges = vtkFeatureEdges.New();
#if VTK_MAJOR_VERSION_5
         featureEdges.SetInputConnection(diskSource.GetOutputPort());
#else
         featureEdges.SetInputData(diskSource);
#endif
         featureEdges.BoundaryEdgesOn();
         featureEdges.FeatureEdgesOff();
         featureEdges.ManifoldEdgesOff();
         featureEdges.NonManifoldEdgesOff();
         featureEdges.Update();

         // Visualize
         vtkPolyDataMapper edgeMapper = vtkPolyDataMapper.New();
#if VTK_MAJOR_VERSION_5
         edgeMapper.SetInputConnection(featureEdges.GetOutputPort());
#else
         edgeMapper.SetInputData(featureEdges);
#endif
         vtkActor edgeActor = vtkActor.New();
         edgeActor.GetProperty().SetLineWidth(3);
         edgeActor.SetMapper(edgeMapper);

         vtkPolyDataMapper diskMapper = vtkPolyDataMapper.New();
#if VTK_MAJOR_VERSION_5
         diskMapper.SetInputConnection(diskSource.GetOutputPort());
#else
         diskMapper.SetInputData(diskSource);
#endif
         vtkActor diskActor = vtkActor.New();
         diskActor.SetMapper(diskMapper);

         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(0.3, 0.6, 0.3);
         // add our actor to the renderer
         renderer.AddActor(diskActor);
         renderer.AddActor(edgeActor);
      }
   }
}
```
