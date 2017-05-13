[VTKExamples](Home)/[CSharp](CSharp)/PolyData/ClosedSurface

### Description
A tutorial on how to setup a Console Application utilizing Kitware.VTK.dll can be found here: [Setup a Console Application to use Kitware.VTK.dll](http://www.vtk.org/Wiki/VTK/CSharp/ActiViz.NET)<br />

**ClosedSurface.cs**
```csharp
using System;

using Kitware.VTK;

namespace ActiViz.Examples {
   class Program {
      static void Main(string[] args) {
         ClosedSurface();
      }


      private static void ClosedSurface() {
         // Create a sphere
         vtkSphereSource sphereSource = vtkSphereSource.New();
         sphereSource.Update();

         vtkFeatureEdges featureEdges = vtkFeatureEdges.New();
         featureEdges.FeatureEdgesOff();
         featureEdges.BoundaryEdgesOn();
         featureEdges.NonManifoldEdgesOn();
         featureEdges.SetInputConnection(sphereSource.GetOutputPort());
         featureEdges.Update();

         int numberOfOpenEdges = featureEdges.GetOutput().GetNumberOfCells();

         if(numberOfOpenEdges > 0) {
            Console.WriteLine("Surface is not closed");
         }
         else {
            Console.WriteLine("Surface is closed");
         }
         // nothing to show graphically
         Console.WriteLine("\nPress any key to continue...");
         Console.ReadKey();
      }
   }
}
```
