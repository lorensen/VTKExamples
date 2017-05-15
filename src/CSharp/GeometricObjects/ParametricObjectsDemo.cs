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
            ParametricObjectsDemo();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void ParametricObjectsDemo() {
         // we create a matrix of 4x4 renderer in our renderwindow
         // each renderer can be interacted with independently from one another
         int rendererSize = 189; // width per renderer
         int gridDimensions = 4;
         this.Size = new System.Drawing.Size(756, 756);
         Random rnd = new Random(2);
         List<vtkParametricFunction>  parametricObjects = new List<vtkParametricFunction>();
         parametricObjects.Add(vtkParametricBoy.New());
         parametricObjects.Add(vtkParametricConicSpiral.New());
         parametricObjects.Add(vtkParametricCrossCap.New());
         parametricObjects.Add(vtkParametricDini.New());
         vtkParametricEllipsoid ellipsoid = vtkParametricEllipsoid.New();
         ellipsoid.SetXRadius(0.5);
         ellipsoid.SetYRadius(2.0);
         parametricObjects.Add(ellipsoid);
         parametricObjects.Add(vtkParametricEnneper.New());
         parametricObjects.Add(vtkParametricFigure8Klein.New());
         parametricObjects.Add(vtkParametricKlein.New());
         parametricObjects.Add(vtkParametricMobius.New());
         vtkParametricRandomHills randomHills = vtkParametricRandomHills.New();
         randomHills.AllowRandomGenerationOff();
         parametricObjects.Add(randomHills);
         parametricObjects.Add(vtkParametricRoman.New());
         vtkParametricSuperEllipsoid superEllipsoid = vtkParametricSuperEllipsoid.New();
         superEllipsoid.SetN1(.50);
         superEllipsoid.SetN2(.1);
         parametricObjects.Add(superEllipsoid);
         vtkParametricSuperToroid superToroid = vtkParametricSuperToroid.New();
         superToroid.SetN1(0.2);
         superToroid.SetN2(3.0);
         parametricObjects.Add(superToroid);
         parametricObjects.Add(vtkParametricTorus.New());

         vtkParametricSpline spline = vtkParametricSpline.New();
         vtkPoints inputPoints = vtkPoints.New();
         vtkMath.RandomSeed(8775070);
         for(int p = 0; p < 10; p++) {
            double x = vtkMath.Random(0.0, 1.0);
            double y = vtkMath.Random(0.0, 1.0);
            double z = vtkMath.Random(0.0, 1.0);
            inputPoints.InsertNextPoint(x, y, z);
         }
         spline.SetPoints(inputPoints);

         parametricObjects.Add(spline);


         List<vtkParametricFunctionSource> parametricFunctionSources = new List<vtkParametricFunctionSource>();
         List<vtkRenderer> renderers = new List<vtkRenderer>();
         List<vtkPolyDataMapper> mappers = new List<vtkPolyDataMapper>();
         List<vtkActor> actors = new List<vtkActor>();
         List<vtkTextMapper> textMappers = new List<vtkTextMapper>();
         List<vtkActor2D> textActors = new List<vtkActor2D>();

         // Create one text property for all
         vtkTextProperty textProperty = vtkTextProperty.New();
         textProperty.SetFontSize(12);
         textProperty.SetJustificationToCentered();

         // Create a source, renderer, mapper, and actor
         // for each object 
         for(int i = 0; i < parametricObjects.Count; i++) {
            parametricFunctionSources.Add(vtkParametricFunctionSource.New());
            parametricFunctionSources[i].SetParametricFunction(parametricObjects[i]);
            parametricFunctionSources[i].Update();
            mappers.Add(vtkPolyDataMapper.New());
            mappers[i].SetInputConnection(parametricFunctionSources[i].GetOutputPort());

            actors.Add(vtkActor.New());
            actors[i].SetMapper(mappers[i]);

            textMappers.Add(vtkTextMapper.New());
            textMappers[i].SetInput(parametricObjects[i].GetClassName());
            textMappers[i].SetTextProperty(textProperty);

            textActors.Add(vtkActor2D.New());
            textActors[i].SetMapper(textMappers[i]);
            textActors[i].SetPosition(rendererSize / 2, 16);

            renderers.Add(vtkRenderer.New());
         }

         // Need a renderer even if there is no actor
         for(int i = parametricObjects.Count; i < gridDimensions * gridDimensions; i++) {
            renderers.Add(vtkRenderer.New());
         }

         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         renderWindow.SetSize(rendererSize * gridDimensions, rendererSize * gridDimensions);

         for(int row = 0; row < gridDimensions; row++) {
            for(int col = 0; col < gridDimensions; col++) {
               int index = row * gridDimensions + col;

               // (xmin, ymin, xmax, ymax)
               double[] viewport = new double[] {
                  (col) * rendererSize / (double)(gridDimensions * rendererSize),
                  (gridDimensions - (row+1)) * rendererSize / (double)(gridDimensions * rendererSize),
                  (col+1)*rendererSize / (double)(gridDimensions * rendererSize),
                  (gridDimensions - row) * rendererSize / (double)(gridDimensions * rendererSize)};

               //Debug.WriteLine(viewport[0] + " " + viewport[1] + " " + viewport[2] + " " + viewport[3]);
               renderWindow.AddRenderer(renderers[index]);
               IntPtr pViewport = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(double)) * 4);
               Marshal.Copy(viewport, 0, pViewport, 4);
               renderers[index].SetViewport(pViewport);
               Marshal.FreeHGlobal(pViewport);
               if(index > parametricObjects.Count - 1)
                  continue;

               renderers[index].AddActor(actors[index]);
               renderers[index].AddActor(textActors[index]);
               renderers[index].SetBackground(.2 + rnd.NextDouble() / 8, .3 + rnd.NextDouble() / 8, .4 + rnd.NextDouble() / 8);
               renderers[index].ResetCamera();
               renderers[index].GetActiveCamera().Azimuth(30);
               renderers[index].GetActiveCamera().Elevation(-50);
               renderers[index].GetActiveCamera().Pitch(-2);
               renderers[index].ResetCameraClippingRange();
            }
         }
      }
   }
}
