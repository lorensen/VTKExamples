#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkClipPolyData.h>
#include <vtkDataSetMapper.h>
#include <vtkFeatureEdges.h>
#include <vtkNamedColors.h>
#include <vtkPlane.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkStripper.h>
#include <vtkXMLPolyDataReader.h>

// Readers
#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>

#include <vtkSphereSource.h>

namespace {
vtkSmartPointer<vtkPolyData> ReadPolyData(std::string const& fileName);
}

//
// Demonstrate the use of clipping and capping on polyhedral data
//

int main(int argc, char* argv[])
{
  // Define colors
  auto colors = vtkSmartPointer<vtkNamedColors>::New();
  auto backgroundColor = colors->GetColor3d("steel_blue");
  auto boundaryColor = colors->GetColor3d("banana");
  auto clipColor = colors->GetColor3d("tomato");
  // PolyData to process
  auto polyData = ReadPolyData(argc > 1 ? argv[1] : "");

  auto plane = vtkSmartPointer<vtkPlane>::New();
  plane->SetOrigin(polyData->GetCenter());
  plane->SetNormal(1.0, -1.0, -1.0);

  auto clipper = vtkSmartPointer<vtkClipPolyData>::New();
  clipper->SetInputData(polyData);
  clipper->SetClipFunction(plane);
  clipper->SetValue(0);
  clipper->Update();

  polyData = clipper->GetOutput();

  auto clipMapper = vtkSmartPointer<vtkDataSetMapper>::New();
  clipMapper->SetInputData(polyData);

  auto clipActor = vtkSmartPointer<vtkActor>::New();
  clipActor->SetMapper(clipMapper);
  clipActor->GetProperty()->SetDiffuseColor(clipColor.GetData());
  clipActor->GetProperty()->SetInterpolationToFlat();
  clipActor->GetProperty()->EdgeVisibilityOn();

  // Now extract feature edges
  auto boundaryEdges = vtkSmartPointer<vtkFeatureEdges>::New();
  boundaryEdges->SetInputData(polyData);
  boundaryEdges->BoundaryEdgesOn();
  boundaryEdges->FeatureEdgesOff();
  boundaryEdges->NonManifoldEdgesOff();
  boundaryEdges->ManifoldEdgesOff();

  auto boundaryStrips = vtkSmartPointer<vtkStripper>::New();
  boundaryStrips->SetInputConnection(boundaryEdges->GetOutputPort());
  boundaryStrips->Update();

  // Change the polylines into polygons
  auto boundaryPoly = vtkSmartPointer<vtkPolyData>::New();
  boundaryPoly->SetPoints(boundaryStrips->GetOutput()->GetPoints());
  boundaryPoly->SetPolys(boundaryStrips->GetOutput()->GetLines());

  auto boundaryMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  boundaryMapper->SetInputData(boundaryPoly);

  auto boundaryActor = vtkSmartPointer<vtkActor>::New();
  boundaryActor->SetMapper(boundaryMapper);
  boundaryActor->GetProperty()->SetDiffuseColor(boundaryColor.GetData());

  // Create graphics stuff
  //
  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(backgroundColor.GetData());
  renderer->UseHiddenLineRemovalOn();

  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Add the actors to the renderer, set the background and size
  //
  renderer->AddActor(clipActor);
  renderer->AddActor(boundaryActor);

  // Generate an interesting view
  //
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->GetActiveCamera()->Dolly(1.2);
  renderer->ResetCameraClippingRange();

  renderWindow->Render();
  renderWindow->SetWindowName("CapClip");
  renderWindow->Render();

  interactor->Start();

  return EXIT_SUCCESS;
}
namespace {
vtkSmartPointer<vtkPolyData> ReadPolyData(std::string const& fileName)
{
  vtkSmartPointer<vtkPolyData> polyData;
  std::string extension = "";
  if (fileName.find_last_of(".") != std::string::npos)
  {
    extension = fileName.substr(fileName.find_last_of("."));
  }
  // Make the extension lowercase
  std::transform(extension.begin(), extension.end(), extension.begin(),
                 ::tolower);
  if (extension == ".ply")
  {
    auto reader = vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName(fileName.c_str());
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtp")
  {
    auto reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(fileName.c_str());
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".obj")
  {
    auto reader = vtkSmartPointer<vtkOBJReader>::New();
    reader->SetFileName(fileName.c_str());
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".stl")
  {
    auto reader = vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName(fileName.c_str());
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtk")
  {
    auto reader = vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName(fileName.c_str());
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".g")
  {
    auto reader = vtkSmartPointer<vtkBYUReader>::New();
    reader->SetGeometryFileName(fileName.c_str());
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    // Return a polydata sphere if the extension is unknown.
    auto source = vtkSmartPointer<vtkSphereSource>::New();
    source->SetThetaResolution(20);
    source->SetPhiResolution(11);
    source->Update();
    polyData = source->GetOutput();
  }
  return polyData;
}
} // namespace
