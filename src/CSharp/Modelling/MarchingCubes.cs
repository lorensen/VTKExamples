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
            MarchingCubes();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void MarchingCubes() {
         vtkSphereSource sphereSource = vtkSphereSource.New();
         sphereSource.SetPhiResolution(20);
         sphereSource.SetThetaResolution(20);
         sphereSource.Update();

         double[] bounds = sphereSource.GetOutput().GetBounds();
         for(int i = 0; i < 6; i += 2) {
            double range = bounds[i + 1] - bounds[i];
            bounds[i] = bounds[i] - .1 * range;
            bounds[i + 1] = bounds[i + 1] + .1 * range;
         }
         vtkVoxelModeller voxelModeller = vtkVoxelModeller.New();
         voxelModeller.SetSampleDimensions(50, 50, 50);
         voxelModeller.SetModelBounds(bounds[0], bounds[1], bounds[2], bounds[3], bounds[4], bounds[5]);
         voxelModeller.SetScalarTypeToFloat();
         voxelModeller.SetMaximumDistance(.1);

#if VTK_MAJOR_VERSION_5
         voxelModeller.SetInputConnection(sphereSource.GetOutputPort());
#else
         voxelModeller.SetInputData(sphereSource);
#endif
         vtkMarchingCubes surface = vtkMarchingCubes.New();

#if VTK_MAJOR_VERSION_5
         surface.SetInputConnection(voxelModeller.GetOutputPort());
#else
         surface.SetInputData(voxelModeller);
#endif
         surface.ComputeNormalsOn();
         surface.SetValue(0, 0.5);
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
#if VTK_MAJOR_VERSION_5
         mapper.SetInputConnection(surface.GetOutputPort());
#else
         mapper.SetInputData(surface);
#endif
         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);

         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(.2, .3, .4);
         // add our actor to the renderer
         renderer.AddActor(actor);
      }
   }
}
