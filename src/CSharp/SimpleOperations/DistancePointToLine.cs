using System;
using System.Runtime.InteropServices;
using System.Diagnostics;
using Kitware.VTK;

void DistancePointToLine() {
   double[] lineP0 = new double[] { 0.0, 0.0, 0.0 };
   double[] lineP1 = new double[] { 2.0, 0.0, 0.0 };

   double[] p0 = new double[] { 1.0, 0, 0 };
   double[] p1 = new double[] { 1.0, 2.0, 0 };

   // Don't worry, fortunately only a few functions in ActiViz.NET need 
   // Marshaling between Managed and Unmanaged Code
   IntPtr pP0 = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(double)) * 3);
   IntPtr pP1 = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(double)) * 3);
   IntPtr pLineP0 = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(double)) * 3);
   IntPtr pLineP1 = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(double)) * 3);
   Marshal.Copy(p0, 0, pP0, 3);
   Marshal.Copy(p1, 0, pP1, 3);
   Marshal.Copy(lineP0, 0, pLineP0, 3);
   Marshal.Copy(lineP1, 0, pLineP1, 3);

   double dist0 = vtkLine.DistanceToLine(pP0, pLineP0, pLineP1);
   Console.WriteLine("Dist0: " + dist0);

   double dist1 = vtkLine.DistanceToLine(pP1, pLineP0, pLineP1);
   Console.WriteLine("Dist1: " + dist1);

   double parametricCoord = 0.0; // must be initialized because this var is passed by reference
   double[] closest = new double[3];
   IntPtr pClosest = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(double)) * 3);
   Marshal.Copy(closest, 0, pClosest, 3);

   dist0 = vtkLine.DistanceToLine(pP0, pLineP0, pLineP1, ref parametricCoord, pClosest);
   Marshal.Copy(pClosest, closest, 0, 3);
   Console.WriteLine(
      "Dist0: " + dist0 
      + " closest point: " + closest[0] + " " + closest[1] + " " + closest[2] 
      + " parametricCoord: " + parametricCoord);

   dist1 = vtkLine.DistanceToLine(pP1, pLineP0, pLineP1, ref parametricCoord, pClosest);
   Marshal.Copy(pClosest, closest, 0, 3);
   Console.WriteLine(
      "Dist1: " + dist1 
      + " closest point: " + closest[0] + " " + closest[1] + " " + closest[2]
      + " parametricCoord: " + parametricCoord);

   Marshal.FreeHGlobal(pP0);
   Marshal.FreeHGlobal(pP1);
   Marshal.FreeHGlobal(pLineP0);
   Marshal.FreeHGlobal(pLineP1);
   Marshal.FreeHGlobal(pClosest);
}
