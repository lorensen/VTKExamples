#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkHedgeHog.h>
#include <vtkLookupTable.h>
#include <vtkNamedColors.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkStructuredPointsReader.h>

int main (int argc , char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " carotid.vtk" << std::endl;
    return EXIT_SUCCESS;
  }

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkStructuredPointsReader> reader =
    vtkSmartPointer<vtkStructuredPointsReader>::New();
  reader->SetFileName(argv[1]);

  vtkSmartPointer<vtkHedgeHog> hhog =
    vtkSmartPointer<vtkHedgeHog>::New();
  hhog->SetInputConnection(reader->GetOutputPort());
  hhog->SetScaleFactor(0.3);

  vtkSmartPointer<vtkLookupTable> lut =
    vtkSmartPointer<vtkLookupTable>::New();
//  lut->SetHueRange(.667, 0.0);
  lut->Build();

  vtkSmartPointer<vtkPolyDataMapper> hhogMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  hhogMapper->SetInputConnection(hhog->GetOutputPort());
  hhogMapper->SetScalarRange(50, 550);
  hhogMapper->SetLookupTable(lut);

  vtkSmartPointer<vtkActor> hhogActor =
    vtkSmartPointer<vtkActor>::New();
  hhogActor->SetMapper(hhogMapper);

  vtkSmartPointer<vtkOutlineFilter> outline =
    vtkSmartPointer<vtkOutlineFilter>::New();
  outline->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkSmartPointer<vtkActor> outlineActor =
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);
  outlineActor->GetProperty()->SetColor(0, 0, 0);

  vtkSmartPointer<vtkRenderer> aRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> aRenderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  aRenderWindow->AddRenderer(aRenderer);
  vtkSmartPointer<vtkRenderWindowInteractor> anInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  anInteractor->SetRenderWindow(aRenderWindow);
  aRenderWindow->SetSize(640, 480);

  aRenderer->AddActor(outlineActor);
  aRenderer->AddActor(hhogActor);

  aRenderer->SetBackground(colors->GetColor3d("Gray").GetData());

  // Generate an interesting view

  aRenderer->GetActiveCamera()->SetFocalPoint(0,0,0);
  aRenderer->GetActiveCamera()->SetPosition(1,0,0);
  aRenderer->GetActiveCamera()->SetViewUp(0,0,1);
  aRenderer->ResetCamera();

  aRenderer->GetActiveCamera()->Azimuth(60);
  aRenderer->GetActiveCamera()->Elevation(30);
  aRenderer->GetActiveCamera()->Dolly(1.1);
  aRenderer->ResetCameraClippingRange();

  aRenderWindow->Render();

  // interact with data
  anInteractor->Start();

  return EXIT_SUCCESS;
}
