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
            VRML();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void VRML() {
         // Path to vtk data must be set as an environment variable
         // VTK_DATA_ROOT = "C:\VTK\vtkdata-5.8.0"
         vtkTesting test = vtkTesting.New();
         string root = test.GetDataRoot();
         string filePath = System.IO.Path.Combine(root, @"Data\bot2.wrl");
         // reader
         vtkVRMLImporter importer = vtkVRMLImporter.New();
         importer.SetFileName(filePath);
         importer.Update();

         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         renderWindow.AddRenderer(importer.GetRenderer());
         renderWindow.Render();

         //vtkActorCollection actors = importer.GetRenderer().GetActors();
         //actors.InitTraversal();
         //vtkActor tmp;
         //while(( tmp = actors.GetNextActor()) != null) {
         //}
      }
   }
}
