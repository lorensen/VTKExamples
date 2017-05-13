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
