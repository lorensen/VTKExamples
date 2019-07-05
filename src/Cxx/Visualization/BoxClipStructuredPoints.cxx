#include <vtkSmartPointer.h>
#include <vtkBoxClipDataSet.h>
#include <vtkLookupTable.h>

#include <vtkMetaImageReader.h>
#include <vtkImageData.h>

#include <vtkDataSetMapper.h>
#include <vtkCamera.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkNamedColors.h>
#include <vtkColor.h>

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " file.mhd" << endl;
    return EXIT_FAILURE;
  }

  auto colors =
    vtkSmartPointer<vtkNamedColors>::New();
  vtkColor3d backgroundColor = colors->GetColor3d("Silver");

  // Read the data
  auto reader =
    vtkSmartPointer<vtkMetaImageReader>::New();
  reader->SetFileName (argv[1]);
  reader->Update();

  double bounds[6];
  reader->GetOutput()->GetBounds(bounds);  

  double range[2];
  reader->GetOutput()->GetScalarRange(range);  

  double minBoxPoint[3];
  double maxBoxPoint[3];
  minBoxPoint[0] = (bounds[1] - bounds[0]) / 2.0 + bounds[0];
  minBoxPoint[1] = (bounds[3] - bounds[2]) / 2.0 + bounds[2];
  minBoxPoint[2] = (bounds[5] - bounds[4]) / 2.0 + bounds[4];
  maxBoxPoint[0] = bounds[1];
  maxBoxPoint[1] = bounds[3];
  maxBoxPoint[2] = bounds[5];

  vtkSmartPointer<vtkBoxClipDataSet> boxClip =
    vtkSmartPointer<vtkBoxClipDataSet>::New();
  boxClip->SetInputConnection (reader->GetOutputPort());

  const double minusx[] = { -1.0, -0.5, 0.0 };
  const double minusy[] = { 0.0, -1.0, 0.0 };
  const double minusz[] = { 0.0, 0.0, -1.0 };
  const double plusx[] = { 1.0, 0.0, 0.0 };
  const double plusy[] = { 0.0, 1.0, 0.0 };
  const double plusz[] = { 0.0, 0.0, 1.0 };
  boxClip->SetBoxClip(minusx, minBoxPoint,
                      minusy, minBoxPoint,
                      minusz, minBoxPoint,
                      plusx, maxBoxPoint,
                      plusy, maxBoxPoint,
                      plusz, maxBoxPoint);
  boxClip->GenerateClippedOutputOn();

  // Define a lut
  auto lut1 =
    vtkSmartPointer<vtkLookupTable>::New();
  lut1->SetHueRange (0.667, 0);

  auto mapperIn =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapperIn->SetInputConnection(boxClip->GetOutputPort(0));
  mapperIn->SetScalarRange(reader->GetOutput()->GetScalarRange());
  mapperIn->SetLookupTable(lut1);
  mapperIn->SetColorModeToMapScalars();

  auto actorIn = 
    vtkSmartPointer<vtkActor>::New();
  actorIn->SetMapper(mapperIn);
 
  auto mapperOut =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapperOut->SetInputConnection(boxClip->GetOutputPort(1));
  mapperOut->SetScalarRange(reader->GetOutput()->GetScalarRange());
  mapperOut->SetLookupTable(lut1);
  mapperOut->SetColorModeToMapScalars();

  // Move the outside actor
  auto actorOut = 
    vtkSmartPointer<vtkActor>::New();
  actorOut->SetMapper(mapperOut);
  actorOut->AddPosition(-.5 * (maxBoxPoint[0] - minBoxPoint[0]),
                        -.5 * (maxBoxPoint[1] - minBoxPoint[1]),
                        -.5 * (maxBoxPoint[2] - minBoxPoint[2]));
 
  // Create a renderer, render window, and interactor
  auto renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(backgroundColor.GetData());
  renderer->UseHiddenLineRemovalOn();

  auto renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);

  auto renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  // Add the actors to the scene
  renderer->AddActor(actorIn);
  renderer->AddActor(actorOut);
  
  // Generate an interesting view
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(120);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->GetActiveCamera()->Dolly(1.0);
  renderer->ResetCameraClippingRange();

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
