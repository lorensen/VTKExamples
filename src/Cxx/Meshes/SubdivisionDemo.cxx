#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkTriangle.h>
#include <vtkTriangleFilter.h>
#include <vtkXMLPolyDataReader.h>

#include <vtkActor.h>
#include <vtkButterflySubdivisionFilter.h>
#include <vtkCamera.h>
#include <vtkColor.h>
#include <vtkLegendBoxActor.h>
#include <vtkLinearSubdivisionFilter.h>
#include <vtkLoopSubdivisionFilter.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkSphereSource.h>
#include <vtkXMLPolyDataReader.h>
#include <vtksys/SystemTools.hxx>

#include <string>

namespace {
vtkSmartPointer<vtkPolyData> ReadPolyData(const char* fileName);
}

int main(int argc, char* argv[])
{
  int numberOfSubdivisions = 2;

  vtkSmartPointer<vtkPolyData> polyData =
      ReadPolyData(argc > 1 ? argv[1] : "");
  vtkSmartPointer<vtkPolyData> originalMesh =
      vtkSmartPointer<vtkPolyData>::New();
  if (argc > 1) // If a file name is specified, open and use the file.
  {
    // Subdivision filters only work on triangles
    vtkSmartPointer<vtkTriangleFilter> triangles =
        vtkSmartPointer<vtkTriangleFilter>::New();
    triangles->SetInputData(polyData);
    triangles->Update();
    originalMesh = triangles->GetOutput();
  }
  else
  {
    originalMesh = polyData;
  }
  if (argc > 2)
  {
    numberOfSubdivisions = std::stod(argv[2]);
  }
  std::cout << "Before subdivision" << std::endl;
  std::cout << "    There are " << originalMesh->GetNumberOfPoints()
            << " points." << std::endl;
  std::cout << "    There are " << originalMesh->GetNumberOfPolys()
            << " triangles." << std::endl;

  vtkSmartPointer<vtkNamedColors> colors =
      vtkSmartPointer<vtkNamedColors>::New();
  vtkColor3d background = colors->GetColor3d("Gray");
  vtkColor3d originalColor = colors->GetColor3d("Tomato");
  vtkColor3d loopColor = colors->GetColor3d("Banana");
  vtkColor3d butterflyColor = colors->GetColor3d("DodgerBlue");

  double numberOfViewports = 3.0;
  vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(400 * numberOfViewports, 512); //(width, height)

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkCamera> camera =
      vtkSmartPointer<vtkCamera>::New();

  vtkSmartPointer<vtkLegendBoxActor> legend =
      vtkSmartPointer<vtkLegendBoxActor>::New();
  legend->SetNumberOfEntries(3);
  vtkSmartPointer<vtkRenderer> legendRen =
      vtkSmartPointer<vtkRenderer>::New();

  for (unsigned i = 0; i < numberOfViewports; i++)
  {
    // Note: Here we create a superclass pointer (vtkPolyDataAlgorithm) so
    // that we can easily instantiate different types of subdivision filters.
    // Typically you would not want to do this, but rather create the pointer
    // to be the type filter you will actually use, e.g.
    // vtkSmartPointer<vtkLinearSubdivisionFilter>  subdivisionFilter =
    // vtkSmartPointer<vtkLinearSubdivisionFilter>::New();
    vtkSmartPointer<vtkPolyDataAlgorithm> subdivisionFilter;
    vtkSmartPointer<vtkRenderer> renderer =
        vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkActor> actor =
        vtkSmartPointer<vtkActor>::New();
    switch (i)
    {
    case 0:
      subdivisionFilter = vtkSmartPointer<vtkLinearSubdivisionFilter>::New();
      dynamic_cast<vtkLinearSubdivisionFilter*>(subdivisionFilter.GetPointer())
          ->SetNumberOfSubdivisions(numberOfSubdivisions);
      actor->GetProperty()->SetDiffuseColor(originalColor.GetData());
      legend->SetEntry(i, subdivisionFilter->GetOutput(), "Linear",
                       originalColor.GetData());
      break;
    case 1:
      subdivisionFilter = vtkSmartPointer<vtkLoopSubdivisionFilter>::New();
      dynamic_cast<vtkLoopSubdivisionFilter*>(subdivisionFilter.GetPointer())
          ->SetNumberOfSubdivisions(numberOfSubdivisions);
      actor->GetProperty()->SetDiffuseColor(loopColor.GetData());
      legend->SetEntry(i, subdivisionFilter->GetOutput(), "Loop",
                       loopColor.GetData());
      break;
    case 2:
      subdivisionFilter = vtkSmartPointer<vtkButterflySubdivisionFilter>::New();
      dynamic_cast<vtkButterflySubdivisionFilter*>(
          subdivisionFilter.GetPointer())
          ->SetNumberOfSubdivisions(numberOfSubdivisions);
      actor->GetProperty()->SetDiffuseColor(butterflyColor.GetData());
      legend->SetEntry(i, subdivisionFilter->GetOutput(), "Butterfly",
                       butterflyColor.GetData());
      break;
    default:
      break;
    }
    subdivisionFilter->SetInputData(originalMesh);
    subdivisionFilter->Update();

    renderWindow->AddRenderer(renderer);
    // We reserve the lower part of the viewport for the legend.
    renderer->SetViewport(static_cast<double>(i) / numberOfViewports, 0.2,
                          static_cast<double>(i + 1) / numberOfViewports, 1);
    renderer->SetBackground(background.GetData());
    renderer->SetActiveCamera(camera);
    renderer->UseHiddenLineRemovalOn();
    // Create a mapper and actor
    vtkSmartPointer<vtkPolyDataMapper> mapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(subdivisionFilter->GetOutputPort());
    actor->SetMapper(mapper);
    renderer->AddActor(actor);
    renderer->ResetCamera();
  }

  // Position the legend below the three viewports defined above.
  legend->GetPositionCoordinate()->SetCoordinateSystemToView();
  legend->GetPositionCoordinate()->SetValue(-0.3, -0.9);
  legend->GetPosition2Coordinate()->SetCoordinateSystemToView();
  legend->GetPosition2Coordinate()->SetValue(0.3, 0.9);
  legend->BorderOff();
  legendRen->AddActor(legend);
  legendRen->SetBackground(background.GetData());
  legendRen->SetViewport(0.0, 0.0, 1.0, 0.2);
  renderWindow->AddRenderer(legendRen);

  renderWindow->Render();
  renderWindow->SetWindowName("Multiple ViewPorts");

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

namespace {
vtkSmartPointer<vtkPolyData> ReadPolyData(const char* fileName)
{
  vtkSmartPointer<vtkPolyData> polyData;
  std::string extension =
      vtksys::SystemTools::GetFilenameLastExtension(std::string(fileName));
  if (extension == ".ply")
  {
    vtkSmartPointer<vtkPLYReader> reader =
        vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtp")
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
        vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".obj")
  {
    vtkSmartPointer<vtkOBJReader> reader =
        vtkSmartPointer<vtkOBJReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".stl")
  {
    vtkSmartPointer<vtkSTLReader> reader =
        vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtk")
  {
    vtkSmartPointer<vtkPolyDataReader> reader =
        vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".g")
  {
    vtkSmartPointer<vtkBYUReader> reader =
        vtkSmartPointer<vtkBYUReader>::New();
    reader->SetGeometryFileName(fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    vtkSmartPointer<vtkSphereSource> source =
        vtkSmartPointer<vtkSphereSource>::New();
    source->Update();
    polyData = source->GetOutput();
  }
  return polyData;
}
} // namespace
