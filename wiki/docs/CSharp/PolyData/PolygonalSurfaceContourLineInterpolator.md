[VTKExamples](/home/)/[CSharp](/CSharp)/PolyData/PolygonalSurfaceContourLineInterpolator

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestPolygonalSurfaceContourLineInterpolator.png?raw=true" width="256" />

### Description
A tutorial on how to setup a Windows Forms Application utilizing ActiViz.NET can be found here: [Setup a Windows Forms Application to use ActiViz.NET](http://www.vtk.org/Wiki/VTK/CSharp/ActiViz.NET)<br />
Note: As long as ActiViz.NET is not build with VTK version 6.0 or higher you must define the preprocessor directive VTK_MAJOR_VERSION_5.

**PolygonalSurfaceContourLineInterpolator.cs**
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
            PolygonalSurfaceContourLineInterpolator();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void PolygonalSurfaceContourLineInterpolator() { 
         vtkPolyData polyData;
         vtkSphereSource sphereSource = vtkSphereSource.New();
         sphereSource.SetThetaResolution(40);
         sphereSource.SetPhiResolution(20);
         sphereSource.Update();

         polyData = sphereSource.GetOutput();
         // The Dijkstra interpolator will not accept cells that aren't triangles
         vtkTriangleFilter triangleFilter = vtkTriangleFilter.New();
#if VTK_MAJOR_VERSION_5
         triangleFilter.SetInput( polyData );
#else
         triangleFilter.SetInputData( polyData );
#endif
         triangleFilter.Update();

         vtkPolyData pd = triangleFilter.GetOutput();

         //Create a mapper and actor
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInputConnection(triangleFilter.GetOutputPort());

         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);
         actor.GetProperty().SetInterpolationToFlat();

         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(0.3, 0.4, 0.5);
         // add our actor to the renderer
         renderer.AddActor(actor);

         // Here comes the contour widget stuff.....
         vtkContourWidget contourWidget = vtkContourWidget.New();
         contourWidget.SetInteractor(renderWindow.GetInteractor());
         vtkOrientedGlyphContourRepresentation rep = 
            vtkOrientedGlyphContourRepresentation.SafeDownCast(
               contourWidget.GetRepresentation());
         rep.GetLinesProperty().SetColor(1, 0.2, 0);
         rep.GetLinesProperty().SetLineWidth(3.0f);

         vtkPolygonalSurfacePointPlacer pointPlacer = 
            vtkPolygonalSurfacePointPlacer.New();
         pointPlacer.AddProp(actor);
         pointPlacer.GetPolys().AddItem(pd);
         rep.SetPointPlacer(pointPlacer);

         vtkPolygonalSurfaceContourLineInterpolator interpolator = 
            vtkPolygonalSurfaceContourLineInterpolator.New();
         interpolator.GetPolys().AddItem(pd);
         rep.SetLineInterpolator(interpolator);

         renderWindow.Render();
         contourWidget.EnabledOn();
      }
   }
}
```
