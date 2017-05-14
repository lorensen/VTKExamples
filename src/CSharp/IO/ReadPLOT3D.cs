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
            ReadPLOT3D();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


     private void ReadPLOT3D() {
         // Path to vtk data must be set as an environment variable
         // VTK_DATA_ROOT = "C:\VTK\vtkdata-5.8.0"
         vtkTesting test = vtkTesting.New();
         string root = test.GetDataRoot();
         string filePathXYZ = System.IO.Path.Combine(root, @"Data\bluntfinxyz.bin");
         string filePathQ = System.IO.Path.Combine(root, @"Data\bluntfinq.bin");
         //string filePathXYZ = System.IO.Path.Combine(root, @"Data\combxyz.bin");
         //string filePathQ = System.IO.Path.Combine(root, @"Data\combq.bin");

         vtkMultiBlockPLOT3DReader reader = vtkMultiBlockPLOT3DReader.New();
         reader.SetXYZFileName(filePathXYZ);
         reader.SetQFileName(filePathQ);

         // Specify the scalar function to extract. If ==(-1), then no scalar function is extracted. 
         int scalarFctNo = reader.GetScalarFunctionNumber();
         int vectorFctNo = reader.GetVectorFunctionNumber();
         if(scalarFctNo != -1)
            reader.SetScalarFunctionNumber(scalarFctNo);
         // Specify the vector function to extract. If ==(-1), then no vector function is extracted. 
         if(vectorFctNo != -1)
            reader.SetVectorFunctionNumber(vectorFctNo);
         reader.Update();

         //// geometry filter
         //// This filter is multi-block aware and will request blocks from the
         //// input. These blocks will be processed by simple processes as if they
         //// are the whole dataset
         //vtkCompositeDataGeometryFilter geom1 = vtkCompositeDataGeometryFilter.New();
         //geom1.SetInputConnection(0, reader.GetOutputPort(0));

         vtkStructuredGridGeometryFilter geometryFilter = vtkStructuredGridGeometryFilter.New();
         geometryFilter.SetInput(reader.GetOutput().GetBlock(0));
         //geometryFilter.SetInputConnection(geom1.GetOutputPort(0));
         geometryFilter.Update();

         // Visualize
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInputConnection(geometryFilter.GetOutputPort());
         //mapper.SetInputConnection(geom1.GetOutputPort());
         mapper.ScalarVisibilityOn();
         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);
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
