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
            PolygonIntersection();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void PolygonIntersection() {
         // Create a square in the XY plane
         vtkPoints points = vtkPoints.New();
         points.InsertNextPoint(0.0, 0.0, 0.0);
         points.InsertNextPoint(1.0, 0.0, 0.0);
         points.InsertNextPoint(1.0, 1.0, 0.0);
         points.InsertNextPoint(0.0, 1.0, 0.0);

         // Create the polygon
         vtkPolygon polygon = vtkPolygon.New();
         polygon.GetPoints().DeepCopy(points);
         polygon.GetPointIds().SetNumberOfIds(4); // 4 corners of the square
         polygon.GetPointIds().SetId(0, 0);
         polygon.GetPointIds().SetId(1, 1);
         polygon.GetPointIds().SetId(2, 2);
         polygon.GetPointIds().SetId(3, 3);

         // our line to intersect the polygon with
         double[] p1 = new double[] { 0.1, 0, -1.0 };
         double[] p2 = new double[] { 0.1, 0, 1.0 };
         double tolerance = 0.001;
         // Outputs
         // t must be initalized cause it is passed by reference (that's a c# convention)
         double t = 0.0; // Parametric coordinate of intersection (0 (corresponding to p1) to 1 (corresponding to p2))
         double[] x = new double[] { 0.0, 0.0, 0.0 };
         double[] coords = new double[] { 0.0, 0.0, 0.0 };
         // subId must be initialized cause it is passed by reference (that's a c# convention)
         int subId = 0;

         IntPtr pP1 = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(double)) * 3);
         IntPtr pP2 = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(double)) * 3);
         IntPtr pX = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(double)) * 3);
         IntPtr pCoords = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(double)) * 3);
         Marshal.Copy(p1, 0, pP1, 3);
         Marshal.Copy(p2, 0, pP2, 3);
         // next two lines are not necessarely needed, but I prefer to initialize ref parameter (in those a result is passed back)
         Marshal.Copy(x, 0, pX, 3);
         Marshal.Copy(coords, 0, pCoords, 3);
         // see vtkCell API for a detailed description of this function
         int iD = polygon.IntersectWithLine(pP1, pP2, tolerance, ref t, pX, pCoords, ref subId);
         // Copy result back to our managed arrays
         Marshal.Copy(pX, x, 0, 3);
         Marshal.Copy(pCoords, coords, 0, 3);
         Console.WriteLine("intersected? " + iD); ;
         Console.WriteLine("intersection: " + x[0] + " " + x[1] + " " + x[2]);
         Marshal.FreeHGlobal(pP1);
         Marshal.FreeHGlobal(pP2);
         Marshal.FreeHGlobal(pX);
         Marshal.FreeHGlobal(pCoords);
         // nothing to visualize
      }
   }
}
