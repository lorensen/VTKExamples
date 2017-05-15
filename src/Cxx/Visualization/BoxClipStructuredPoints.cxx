#include <vtkSmartPointer.h>
#include <vtkBoxClipDataSet.h>
#include <vtkLookupTable.h>

#include <vtkMetaImageReader.h>
#include <vtkImageData.h>

#include <vtkDataSetSurfaceFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkCamera.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " file.mhd" << endl;
    return EXIT_FAILURE;
  }

  // Read the data
  vtkSmartPointer<vtkMetaImageReader> reader =
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
  vtkSmartPointer<vtkLookupTable> lut1 =
    vtkSmartPointer<vtkLookupTable>::New();
  lut1->SetHueRange (0.667, 0);

  vtkSmartPointer<vtkDataSetSurfaceFilter> surfaceIn =
    vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
  surfaceIn->SetInputConnection (boxClip->GetOutputPort(0));

  vtkSmartPointer<vtkDataSetMapper> mapperIn =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapperIn->SetInputConnection(surfaceIn->GetOutputPort());
  mapperIn->SetScalarRange(reader->GetOutput()->GetScalarRange());
  mapperIn->SetLookupTable(lut1);
  mapperIn->SetColorModeToMapScalars();

  vtkSmartPointer<vtkActor> actorIn = 
    vtkSmartPointer<vtkActor>::New();
  actorIn->SetMapper(mapperIn);
 
  vtkSmartPointer<vtkDataSetSurfaceFilter> surfaceOut =
    vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
  surfaceOut->SetInputConnection (boxClip->GetOutputPort(1));

  vtkSmartPointer<vtkDataSetMapper> mapperOut =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapperOut->SetInputConnection(surfaceOut->GetOutputPort());
  mapperOut->SetScalarRange(reader->GetOutput()->GetScalarRange());
  mapperOut->SetLookupTable(lut1);
  mapperOut->SetColorModeToMapScalars();

  // Move the outside actor
  vtkSmartPointer<vtkActor> actorOut = 
    vtkSmartPointer<vtkActor>::New();
  actorOut->SetMapper(mapperOut);
  actorOut->AddPosition(-.5 * (maxBoxPoint[0] - minBoxPoint[0]),
                        -.5 * (maxBoxPoint[1] - minBoxPoint[1]),
                        -.5 * (maxBoxPoint[2] - minBoxPoint[2]));
 
  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(.5, .5, .5);

  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  // Add the actor to the scene
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
