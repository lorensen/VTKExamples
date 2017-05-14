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
