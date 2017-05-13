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
            Polygon();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void Polygon() {
         // Setup four points
         vtkPoints points = vtkPoints.New();
         double c = Math.Cos(Math.PI / 6); // helper variable

         points.InsertNextPoint(0.0, -1.0, 0.0);
         points.InsertNextPoint(c, -0.5, 0.0);
         points.InsertNextPoint(c, 0.5, 0.0);
         points.InsertNextPoint(0.0, 1.0, 0.0);
         points.InsertNextPoint(-c, 0.5, 0.0);
         points.InsertNextPoint(-c, -0.5, 0.0);

         // Create the polygon
         vtkPolygon polygon = vtkPolygon.New();
         polygon.GetPointIds().SetNumberOfIds(6); //make a six-sided figure
         polygon.GetPointIds().SetId(0, 0);
         polygon.GetPointIds().SetId(1, 1);
         polygon.GetPointIds().SetId(2, 2);
         polygon.GetPointIds().SetId(3, 3);
         polygon.GetPointIds().SetId(4, 4);
         polygon.GetPointIds().SetId(5, 5);

         // Add the polygon to a list of polygons
         vtkCellArray polygons = vtkCellArray.New();
         polygons.InsertNextCell(polygon);

         // Create a PolyData
         vtkPolyData polygonPolyData = vtkPolyData.New();
         polygonPolyData.SetPoints(points);
         polygonPolyData.SetPolys(polygons);

         // Create a mapper and actor
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInput(polygonPolyData);
         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         renderer.SetBackground(0.2, 0.3, 0.4);
         renderer.AddActor(actor);
         renderer.ResetCamera();
      }
   }
}
