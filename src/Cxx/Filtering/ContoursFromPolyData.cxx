#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkPlane.h>
#include <vtkCutter.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMath.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> inputPolyData;
  if(argc > 1)
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();
    inputPolyData = reader->GetOutput();
  }
  else
  {
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetThetaResolution(30);
    sphereSource->SetPhiResolution(15);
    sphereSource->Update();
    inputPolyData = sphereSource->GetOutput();
  }

  vtkSmartPointer<vtkPolyDataMapper> inputMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  inputMapper->SetInput(inputPolyData);
#else
  inputMapper->SetInputData(inputPolyData);
#endif

  // Create a plane to cut
  vtkSmartPointer<vtkPlane> plane =
    vtkSmartPointer<vtkPlane>::New();
  plane->SetOrigin(inputPolyData->GetCenter());
  plane->SetNormal(1,1,1);

  double minBound[3];
  minBound[0] = inputPolyData->GetBounds()[0];
  minBound[1] = inputPolyData->GetBounds()[2];
  minBound[2] = inputPolyData->GetBounds()[4];

  double maxBound[3];
  maxBound[0] = inputPolyData->GetBounds()[1];
  maxBound[1] = inputPolyData->GetBounds()[3];
  maxBound[2] = inputPolyData->GetBounds()[5];

  double center[3];
  center[0] = inputPolyData->GetCenter()[0];
  center[1] = inputPolyData->GetCenter()[1];
  center[2] = inputPolyData->GetCenter()[2];

  double distanceMin = sqrt(vtkMath::Distance2BetweenPoints(minBound, center));
  double distanceMax = sqrt(vtkMath::Distance2BetweenPoints(maxBound, center));

  // Create cutter
  vtkSmartPointer<vtkCutter> cutter =
    vtkSmartPointer<vtkCutter>::New();
  cutter->SetCutFunction(plane);
#if VTK_MAJOR_VERSION <= 5
  cutter->SetInput(inputPolyData);
#else
  cutter->SetInputData(inputPolyData);
#endif
  cutter->GenerateValues(20, -distanceMin, distanceMax);
  vtkSmartPointer<vtkPolyDataMapper> cutterMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cutterMapper->SetInputConnection( cutter->GetOutputPort());
  cutterMapper->ScalarVisibilityOff();

  // Create plane actor
  vtkSmartPointer<vtkActor> planeActor =
    vtkSmartPointer<vtkActor>::New();
  planeActor->GetProperty()->SetColor(1.0,1,0);
  planeActor->GetProperty()->SetLineWidth(3);
  planeActor->SetMapper(cutterMapper);

  // Create input actor
  vtkSmartPointer<vtkActor> inputActor =
    vtkSmartPointer<vtkActor>::New();
  inputActor->GetProperty()->SetColor(1.0, 0.8941, 0.7686); // bisque
  inputActor->SetMapper(inputMapper);

  // Create renderers and add actors of plane and cube
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(planeActor); //display the rectangle resulting from the cut
  renderer->AddActor(inputActor); //display the cube

  //Add renderer to renderwindow and render
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(600, 600);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
  renderer->SetBackground(.1, .2, .3);
  renderWindow->Render();

  interactor->Start();

  return EXIT_SUCCESS;
}
