using System;
using System.Runtime.InteropServices;
using System.Diagnostics;
using Kitware.VTK;

void ProjectPointPlane() {
   vtkPlane plane = vtkPlane.New();
   plane.SetOrigin(0.0, 0.0, 0.0);
   plane.SetNormal(0.0, 0.0, 1.0);

   double[] p = new double[] { 23.1, 54.6, 9.2 };
   double[] projected = new double[3];

   IntPtr pP = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(double)) * 3);
   IntPtr pProjected = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(double)) * 3);
   Marshal.Copy(p, 0, pP, 3);
   Marshal.Copy(projected, 0, pProjected, 3);

   // NOTE: normal assumed to have magnitude 1
   plane.ProjectPoint(pP, pProjected);
   Marshal.Copy(pProjected, projected, 0, 3);
   Marshal.FreeHGlobal(pP);
   Marshal.FreeHGlobal(pProjected);

   Console.WriteLine("Projected: "
      + projected[0] + " "
      + projected[1] + " "
      + projected[2]);
}
