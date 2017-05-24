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
            WritePolyData();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void WritePolyData() {
         // Path to vtk data must be set as an environment variable
         // VTK_DATA_ROOT = "C:\VTK\vtkdata-5.8.0"
         vtkTesting test = vtkTesting.New();
         string root = test.GetDataRoot();
         string filePath = System.IO.Path.Combine(root, @"Data\poly_test.vtp");
         // Create 4 points for a tetrahedron
         vtkPoints points = vtkPoints.New();

         points.InsertNextPoint(0, 0, 0);
         points.InsertNextPoint(0, 0, 1);
         points.InsertNextPoint(1, 0, 0);
         points.InsertNextPoint(0, 1, 0);

         // Create a polydata object and add the points to it.
         vtkPolyData polydata = vtkPolyData.New();
         polydata.SetPoints(points);

         // it's not enough only to define points
         // we need to define faces too
         // (must be defined in counter clockwise order as viewed from the outside)
         vtkTriangle face0 = vtkTriangle.New();
         face0.GetPointIds().SetId(0, 0);
         face0.GetPointIds().SetId(1, 2);
         face0.GetPointIds().SetId(2, 1);
         vtkTriangle face1 = vtkTriangle.New();
         face1.GetPointIds().SetId(0, 0);
         face1.GetPointIds().SetId(1, 3);
         face1.GetPointIds().SetId(2, 2);
         vtkTriangle face2 = vtkTriangle.New();
         face2.GetPointIds().SetId(0, 0);
         face2.GetPointIds().SetId(1, 1);
         face2.GetPointIds().SetId(2, 3);
         vtkTriangle face3 = vtkTriangle.New();
         face3.GetPointIds().SetId(0, 1);
         face3.GetPointIds().SetId(1, 2);
         face3.GetPointIds().SetId(2, 3);

         vtkCellArray faces = vtkCellArray.New();
         faces.InsertNextCell(face0);
         faces.InsertNextCell(face1);
         faces.InsertNextCell(face2);
         faces.InsertNextCell(face3);

         polydata.SetPolys(faces);

         // Write the file
         vtkXMLPolyDataWriter writer = vtkXMLPolyDataWriter.New();
         writer.SetFileName(filePath);
         writer.SetInput(polydata);

         // Optional - set the mode. The default is binary.
         //writer.SetDataModeToBinary();
         writer.SetDataModeToAscii();
         writer.Write();

         // Read and display file for verification that it was written correctly
         vtkXMLPolyDataReader reader = vtkXMLPolyDataReader.New();
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
