using System;
using Kitware.VTK;

namespace ActiViz.Examples {
   class Program {
      static void Main(string[] args) {
         NullPoint();
         Console.WriteLine("\nPress any key to continue...");
         Console.ReadKey();
      }


      private static void NullPoint() {
         vtkPoints points = vtkPoints.New();
         points.InsertNextPoint(1, 1, 1);
         points.InsertNextPoint(2, 2, 2);
         points.InsertNextPoint(3, 3, 3);

         vtkPolyData polydata = vtkPolyData.New();
         polydata.SetPoints(points);

         vtkFloatArray floatArray = vtkFloatArray.New();
         floatArray.SetNumberOfValues(3);
         floatArray.SetNumberOfComponents(1);
         floatArray.SetName("FloatArray");
         for(int i = 0; i < 3; i++) {
            floatArray.SetValue(i, 2);
         }
         polydata.GetPointData().AddArray(floatArray);

         vtkIntArray intArray = vtkIntArray.New();
         intArray.SetNumberOfValues(3);
         intArray.SetNumberOfComponents(1);
         intArray.SetName("IntArray");
         for(int i = 0; i < 3; i++) {
            intArray.SetValue(i, 2);
         }

         polydata.GetPointData().AddArray(intArray);

         Console.WriteLine("PointIdx   x y z " + "floatArray" + " " + "intArray");
         Console.WriteLine("----------------------------------------");
         for(int i = 0; i < 3; i++) {
            double[] p = polydata.GetPoint(i);
            vtkFloatArray pointsFloatArray = vtkFloatArray.SafeDownCast(polydata.GetPointData().GetArray("FloatArray"));
            vtkIntArray pointsIntArray = vtkIntArray.SafeDownCast(polydata.GetPointData().GetArray("IntArray"));
            Console.WriteLine("   " + i + "       " + p[0] + " " + p[1] + " " + p[2] + "    "
                      + pointsFloatArray.GetValue(i) + "          " + pointsIntArray.GetValue(i));
         }

         polydata.GetPointData().NullPoint(1);
         polydata.Modified();
         Console.WriteLine("");

         for(int i = 0; i < 3; i++) {
            double[] p = polydata.GetPoint(i);
            vtkFloatArray pointsFloatArray = vtkFloatArray.SafeDownCast(polydata.GetPointData().GetArray("FloatArray"));
            vtkIntArray pointsIntArray = vtkIntArray.SafeDownCast(polydata.GetPointData().GetArray("IntArray"));
            Console.WriteLine("   " + i + "       " + p[0] + " " + p[1] + " " + p[2] + "    "
                      + pointsFloatArray.GetValue(i) + "          " + pointsIntArray.GetValue(i));

         }
      }
   }
}
