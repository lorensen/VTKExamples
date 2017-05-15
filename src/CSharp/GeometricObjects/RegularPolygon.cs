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
            RegularPolygon();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void RegularPolygon() {
         // Create a pentagon
         vtkRegularPolygonSource polygonSource = vtkRegularPolygonSource.New();

         //polygonSource.GeneratePolygonOff();
         polygonSource.SetNumberOfSides(5);
         polygonSource.SetRadius(5);
         polygonSource.SetCenter(0, 0, 0);
         //polygonSource.Update(); // not necessary

         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInputConnection(polygonSource.GetOutputPort());
         vtkActor actor = vtkActor.New();
         actor.GetProperty().SetLineWidth(4);
         actor.SetMapper(mapper);
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         renderer.SetBackground(0.2, 0.3, 0.4);
         renderer.AddActor(actor);
      }
   }
}
