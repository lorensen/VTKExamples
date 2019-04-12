#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkVectorDot.h>

// For compatibility with new VTK generic data arrays
#ifdef vtkGenericDataArray_h
#define InsertNextTupleValue InsertNextTypedTuple
#endif

int main(int, char *[])
{
  // Generate data
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(1,0,0);
  points->InsertNextPoint(2,0,0);

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  // Add normals
  vtkSmartPointer<vtkFloatArray> normals =
    vtkSmartPointer<vtkFloatArray>::New();
  normals->SetNumberOfComponents(3);
  normals->SetName("Normals");

  float n0[3] = {1,0,0};
  float n1[3] = {1,0,0};
  float n2[3] = {1,0,0};
  normals->InsertNextTupleValue(n0);
  normals->InsertNextTupleValue(n1);
  normals->InsertNextTupleValue(n2);

  polydata->GetPointData()->SetNormals(normals);

  // Add vectors
  vtkSmartPointer<vtkFloatArray> vectors =
    vtkSmartPointer<vtkFloatArray>::New();
  vectors->SetNumberOfComponents(3);
  vectors->SetName("Vectors");

  float v0[3] = {1,0,0};
  float v1[3] = {.707f,.707f,0};
  float v2[3] = {0,1,0};
  vectors->InsertNextTupleValue(v0);
  vectors->InsertNextTupleValue(v1);
  vectors->InsertNextTupleValue(v2);

  polydata->GetPointData()->SetVectors(vectors);

  // Compute the dot products between normals and vectors
  vtkSmartPointer<vtkVectorDot> vectorDot =
      vtkSmartPointer<vtkVectorDot>::New();
  vectorDot->SetInputData(polydata);
  vectorDot->Update();

  // Get the results
  vtkFloatArray* scalars = dynamic_cast<vtkFloatArray*> ( vectorDot->GetOutput()->GetPointData()->GetScalars() );

  // Output the results
  for(vtkIdType i = 0; i < scalars->GetNumberOfTuples(); i++)
  {
    std::cout << "Value " << i << " : " << scalars->GetValue(i) << std::endl;
  }

  return EXIT_SUCCESS;
}
