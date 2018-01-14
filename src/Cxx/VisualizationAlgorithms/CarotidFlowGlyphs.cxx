#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkConeSource.h>
#include <vtkContourFilter.h>
#include <vtkGlyph3D.h>
#include <vtkLookupTable.h>
#include <vtkMaskPoints.h>
#include <vtkNamedColors.h>
#include <vtkOutlineFilter.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkStructuredPoints.h>
#include <vtkStructuredPointsReader.h>
#include <vtkThresholdPoints.h>

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " carotid.vtk" << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

// create pipeline
//
  vtkSmartPointer<vtkStructuredPointsReader> reader =
    vtkSmartPointer<vtkStructuredPointsReader>::New();
  reader->SetFileName(argv[1]);

  vtkSmartPointer<vtkThresholdPoints> threshold =
    vtkSmartPointer<vtkThresholdPoints>::New();
  threshold->SetInputConnection(reader->GetOutputPort());
  threshold->ThresholdByUpper(200);

  vtkSmartPointer<vtkMaskPoints> mask =
    vtkSmartPointer<vtkMaskPoints>::New();
  mask->SetInputConnection(threshold->GetOutputPort());
  mask->SetOnRatio(5);

  vtkSmartPointer<vtkConeSource> cone =
    vtkSmartPointer<vtkConeSource>::New();
  cone->SetResolution(11);
  cone->SetHeight(1);
  cone->SetRadius(0.25);

  vtkSmartPointer<vtkGlyph3D> cones =
    vtkSmartPointer<vtkGlyph3D>::New();
  cones->SetInputConnection(mask->GetOutputPort());
  cones->SetSourceConnection(cone->GetOutputPort());
  cones->SetScaleFactor(0.4);
  cones->SetScaleModeToScaleByVector();

  vtkSmartPointer<vtkLookupTable> lut =
    vtkSmartPointer<vtkLookupTable>::New();
  lut->SetHueRange(.667, 0.0);
  lut->Build();

  double range[2];
  cones->Update();
  range[0] = cones->GetOutput()->GetPointData()->GetScalars()->GetRange()[0];
  range[1] = cones->GetOutput()->GetPointData()->GetScalars()->GetRange()[1];
  std::cout << "range: " << range[0] << ", " << range[1] << std::endl;

  vtkSmartPointer<vtkPolyDataMapper> vectorMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  vectorMapper->SetInputConnection(cones->GetOutputPort());
  vectorMapper->SetScalarRange(range[0], range[1]);
  vectorMapper->SetLookupTable(lut);

  vtkSmartPointer<vtkActor> vectorActor =
    vtkSmartPointer<vtkActor>::New();
  vectorActor->SetMapper(vectorMapper);

// contours of speed
  vtkSmartPointer<vtkContourFilter> iso =
    vtkSmartPointer<vtkContourFilter>::New();
  iso->SetInputConnection(reader->GetOutputPort());
  iso->SetValue(0, 175);

  vtkSmartPointer<vtkPolyDataMapper> isoMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  isoMapper->SetInputConnection(iso->GetOutputPort());
  isoMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> isoActor =
    vtkSmartPointer<vtkActor>::New();
  isoActor->SetMapper(isoMapper);
  isoActor->GetProperty()->SetRepresentationToWireframe();
  isoActor->GetProperty()->SetOpacity(0.25);

// outline
  vtkSmartPointer<vtkOutlineFilter> outline =
    vtkSmartPointer<vtkOutlineFilter>::New();
  outline->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkSmartPointer<vtkActor> outlineActor =
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);
  outlineActor->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());

// Add the actors to the renderer, set the background and size
//
  ren1->AddActor(outlineActor);
  ren1->AddActor(vectorActor);
  ren1->AddActor(isoActor);
  ren1->SetBackground(colors->GetColor3d("Wheat").GetData());
  renWin->SetSize(640, 480);

  vtkSmartPointer<vtkCamera> cam1 =
    vtkSmartPointer<vtkCamera>::New();
  cam1->SetClippingRange(17.4043, 870.216);
  cam1->SetFocalPoint(136.71, 104.025, 23);
  cam1->SetPosition(204.747, 258.939, 63.7925);
  cam1->SetViewUp(-0.102647, -0.210897, 0.972104);
  cam1->Zoom(1.6);
  ren1->SetActiveCamera(cam1);

// render the image
//
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
