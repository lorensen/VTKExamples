#include <vtkIntArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkSmartPointer.h>
#include <vtkThresholdPoints.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(1,1,1);
  points->InsertNextPoint(2,2,2);
  points->InsertNextPoint(3,3,3);
  points->InsertNextPoint(4,4,4);

  std::cout << "There are " << points->GetNumberOfPoints()
            << " points before thresholding." << std::endl;

  //setup position index
  vtkSmartPointer<vtkIntArray> index =
    vtkSmartPointer<vtkIntArray>::New();
  index->SetNumberOfComponents(1);
  index->SetName("index");
  index->InsertNextValue(0);
  index->InsertNextValue(1);
  index->InsertNextValue(2);
  index->InsertNextValue(3);
  index->InsertNextValue(4);

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->GetPointData()->AddArray(index);

  vtkSmartPointer<vtkThresholdPoints> threshold =
    vtkSmartPointer<vtkThresholdPoints>::New();
  threshold->SetInputData(polydata);
  threshold->ThresholdByLower(2);
  threshold->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, "index");
  threshold->Update();

  //vtkPolyData* thresholdedPolydata = threshold->GetOutput();
  vtkPolyData* thresholdedPolydata = threshold->GetOutput();
  std::cout << "There are " << thresholdedPolydata->GetNumberOfPoints()
            << " points after thresholding." << std::endl;
  for(vtkIdType i = 0; i < thresholdedPolydata->GetNumberOfPoints(); i++)
  {
    double p[3];
    thresholdedPolydata->GetPoint(i,p);
    std::cout << "Point " << i << " : " << p[0] << " " << p[1] << " " << p[2] << std::endl;
  }

  return EXIT_SUCCESS;
}
