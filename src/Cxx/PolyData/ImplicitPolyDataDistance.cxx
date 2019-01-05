#include <vtkImplicitPolyDataDistance.h>

#include <vtkActor.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkVertexGlyphFilter.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(1.0f);
  sphereSource->Update();
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection( sphereSource->GetOutputPort() );
  sphereMapper->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> sphereActor =
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper( sphereMapper );
  sphereActor->GetProperty()->SetOpacity(.3);
  sphereActor->GetProperty()->SetColor(1,0,0);

  vtkSmartPointer<vtkImplicitPolyDataDistance> implicitPolyDataDistance =
    vtkSmartPointer<vtkImplicitPolyDataDistance>::New();
  implicitPolyDataDistance->SetInput(sphereSource->GetOutput());

  // Setup a grid
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  float step = 0.1;
  for(float x = - 2.0; x <= 2.0; x += step)
  {
    for(float y = - 2.0; y <= 2.0; y += step)
    {
      for(float z = - 2.0; z <= 2.0; z += step)
      {
        points->InsertNextPoint(x,y,z);
      }
    }
  }

  // Add distances to each point
  vtkSmartPointer<vtkFloatArray> signedDistances =
    vtkSmartPointer<vtkFloatArray>::New();
  signedDistances->SetNumberOfComponents(1);
  signedDistances->SetName("SignedDistances");

  // Evaluate the signed distance function at all of the grid points
  for(vtkIdType pointId = 0; pointId < points->GetNumberOfPoints(); ++pointId)
  {
    double p[3];
    points->GetPoint(pointId, p);
    float signedDistance = implicitPolyDataDistance->EvaluateFunction(p);
    signedDistances->InsertNextValue(signedDistance);
  }

  vtkSmartPointer<vtkPolyData> polyData =
    vtkSmartPointer<vtkPolyData>::New();
  polyData->SetPoints(points);
  polyData->GetPointData()->SetScalars(signedDistances);

  vtkSmartPointer<vtkVertexGlyphFilter> vertexGlyphFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
  vertexGlyphFilter->SetInputData(polyData);
  vertexGlyphFilter->Update();

  vtkSmartPointer<vtkPolyDataMapper> signedDistanceMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  signedDistanceMapper->SetInputConnection(vertexGlyphFilter->GetOutputPort());
  signedDistanceMapper->ScalarVisibilityOn();

  vtkSmartPointer<vtkActor> signedDistanceActor =
    vtkSmartPointer<vtkActor>::New();
  signedDistanceActor->SetMapper( signedDistanceMapper );

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddViewProp(sphereActor);
  renderer->AddViewProp(signedDistanceActor);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer( renderer );

  vtkSmartPointer<vtkRenderWindowInteractor> renWinInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renWinInteractor->SetRenderWindow( renderWindow );

  renderWindow->Render();
  renWinInteractor->Start();

  return EXIT_SUCCESS;
}
