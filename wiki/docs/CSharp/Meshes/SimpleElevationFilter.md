[VTKExamples](/index/)/[CSharp](/CSharp)/Meshes/SimpleElevationFilter

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Meshes/TestSimpleElevationFilter.png?raw=true" width="256" />

### Description
A tutorial on how to setup a Windows Forms Application utilizing ActiViz.NET can be found here: [Setup a Windows Forms Application to use ActiViz.NET](http://www.vtk.org/Wiki/VTK/CSharp/ActiViz.NET)<br />
Note: As long as ActiViz.NET is not build with VTK version 6.0 or higher you must define the preprocessor directive VTK_MAJOR_VERSION_5.

**SimpleElevationFilter.cs**
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
            SimpleElevationFilter();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void SimpleElevationFilter() {
         // Created a grid of points (heigh/terrian map)
         vtkPoints points = vtkPoints.New();

         uint GridSize = 10;
         for(uint x = 0; x < GridSize; x++) {
            for(uint y = 0; y < GridSize; y++) {
               points.InsertNextPoint(x, y, ( x + y ) / ( y + 1 ));
            }
         }
         double[] bounds = points.GetBounds();

         // Add the grid points to a polydata object
         vtkPolyData inputPolyData = vtkPolyData.New();
         inputPolyData.SetPoints(points);

         // Triangulate the grid points
         vtkDelaunay2D delaunay = vtkDelaunay2D.New();
#if VTK_MAJOR_VERSION_5
         delaunay.SetInput(inputPolyData);
#else
         delaunay.SetInputData(inputPolyData);
#endif
         delaunay.Update();

         vtkSimpleElevationFilter elevationFilter = vtkSimpleElevationFilter.New();
         elevationFilter.SetInputConnection(delaunay.GetOutputPort());
         elevationFilter.SetVector(0.0, 0.0, 1.0);
         elevationFilter.Update();

         vtkPolyData output = vtkPolyData.New();
         output.ShallowCopy(vtkPolyData.SafeDownCast(elevationFilter.GetOutput()));

         vtkFloatArray elevation = 
            vtkFloatArray.SafeDownCast(output.GetPointData().GetArray("Elevation"));

         // Create the color map
         vtkLookupTable colorLookupTable = vtkLookupTable.New();
         colorLookupTable.SetTableRange(bounds[4], bounds[5]);
         colorLookupTable.Build();

         // Generate the colors for each point based on the color map
         vtkUnsignedCharArray colors = vtkUnsignedCharArray.New();
         colors.SetNumberOfComponents(3);
         colors.SetName("Colors");

         for(int i = 0; i < output.GetNumberOfPoints(); i++) {
            double val = elevation.GetValue(i);
            Debug.WriteLine("val: " + val);

            double[] dcolor = colorLookupTable.GetColor(val);
            //Debug.WriteLine("dcolor: "
            //          + dcolor[0] + " "
            //          + dcolor[1] + " "
            //          + dcolor[2]);
            byte[] color = new byte[3];
            for(int j = 0; j < 3; j++) {
               color[j] = (byte)( 255 * dcolor[j] );
            }
            //Debug.WriteLine("color: "
            //          + color[0] + " "
            //          + color[1] + " "
            //          + color[2]);

            colors.InsertNextTuple3(color[0], color[1], color[2]);
         }

         output.GetPointData().AddArray(colors);

         // Visualize
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
#if VTK_MAJOR_VERSION_5
         mapper.SetInputConnection(output.GetProducerPort());
#else
         mapper.SetInputData(output);
#endif

         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);

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
