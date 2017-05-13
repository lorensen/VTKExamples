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
            Tetrahedron();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void Tetrahedron() {
         vtkPoints points = vtkPoints.New();
         points.InsertNextPoint(0, 0, 0);
         points.InsertNextPoint(1, 0, 0);
         points.InsertNextPoint(1, 1, 0);
         points.InsertNextPoint(0, 1, 1);
         points.InsertNextPoint(5, 5, 5);
         points.InsertNextPoint(6, 5, 5);
         points.InsertNextPoint(6, 6, 5);
         points.InsertNextPoint(5, 6, 6);

         // Method 1
         vtkUnstructuredGrid unstructuredGrid1 = vtkUnstructuredGrid.New();
         unstructuredGrid1.SetPoints(points);

         int[] ptIds = new int[] { 0, 1, 2, 3 };
         IntPtr ptIdsPointer = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(int)) * 4);
         Marshal.Copy(ptIds, 0, ptIdsPointer, 4);
         unstructuredGrid1.InsertNextCell(10, 4, ptIdsPointer);
         Marshal.FreeHGlobal(ptIdsPointer);

         // Method 2
         vtkUnstructuredGrid unstructuredGrid2 = vtkUnstructuredGrid.New();
         unstructuredGrid2.SetPoints(points);

         vtkTetra tetra = vtkTetra.New();

         tetra.GetPointIds().SetId(0, 4);
         tetra.GetPointIds().SetId(1, 5);
         tetra.GetPointIds().SetId(2, 6);
         tetra.GetPointIds().SetId(3, 7);

         vtkCellArray cellArray = vtkCellArray.New();
         cellArray.InsertNextCell(tetra);
         unstructuredGrid2.SetCells(10, cellArray);

         // Create a mapper and actor
         vtkDataSetMapper mapper1 = vtkDataSetMapper.New();
         mapper1.SetInputConnection(unstructuredGrid1.GetProducerPort());

         vtkActor actor1 = vtkActor.New();
         actor1.SetMapper(mapper1);

         // Create a mapper and actor
         vtkDataSetMapper mapper2 = vtkDataSetMapper.New();
         mapper2.SetInputConnection(unstructuredGrid2.GetProducerPort());

         vtkActor actor2 = vtkActor.New();
         actor2.SetMapper(mapper2);

         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         renderer.SetBackground(0.2, 0.3, 0.4);
         // Add the actor to the scene
         renderer.AddActor(actor1);
         renderer.AddActor(actor2);
         renderer.SetBackground(.3, .6, .3); // Background color green
      }
   }
}
