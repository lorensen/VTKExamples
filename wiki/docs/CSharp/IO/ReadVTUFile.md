[VTKExamples](Home)/[CSharp](CSharp)/IO/ReadVTUFile

### Description
This examples demonstrates how to read an unstructured grid (VTU) file. 

An example data file (.vtu) for testing can be found in VTKData/Data/quadraticTetra01.vtu.

A tutorial on how to setup a Windows Forms Application utilizing ActiViz.NET can be found here: [Setup a Windows Forms Application to use ActiViz.NET](http://www.vtk.org/Wiki/VTK/CSharp/ActiViz.NET)

**ReadVTUFile.cs**
```csharp
using System;
using System.ComponentModel;
using System.Windows.Forms;

using Kitware.VTK;

namespace ActiViz.Examples {
   public partial class Form1 : Form {
      public Form1() {
         InitializeComponent();
      }


      private void renderWindowControl1_Load(object sender, EventArgs e) {
         try {
            string filePath = @"C:\VTK\vtkdata-5.8.0\Data\quadraticTetra01.vtu";

            // reader
            vtkXMLUnstructuredGridReader reader = vtkXMLUnstructuredGridReader.New();
            if(reader.CanReadFile(filePath) == 0) {
               MessageBox.Show("Cannot read file \"" + filePath + "\"", "Error", MessageBoxButtons.OK);
               return;
            }
            reader.SetFileName(filePath);
            reader.Update(); // here we read the file actually

            // mapper
            vtkDataSetMapper gridMapper = vtkDataSetMapper.New();
            gridMapper.SetInputConnection(reader.GetOutputPort());

            // actor
            vtkActor gridActor = vtkActor.New();
            gridActor.SetMapper(gridMapper);

            // get a reference to the renderwindow of our renderWindowControl1
            vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;

            // renderer
            vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
            // set background color
            renderer.SetBackground(0.2, 0.3, 0.4);

            // add our actor to the renderer
            renderer.AddActor(gridActor);

            // reposition the camera, so that actor can be fully seen
            renderer.ResetCamera();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }
   }
}
```
