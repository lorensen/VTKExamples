using System;
using System.Diagnostics;
using Kitware.VTK;

void PerspectiveTransform() {
   vtkMatrix4x4 m = vtkMatrix4x4.New();
   m.SetElement(0, 0, 1);
   m.SetElement(0, 1, 2);
   m.SetElement(0, 2, 3);
   m.SetElement(0, 3, 4);
   m.SetElement(1, 0, 2);
   m.SetElement(1, 1, 2);
   m.SetElement(1, 2, 3);
   m.SetElement(1, 3, 4);
   m.SetElement(2, 0, 3);
   m.SetElement(2, 1, 2);
   m.SetElement(2, 2, 3);
   m.SetElement(2, 3, 4);
   m.SetElement(3, 0, 4);
   m.SetElement(3, 1, 2);
   m.SetElement(3, 2, 3);
   m.SetElement(3, 3, 4);

   vtkPerspectiveTransform perspectiveTransform = vtkPerspectiveTransform.New();
   perspectiveTransform.SetMatrix(m);

   vtkTransform transform = vtkTransform.New();
   transform.SetMatrix(m);

   double[] p = new double[]{1.0, 2.0, 3.0};

   double[] normalProjection = transform.TransformPoint(p[0], p[1], p[2]);

   Console.WriteLine("Standard projection: "
      + normalProjection[0] + " "
      + normalProjection[1] + " "
      + normalProjection[2]);

   double[] perspectiveProjection = perspectiveTransform.TransformPoint(p[0], p[1], p[2]);

   Console.WriteLine("Perspective  projection: "
      + perspectiveProjection[0] + " "
      + perspectiveProjection[1] + " "
      + perspectiveProjection[2]);
}
