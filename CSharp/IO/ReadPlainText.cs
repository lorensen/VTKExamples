using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Windows.Forms;
using System.Diagnostics;
using System.Globalization;
using System.IO;

using Kitware.VTK;

namespace ActiViz.Examples {
   public partial class Form1 : Form {
      public Form1() {
         InitializeComponent();
      }


      private void renderWindowControl1_Load(object sender, EventArgs e) {
         try {
            ReadPlainText();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void ReadPlainText() {
         // Path to vtk data must be set as an environment variable
         // VTK_DATA_ROOT = "C:\VTK\vtkdata-5.8.0"
         vtkTesting test = vtkTesting.New();
         string root = test.GetDataRoot();
         string filePath = System.IO.Path.Combine(root, @"Data\teapot.xyz");
         
         FileStream fs = null;
         StreamReader sr = null;
         String sLineBuffer;
         String[] sXYZ;
         char[] chDelimiter = new char[] { ' ', '\t', ';' };
         double[] xyz = new double[3];
         vtkPoints points = vtkPoints.New();
         int cnt = 0;

         try {
            // in case file must be open in another application too use "FileShare.ReadWrite"
            fs = new FileStream(filePath, FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
            sr = new StreamReader(fs);
            while(!sr.EndOfStream) {
               sLineBuffer = sr.ReadLine();
               cnt++;
               sXYZ = sLineBuffer.Split(chDelimiter, StringSplitOptions.RemoveEmptyEntries);
               if(sXYZ == null || sXYZ.Length != 3) {
                  MessageBox.Show("data seems to be in wrong format at line " + cnt, "Format Exception", MessageBoxButtons.OK);
                  return;
               }
               xyz[0] = double.Parse(sXYZ[0], CultureInfo.InvariantCulture);
               xyz[1] = double.Parse(sXYZ[1], CultureInfo.InvariantCulture);
               xyz[2] = double.Parse(sXYZ[2], CultureInfo.InvariantCulture);
               points.InsertNextPoint(xyz[0], xyz[1], xyz[2]);
            }
            vtkPolyData polydata = vtkPolyData.New();
            polydata.SetPoints(points);
            vtkVertexGlyphFilter glyphFilter = vtkVertexGlyphFilter.New();
            glyphFilter.SetInputConnection(polydata.GetProducerPort());

            // Visualize
            vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
            mapper.SetInputConnection(glyphFilter.GetOutputPort());

            vtkActor actor = vtkActor.New();
            actor.SetMapper(mapper);
            actor.GetProperty().SetPointSize(4);
            actor.GetProperty().SetColor(1, 0.5, 0);
            // get a reference to the renderwindow of our renderWindowControl1
            vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
            // renderer
            vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
            // set background color
            renderer.SetBackground(0.2, 0.3, 0.4);
            // add our actor to the renderer
            renderer.AddActor(actor);
         }
         catch(IOException ex) {
            MessageBox.Show(ex.Message, "IOException", MessageBoxButtons.OK);
         }
         finally {
            if(sr != null) {
               sr.Close();
               sr.Dispose();
               sr = null;
            }
         }
      }
   }
}
