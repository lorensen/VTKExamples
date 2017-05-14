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
            WriteVTI();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void WriteVTI() {
         // Path to vtk data must be set as an environment variable
         // VTK_DATA_ROOT = "C:\VTK\vtkdata-5.8.0"
         vtkTesting test = vtkTesting.New();
         string root = test.GetDataRoot();
         string filePath = System.IO.Path.Combine(root, @"Data\test_vti.vti");
         vtkImageData imageData = vtkImageData.New();
         imageData.SetDimensions(3, 4, 5);
         imageData.SetNumberOfScalarComponents(1);
         imageData.SetScalarTypeToDouble();
         int[] dims = imageData.GetDimensions();

         // Fill every entry of the image data with "2.0"
         /* we can do this in unsafe mode which looks pretty similar to the c++ version 
           but then you must declare at the very top of your file the "preprocessor" directive 
           
          #define UNSAFE
          
          * or whatever name you choose for the following preprocessor #if statement
          */
#if UNSAFE
         unsafe {
            for(int z = 0; z < dims[2]; z++) {
               for(int y = 0; y < dims[1]; y++) {
                  for(int x = 0; x < dims[0]; x++) {
                     double* pixel = (double*)imageData.GetScalarPointer(x, y, z).ToPointer();
                     // c++ version:
                     // double* pixel = static_cast<double*>(imageData->GetScalarPointer(x,y,z));
                     pixel[0] = 2.0;
                  }
               }
            }
         }
#else
         /* or we can do it in managed mode */
         int size = imageData.GetScalarSize();
         IntPtr ptr = Marshal.AllocHGlobal(size);

         for(int z = 0; z < dims[2]; z++) {
            for(int y = 0; y < dims[1]; y++) {
               for(int x = 0; x < dims[0]; x++) {
                  ptr = imageData.GetScalarPointer(x, y, z);
                  Marshal.Copy(new double[] { 2.0 }, 0, ptr, 1);
               }
            }
         }
         Marshal.FreeHGlobal(ptr);
#endif

         vtkXMLImageDataWriter writer = vtkXMLImageDataWriter.New();
         writer.SetFileName(filePath);
         writer.SetInputConnection(imageData.GetProducerPort());
         writer.Write();

         // Read and display file for verification that it was written correctly
         vtkXMLImageDataReader reader = vtkXMLImageDataReader.New();
         if(reader.CanReadFile(filePath) == 0) {
            MessageBox.Show("Cannot read file \"" + filePath + "\"", "Error", MessageBoxButtons.OK);
            return;
         }
         reader.SetFileName(filePath);
         reader.Update();

         // Convert the image to a polydata
         vtkImageDataGeometryFilter imageDataGeometryFilter = vtkImageDataGeometryFilter.New();
         imageDataGeometryFilter.SetInputConnection(reader.GetOutputPort());
         imageDataGeometryFilter.Update();

         vtkDataSetMapper mapper = vtkDataSetMapper.New();
         mapper.SetInputConnection(imageDataGeometryFilter.GetOutputPort());
         // actor
         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);
         actor.GetProperty().SetPointSize(4);
         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(0.2, 0.3, 0.4);
         // add our actor to the renderer
         renderer.AddActor(actor);
      }
   }
}
