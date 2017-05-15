using System;
using Kitware.VTK;

namespace ActiViz.Examples {
   class Program {
      static void Main(string[] args) {
         MultiBlockMergeFilter();
         Console.WriteLine("\nPress any key to continue...");
         Console.ReadKey();
      }


      private static void MultiBlockMergeFilter() {
         vtkSphereSource sphereSource1 = vtkSphereSource.New();
         sphereSource1.Update();

         vtkSphereSource sphereSource2 = vtkSphereSource.New();
         sphereSource2.SetCenter(10, 10, 10);
         sphereSource2.Update();

         vtkMultiBlockDataSet multiBlockDataSet1 = vtkMultiBlockDataSet.New();
         multiBlockDataSet1.SetNumberOfBlocks(1);
         multiBlockDataSet1.SetBlock(0, sphereSource1.GetOutput());
#if VTK_MAJOR_VERSION_5
         multiBlockDataSet1.Update();
#endif

         vtkMultiBlockDataSet multiBlockDataSet2 = vtkMultiBlockDataSet.New();
         multiBlockDataSet2.SetNumberOfBlocks(1);
         multiBlockDataSet2.SetBlock(0, sphereSource2.GetOutput());
#if VTK_MAJOR_VERSION_5
         multiBlockDataSet2.Update();
#endif

         vtkMultiBlockMergeFilter multiBlockMergeFilter = vtkMultiBlockMergeFilter.New();
#if VTK_MAJOR_VERSION_5
         multiBlockMergeFilter.AddInput(multiBlockDataSet1);
         multiBlockMergeFilter.AddInput(multiBlockDataSet2);
#else
         multiBlockMergeFilter.AddInputData(multiBlockDataSet1);
         multiBlockMergeFilter.AddInputData(multiBlockDataSet2);
#endif
         multiBlockMergeFilter.Update();
      }
   }
}
