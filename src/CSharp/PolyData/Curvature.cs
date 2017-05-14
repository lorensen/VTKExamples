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
            Curvature();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void Curvature() {
         // Path to vtk data must be set as an environment variable
         // VTK_DATA_ROOT = "C:\VTK\vtkdata-5.8.0"
         vtkTesting test = vtkTesting.New();
         string root = test.GetDataRoot();
         // note: one should use a coarse surface mesh to achieve a good visual effect
         string filePath = System.IO.Path.Combine(root, @"Data\bunny.vtp");
         // Create a polydata
         vtkXMLPolyDataReader reader = vtkXMLPolyDataReader.New();
         reader.SetFileName(filePath);

         vtkCurvatures curvaturesFilter = vtkCurvatures.New();
         curvaturesFilter.SetInputConnection(reader.GetOutputPort());
         //curvaturesFilter.SetCurvatureTypeToGaussian();
         //curvaturesFilter.SetCurvatureTypeToMean();
         //curvaturesFilter.SetCurvatureTypeToMaximum();
         curvaturesFilter.SetCurvatureTypeToMinimum();

         // To inspect more closely, if required
         vtkXMLPolyDataWriter writer = vtkXMLPolyDataWriter.New();
         writer.SetInputConnection(curvaturesFilter.GetOutputPort());
         writer.SetFileName(System.IO.Path.Combine(root, @"Data\gauss.vtp"));
         writer.Write();

         // Create a mapper and actor
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInputConnection(curvaturesFilter.GetOutputPort());
         double[] range = curvaturesFilter.GetOutput().GetScalarRange();
         mapper.SetScalarRange(range[0], range[1]);
         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);
         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(0.0, 0.0, 0.0);
         // add our actor to the renderer
         renderer.AddActor(actor);
      }
   }
}
