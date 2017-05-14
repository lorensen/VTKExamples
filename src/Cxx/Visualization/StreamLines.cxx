#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#if VTK_MAJOR_VERSION <= 5
#include <vtkPLOT3DReader.h>
#else
#include <vtkMultiBlockPLOT3DReader.h>
#include <vtkMultiBlockDataSet.h>
#endif
#include <vtkPlaneSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkStreamLine.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkStructuredGridOutlineFilter.h>
#include <vtkProperty.h>

int main(int argc, char *argv[])
{
  if(argc < 3)
  {
    std::cerr << "Required arguments: xyzFile qFile" << std::endl;
    return EXIT_FAILURE;
  }

  std::string xyzFile = argv[1]; // "combxyz.bin";
  std::string qFile = argv[2]; // "combq.bin";

#if VTK_MAJOR_VERSION <= 5
  vtkSmartPointer<vtkPLOT3DReader> pl3d =
    vtkSmartPointer<vtkPLOT3DReader>::New();
#else
  vtkSmartPointer<vtkMultiBlockPLOT3DReader> pl3d =
    vtkSmartPointer<vtkMultiBlockPLOT3DReader>::New();
#endif
  pl3d->SetXYZFileName(xyzFile.c_str());
  pl3d->SetQFileName(qFile.c_str());
  pl3d->SetScalarFunctionNumber(100);
  pl3d->SetVectorFunctionNumber(202);
  pl3d->Update();

  // Source of the streamlines
  vtkSmartPointer<vtkPlaneSource> seeds = 
    vtkSmartPointer<vtkPlaneSource>::New();
  seeds->SetXResolution(4);
  seeds->SetYResolution(4);
  seeds->SetOrigin(2,-2,26);
  seeds->SetPoint1(2,2,26);
  seeds->SetPoint2(2,-2,32);
  
  // Streamline itself
  vtkSmartPointer<vtkStreamLine> streamLine = 
    vtkSmartPointer<vtkStreamLine>::New();
#if VTK_MAJOR_VERSION <= 5
  streamLine->SetInputConnection(pl3d->GetOutputPort());
  streamLine->SetSource(seeds->GetOutput());
#else
  pl3d->Update();
  streamLine->SetInputData(pl3d->GetOutput()->GetBlock(0));
  streamLine->SetSourceConnection(seeds->GetOutputPort());
#endif
  //streamLine->SetStartPosition(2,-2,30);
  // as alternative to the SetSource(), which can handle multiple
  // streamlines, you can set a SINGLE streamline from
  // SetStartPosition()
  streamLine->SetMaximumPropagationTime(200);
  streamLine->SetIntegrationStepLength(.2);
  streamLine->SetStepLength(.001);
  streamLine->SetNumberOfThreads(1);
  streamLine->SetIntegrationDirectionToForward();
  streamLine->VorticityOn();

  vtkSmartPointer<vtkPolyDataMapper> streamLineMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  streamLineMapper->SetInputConnection(streamLine->GetOutputPort());

  vtkSmartPointer<vtkActor> streamLineActor = 
    vtkSmartPointer<vtkActor>::New();
  streamLineActor->SetMapper(streamLineMapper);
  streamLineActor->VisibilityOn();

  // Outline-Filter for the grid
  vtkSmartPointer<vtkStructuredGridOutlineFilter> outline = 
    vtkSmartPointer<vtkStructuredGridOutlineFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  outline->SetInputConnection(pl3d->GetOutputPort());
#else
  outline->SetInputData(pl3d->GetOutput()->GetBlock(0));
#endif
  vtkSmartPointer<vtkPolyDataMapper> outlineMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkSmartPointer<vtkActor> outlineActor = 
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);
  outlineActor->GetProperty()->SetColor(1, 1, 1);

  // Create the RenderWindow, Renderer and Actors
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = 
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  interactor->SetInteractorStyle(style);

  renderer->AddActor(streamLineActor);
  renderer->AddActor(outlineActor);

  // Add the actors to the renderer, set the background and size
  renderer->SetBackground(0.1, 0.2, 0.4);
  renderWindow->SetSize(300, 300);
  interactor->Initialize();
  renderWindow->Render();

  interactor->Start();

  return EXIT_SUCCESS;
}
