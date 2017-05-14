[VTKExamples](/index/)/[CSharp](/CSharp)/IO/ParticleReader

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/IO/TestParticleReader.png?raw=true" width="256" />

### Description
This example reads ascii files where each line consists of points with its position (x,y,z) and (optionally) <u>one</u> scalar
or binary files in RAW 3d file format.<br />
A tutorial on how to setup a Windows Forms Application utilizing ActiViz.NET can be found here: [Setup a Windows Forms Application to use ActiViz.NET](http://www.vtk.org/Wiki/VTK/CSharp/ActiViz.NET)

**ParticleReader.cs**
```csharp
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

using Kitware.VTK;

namespace ActiViz.Examples {
   public partial class Form1 : Form {
      public Form1() {
         InitializeComponent();
      }


      private void renderWindowControl1_Load(object sender, EventArgs e) {
         try {
            ParticleReader();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void ParticleReader() {
         // Path to vtk data must be set as an environment variable
         // VTK_DATA_ROOT = "C:\VTK\vtkdata-5.8.0"
         vtkTesting test = vtkTesting.New();
         string root = test.GetDataRoot();
         string filePath = System.IO.Path.Combine(root, @"Data\Particles.raw");
         
         // Read the file
         vtkParticleReader reader = vtkParticleReader.New();
         reader.SetFileName(filePath);
         reader.SetDataByteOrderToBigEndian();
         reader.Update();
         Debug.WriteLine("NumberOfPieces: " + reader.GetOutput().GetNumberOfPieces());

         // Visualize
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInputConnection(reader.GetOutputPort());
         mapper.SetScalarRange(4, 9);
         mapper.SetPiece(1);

         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);
         actor.GetProperty().SetPointSize(4);
         actor.GetProperty().SetColor(1, 0, 0);
         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(0.2, 0.3, 0.4);
         // add our actor to the renderer
         renderer.AddActor(actor);
      }
   }
}
```
