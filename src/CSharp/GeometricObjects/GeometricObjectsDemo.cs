using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Windows.Forms;
using System.Diagnostics;
using System.Runtime.InteropServices;

using Kitware.VTK;

namespace ActiViz.Examples {
   public partial class Form1 : Form {
      public Form1() {
         InitializeComponent();
      }


      private void renderWindowControl1_Load(object sender, EventArgs e) {
         try {
            GeometricObjectsDemo();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void GeometricObjectsDemo() {
         // we create a matrix of 3x3 renderer in our renderwindow
         // each renderer can be interacted with independently from one another
         int rendererSize = 234; // width per renderer
         int gridDimensions = 3;
         this.Size = new System.Drawing.Size(756, 756);
         Random rnd = new Random(2); // for background color variation

         List<vtkPolyDataAlgorithm>  geometricObjectSources = new List<vtkPolyDataAlgorithm>();
         geometricObjectSources.Add(vtkArrowSource.New());
         geometricObjectSources.Add(vtkConeSource.New());
         geometricObjectSources.Add(vtkCubeSource.New());
         geometricObjectSources.Add(vtkCylinderSource.New());
         geometricObjectSources.Add(vtkDiskSource.New());
         geometricObjectSources.Add(vtkLineSource.New());
         geometricObjectSources.Add(vtkRegularPolygonSource.New());
         geometricObjectSources.Add(vtkSphereSource.New());
         geometricObjectSources.Add(vtkEarthSource.New());

         List<vtkRenderer> renderers = new List<vtkRenderer>();
         List<vtkPolyDataMapper> mappers = new List<vtkPolyDataMapper>();
         List<vtkActor> actors = new List<vtkActor>();
         List<vtkTextMapper> textMappers = new List<vtkTextMapper>();
         List<vtkActor2D> textActors = new List<vtkActor2D>();

         // Create one text property for all
         vtkTextProperty textProperty = vtkTextProperty.New();
         textProperty.SetFontSize(18);
         textProperty.SetJustificationToCentered();

         // Create a source, renderer, mapper, and actor
         // for each object 
         for(int i = 0; i < geometricObjectSources.Count; i++) {
            geometricObjectSources[i].Update();
            mappers.Add(vtkPolyDataMapper.New());
            mappers[i].SetInputConnection(geometricObjectSources[i].GetOutputPort());

            actors.Add(vtkActor.New());
            actors[i].SetMapper(mappers[i]);

            textMappers.Add(vtkTextMapper.New());
            textMappers[i].SetInput(geometricObjectSources[i].GetClassName());
            textMappers[i].SetTextProperty(textProperty);

            textActors.Add(vtkActor2D.New());
            textActors[i].SetMapper(textMappers[i]);
            textActors[i].SetPosition(rendererSize/2, 16);

            renderers.Add(vtkRenderer.New());
         }

         // Need a renderer even if there is no actor
         for(int i = geometricObjectSources.Count; i < gridDimensions * gridDimensions; i++) {
            renderers.Add(vtkRenderer.New());
         }

         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         renderWindow.SetSize(rendererSize*gridDimensions, rendererSize*gridDimensions);

         for(int row = 0; row < gridDimensions; row++) {
            for(int col = 0; col < gridDimensions; col++) {
               int index = row * gridDimensions + col;

               // (xmin, ymin, xmax, ymax)
               double[] viewport = new double[] {
                  (col) * rendererSize / (double)(gridDimensions * rendererSize),
                  (gridDimensions - (row+1)) * rendererSize / (double)(gridDimensions * rendererSize),
                  (col+1)*rendererSize / (double)(gridDimensions * rendererSize),
                  (gridDimensions - row) * rendererSize / (double)(gridDimensions * rendererSize)};

               Debug.WriteLine(viewport[0] + " " + viewport[1] + " " + viewport[2] + " " + viewport[3]);
               renderWindow.AddRenderer(renderers[index]);
               IntPtr pViewport = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(double))*4);
               Marshal.Copy(viewport, 0, pViewport, 4);
               renderers[index].SetViewport(pViewport);
               Marshal.FreeHGlobal(pViewport);
               if(index > geometricObjectSources.Count - 1)
                  continue;

               renderers[index].AddActor(actors[index]);
               renderers[index].AddActor(textActors[index]);
               renderers[index].SetBackground(.2 + rnd.NextDouble() / 8, .3 + rnd.NextDouble() / 8, .4 + rnd.NextDouble() / 8);
            }
         }
      }
   }
}
