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
            WriteVTUFile();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void WriteVTUFile() {
         // Path to vtk data must be set as an environment variable
         // VTK_DATA_ROOT = "C:\VTK\vtkdata-5.8.0"
         vtkTesting test = vtkTesting.New();
         string root = test.GetDataRoot();
         string filePath = System.IO.Path.Combine(root, @"Data\tetra_test.vtu");

         vtkPoints points = vtkPoints.New();
         points.InsertNextPoint(0, 0, 0);
         points.InsertNextPoint(1, 0, 0);
         points.InsertNextPoint(1, 1, 0);
         points.InsertNextPoint(0, 1, 1);

         vtkTetra tetra = vtkTetra.New();

         tetra.GetPointIds().SetId(0, 0);
         tetra.GetPointIds().SetId(1, 1);
         tetra.GetPointIds().SetId(2, 2);
         tetra.GetPointIds().SetId(3, 3);

         vtkCellArray cellArray = vtkCellArray.New();
         cellArray.InsertNextCell(tetra);

         vtkUnstructuredGrid unstructuredGrid = vtkUnstructuredGrid.New();
         unstructuredGrid.SetPoints(points);
         const int VTK_TETRA = 10;
         unstructuredGrid.SetCells(VTK_TETRA, cellArray);

         // Write file
         vtkXMLUnstructuredGridWriter writer = vtkXMLUnstructuredGridWriter.New();
         writer.SetFileName(filePath);
         writer.SetInput(unstructuredGrid);
         writer.Write();

         // Read and display file for verification that it was written correctly
         vtkXMLUnstructuredGridReader reader = vtkXMLUnstructuredGridReader.New();
         if(reader.CanReadFile(filePath) == 0) {
            MessageBox.Show("Cannot read file \"" + filePath + "\"", "Error", MessageBoxButtons.OK);
            return;
         }
         reader.SetFileName(filePath);
         reader.Update();

         vtkDataSetMapper mapper = vtkDataSetMapper.New();
         mapper.SetInputConnection(reader.GetOutputPort());

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
