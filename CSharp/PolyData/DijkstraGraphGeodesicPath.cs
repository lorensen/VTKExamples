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
            DijkstraGraphGeodesicPath();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void DijkstraGraphGeodesicPath() {
         // Create a sphere
         vtkSphereSource sphereSource = vtkSphereSource.New();
         sphereSource.Update();

         vtkDijkstraGraphGeodesicPath dijkstra = vtkDijkstraGraphGeodesicPath.New();
         dijkstra.SetInputConnection(sphereSource.GetOutputPort());
         dijkstra.SetStartVertex(0);
         dijkstra.SetEndVertex(10);
         dijkstra.Update();

         // Create a mapper and actor
         vtkPolyDataMapper pathMapper = vtkPolyDataMapper.New();
         pathMapper.SetInputConnection(dijkstra.GetOutputPort());

         vtkActor pathActor = vtkActor.New();
         pathActor.SetMapper(pathMapper);
         pathActor.GetProperty().SetColor(1, 0, 0); // Red
         pathActor.GetProperty().SetLineWidth(4);

         // Create a mapper and actor
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInputConnection(sphereSource.GetOutputPort());

         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);

         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(0.3, 0.6, 0.3);
         // add our actor to the renderer
         renderer.AddActor(actor);
         renderer.AddActor(pathActor);
      }
   }
}
