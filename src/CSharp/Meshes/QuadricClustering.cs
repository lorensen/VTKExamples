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
            QuadricClustering();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void QuadricClustering() { 
         vtkSphereSource sphereSource = vtkSphereSource.New();
         sphereSource.Update();

         vtkPolyData input = vtkPolyData.New();
         input.ShallowCopy(sphereSource.GetOutput());

         Debug.WriteLine("Before decimation" + Environment.NewLine + "------------" );
         Debug.WriteLine("There are " + input.GetNumberOfPoints() + " points." );
         Debug.WriteLine("There are " + input.GetNumberOfPolys() + " polygons." );

         vtkQuadricClustering decimate = vtkQuadricClustering.New();
#if VTK_MAJOR_VERSION_5
         decimate.SetInputConnection(input.GetProducerPort());
#else
         decimate.SetInputData(input);
#endif
         decimate.Update();

         vtkPolyData decimated = vtkPolyData.New();
         decimated.ShallowCopy(decimate.GetOutput());

         Debug.WriteLine("After decimation" + Environment.NewLine + "------------" );

         Debug.WriteLine("There are " + decimated.GetNumberOfPoints() + " points." );
         Debug.WriteLine("There are " + decimated.GetNumberOfPolys() + " polygons." );

         vtkPolyDataMapper inputMapper = vtkPolyDataMapper.New();
#if VTK_MAJOR_VERSION_5
         inputMapper.SetInputConnection(input.GetProducerPort());
#else
         inputMapper.SetInputData(input);
#endif
         vtkActor inputActor = vtkActor.New();
         inputActor.SetMapper(inputMapper);

         vtkPolyDataMapper decimatedMapper = vtkPolyDataMapper.New();
#if VTK_MAJOR_VERSION_5
         decimatedMapper.SetInputConnection(decimated.GetProducerPort());
#else
         decimatedMapper.SetInputData(decimated);
#endif
         vtkActor decimatedActor = vtkActor.New();
         decimatedActor.SetMapper(decimatedMapper);

         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         this.Size = new System.Drawing.Size(612, 352);

         // Define viewport ranges
         // (xmin, ymin, xmax, ymax)
         double[] leftViewport = new double[] { 0.0, 0.0, 0.5, 1.0 };
         double[] rightViewport = new double[] { 0.5, 0.0, 1.0, 1.0 };

         // Setup both renderers
         vtkRenderer leftRenderer = vtkRenderer.New();
         renderWindow.AddRenderer(leftRenderer);
         leftRenderer.SetViewport(leftViewport[0], leftViewport[1], leftViewport[2], leftViewport[3]);
         leftRenderer.SetBackground(.6, .5, .4);

         vtkRenderer rightRenderer = vtkRenderer.New();
         renderWindow.AddRenderer(rightRenderer);
         rightRenderer.SetViewport(rightViewport[0], rightViewport[1], rightViewport[2], rightViewport[3]);
         rightRenderer.SetBackground(.4, .5, .6);

         // Add the sphere to the left and the cube to the right
         leftRenderer.AddActor(inputActor);
         rightRenderer.AddActor(decimatedActor);
         leftRenderer.ResetCamera();
         rightRenderer.ResetCamera();
         renderWindow.Render();
      }
   }
}
