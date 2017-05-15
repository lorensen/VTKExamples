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
            SimplePointsReader();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void SimplePointsReader() {
         // Path to vtk data must be set as an environment variable
         // VTK_DATA_ROOT = "C:\VTK\vtkdata-5.8.0"
         vtkTesting test = vtkTesting.New();
         string root = test.GetDataRoot();
         string filePath = System.IO.Path.Combine(root, @"Data\points.txt");

         vtkSimplePointsReader reader = vtkSimplePointsReader.New();
         reader.SetFileName(filePath);
         reader.Update();
         // Visualize
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInputConnection(reader.GetOutputPort());
         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);
         actor.GetProperty().SetPointSize(4);
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         renderer.SetBackground(0.2, 0.3, 0.4);
         renderer.AddActor(actor);
         //renderer.ResetCamera();
      }
   }
}
