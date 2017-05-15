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
            MatrixMathFilter();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void MatrixMathFilter() {
         // Path to vtk data must be set as an environment variable
         // VTK_DATA_ROOT = "C:\VTK\vtkdata-5.8.0"
         vtkTesting test = vtkTesting.New();
         string root = test.GetDataRoot();
         string filePath = System.IO.Path.Combine(root, @"Data\tensors.vtk");
         vtkUnstructuredGridReader reader = vtkUnstructuredGridReader.New();
         reader.SetFileName(filePath);
         reader.Update();

         vtkDataSetSurfaceFilter surfaceFilter = vtkDataSetSurfaceFilter.New();
         surfaceFilter.SetInputConnection(reader.GetOutputPort());
         surfaceFilter.Update();

         vtkMatrixMathFilter matrixMathFilter = vtkMatrixMathFilter.New();
         //matrixMathFilter.SetOperationToDeterminant();
         matrixMathFilter.SetOperationToEigenvalue();
         matrixMathFilter.SetInputConnection(surfaceFilter.GetOutputPort());
         matrixMathFilter.Update();
         matrixMathFilter.GetOutput().GetPointData().SetActiveScalars("Eigenvalue");

         vtkXMLPolyDataWriter writer = vtkXMLPolyDataWriter.New();
         writer.SetInputConnection(matrixMathFilter.GetOutputPort());
         writer.SetFileName(System.IO.Path.Combine(root, @"Data\output.vtp"));
         writer.Write();

         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInputConnection(matrixMathFilter.GetOutputPort());

         // actor
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
