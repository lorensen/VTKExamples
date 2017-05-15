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
            Point();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void Point() {
         // Create the geometry of the points (the coordinate)
         vtkPoints points = vtkPoints.New();
         double[,] p = new double[,] {
            {1.0, 2.0, 3.0}, 
            {3.0, 1.0, 2.0}, 
            {2.0, 3.0, 1.0}
         };

         // Create topology of the points (a vertex per point)
         vtkCellArray vertices = vtkCellArray.New();
         int nPts = 3;

         int[] ids = new int[nPts];
         for(int i = 0; i < nPts; i++)
            ids[i] = points.InsertNextPoint(p[i, 0], p[i, 1], p[i, 2]);

         int size = Marshal.SizeOf(typeof(int)) * nPts;
         IntPtr pIds = Marshal.AllocHGlobal(size);
         Marshal.Copy(ids, 0, pIds, nPts);
         vertices.InsertNextCell(nPts, pIds);
         Marshal.FreeHGlobal(pIds);

         // Create a polydata object
         vtkPolyData pointPoly = vtkPolyData.New();

         // Set the points and vertices we created as the geometry and topology of the polydata
         pointPoly.SetPoints(points);
         pointPoly.SetVerts(vertices);

         // Visualize
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInput(pointPoly);

         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);
         actor.GetProperty().SetPointSize(20);
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         renderer.SetBackground(0.3, 0.2, 0.1);
         renderer.AddActor(actor);
      }
   }
}
