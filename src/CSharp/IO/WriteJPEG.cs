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
            WriteJPEG();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void WriteJPEG() {
         // Path to vtk data must be set as an environment variable
         // VTK_DATA_ROOT = "C:\VTK\vtkdata-5.8.0"
         vtkTesting test = vtkTesting.New();
         string root = test.GetDataRoot();
         string filePath = System.IO.Path.Combine(root, @"Data\test_jpeg.jpg");
         int[] extent = new int[] { 0, 99, 0, 99, 0, 0 };
         vtkImageCanvasSource2D imageSource = vtkImageCanvasSource2D.New();
         imageSource.SetExtent(extent[0], extent[1], extent[2], extent[3], extent[4], extent[5]);
         imageSource.SetScalarTypeToUnsignedChar();
         imageSource.SetNumberOfScalarComponents(3);
         imageSource.SetDrawColor(127, 45, 255);
         imageSource.FillBox(0, 99, 0, 99);
         imageSource.SetDrawColor(255, 255, 255);
         imageSource.FillBox(40, 70, 20, 50);
         imageSource.Update();

         vtkImageCast castFilter = vtkImageCast.New();
         castFilter.SetOutputScalarTypeToUnsignedChar();
         castFilter.SetInputConnection(imageSource.GetOutputPort());
         castFilter.Update();

         vtkJPEGWriter writer = vtkJPEGWriter.New();
         writer.SetFileName(filePath);
         writer.SetInputConnection(castFilter.GetOutputPort());
         writer.Write();
         // Read and display file for verification that it was written correctly
         vtkJPEGReader reader = vtkJPEGReader.New();
         if(reader.CanReadFile(filePath) == 0) {
            MessageBox.Show("Cannot read file \"" + filePath + "\"", "Error", MessageBoxButtons.OK);
            return;
         }
         reader.SetFileName(filePath);
         reader.Update();

         // Visualize
         vtkImageViewer2 imageViewer = vtkImageViewer2.New();
         imageViewer.SetInputConnection(reader.GetOutputPort());
         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(0.2, 0.3, 0.4);
         imageViewer.SetRenderer(renderer);
         renderer.ResetCamera();
      }
   }
}
