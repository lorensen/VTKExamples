[VTKExamples](/home/)/[CSharp](/CSharp)/Meshes/CapClip

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Meshes/TestCapClip.png?raw=true" width="256" />

### Description
<p>This example shows how to generate a "cap" on a clipped polydata. It uses a clever trick to convert polylines into polygons. If a polydata file (.vtp) is provided, it will cap it. Otherwise it caps a clipped sphere.</p>
A tutorial on how to setup a Windows Forms Application utilizing ActiViz.NET can be found here: [Setup a Windows Forms Application to use ActiViz.NET](http://www.vtk.org/Wiki/VTK/CSharp/ActiViz.NET)<br />
Note: As long as ActiViz.NET is not build with VTK version 6.0 or higher you have to define the preprocessor directive VTK_MAJOR_VERSION_5.

**CapClip.cs**
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
            CapClip(null);
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void CapClip(string filePath) {
         // PolyData to process
         vtkPolyData polyData;

         if(filePath != null) {
            vtkXMLPolyDataReader reader = vtkXMLPolyDataReader.New();
            reader.SetFileName(filePath);
            reader.Update();
            polyData = reader.GetOutput();
         }
         else {
            // Create a sphere
            vtkSphereSource sphereSource = vtkSphereSource.New();
            sphereSource.SetThetaResolution(20);
            sphereSource.SetPhiResolution(11);

            vtkPlane plane = vtkPlane.New();
            plane.SetOrigin(0, 0, 0);
            plane.SetNormal(1.0, -1.0, -1.0);

            vtkClipPolyData clipper = vtkClipPolyData.New();
            clipper.SetInputConnection(sphereSource.GetOutputPort());
            clipper.SetClipFunction(plane);
            clipper.SetValue(0);
            clipper.Update();

            polyData = clipper.GetOutput();
         }

         vtkDataSetMapper clipMapper = vtkDataSetMapper.New();
#if VTK_MAJOR_VERSION_5
         clipMapper.SetInput(polyData);
#else
         clipMapper.SetInputData(polyData);
#endif

         vtkActor clipActor = vtkActor.New();
         clipActor.SetMapper(clipMapper);
         clipActor.GetProperty().SetColor(1.0000, 0.3882, 0.2784);
         clipActor.GetProperty().SetInterpolationToFlat();

         // Now extract feature edges
         vtkFeatureEdges boundaryEdges = vtkFeatureEdges.New();
#if VTK_MAJOR_VERSION_5
         boundaryEdges.SetInput(polyData);
#else
         boundaryEdges.SetInputData(polyData);
#endif
         boundaryEdges.BoundaryEdgesOn();
         boundaryEdges.FeatureEdgesOff();
         boundaryEdges.NonManifoldEdgesOff();
         boundaryEdges.ManifoldEdgesOff();

         vtkStripper boundaryStrips = vtkStripper.New();
         boundaryStrips.SetInputConnection(boundaryEdges.GetOutputPort());
         boundaryStrips.Update();

         // Change the polylines into polygons
         vtkPolyData boundaryPoly = vtkPolyData.New();
         boundaryPoly.SetPoints(boundaryStrips.GetOutput().GetPoints());
         boundaryPoly.SetPolys(boundaryStrips.GetOutput().GetLines());

         vtkPolyDataMapper boundaryMapper = vtkPolyDataMapper.New();
#if VTK_MAJOR_VERSION_5
         boundaryMapper.SetInput(boundaryPoly);
#else
         boundaryMapper.SetInputData(boundaryPoly);
#endif

         vtkActor boundaryActor = vtkActor.New();
         boundaryActor.SetMapper(boundaryMapper);
         boundaryActor.GetProperty().SetColor(0.8900, 0.8100, 0.3400);
         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(.2, .3, .4);
         // add our actor to the renderer
         renderer.AddActor(clipActor);
         renderer.AddActor(boundaryActor);
         // Generate an interesting view
         //
         renderer.ResetCamera();
         renderer.GetActiveCamera().Azimuth(30);
         renderer.GetActiveCamera().Elevation(30);
         renderer.GetActiveCamera().Dolly(1.2);
         renderer.ResetCameraClippingRange();
      }
   }
}
```
