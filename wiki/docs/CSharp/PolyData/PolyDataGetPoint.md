[VTKExamples](/home/)/[CSharp](/CSharp)/PolyData/PolyDataGetPoint

### Description
<p>This example demonstrates how to obtain the coordinates of a point in a vtkPolyData object.

* Suggested by Sara Rolfe
</p>
A tutorial on how to setup a Console Application utilizing Kitware.VTK.dll can be found here: [Setup a Console Application to use Kitware.VTK.dll](http://www.vtk.org/Wiki/VTK/CSharp/ActiViz.NET)<br />

**PolyDataGetPoint.cs**
```csharp
using System;
using Kitware.VTK;

namespace ActiViz.Examples {
   class Program {
      static void Main(string[] args) {
         PolyDataGetPoint();
         Console.WriteLine("\nPress any key to continue...");
         Console.ReadKey();
      }


      private void PolyDataGetPoint() {
         // Create a sphere
         vtkSphereSource sphereSource = vtkSphereSource.New();
         sphereSource.Update();
         vtkPolyData polydata = sphereSource.GetOutput();

         // Write all of the coordinates of the points in the vtkPolyData to the console.
         for(int i = 0; i < polydata.GetNumberOfPoints(); i++) {
            double[] p = polydata.GetPoint(i);
            // This is identical to:
            // double[] p = polydata.GetPoints().GetPoint(i);
            Console.WriteLine("Point " + i + " : (" + p[0] + " " + p[1] + " " + p[2] + ")");
         }
      }
   }
}
```
