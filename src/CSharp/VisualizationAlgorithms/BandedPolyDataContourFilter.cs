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
            BandedPolyDataContourFilter();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void BandedPolyDataContourFilter() {
         vtkPoints pts = vtkPoints.New();
         pts.InsertPoint(0, 0, 0, 0);
         pts.InsertPoint(1, 0, 1, 0);
         pts.InsertPoint(2, 0, 2, 0);
         pts.InsertPoint(3, 1, 0, 0);
         pts.InsertPoint(4, 1, 1, 0);
         pts.InsertPoint(5, 1, 2, 0);
         pts.InsertPoint(6, 2, 0, 0);
         pts.InsertPoint(7, 2, 2, 0);
         pts.InsertPoint(8, 3, 0, 0);
         pts.InsertPoint(9, 3, 1, 0);
         pts.InsertPoint(10, 3, 2, 0);
         pts.InsertPoint(11, 4, 0, 0);
         pts.InsertPoint(12, 6, 0, 0);
         pts.InsertPoint(13, 5, 2, 0);
         pts.InsertPoint(14, 7, 0, 0);
         pts.InsertPoint(15, 9, 0, 0);
         pts.InsertPoint(16, 7, 2, 0);
         pts.InsertPoint(17, 9, 2, 0);
         pts.InsertPoint(18, 10, 0, 0);
         pts.InsertPoint(19, 12, 0, 0);
         pts.InsertPoint(20, 10, 1, 0);
         pts.InsertPoint(21, 12, 1, 0);
         pts.InsertPoint(22, 10, 2, 0);
         pts.InsertPoint(23, 12, 2, 0);
         pts.InsertPoint(24, 10, 3, 0);
         pts.InsertPoint(25, 12, 3, 0);

         vtkCellArray polys = vtkCellArray.New();
         polys.InsertNextCell(4);
         polys.InsertCellPoint(14);
         polys.InsertCellPoint(15);
         polys.InsertCellPoint(17);
         polys.InsertCellPoint(16);
         polys.InsertNextCell(3);
         polys.InsertCellPoint(11);
         polys.InsertCellPoint(12);
         polys.InsertCellPoint(13);

         vtkFloatArray scalars = vtkFloatArray.New();
         scalars.SetNumberOfTuples(26);
         scalars.SetTuple1(0, 0);
         scalars.SetTuple1(1, 50);
         scalars.SetTuple1(2, 100);
         scalars.SetTuple1(3, 0);
         scalars.SetTuple1(4, 50);
         scalars.SetTuple1(5, 100);
         scalars.SetTuple1(6, 10);
         scalars.SetTuple1(7, 90);
         scalars.SetTuple1(8, 10);
         scalars.SetTuple1(9, 50);
         scalars.SetTuple1(10, 90);
         scalars.SetTuple1(11, 10);
         scalars.SetTuple1(12, 40);
         scalars.SetTuple1(13, 100);
         scalars.SetTuple1(14, 0);
         scalars.SetTuple1(15, 60);
         scalars.SetTuple1(16, 40);
         scalars.SetTuple1(17, 100);
         scalars.SetTuple1(18, 0);
         scalars.SetTuple1(19, 25);
         scalars.SetTuple1(20, 25);
         scalars.SetTuple1(21, 50);
         scalars.SetTuple1(22, 50);
         scalars.SetTuple1(23, 75);
         scalars.SetTuple1(24, 75);
         scalars.SetTuple1(25, 100);

         vtkPolyData polyData = vtkPolyData.New();
         polyData.SetPoints(pts);
         polyData.SetPolys(polys);
         polyData.GetPointData().SetScalars(scalars);

         vtkBandedPolyDataContourFilter bf = vtkBandedPolyDataContourFilter.New();
#if VTK_MAJOR_VERSION_5
         bf.SetInput(polyData);
#else
         bf.SetInputData (polyData);
#endif
         bf.GenerateValues(3, 25, 75);

         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInputConnection(bf.GetOutputPort());
         mapper.SetScalarModeToUseCellData();
         mapper.SetScalarRange(0, 4);
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
