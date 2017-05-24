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
            // don't forget to adapt the file path
            ExtractLargestIsoSurface("test.vtk", 50, true);
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void ExtractLargestIsoSurface(string filePath, double threshold, bool extractLargest) { 
         // Load data
         vtkStructuredPointsReader reader = vtkStructuredPointsReader.New();
         reader.SetFileName(filePath);

         // Create a 3D model using marching cubes
         vtkMarchingCubes mc = vtkMarchingCubes.New();
         mc.SetInputConnection(reader.GetOutputPort());
         mc.ComputeNormalsOn();
         mc.ComputeGradientsOn();
         mc.SetValue(0, threshold);  // second value acts as threshold

         // To remain largest region
         vtkPolyDataConnectivityFilter confilter = vtkPolyDataConnectivityFilter.New();
         confilter.SetInputConnection(mc.GetOutputPort());
         confilter.SetExtractionModeToLargestRegion();

         // Create a mapper
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         if(extractLargest) {
            mapper.SetInputConnection(confilter.GetOutputPort());
         }
         else {
            mapper.SetInputConnection(mc.GetOutputPort());
         }

         mapper.ScalarVisibilityOff();    // utilize actor's property I set

         // Visualize
         vtkActor actor = vtkActor.New();
         actor.GetProperty().SetColor(1, 1, 1);
         actor.SetMapper(mapper);

         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // add our actor to the renderer
         renderer.AddActor(actor);
      }
   }
}
