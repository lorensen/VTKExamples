#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkNamedColors.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRungeKutta4.h>
#include <vtkStreamTracer.h>
#include <vtkStructuredGrid.h>
#include <vtkStructuredGridGeometryFilter.h>
#include <vtkStructuredGridOutlineFilter.h>
#include <vtkStructuredGridReader.h>
#include <vtkTubeFilter.h>

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " office.binary.vtk" << std::endl;
    return EXIT_FAILURE;
  }

  auto colors =
    vtkSmartPointer<vtkNamedColors>::New();

// We read a data file the is a CFD analysis of airflow in an office (with
// ventilation and a burning cigarette). We force an update so that we
// can query the output for its length, i.e., the length of the diagonal
// of the bounding box. This is useful for normalizing the data.
//
  auto reader =
    vtkSmartPointer<vtkStructuredGridReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update(); //force a read to occur

// Now we will generate a single streamline in the data. We select the
// integration order to use (RungeKutta order 4) and associate it with
// the streamer. The start position is the position in world space where
// we want to begin streamline integration; and we integrate in both
// directions. The step length is the length of the line segments that
// make up the streamline (i.e., related to display). The
// IntegrationStepLength specifies the integration step length as a
// fraction of the cell size that the streamline is in.
  auto integ =
    vtkSmartPointer<vtkRungeKutta4>::New();

  auto streamer =
    vtkSmartPointer<vtkStreamTracer>::New();
  streamer->SetInputConnection(reader->GetOutputPort());
  streamer->SetStartPosition(0.1, 2.1, 0.5);
  streamer->SetMaximumPropagation(500);
  streamer->SetInitialIntegrationStep(0.05);
  streamer->SetIntegrationDirectionToBoth();
  streamer->SetIntegrator(integ);

// The tube is wrapped around the generated streamline. By varying the radius
// by the inverse of vector magnitude, we are creating a tube whose radius is
// proportional to mass flux (in incompressible flow).
  auto streamTube =
    vtkSmartPointer<vtkTubeFilter>::New();
  streamTube->SetInputConnection(streamer->GetOutputPort());
  streamTube->SetInputArrayToProcess(1, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, "vectors");
  streamTube->SetRadius(0.02);
  streamTube->SetNumberOfSides(12);
  streamTube->SetVaryRadiusToVaryRadiusByVector();

  auto mapStreamTube =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapStreamTube->SetInputConnection(streamTube->GetOutputPort());
  mapStreamTube->SetScalarRange(reader->GetOutput()->GetPointData()->GetScalars()->GetRange());

  auto streamTubeActor =
    vtkSmartPointer<vtkActor>::New();
  streamTubeActor->SetMapper(mapStreamTube);
  streamTubeActor->GetProperty()->BackfaceCullingOn();

// From here on we generate a whole bunch of planes which correspond to
// the geometry in the analysis; tables, bookshelves and so on.
  auto table1 =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  table1->SetInputConnection(reader->GetOutputPort());
  table1->SetExtent(11, 15, 7, 9, 8, 8);
  auto mapTable1 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapTable1->SetInputConnection(table1->GetOutputPort());
  mapTable1->ScalarVisibilityOff();
  
  auto table1Actor =
    vtkSmartPointer<vtkActor>::New();
  table1Actor->SetMapper(mapTable1);
  table1Actor->GetProperty()->SetColor(.59, .427, .392);

  auto table2 =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  table2->SetInputConnection(reader->GetOutputPort());
  table2->SetExtent(11, 15, 10, 12, 8, 8);
  auto mapTable2 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapTable2->SetInputConnection(table2->GetOutputPort());
  mapTable2->ScalarVisibilityOff();
  auto table2Actor =
    vtkSmartPointer<vtkActor>::New();
  table2Actor->SetMapper(mapTable2);
  table2Actor->GetProperty()->SetColor(.59, .427, .392);

  auto FilingCabinet1 =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  FilingCabinet1->SetInputConnection(reader->GetOutputPort());
  FilingCabinet1->SetExtent(15, 15, 7, 9, 0, 8);
  auto mapFilingCabinet1 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapFilingCabinet1->SetInputConnection(FilingCabinet1->GetOutputPort());
  mapFilingCabinet1->ScalarVisibilityOff();
  auto FilingCabinet1Actor =
    vtkSmartPointer<vtkActor>::New();
  FilingCabinet1Actor->SetMapper(mapFilingCabinet1);
  FilingCabinet1Actor->GetProperty()->SetColor(.8, .8, .6);

  auto FilingCabinet2 =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  FilingCabinet2->SetInputConnection(reader->GetOutputPort());
  FilingCabinet2->SetExtent(15, 15, 10, 12, 0, 8);
  auto mapFilingCabinet2 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapFilingCabinet2->SetInputConnection(FilingCabinet2->GetOutputPort());
  mapFilingCabinet2->ScalarVisibilityOff();
  auto FilingCabinet2Actor =
    vtkSmartPointer<vtkActor>::New();
  FilingCabinet2Actor->SetMapper(mapFilingCabinet2);
  FilingCabinet2Actor->GetProperty()->SetColor(.8, .8, .6);

  auto bookshelf1Top =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  bookshelf1Top->SetInputConnection(reader->GetOutputPort());
  bookshelf1Top->SetExtent(13, 13, 0, 4, 0, 11);
  auto mapBookshelf1Top =
    vtkSmartPointer<vtkPolyDataMapper>::New();

  mapBookshelf1Top->SetInputConnection(bookshelf1Top->GetOutputPort());
  mapBookshelf1Top->ScalarVisibilityOff();
  auto bookshelf1TopActor =
    vtkSmartPointer<vtkActor>::New();
  bookshelf1TopActor->SetMapper(mapBookshelf1Top);
  bookshelf1TopActor->GetProperty()->SetColor(.8, .8, .6);

  auto bookshelf1Bottom =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  bookshelf1Bottom->SetInputConnection(reader->GetOutputPort());
  bookshelf1Bottom->SetExtent(20, 20, 0, 4, 0, 11);
  auto mapBookshelf1Bottom =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapBookshelf1Bottom->SetInputConnection(bookshelf1Bottom->GetOutputPort());
  mapBookshelf1Bottom->ScalarVisibilityOff();
  auto bookshelf1BottomActor =
    vtkSmartPointer<vtkActor>::New();
  bookshelf1BottomActor->SetMapper(mapBookshelf1Bottom);
  bookshelf1BottomActor->GetProperty()->SetColor(.8, .8, .6);

  auto bookshelf1Front =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  bookshelf1Front->SetInputConnection(reader->GetOutputPort());
  bookshelf1Front->SetExtent(13, 20, 0, 0, 0, 11);
  auto mapBookshelf1Front =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapBookshelf1Front->SetInputConnection(bookshelf1Front->GetOutputPort());
  mapBookshelf1Front->ScalarVisibilityOff();
  auto bookshelf1FrontActor =
    vtkSmartPointer<vtkActor>::New();
  bookshelf1FrontActor->SetMapper(mapBookshelf1Front);
  bookshelf1FrontActor->GetProperty()->SetColor(.8, .8, .6);

  auto bookshelf1Back =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  bookshelf1Back->SetInputConnection(reader->GetOutputPort());
  bookshelf1Back->SetExtent(13, 20, 4, 4, 0, 11);
  auto mapBookshelf1Back =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapBookshelf1Back->SetInputConnection(bookshelf1Back->GetOutputPort());
  mapBookshelf1Back->ScalarVisibilityOff();
  auto bookshelf1BackActor =
    vtkSmartPointer<vtkActor>::New();
  bookshelf1BackActor->SetMapper(mapBookshelf1Back);
  bookshelf1BackActor->GetProperty()->SetColor(.8, .8, .6);

  auto bookshelf1LHS =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  bookshelf1LHS->SetInputConnection(reader->GetOutputPort());
  bookshelf1LHS->SetExtent(13, 20, 0, 4, 0, 0);
  auto mapBookshelf1LHS =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapBookshelf1LHS->SetInputConnection(bookshelf1LHS->GetOutputPort());
  mapBookshelf1LHS->ScalarVisibilityOff();
  auto bookshelf1LHSActor =
    vtkSmartPointer<vtkActor>::New();
  bookshelf1LHSActor->SetMapper(mapBookshelf1LHS);
  bookshelf1LHSActor->GetProperty()->SetColor(.8, .8, .6);

  auto bookshelf1RHS =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  bookshelf1RHS->SetInputConnection(reader->GetOutputPort());
  bookshelf1RHS->SetExtent(13, 20, 0, 4, 11, 11);
  auto mapBookshelf1RHS =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapBookshelf1RHS->SetInputConnection(bookshelf1RHS->GetOutputPort());
  mapBookshelf1RHS->ScalarVisibilityOff();
  auto bookshelf1RHSActor =
    vtkSmartPointer<vtkActor>::New();
  bookshelf1RHSActor->SetMapper(mapBookshelf1RHS);
  bookshelf1RHSActor->GetProperty()->SetColor(.8, .8, .6);

  auto bookshelf2Top =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  bookshelf2Top->SetInputConnection(reader->GetOutputPort());
  bookshelf2Top->SetExtent(13, 13, 15, 19, 0, 11);
  auto mapBookshelf2Top =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapBookshelf2Top->SetInputConnection(bookshelf2Top->GetOutputPort());
  mapBookshelf2Top->ScalarVisibilityOff();
  auto bookshelf2TopActor =
    vtkSmartPointer<vtkActor>::New();
  bookshelf2TopActor->SetMapper(mapBookshelf2Top);
  bookshelf2TopActor->GetProperty()->SetColor(.8, .8, .6);

  auto bookshelf2Bottom =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  bookshelf2Bottom->SetInputConnection(reader->GetOutputPort());
  bookshelf2Bottom->SetExtent(20, 20, 15, 19, 0, 11);
  auto mapBookshelf2Bottom =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapBookshelf2Bottom->SetInputConnection(bookshelf2Bottom->GetOutputPort());
  mapBookshelf2Bottom->ScalarVisibilityOff();
  auto bookshelf2BottomActor =
    vtkSmartPointer<vtkActor>::New();
  bookshelf2BottomActor->SetMapper(mapBookshelf2Bottom);
  bookshelf2BottomActor->GetProperty()->SetColor(.8, .8, .6);

  auto bookshelf2Front =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  bookshelf2Front->SetInputConnection(reader->GetOutputPort());
  bookshelf2Front->SetExtent(13, 20, 15, 15, 0, 11);
  auto mapBookshelf2Front =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapBookshelf2Front->SetInputConnection(bookshelf2Front->GetOutputPort());
  mapBookshelf2Front->ScalarVisibilityOff();
  auto bookshelf2FrontActor =
    vtkSmartPointer<vtkActor>::New();

  bookshelf2FrontActor->SetMapper(mapBookshelf2Front);
  bookshelf2FrontActor->GetProperty()->SetColor(.8, .8, .6);

  auto bookshelf2Back =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  bookshelf2Back->SetInputConnection(reader->GetOutputPort());
  bookshelf2Back->SetExtent(13, 20, 19, 19, 0, 11);
  auto mapBookshelf2Back =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapBookshelf2Back->SetInputConnection(bookshelf2Back->GetOutputPort());
  mapBookshelf2Back->ScalarVisibilityOff();
  auto bookshelf2BackActor =
    vtkSmartPointer<vtkActor>::New();
  bookshelf2BackActor->SetMapper(mapBookshelf2Back);
  bookshelf2BackActor->GetProperty()->SetColor(.8, .8, .6);

  auto bookshelf2LHS =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();

  bookshelf2LHS->SetInputConnection(reader->GetOutputPort());
  bookshelf2LHS->SetExtent(13, 20, 15, 19, 0, 0);
  auto mapBookshelf2LHS =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapBookshelf2LHS->SetInputConnection(bookshelf2LHS->GetOutputPort());
  mapBookshelf2LHS->ScalarVisibilityOff();
  auto bookshelf2LHSActor =
    vtkSmartPointer<vtkActor>::New();
  bookshelf2LHSActor->SetMapper(mapBookshelf2LHS);
  bookshelf2LHSActor->GetProperty()->SetColor(.8, .8, .6);

  auto bookshelf2RHS =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  bookshelf2RHS->SetInputConnection(reader->GetOutputPort());
  bookshelf2RHS->SetExtent(13, 20, 15, 19, 11, 11);
  auto mapBookshelf2RHS =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapBookshelf2RHS->SetInputConnection(bookshelf2RHS->GetOutputPort());
  mapBookshelf2RHS->ScalarVisibilityOff();
  auto bookshelf2RHSActor =
    vtkSmartPointer<vtkActor>::New();
  bookshelf2RHSActor->SetMapper(mapBookshelf2RHS);
  bookshelf2RHSActor->GetProperty()->SetColor(.8, .8, .6);

  auto window =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  window->SetInputConnection(reader->GetOutputPort());
  window->SetExtent(20, 20, 6, 13, 10, 13);
  auto mapWindow =
    vtkSmartPointer<vtkPolyDataMapper>::New();

  mapWindow->SetInputConnection(window->GetOutputPort());
  mapWindow->ScalarVisibilityOff();
  auto windowActor =
    vtkSmartPointer<vtkActor>::New();
  windowActor->SetMapper(mapWindow);
  windowActor->GetProperty()->SetColor(.3, .3, .5);

  auto outlet =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  outlet->SetInputConnection(reader->GetOutputPort());
  outlet->SetExtent(0, 0, 9, 10, 14, 16);
  auto mapOutlet =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapOutlet->SetInputConnection(outlet->GetOutputPort());
  mapOutlet->ScalarVisibilityOff();
  auto outletActor =
    vtkSmartPointer<vtkActor>::New();
  outletActor->SetMapper(mapOutlet);
  outletActor->GetProperty()->SetColor(0 ,0, 0);

  auto inlet =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  inlet->SetInputConnection(reader->GetOutputPort());
  inlet->SetExtent(0, 0, 9, 10, 0, 6);
  auto mapInlet =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapInlet->SetInputConnection(inlet->GetOutputPort());
  mapInlet->ScalarVisibilityOff();
  auto inletActor =
    vtkSmartPointer<vtkActor>::New();
  inletActor->SetMapper(mapInlet);
  inletActor->GetProperty()->SetColor(0 ,0, 0);

  auto outline =
    vtkSmartPointer<vtkStructuredGridOutlineFilter>::New();
  outline->SetInputConnection(reader->GetOutputPort());
  auto mapOutline =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapOutline->SetInputConnection(outline->GetOutputPort());
  auto outlineActor =
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(mapOutline);
  outlineActor->GetProperty()->SetColor(0, 0, 0);

// Now create the usual graphics stuff.
  auto renderer =
    vtkSmartPointer<vtkRenderer>::New();
  auto renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  auto interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderer->AddActor(table1Actor);
  renderer->AddActor(table2Actor);
  renderer->AddActor(FilingCabinet1Actor);
  renderer->AddActor(FilingCabinet2Actor);
  renderer->AddActor(bookshelf1TopActor);
  renderer->AddActor(bookshelf1BottomActor);
  renderer->AddActor(bookshelf1FrontActor);
  renderer->AddActor(bookshelf1BackActor);
  renderer->AddActor(bookshelf1LHSActor);
  renderer->AddActor(bookshelf1RHSActor);
  renderer->AddActor(bookshelf2TopActor);
  renderer->AddActor(bookshelf2BottomActor);
  renderer->AddActor(bookshelf2FrontActor);
  renderer->AddActor(bookshelf2BackActor);
  renderer->AddActor(bookshelf2LHSActor);
  renderer->AddActor(bookshelf2RHSActor);
  renderer->AddActor(windowActor);
  renderer->AddActor(outletActor);
  renderer->AddActor(inletActor);
  renderer->AddActor(outlineActor);
  renderer->AddActor(streamTubeActor);

  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());

// Here we specify a particular view.
  auto aCamera =
    vtkSmartPointer<vtkCamera>::New();
  aCamera->SetClippingRange(0.726079, 36.3039);
  aCamera->SetFocalPoint(2.43584, 2.15046, 1.11104);
  aCamera->SetPosition(-4.76183, -10.4426, 3.17203);
  aCamera->SetViewUp(0.0511273, 0.132773, 0.989827);
  aCamera->SetViewAngle(18.604);
  aCamera->Zoom(1.2);

  renderer->SetActiveCamera(aCamera);

  renderWindow->SetSize(640, 480);
  renderWindow->Render();

  interactor->Start();

  return EXIT_SUCCESS;
}
