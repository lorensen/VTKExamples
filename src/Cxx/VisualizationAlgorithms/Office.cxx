#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkNamedColors.h>
#include <vtkPointData.h>
#include <vtkPointSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkStreamTracer.h>
#include <vtkStructuredGrid.h>
#include <vtkStructuredGridGeometryFilter.h>
#include <vtkStructuredGridOutlineFilter.h>
#include <vtkStructuredGridReader.h>

#include <array>
#include <vector>

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " filename [center]" << std::endl;
    std::cout
      << "Demonstrate the use of vtkPointSource to generate streamlines."
      << std::endl;
    std::cout << "Where: " << std::endl;
    std::cout << "       filename: office.binary.vtk" << std::endl;
    std::cout << "       center: An optional parameter choosing the center for "
                 "the seeds."
              << std::endl;
    std::cout
      << "               0 - Corresponds to Fig 9-47(a) in the VTK textbook."
      << std::endl;
    std::cout << "               1 - A slight shift to the left." << std::endl;
    std::cout << "               2 - A slight shift to the upper left. (from "
                 "the Original code)."
              << std::endl;
    std::cout
      << "               3 - The default, a slight shift to the upper left."
      << std::endl;
    std::cout << "                   Roughly corresponds to Fig 9-47(b) in the "
                 "VTK textbook."
              << std::endl;
    return EXIT_FAILURE;
  }

  auto center = 3;
  if (argc > 2)
  {
    center = std::abs(atoi(argv[2]));
  }
  // These are the centers for the streamline seed.
  std::vector<std::array<double, 3>> seedCenters{
    {0.0, 2.1, 0.5}, {0.1, 2.1, 0.5}, {0.1, 2.7, 0.5}, {0.08, 2.7, 0.5}};
  center = (center < static_cast<int>(seedCenters.size()))
             ? center
             : static_cast<int>(seedCenters.size()) - 1;

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
  std::array<double, 3> tableTopColor = {0.59, 0.427, 0.392};
  std::array<double, 3> filingCabinetColor = {0.8, 0.8, 0.6};
  std::array<double, 3> bookShelfColor = {0.8, 0.8, 0.6};
  std::array<double, 3> windowColor = {0.3, 0.3, 0.5};
  colors->SetColor("TableTop", tableTopColor.data());
  colors->SetColor("FilingCabinet", filingCabinetColor.data());
  colors->SetColor("BookShelf", bookShelfColor.data());
  colors->SetColor("Window", windowColor.data());

  // We read a data file that represents a CFD analysis of airflow in an office
  // (with ventilation and a burning cigarette).
  vtkSmartPointer<vtkStructuredGridReader> reader =
    vtkSmartPointer<vtkStructuredGridReader>::New();
  reader->SetFileName(argv[1]);

  // Create the scene.
  // We generate a whole bunch of planes which correspond to
  // the geometry in the analysis; tables, bookshelves and so on.
  vtkSmartPointer<vtkStructuredGridGeometryFilter> table1 =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  table1->SetInputConnection(reader->GetOutputPort());
  table1->SetExtent(11, 15, 7, 9, 8, 8);
  vtkSmartPointer<vtkPolyDataMapper> mapTable1 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapTable1->SetInputConnection(table1->GetOutputPort());
  mapTable1->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> table1Actor = vtkSmartPointer<vtkActor>::New();
  table1Actor->SetMapper(mapTable1);
  table1Actor->GetProperty()->SetColor(
    colors->GetColor3d("TableTop").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> table2 =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  table2->SetInputConnection(reader->GetOutputPort());
  table2->SetExtent(11, 15, 10, 12, 8, 8);
  vtkSmartPointer<vtkPolyDataMapper> mapTable2 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapTable2->SetInputConnection(table2->GetOutputPort());
  mapTable2->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> table2Actor = vtkSmartPointer<vtkActor>::New();
  table2Actor->SetMapper(mapTable2);
  table2Actor->GetProperty()->SetColor(
    colors->GetColor3d("TableTop").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> FilingCabinet1 =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  FilingCabinet1->SetInputConnection(reader->GetOutputPort());
  FilingCabinet1->SetExtent(15, 15, 7, 9, 0, 8);
  vtkSmartPointer<vtkPolyDataMapper> mapFilingCabinet1 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapFilingCabinet1->SetInputConnection(FilingCabinet1->GetOutputPort());
  mapFilingCabinet1->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> FilingCabinet1Actor =
    vtkSmartPointer<vtkActor>::New();
  FilingCabinet1Actor->SetMapper(mapFilingCabinet1);
  FilingCabinet1Actor->GetProperty()->SetColor(
    colors->GetColor3d("FilingCabinet").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> FilingCabinet2 =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  FilingCabinet2->SetInputConnection(reader->GetOutputPort());
  FilingCabinet2->SetExtent(15, 15, 10, 12, 0, 8);
  vtkSmartPointer<vtkPolyDataMapper> mapFilingCabinet2 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapFilingCabinet2->SetInputConnection(FilingCabinet2->GetOutputPort());
  mapFilingCabinet2->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> FilingCabinet2Actor =
    vtkSmartPointer<vtkActor>::New();
  FilingCabinet2Actor->SetMapper(mapFilingCabinet2);
  FilingCabinet2Actor->GetProperty()->SetColor(
    colors->GetColor3d("FilingCabinet").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> bookshelf1Top =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  bookshelf1Top->SetInputConnection(reader->GetOutputPort());
  bookshelf1Top->SetExtent(13, 13, 0, 4, 0, 11);
  vtkSmartPointer<vtkPolyDataMapper> mapBookshelf1Top =
    vtkSmartPointer<vtkPolyDataMapper>::New();

  mapBookshelf1Top->SetInputConnection(bookshelf1Top->GetOutputPort());
  mapBookshelf1Top->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> bookshelf1TopActor =
    vtkSmartPointer<vtkActor>::New();
  bookshelf1TopActor->SetMapper(mapBookshelf1Top);
  bookshelf1TopActor->GetProperty()->SetColor(
    colors->GetColor3d("BookShelf").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> bookshelf1Bottom =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  bookshelf1Bottom->SetInputConnection(reader->GetOutputPort());
  bookshelf1Bottom->SetExtent(20, 20, 0, 4, 0, 11);
  vtkSmartPointer<vtkPolyDataMapper> mapBookshelf1Bottom =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapBookshelf1Bottom->SetInputConnection(bookshelf1Bottom->GetOutputPort());
  mapBookshelf1Bottom->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> bookshelf1BottomActor =
    vtkSmartPointer<vtkActor>::New();
  bookshelf1BottomActor->SetMapper(mapBookshelf1Bottom);
  bookshelf1BottomActor->GetProperty()->SetColor(
    colors->GetColor3d("BookShelf").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> bookshelf1Front =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  bookshelf1Front->SetInputConnection(reader->GetOutputPort());
  bookshelf1Front->SetExtent(13, 20, 0, 0, 0, 11);
  vtkSmartPointer<vtkPolyDataMapper> mapBookshelf1Front =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapBookshelf1Front->SetInputConnection(bookshelf1Front->GetOutputPort());
  mapBookshelf1Front->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> bookshelf1FrontActor =
    vtkSmartPointer<vtkActor>::New();
  bookshelf1FrontActor->SetMapper(mapBookshelf1Front);
  bookshelf1FrontActor->GetProperty()->SetColor(
    colors->GetColor3d("BookShelf").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> bookshelf1Back =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  bookshelf1Back->SetInputConnection(reader->GetOutputPort());
  bookshelf1Back->SetExtent(13, 20, 4, 4, 0, 11);
  vtkSmartPointer<vtkPolyDataMapper> mapBookshelf1Back =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapBookshelf1Back->SetInputConnection(bookshelf1Back->GetOutputPort());
  mapBookshelf1Back->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> bookshelf1BackActor =
    vtkSmartPointer<vtkActor>::New();
  bookshelf1BackActor->SetMapper(mapBookshelf1Back);
  bookshelf1BackActor->GetProperty()->SetColor(
    colors->GetColor3d("BookShelf").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> bookshelf1LHS =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  bookshelf1LHS->SetInputConnection(reader->GetOutputPort());
  bookshelf1LHS->SetExtent(13, 20, 0, 4, 0, 0);
  vtkSmartPointer<vtkPolyDataMapper> mapBookshelf1LHS =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapBookshelf1LHS->SetInputConnection(bookshelf1LHS->GetOutputPort());
  mapBookshelf1LHS->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> bookshelf1LHSActor =
    vtkSmartPointer<vtkActor>::New();
  bookshelf1LHSActor->SetMapper(mapBookshelf1LHS);
  bookshelf1LHSActor->GetProperty()->SetColor(
    colors->GetColor3d("BookShelf").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> bookshelf1RHS =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  bookshelf1RHS->SetInputConnection(reader->GetOutputPort());
  bookshelf1RHS->SetExtent(13, 20, 0, 4, 11, 11);
  vtkSmartPointer<vtkPolyDataMapper> mapBookshelf1RHS =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapBookshelf1RHS->SetInputConnection(bookshelf1RHS->GetOutputPort());
  mapBookshelf1RHS->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> bookshelf1RHSActor =
    vtkSmartPointer<vtkActor>::New();
  bookshelf1RHSActor->SetMapper(mapBookshelf1RHS);
  bookshelf1RHSActor->GetProperty()->SetColor(
    colors->GetColor3d("BookShelf").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> bookshelf2Top =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  bookshelf2Top->SetInputConnection(reader->GetOutputPort());
  bookshelf2Top->SetExtent(13, 13, 15, 19, 0, 11);
  vtkSmartPointer<vtkPolyDataMapper> mapBookshelf2Top =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapBookshelf2Top->SetInputConnection(bookshelf2Top->GetOutputPort());
  mapBookshelf2Top->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> bookshelf2TopActor =
    vtkSmartPointer<vtkActor>::New();
  bookshelf2TopActor->SetMapper(mapBookshelf2Top);
  bookshelf2TopActor->GetProperty()->SetColor(
    colors->GetColor3d("BookShelf").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> bookshelf2Bottom =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  bookshelf2Bottom->SetInputConnection(reader->GetOutputPort());
  bookshelf2Bottom->SetExtent(20, 20, 15, 19, 0, 11);
  vtkSmartPointer<vtkPolyDataMapper> mapBookshelf2Bottom =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapBookshelf2Bottom->SetInputConnection(bookshelf2Bottom->GetOutputPort());
  mapBookshelf2Bottom->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> bookshelf2BottomActor =
    vtkSmartPointer<vtkActor>::New();
  bookshelf2BottomActor->SetMapper(mapBookshelf2Bottom);
  bookshelf2BottomActor->GetProperty()->SetColor(
    colors->GetColor3d("BookShelf").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> bookshelf2Front =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  bookshelf2Front->SetInputConnection(reader->GetOutputPort());
  bookshelf2Front->SetExtent(13, 20, 15, 15, 0, 11);
  vtkSmartPointer<vtkPolyDataMapper> mapBookshelf2Front =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapBookshelf2Front->SetInputConnection(bookshelf2Front->GetOutputPort());
  mapBookshelf2Front->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> bookshelf2FrontActor =
    vtkSmartPointer<vtkActor>::New();

  bookshelf2FrontActor->SetMapper(mapBookshelf2Front);
  bookshelf2FrontActor->GetProperty()->SetColor(
    colors->GetColor3d("BookShelf").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> bookshelf2Back =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  bookshelf2Back->SetInputConnection(reader->GetOutputPort());
  bookshelf2Back->SetExtent(13, 20, 19, 19, 0, 11);
  vtkSmartPointer<vtkPolyDataMapper> mapBookshelf2Back =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapBookshelf2Back->SetInputConnection(bookshelf2Back->GetOutputPort());
  mapBookshelf2Back->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> bookshelf2BackActor =
    vtkSmartPointer<vtkActor>::New();
  bookshelf2BackActor->SetMapper(mapBookshelf2Back);
  bookshelf2BackActor->GetProperty()->SetColor(
    colors->GetColor3d("BookShelf").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> bookshelf2LHS =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();

  bookshelf2LHS->SetInputConnection(reader->GetOutputPort());
  bookshelf2LHS->SetExtent(13, 20, 15, 19, 0, 0);
  vtkSmartPointer<vtkPolyDataMapper> mapBookshelf2LHS =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapBookshelf2LHS->SetInputConnection(bookshelf2LHS->GetOutputPort());
  mapBookshelf2LHS->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> bookshelf2LHSActor =
    vtkSmartPointer<vtkActor>::New();
  bookshelf2LHSActor->SetMapper(mapBookshelf2LHS);
  bookshelf2LHSActor->GetProperty()->SetColor(
    colors->GetColor3d("BookShelf").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> bookshelf2RHS =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  bookshelf2RHS->SetInputConnection(reader->GetOutputPort());
  bookshelf2RHS->SetExtent(13, 20, 15, 19, 11, 11);
  vtkSmartPointer<vtkPolyDataMapper> mapBookshelf2RHS =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapBookshelf2RHS->SetInputConnection(bookshelf2RHS->GetOutputPort());
  mapBookshelf2RHS->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> bookshelf2RHSActor =
    vtkSmartPointer<vtkActor>::New();
  bookshelf2RHSActor->SetMapper(mapBookshelf2RHS);
  bookshelf2RHSActor->GetProperty()->SetColor(
    colors->GetColor3d("BookShelf").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> window =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  window->SetInputConnection(reader->GetOutputPort());
  window->SetExtent(20, 20, 6, 13, 10, 13);
  vtkSmartPointer<vtkPolyDataMapper> mapWindow =
    vtkSmartPointer<vtkPolyDataMapper>::New();

  mapWindow->SetInputConnection(window->GetOutputPort());
  mapWindow->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> windowActor = vtkSmartPointer<vtkActor>::New();
  windowActor->SetMapper(mapWindow);
  windowActor->GetProperty()->SetColor(colors->GetColor3d("Window").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> outlet =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  outlet->SetInputConnection(reader->GetOutputPort());
  outlet->SetExtent(0, 0, 9, 10, 14, 16);
  vtkSmartPointer<vtkPolyDataMapper> mapOutlet =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapOutlet->SetInputConnection(outlet->GetOutputPort());
  mapOutlet->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> outletActor = vtkSmartPointer<vtkActor>::New();
  outletActor->SetMapper(mapOutlet);
  outletActor->GetProperty()->SetColor(
    colors->GetColor3d("lamp_black").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> inlet =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  inlet->SetInputConnection(reader->GetOutputPort());
  inlet->SetExtent(0, 0, 9, 10, 0, 6);
  vtkSmartPointer<vtkPolyDataMapper> mapInlet =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapInlet->SetInputConnection(inlet->GetOutputPort());
  mapInlet->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> inletActor = vtkSmartPointer<vtkActor>::New();
  inletActor->SetMapper(mapInlet);
  inletActor->GetProperty()->SetColor(
    colors->GetColor3d("lamp_black").GetData());

  vtkSmartPointer<vtkStructuredGridOutlineFilter> outline =
    vtkSmartPointer<vtkStructuredGridOutlineFilter>::New();
  outline->SetInputConnection(reader->GetOutputPort());
  vtkSmartPointer<vtkPolyDataMapper> mapOutline =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapOutline->SetInputConnection(outline->GetOutputPort());
  vtkSmartPointer<vtkActor> outlineActor = vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(mapOutline);
  outlineActor->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());

  // Create the source for the streamtubes.
  vtkSmartPointer<vtkPointSource> seeds =
    vtkSmartPointer<vtkPointSource>::New();
  seeds->SetRadius(0.075);
  seeds->SetCenter(seedCenters[center].data());
  seeds->SetNumberOfPoints(25);
  vtkSmartPointer<vtkStreamTracer> streamers =
    vtkSmartPointer<vtkStreamTracer>::New();
  streamers->SetInputConnection(reader->GetOutputPort());
  streamers->SetSourceConnection(seeds->GetOutputPort());
  streamers->SetMaximumPropagation(500);
  streamers->SetMinimumIntegrationStep(0.1);
  streamers->SetMaximumIntegrationStep(1.0);
  streamers->SetInitialIntegrationStep(0.2);
  streamers->Update();
  vtkSmartPointer<vtkPolyDataMapper> mapStreamers =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapStreamers->SetInputConnection(streamers->GetOutputPort());
  mapStreamers->SetScalarRange(
    reader->GetOutput()->GetPointData()->GetScalars()->GetRange());
  vtkSmartPointer<vtkActor> streamersActor = vtkSmartPointer<vtkActor>::New();
  streamersActor->SetMapper(mapStreamers);

  // Now create the usual graphics stuff.
  vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  ren->AddActor(table1Actor);
  ren->AddActor(table2Actor);
  ren->AddActor(FilingCabinet1Actor);
  ren->AddActor(FilingCabinet2Actor);
  ren->AddActor(bookshelf1TopActor);
  ren->AddActor(bookshelf1BottomActor);
  ren->AddActor(bookshelf1FrontActor);
  ren->AddActor(bookshelf1BackActor);
  ren->AddActor(bookshelf1LHSActor);
  ren->AddActor(bookshelf1RHSActor);
  ren->AddActor(bookshelf2TopActor);
  ren->AddActor(bookshelf2BottomActor);
  ren->AddActor(bookshelf2FrontActor);
  ren->AddActor(bookshelf2BackActor);
  ren->AddActor(bookshelf2LHSActor);
  ren->AddActor(bookshelf2RHSActor);
  ren->AddActor(windowActor);
  ren->AddActor(outletActor);
  ren->AddActor(inletActor);
  ren->AddActor(outlineActor);
  ren->AddActor(streamersActor);

  ren->SetBackground(colors->GetColor3d("SlateGray").GetData());

  // Here we specify a particular view.
  vtkSmartPointer<vtkCamera> aCamera = vtkSmartPointer<vtkCamera>::New();
  aCamera->SetClippingRange(0.726079, 36.3039);
  aCamera->SetFocalPoint(2.43584, 2.15046, 1.11104);
  aCamera->SetPosition(-4.76183, -10.4426, 3.17203);
  aCamera->SetViewUp(0.0511273, 0.132773, 0.989827);
  aCamera->SetViewAngle(18.604);
  aCamera->Zoom(1.2);

  ren->SetActiveCamera(aCamera);

  renWin->SetSize(640, 400);
  iren->Start();

  return EXIT_SUCCESS;
}
