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
            MarchingSquares();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void MarchingSquares() { 
         // Path to vtk data must be set as an environment variable
         // VTK_DATA_ROOT = "C:\VTK\vtkdata-5.8.0"
         vtkTesting test = vtkTesting.New();
         string root = test.GetDataRoot();

         vtkVolume16Reader v16 = vtkVolume16Reader.New();
         v16.SetDataDimensions(64, 64); 

         v16.GetOutput().SetOrigin(0.0, 0.0, 0.0);
         v16.SetDataByteOrderToLittleEndian();
         v16.SetFilePrefix(System.IO.Path.Combine(root, @"Data\headsq\quarter"));
         v16.SetImageRange(1, 93);
         v16.SetDataSpacing(3.2, 3.2, 1.5);
         v16.Update();

         vtkMergePoints myLocator = vtkMergePoints.New();

         vtkMarchingSquares isoXY = vtkMarchingSquares.New();

#if VTK_MAJOR_VERSION_5
         isoXY.SetInputConnection(v16.GetOutputPort());
#else
         isoXY.SetInputData(v16);
#endif
         isoXY.GenerateValues(2, 600, 1200);
         isoXY.SetImageRange(0, 32, 32, 63, 45, 45);
         isoXY.SetLocator(myLocator);

         vtkPolyDataMapper isoXYMapper = vtkPolyDataMapper.New();
#if VTK_MAJOR_VERSION_5
         isoXYMapper.SetInputConnection(isoXY.GetOutputPort());
#else
         isoXYMapper.SetInputData(isoXY);
#endif
         isoXYMapper.SetScalarRange(600, 1200);

         vtkActor isoXYActor = vtkActor.New();
         isoXYActor.SetMapper(isoXYMapper);

         vtkMarchingSquares isoYZ = vtkMarchingSquares.New();
#if VTK_MAJOR_VERSION_5
         isoYZ.SetInputConnection(v16.GetOutputPort());
#else
         isoYZ.SetInputData(v16);
#endif
         isoYZ.GenerateValues(2, 600, 1200);
         isoYZ.SetImageRange(32, 32, 32, 63, 46, 92);

         vtkPolyDataMapper isoYZMapper = vtkPolyDataMapper.New();
#if VTK_MAJOR_VERSION_5
         isoYZMapper.SetInputConnection(isoYZ.GetOutputPort());
#else
         isoYZMapper.SetInputData(isoYZ);
#endif
         isoYZMapper.SetScalarRange(600, 1200);

         vtkActor isoYZActor = vtkActor.New();
         isoYZActor.SetMapper(isoYZMapper);

         vtkMarchingSquares isoXZ  = vtkMarchingSquares.New();
#if VTK_MAJOR_VERSION_5
         isoXZ.SetInputConnection(v16.GetOutputPort());
#else
         isoXZ.SetInputData(v16);
#endif
         isoXZ.GenerateValues(2, 600, 1200);
         isoXZ.SetImageRange(0, 32, 32, 32, 0, 46);

         vtkPolyDataMapper isoXZMapper = vtkPolyDataMapper.New();
#if VTK_MAJOR_VERSION_5
         isoXZMapper.SetInputConnection(isoXZ.GetOutputPort());
#else
         isoXZMapper.SetInputData(isoXZ);
#endif
         isoXZMapper.SetScalarRange(600, 1200);

         vtkActor isoXZActor = vtkActor.New();
         isoXZActor.SetMapper(isoXZMapper);

         vtkOutlineFilter outline  = vtkOutlineFilter.New();
#if VTK_MAJOR_VERSION_5
         outline.SetInputConnection(v16.GetOutputPort());
#else
         outline.SetInputData(v16);
#endif
         vtkPolyDataMapper outlineMapper = vtkPolyDataMapper.New();
#if VTK_MAJOR_VERSION_5
         outlineMapper.SetInputConnection(outline.GetOutputPort());
#else
         outlineMapper.SetInputData(outline);
#endif
         vtkActor outlineActor = vtkActor.New();
         outlineActor.SetMapper(outlineMapper);
         outlineActor.VisibilityOff();

         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(1.0, 1.0, 1.0);
         //Add the actors to the renderer, set the background and size 
         renderer.AddActor(outlineActor);
         renderer.AddActor(isoXYActor);
         renderer.AddActor(isoYZActor);
         renderer.AddActor(isoXZActor);
         renderer.GetActiveCamera().SetPosition(324.368, 284.266, -19.3293);
         renderer.GetActiveCamera().SetFocalPoint(73.5683, 120.903, 70.7309);
         renderer.GetActiveCamera().SetViewAngle(30);
         renderer.GetActiveCamera().SetViewUp(-0.304692, -0.0563843, -0.950781);
      }
   }
}
