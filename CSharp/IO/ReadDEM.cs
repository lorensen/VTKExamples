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
            ReadDEM();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void ReadDEM() {
         // Path to vtk data must be set as an environment variable
         // VTK_DATA_ROOT = "C:\VTK\vtkdata-5.8.0"
         vtkTesting test = vtkTesting.New();
         string root = test.GetDataRoot();
         string filePath = System.IO.Path.Combine(root, @"Data\SainteHelens.dem");

         vtkDEMReader reader = vtkDEMReader.New();
         reader.SetFileName(filePath);
         reader.Update();

         vtkLookupTable lut = vtkLookupTable.New();
         lut.SetHueRange(0.6, 0);
         lut.SetSaturationRange(1.0, 0);
         lut.SetValueRange(0.5, 1.0);
         double[] range = reader.GetOutput().GetScalarRange();
         lut.SetTableRange(range[0], range[1]);

         // Visualize
         vtkImageMapToColors mapColors = vtkImageMapToColors.New();
         mapColors.SetLookupTable(lut);
         mapColors.SetInputConnection(reader.GetOutputPort());

         // Create an actor
         vtkImageActor actor = vtkImageActor.New();
         actor.SetInput(mapColors.GetOutput());
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
