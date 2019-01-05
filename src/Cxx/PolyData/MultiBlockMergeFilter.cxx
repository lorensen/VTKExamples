#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkMultiBlockMergeFilter.h>
#include <vtkMultiBlockDataSet.h>

int main(int, char *[])
{

  vtkSmartPointer<vtkSphereSource> sphereSource1 =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource1->Update();
  
  vtkSmartPointer<vtkSphereSource> sphereSource2 =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource2->SetCenter(10,10,10);
  sphereSource2->Update();

  vtkSmartPointer<vtkMultiBlockDataSet> multiBlockDataSet1 =
    vtkSmartPointer<vtkMultiBlockDataSet>::New();
  multiBlockDataSet1->SetNumberOfBlocks(1);
  multiBlockDataSet1->SetBlock(0, sphereSource1->GetOutput());

  vtkSmartPointer<vtkMultiBlockDataSet> multiBlockDataSet2 =
    vtkSmartPointer<vtkMultiBlockDataSet>::New();
  multiBlockDataSet2->SetNumberOfBlocks(1);
  multiBlockDataSet2->SetBlock(0, sphereSource2->GetOutput());
  
  vtkSmartPointer<vtkMultiBlockMergeFilter> multiBlockMergeFilter =
      vtkSmartPointer<vtkMultiBlockMergeFilter>::New();
  multiBlockMergeFilter->AddInputData(multiBlockDataSet1);
  multiBlockMergeFilter->AddInputData(multiBlockDataSet2);
  multiBlockMergeFilter->Update();
  
  return EXIT_SUCCESS;
}
