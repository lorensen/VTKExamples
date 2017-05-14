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
            BoundaryEdges();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void BoundaryEdges() {
         vtkDiskSource diskSource = vtkDiskSource.New();
         diskSource.Update();

         vtkFeatureEdges featureEdges = vtkFeatureEdges.New();
#if VTK_MAJOR_VERSION_5
         featureEdges.SetInputConnection(diskSource.GetOutputPort());
#else
         featureEdges.SetInputData(diskSource);
#endif
         featureEdges.BoundaryEdgesOn();
         featureEdges.FeatureEdgesOff();
         featureEdges.ManifoldEdgesOff();
         featureEdges.NonManifoldEdgesOff();
         featureEdges.Update();

         // Visualize
         vtkPolyDataMapper edgeMapper = vtkPolyDataMapper.New();
#if VTK_MAJOR_VERSION_5
         edgeMapper.SetInputConnection(featureEdges.GetOutputPort());
#else
         edgeMapper.SetInputData(featureEdges);
#endif
         vtkActor edgeActor = vtkActor.New();
         edgeActor.GetProperty().SetLineWidth(3);
         edgeActor.SetMapper(edgeMapper);

         vtkPolyDataMapper diskMapper = vtkPolyDataMapper.New();
#if VTK_MAJOR_VERSION_5
         diskMapper.SetInputConnection(diskSource.GetOutputPort());
#else
         diskMapper.SetInputData(diskSource);
#endif
         vtkActor diskActor = vtkActor.New();
         diskActor.SetMapper(diskMapper);

         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(0.3, 0.6, 0.3);
         // add our actor to the renderer
         renderer.AddActor(diskActor);
         renderer.AddActor(edgeActor);
      }
   }
}
