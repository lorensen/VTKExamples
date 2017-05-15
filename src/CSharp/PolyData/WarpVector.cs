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
            WarpVector();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void WarpVector() {
         vtkPoints points = vtkPoints.New();
         points.InsertNextPoint(0.0, 0.0, 0.0);
         points.InsertNextPoint(1.0, 0.0, 0.0);
         points.InsertNextPoint(2.0, 0.0, 0.0);
         points.InsertNextPoint(3.0, 0.0, 0.0);
         points.InsertNextPoint(4.0, 0.0, 0.0);

         vtkCellArray lines = vtkCellArray.New();
         vtkLine line = vtkLine.New();
         line.GetPointIds().SetId(0, 0);
         line.GetPointIds().SetId(1, 1);
         lines.InsertNextCell(line);
         line.GetPointIds().SetId(0, 1);
         line.GetPointIds().SetId(1, 2);
         lines.InsertNextCell(line);
         line.GetPointIds().SetId(0, 2);
         line.GetPointIds().SetId(1, 3);
         lines.InsertNextCell(line);
         line.GetPointIds().SetId(0, 3);
         line.GetPointIds().SetId(1, 4);
         lines.InsertNextCell(line);

         vtkDoubleArray warpData = vtkDoubleArray.New();
         warpData.SetNumberOfComponents(3);
         warpData.SetName("warpData");
         double[] warp = new double[] { 0.0, 0.0, 0.0 };
         warp[1] = 0.0;
         warpData.InsertNextTuple3(warp[0], warp[1], warp[2]);
         warp[1] = 0.1;
         warpData.InsertNextTuple3(warp[0], warp[1], warp[2]);
         warp[1] = 0.3;
         warpData.InsertNextTuple3(warp[0], warp[1], warp[2]);
         warp[1] = 0.0;
         warpData.InsertNextTuple3(warp[0], warp[1], warp[2]);
         warp[1] = 0.1;
         warpData.InsertNextTuple3(warp[0], warp[1], warp[2]);

         vtkPolyData polydata = vtkPolyData.New();
         polydata.SetPoints(points);
         polydata.SetLines(lines);
         polydata.GetPointData().AddArray(warpData);
         polydata.GetPointData().SetActiveVectors(warpData.GetName());

         //WarpVector will use the array marked as active vector in polydata
         //it has to be a 3 component array
         //with the same number of tuples as points in polydata
         vtkWarpVector warpVector = vtkWarpVector.New();
#if VTK_MAJOR_VERSION_5
         warpVector.SetInput(polydata);
#else
         warpVector.SetInputData(polydata);
#endif
         warpVector.Update();

         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
#if VTK_MAJOR_VERSION_5
         mapper.SetInput(warpVector.GetPolyDataOutput());
#else
         mapper.SetInputData(warpVector.GetPolyDataOutput());
#endif
         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);
         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(.2, .6, .3);
         renderer.AddActor(actor);
      }
   }
}
