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
            WriteMetaImage();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void WriteMetaImage() {
         // Path to vtk data must be set as an environment variable
         // VTK_DATA_ROOT = "C:\VTK\vtkdata-5.8.0"
         vtkTesting test = vtkTesting.New();
         string root = test.GetDataRoot();
         string filePath = System.IO.Path.Combine(root, @"Data\test_mha.mhd");
         string filePathRaw = System.IO.Path.Combine(root, @"Data\test_mha.raw");
         // Create an image
         vtkImageMandelbrotSource source = vtkImageMandelbrotSource.New();
         source.Update();

         vtkImageCast castFilter = vtkImageCast.New();
         castFilter.SetOutputScalarTypeToUnsignedChar();
         castFilter.SetInputConnection(source.GetOutputPort());
         castFilter.Update();

         vtkMetaImageWriter writer = vtkMetaImageWriter.New();
         writer.SetInputConnection(castFilter.GetOutputPort());
         writer.SetFileName(filePath);
         writer.SetRAWFileName(filePathRaw);
         writer.Write();

         // Read and display file for verification that it was written correctly
         vtkMetaImageReader reader = vtkMetaImageReader.New();
         if(reader.CanReadFile(filePath) == 0) {
            MessageBox.Show("Cannot read file \"" + filePath + "\"", "Error", MessageBoxButtons.OK);
            return;
         }
         reader.SetFileName(filePath);
         reader.Update();
         vtkImageActor actor = vtkImageActor.New();
         actor.SetInput(reader.GetOutput());

         // Visualize
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(0.2, 0.3, 0.4);
         renderer.AddActor(actor);
      }
   }
}
