[VTKExamples](/home/)/[CSharp](/CSharp)/Meshes/OBBDicer

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Meshes/TestOBBDicer.png?raw=true" width="256" />

### Description
<p>The vtkOBBDicer filter breaks up an input mesh into a number of pieces. The resulting mesh contains scalar point data that can be used to extract the individual pieces with a filter like vtkThresholdFilter. This examples displays the output of vtkOBBDicer with a different color for each piece. </p>
A tutorial on how to setup a Windows Forms Application utilizing ActiViz.NET can be found here: [Setup a Windows Forms Application to use ActiViz.NET](http://www.vtk.org/Wiki/VTK/CSharp/ActiViz.NET)<br />
Note: As long as ActiViz.NET is not build with VTK version 6.0 or higher you must define the preprocessor directive VTK_MAJOR_VERSION_5.

**OBBDicer.cs**
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
            OBBDicer(null);
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void OBBDicer(string filePath) {
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

         // Create pipeline
         vtkOBBDicer dicer = vtkOBBDicer.New();
#if VTK_MAJOR_VERSION_5
         dicer.SetInput(inputPolyData);
#else
         dicer.SetInputData(inputPolyData);
#endif
         dicer.SetNumberOfPieces(4);
         dicer.SetDiceModeToSpecifiedNumberOfPieces();
         dicer.Update();

         vtkPolyDataMapper inputMapper = vtkPolyDataMapper.New();
         inputMapper.SetInputConnection(dicer.GetOutputPort());
         inputMapper.SetScalarRange(0, dicer.GetNumberOfActualPieces());

         Debug.WriteLine("Asked for: "
                   + dicer.GetNumberOfPieces() + " pieces, got: "
                   + dicer.GetNumberOfActualPieces());

         vtkActor inputActor = vtkActor.New();
         inputActor.SetMapper(inputMapper);
         inputActor.GetProperty().SetInterpolationToFlat();

         vtkOutlineCornerFilter outline = vtkOutlineCornerFilter.New();
#if VTK_MAJOR_VERSION_5
         outline.SetInput(inputPolyData);
#else
         outline.SetInputData(inputPolyData);
#endif

         vtkPolyDataMapper outlineMapper = vtkPolyDataMapper.New();
         outlineMapper.SetInputConnection(outline.GetOutputPort());

         vtkActor outlineActor = vtkActor.New();
         outlineActor.SetMapper(outlineMapper);
         outlineActor.GetProperty().SetColor(0, 0, 0);
         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(.2, .3, .4);
         // add our actor to the renderer
         renderer.AddActor(inputActor);
         renderer.AddActor(outlineActor);
      }
   }
}
```
