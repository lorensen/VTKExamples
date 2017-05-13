using System;
using Kitware.VTK;

namespace ActiViz.Examples {
   class Program {
      static void Main(string[] args) {
         IterateOverLines();
         Console.WriteLine("\nPress any key to continue...");
         Console.ReadKey();
      }


      private static void IterateOverLines() {
         double[] origin = new double[] { 0.0, 0.0, 0.0 };
         double[,] p = new double[,] {
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0},
            {0.0, 1.0, 2.0},
            {1.0, 2.0, 3.0}};

         // Create a vtkPoints object and store the points in it
         vtkPoints points = vtkPoints.New();
         points.InsertNextPoint(origin[0], origin[1], origin[2]);
         for(int i = 0; i < 4; i++)
            points.InsertNextPoint(p[i, 0], p[i, 1], p[i, 2]);

         // Create a cell array to store the lines in and add the lines to it
         vtkCellArray lines = vtkCellArray.New();

         // Create four lines
         for(int i = 0; i < 4; i++) {
            vtkLine line = vtkLine.New();
            line.GetPointIds().SetId(0, i);
            line.GetPointIds().SetId(1, i + 1);
            lines.InsertNextCell(line);
         }

         // Create a polydata to store everything in
         vtkPolyData linesPolyData = vtkPolyData.New();

         // Add the points to the dataset
         linesPolyData.SetPoints(points);

         // Add the lines to the dataset
         linesPolyData.SetLines(lines);

         Console.WriteLine("There are " + linesPolyData.GetNumberOfLines() + " lines.");
         linesPolyData.GetLines().InitTraversal();
         vtkIdList idList = vtkIdList.New();
         while(linesPolyData.GetLines().GetNextCell(idList) != 0) {
            Console.WriteLine("Line has " + idList.GetNumberOfIds() + " points.");

            for(int pointId = 0; pointId < idList.GetNumberOfIds(); pointId++) {
               Console.Write(idList.GetId(pointId) + " ");
            }
            Console.Write(Environment.NewLine);
         }
      }
   }
}
