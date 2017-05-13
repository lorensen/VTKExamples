[VTKExamples](/home/)/[CSharp](/CSharp)/InfoVis/XGMLReader

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/InfoVis/TestXGMLReader.png?raw=true" width="256" />

### Description
This example reads and displays the graph from a gml file. You can test this with VTKData/Data/Infovis/fsm.gml.<br />
A tutorial on how to setup a Windows Forms Application utilizing ActiViz.NET can be found here: [Setup a Windows Forms Application to use ActiViz.NET](http://www.vtk.org/Wiki/VTK/CSharp/ActiViz.NET)

**XGMLReader.cs**
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
            XGMLReader();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void XGMLReader() {
         // Path to vtk data must be set as an environment variable
         // VTK_DATA_ROOT = "C:\VTK\vtkdata-5.8.0"
         vtkTesting test = vtkTesting.New();
         string root = test.GetDataRoot();
         string filePath = System.IO.Path.Combine(root, @"Data\Infovis\fsm.gml");

         vtkXGMLReader reader = vtkXGMLReader.New();
         reader.SetFileName(filePath);
         reader.Update();

         vtkUndirectedGraph g = reader.GetOutput();

         vtkGraphLayoutView graphLayoutView = vtkGraphLayoutView.New();
         graphLayoutView.SetRenderWindow(renderWindowControl1.RenderWindow);
         graphLayoutView.AddRepresentationFromInput(g);
         graphLayoutView.SetLayoutStrategy("Simple 2D");
         graphLayoutView.ResetCamera();
         graphLayoutView.Render();
      }
   }
}
```
