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
            Axes();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void Axes() {
         vtkSphereSource sphereSource = vtkSphereSource.New();
         sphereSource.SetCenter(0.0, 0.0, 0.0);
         sphereSource.SetRadius(0.5);

         //create a mapper
         vtkPolyDataMapper sphereMapper = vtkPolyDataMapper.New();
         sphereMapper.SetInputConnection(sphereSource.GetOutputPort());

         // create an actor
         vtkActor sphereActor = vtkActor.New();
         sphereActor.SetMapper(sphereMapper);

         // a renderer and render window
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         renderer.SetBackground(0.2, 0.3, 0.4);

         // add the actors to the scene
         renderer.AddActor(sphereActor);

         vtkAxesActor axes = vtkAxesActor.New();
         // The axes are positioned with a user transform
         vtkTransform transform = vtkTransform.New();
         transform.Translate(0.75, 0.0, 0.0);
         axes.SetUserTransform(transform);
         // properties of the axes labels can be set as follows
         // this sets the x axis label to red
         // axes.GetXAxisCaptionActor2D().GetCaptionTextProperty().SetColor(1,0,0);

         // the actual text of the axis label can be changed:
         // axes.SetXAxisLabelText("test");

         renderer.AddActor(axes);
         // we need to call Render() for the whole renderWindow, 
         // because vtkAxesActor uses an overlayed renderer for the axes label
         // in total we have now two renderer
         renderWindow.Render();
      }
   }
}
