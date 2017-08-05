#include <vtkSmartPointer.h>
#include <vtkCutter.h>

#include <vtkXMLPolyDataReader.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkPlane.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMath.h>
#include <vtkNamedColors.h>

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
  inputMapper->SetInputData(inputPolyData);

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
  cutter->SetInputData(inputPolyData);

  cutter->GenerateValues(20, -distanceMin, distanceMax);
  vtkSmartPointer<vtkPolyDataMapper> cutterMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cutterMapper->SetInputConnection( cutter->GetOutputPort());
  cutterMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Create plane actor
  vtkSmartPointer<vtkActor> planeActor =
    vtkSmartPointer<vtkActor>::New();
  planeActor->GetProperty()->SetColor(colors->GetColor3d("Deep_pink").GetData());
  planeActor->GetProperty()->SetLineWidth(5);
  planeActor->SetMapper(cutterMapper);

  // Create input actor
  vtkSmartPointer<vtkActor> inputActor =
    vtkSmartPointer<vtkActor>::New();
  inputActor->GetProperty()->SetColor(colors->GetColor3d("Bisque").GetData());
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
  renderer->SetBackground(colors->GetColor3d("Slate_grey").GetData());
  renderWindow->Render();

  interactor->Start();

  return EXIT_SUCCESS;
}
