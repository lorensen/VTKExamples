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
            GreedyTerrainDecimation();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void GreedyTerrainDecimation() {
         // Create an image
         vtkImageData image = vtkImageData.New();
         image.SetDimensions(3, 3, 1);
         image.SetNumberOfScalarComponents(1);
         image.SetScalarTypeToUnsignedChar();
         int[] dims = image.GetDimensions();
         unsafe {
            for(int i = 0; i < dims[0]; i++) {
               for(int j = 0; j < dims[1]; j++) {
                  byte* ptr = (byte*)image.GetScalarPointer(i, j, 0);
                  *ptr = (byte)vtkMath.Round(vtkMath.Random(0, 1));
               }
            }
         }
         vtkGreedyTerrainDecimation decimation = vtkGreedyTerrainDecimation.New();
         decimation.SetInputConnection(image.GetProducerPort());
         decimation.Update();
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInputConnection(decimation.GetOutputPort());
         // actor
         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);
         actor.GetProperty().SetInterpolationToFlat();
         actor.GetProperty().EdgeVisibilityOn();
         actor.GetProperty().SetEdgeColor(1, 0, 0);

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
