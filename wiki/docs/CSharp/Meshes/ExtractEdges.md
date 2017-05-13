[VTKExamples](Home)/[CSharp](CSharp)/Meshes/ExtractEdges

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Meshes/TestExtractEdges.png" width="256" />

### Description
<p>This example shows how to extract the edges from a PolyData. In this case, we convert a sphere into a wireframe sphere. We demonstrate how to traverse the resulting edges.</p>
A tutorial on how to setup a Windows Forms Application utilizing ActiViz.NET can be found here: [Setup a Windows Forms Application to use ActiViz.NET](http://www.vtk.org/Wiki/VTK/CSharp/ActiViz.NET)<br />
Note: As long as ActiViz.NET is not build with VTK version 6.0 or higher you must define the preprocessor directive VTK_MAJOR_VERSION_5.

**ExtractEdges.cs**
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
            ExtractEdges();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void ExtractEdges() {
         vtkSphereSource sphereSource = vtkSphereSource.New();
         sphereSource.Update();

         Debug.WriteLine("Sphere" + Environment.NewLine + "----------");
         Debug.WriteLine("There are " + sphereSource.GetOutput().GetNumberOfCells() + " cells.");
         Debug.WriteLine("There are " + sphereSource.GetOutput().GetNumberOfPoints() + " points.");

         vtkExtractEdges extractEdges = vtkExtractEdges.New();
#if VTK_MAJOR_VERSION_5
         extractEdges.SetInputConnection(sphereSource.GetOutputPort());
#else
         extractEdges.SetInputData(sphereSource);
#endif
         extractEdges.Update();

         vtkCellArray lines = extractEdges.GetOutput().GetLines();
         vtkPoints points = extractEdges.GetOutput().GetPoints();

         Debug.WriteLine(Environment.NewLine + "Edges" + Environment.NewLine + "----------" );
         Debug.WriteLine("There are " + lines.GetNumberOfCells() + " cells." );
         Debug.WriteLine("There are " + points.GetNumberOfPoints() + " points." );

         // Traverse all of the edges
         for(int i = 0; i < extractEdges.GetOutput().GetNumberOfCells(); i++) {
            //Debug.WriteLine("Type: " + extractEdges.GetOutput().GetCell(i).GetClassName() );
            vtkLine line = vtkLine.SafeDownCast(extractEdges.GetOutput().GetCell(i));
            Debug.WriteLine("Line " + i + " : " + line );
         }

         // Visualize the edges

         // Create a mapper and actor
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
#if VTK_MAJOR_VERSION_5
         mapper.SetInputConnection(extractEdges.GetOutputPort());
#else
         mapper.SetInputData(extractEdges);
#endif
         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);
         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(1, 1, 1);
         // add our actor to the renderer
         renderer.AddActor(actor);
      }
   }
}
```
