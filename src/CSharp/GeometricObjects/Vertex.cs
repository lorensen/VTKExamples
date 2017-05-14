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
            Vertex();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void Vertex() {
         vtkPoints points = vtkPoints.New();
         points.InsertNextPoint(0, 0, 0);

         vtkVertex vertex = vtkVertex.New();
         vertex.GetPointIds().SetId(0, 0);

         vtkCellArray vertices = vtkCellArray.New();
         vertices.InsertNextCell(vertex);

         vtkPolyData polydata = vtkPolyData.New();
         polydata.SetPoints(points);
         polydata.SetVerts(vertices);

         // Visualize
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInputConnection(polydata.GetProducerPort());
         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);
         actor.GetProperty().SetPointSize(10);
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         renderer.SetBackground(0.2, 0.3, 0.4);
         // Add the actor to the scene
         renderer.AddActor(actor);
      }
   }
}
