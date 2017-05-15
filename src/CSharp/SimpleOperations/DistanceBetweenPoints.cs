using System;
using System.Runtime.InteropServices;
using System.Diagnostics;
using Kitware.VTK;

void DistanceBetweenPoints() {
   // Create two points.
   double[] p0 = new double[] { 0.0, 0.0, 0.0 };
   double[] p1 = new double[] { 1.0, 1.0, 1.0 };

   IntPtr pP0 = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(double)) * 3);
   IntPtr pP1 = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(double)) * 3);
   Marshal.Copy(p0, 0, pP0, 3);
   Marshal.Copy(p1, 0, pP1, 3);

   // Find the squared distance between the points.
   double squaredDistance = vtkMath.Distance2BetweenPoints(pP0, pP1);

   // Take the square root to get the Euclidean distance between the points.
   double distance = Math.Sqrt(squaredDistance);

   // Output the results.
   Console.WriteLine("SquaredDistance = " + squaredDistance);
   Console.WriteLine("Distance = " + distance);
   Marshal.FreeHGlobal(pP0);
   Marshal.FreeHGlobal(pP1);
}
