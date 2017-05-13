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
            ParametricObjects();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void ParametricObjects() {
         // Select one of the following (matching the selection above)
         vtkParametricTorus parametricObject = vtkParametricTorus.New();
         //vtkParametricBoy parametricObject = vtkParametricBoy.New();
         //vtkParametricConicSpiral parametricObject = vtkParametricConicSpiral.New();
         //vtkParametricCrossCap parametricObject = vtkParametricCrossCap.New();
         //vtkParametricDini parametricObject = vtkParametricDini.New();
         //vtkParametricEllipsoid parametricObject = vtkParametricEllipsoid.New();
         //vtkParametricEnneper parametricObject = vtkParametricEnneper.New();
         //vtkParametricFigure8Klein parametricObject = vtkParametricFigure8Klein.New();
         //vtkParametricKlein parametricObject = vtkParametricKlein.New();
         //vtkParametricMobius parametricObject = vtkParametricMobius.New();
         //vtkParametricRandomHills parametricObject = vtkParametricRandomHills.New();
         //vtkParametricRoman parametricObject = vtkParametricRoman.New();
         //vtkParametricSpline parametricObject = vtkParametricSpline.New();
         //vtkParametricSuperEllipsoid parametricObject = vtkParametricSuperEllipsoid.New();
         //vtkParametricSuperToroid parametricObject = vtkParametricSuperToroid.New();
         //vtkParametricTorus parametricObject = vtkParametricTorus.New();


         vtkParametricFunctionSource parametricFunctionSource = vtkParametricFunctionSource.New();
         parametricFunctionSource.SetParametricFunction(parametricObject);
         parametricFunctionSource.Update();

         // Setup mapper and actor
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInputConnection(parametricFunctionSource.GetOutputPort());
         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);

         // Visualize
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         renderer.SetBackground(0.2, 0.3, 0.4);
         renderer.AddActor(actor);
      }
   }
}
