using System;

using Kitware.VTK;

namespace ActiViz.Examples {
   class Program {
      static void Main(string[] args) {
         CellEdges();
         Console.WriteLine("\nPress any key to continue...");
         Console.ReadKey();
      }


      private static void CellEdges() {
         vtkTriangle triangle = vtkTriangle.New();
         triangle.GetPoints().SetPoint(0, 1.0, 0.0, 0.0);
         triangle.GetPoints().SetPoint(1, 0.0, 0.0, 0.0);
         triangle.GetPoints().SetPoint(2, 0.0, 1.0, 0.0);
         triangle.GetPointIds().SetId(0, 0);
         triangle.GetPointIds().SetId(1, 1);
         triangle.GetPointIds().SetId(2, 2);

         Console.WriteLine("The cell has " + triangle.GetNumberOfEdges() + " edges.");

         for(int i = 0; i < triangle.GetNumberOfEdges(); i++) {
            vtkCell edge = triangle.GetEdge(i);

            vtkIdList pointIdList = edge.GetPointIds();
            Console.WriteLine("Edge " + i + " has " + pointIdList.GetNumberOfIds() + " points.");

            for(int p = 0; p < pointIdList.GetNumberOfIds(); p++) {
               Console.WriteLine("Edge " + i + " uses point " + pointIdList.GetId(p));
            }
         }
      }
   }
}
