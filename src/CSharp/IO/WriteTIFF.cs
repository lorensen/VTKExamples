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
            WriteTIFF();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void WriteTIFF() {
         // Path to vtk data must be set as an environment variable
         // VTK_DATA_ROOT = "C:\VTK\vtkdata-5.8.0"
         vtkTesting test = vtkTesting.New();
         string root = test.GetDataRoot();
         string filePath = System.IO.Path.Combine(root, @"Data\test_tiff.tif");

         vtkImageCanvasSource2D imageSource = vtkImageCanvasSource2D.New();
         imageSource.SetScalarTypeToUnsignedChar();
         imageSource.SetExtent(0, 9, 0, 9, 0, 0);
         imageSource.SetNumberOfScalarComponents(3);
         imageSource.SetDrawColor(0, 0, 0, 0);
         imageSource.FillBox(0, 9, 0, 9);
         imageSource.SetDrawColor(255, 0, 0, 0);
         imageSource.FillBox(5, 7, 5, 7);
         imageSource.Update();

         vtkTIFFWriter tiffWriter = vtkTIFFWriter.New();
         tiffWriter.SetFileName(filePath);
         tiffWriter.SetInputConnection(imageSource.GetOutputPort());
         tiffWriter.Write();

         // Read and display file for verification that it was written correctly
         vtkTIFFReader reader = vtkTIFFReader.New();
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
