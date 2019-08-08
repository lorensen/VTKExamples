#include <vtkSmartPointer.h>
#include "vtkGLTFExporter.h"

#include <vtkArrowSource.h>
#include <vtkSphereSource.h>
#include <vtkMath.h>
#include <vtkMinimalStandardRandomSequence.h>
#include <vtkNamedColors.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>

#include <array>

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Uaage: GLTFExporter file.gltf" << std::endl;
    return EXIT_FAILURE;
  }
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Set the background color.
  vtkColor3d backgroundColor = colors->GetColor3d("SlateGray");

  //Create an arrow.
  vtkSmartPointer<vtkArrowSource> arrowSource =
    vtkSmartPointer<vtkArrowSource>::New();

  // Generate a random start and end point
  double startPoint[3];
  double endPoint[3];
  vtkSmartPointer<vtkMinimalStandardRandomSequence> rng =
    vtkSmartPointer<vtkMinimalStandardRandomSequence>::New();
  rng->SetSeed(8775070); // For testing.
  for (auto i = 0; i < 3; ++i)
  {
    rng->Next();
    startPoint[i] = rng->GetRangeValue(-10, 10);
    rng->Next();
    endPoint[i] = rng->GetRangeValue(-10, 10);
  }

  // Compute a basis
  double normalizedX[3];
  double normalizedY[3];
  double normalizedZ[3];

  // The X axis is a vector from start to end
  vtkMath::Subtract(endPoint, startPoint, normalizedX);
  double length = vtkMath::Norm(normalizedX);
  vtkMath::Normalize(normalizedX);

  // The Z axis is an arbitrary vector cross X
  double arbitrary[3];
  for (auto i = 0; i < 3; ++i)
  {
    rng->Next();
    arbitrary[i] = rng->GetRangeValue(-10, 10);
  }
  vtkMath::Cross(normalizedX, arbitrary, normalizedZ);
  vtkMath::Normalize(normalizedZ);

  // The Y axis is Z cross X
  vtkMath::Cross(normalizedZ, normalizedX, normalizedY);
  vtkSmartPointer<vtkMatrix4x4> matrix =
    vtkSmartPointer<vtkMatrix4x4>::New();

  // Create the direction cosine matrix
  matrix->Identity();
  for (auto i = 0; i < 3; i++)
  {
    matrix->SetElement(i, 0, normalizedX[i]);
    matrix->SetElement(i, 1, normalizedY[i]);
    matrix->SetElement(i, 2, normalizedZ[i]);
  }

  // Apply the transforms
  vtkSmartPointer<vtkTransform> transform =
    vtkSmartPointer<vtkTransform>::New();
  transform->Translate(startPoint);
  transform->Concatenate(matrix);
  transform->Scale(length, length, length);

  // Transform the polydata
  vtkSmartPointer<vtkTransformPolyDataFilter> transformPD =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transformPD->SetTransform(transform);
  transformPD->SetInputConnection(arrowSource->GetOutputPort());

  //Create a mapper and actor for the arrow
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
#ifdef USER_MATRIX
  mapper->SetInputConnection(arrowSource->GetOutputPort());
  actor->SetUserMatrix(transform->GetMatrix());
#else
  mapper->SetInputConnection(transformPD->GetOutputPort());
#endif
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(colors->GetColor3d("Cyan").GetData());

  // Create spheres for start and end point
  vtkSmartPointer<vtkSphereSource> sphereStartSource =
    vtkSmartPointer<vtkSphereSource>::New();
    sphereStartSource->SetCenter(startPoint);
    sphereStartSource->SetRadius(0.8);
  vtkSmartPointer<vtkPolyDataMapper> sphereStartMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereStartMapper->SetInputConnection(sphereStartSource->GetOutputPort());
  vtkSmartPointer<vtkActor> sphereStart =
    vtkSmartPointer<vtkActor>::New();
  sphereStart->SetMapper(sphereStartMapper);
  sphereStart->GetProperty()->SetColor(colors->GetColor3d("Yellow").GetData());

  vtkSmartPointer<vtkSphereSource> sphereEndSource =
    vtkSmartPointer<vtkSphereSource>::New();
    sphereEndSource->SetCenter(endPoint);
    sphereEndSource->SetRadius(0.8);
  vtkSmartPointer<vtkPolyDataMapper> sphereEndMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereEndMapper->SetInputConnection(sphereEndSource->GetOutputPort());
  vtkSmartPointer<vtkActor> sphereEnd =
    vtkSmartPointer<vtkActor>::New();
  sphereEnd->SetMapper(sphereEndMapper);
  sphereEnd->GetProperty()->SetColor(colors->GetColor3d("Magenta").GetData());

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);
  renderWindow->SetWindowName("Oriented Arrow");

  auto style =
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->SetInteractorStyle(style);

  //Add the actor to the scene
  renderer->AddActor(actor);
  renderer->AddActor(sphereStart);
  renderer->AddActor(sphereEnd);
  renderer->SetBackground(backgroundColor.GetData());

  //Render and interact
  renderWindow->Render();
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->GetActiveCamera()->Roll(30);
  renderer->ResetCameraClippingRange();

  renderWindowInteractor->Start();

  auto writer =
    vtkSmartPointer<vtkGLTFExporter>::New();
  writer->SetFileName(argv[1]);
  writer->InlineDataOn();
  writer->SetRenderWindow(renderWindow);
  writer->Write();

  return EXIT_SUCCESS;
}
