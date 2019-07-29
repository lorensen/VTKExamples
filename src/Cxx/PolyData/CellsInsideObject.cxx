#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkMultiThreshold.h>
#include <vtkNamedColors.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSelectEnclosedPoints.h>
#include <vtkSmartPointer.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkUnstructuredGrid.h>

// Readers
#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>

#include <vtkPolyData.h>
#include <vtkSphereSource.h>

#include <algorithm> // For transform()
#include <cctype>    // For to_lower
#include <iostream>
#include <string> // For find_last_of()
#include <vector>

namespace {
vtkSmartPointer<vtkPolyData> ReadPolyData(std::string const& fileName);
}

int main(int argc, char* argv[])
{
  // Read the polyData's
  auto polyData1 = ReadPolyData(argc > 1 ? argv[1] : "");
  ;
  auto polyData = ReadPolyData(argc > 2 ? argv[2] : "");
  ;

  vtkSmartPointer<vtkPolyData> polyData2;
  auto transform = vtkSmartPointer<vtkTransform>::New();
  auto transformPD = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  // If only one polydata is present, generate a second polydata by
  // rotating the orginal about its center.
  if (argc < 3)
  {
    std::cout << "Generating modified polyData1" << std::endl;
    double center[3];
    polyData1->GetCenter(center);
    transform->Translate(center[0], center[1], center[2]);
    transform->RotateY(90.0);
    transform->Translate(-center[0], -center[1], -center[2]);
    transformPD->SetTransform(transform);
    transformPD->SetInputData(polyData1);
    transformPD->Update();
    polyData2 = transformPD->GetOutput();
  }
  else
  {
    polyData2 = polyData;
  }
  // Mark points inside with 1 and outside with a 0
  auto select = vtkSmartPointer<vtkSelectEnclosedPoints>::New();
  select->SetInputData(polyData1);
  select->SetSurfaceData(polyData2);

  // Extract three meshes, one completely inside, one completely
  // outside and on the border between the inside and outside.

  auto threshold = vtkSmartPointer<vtkMultiThreshold>::New();
  // Outside points have a 0 value in ALL points of a cell
  int outsideId = threshold->AddBandpassIntervalSet(
      0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, "SelectedPoints", 0, 1);
  // Inside points have a 1 value in ALL points of a cell
  int insideId = threshold->AddBandpassIntervalSet(
      1, 1, vtkDataObject::FIELD_ASSOCIATION_POINTS, "SelectedPoints", 0, 1);
  // Border points have a 0 or a 1 in at least one point of a cell
  int borderId = threshold->AddIntervalSet(
      0, 1, vtkMultiThreshold::OPEN, vtkMultiThreshold::OPEN,
      vtkDataObject::FIELD_ASSOCIATION_POINTS, "SelectedPoints", 0, 0);

  threshold->SetInputConnection(select->GetOutputPort());

  // Select the intervals to be output
  threshold->OutputSet(outsideId);
  threshold->OutputSet(insideId);
  threshold->OutputSet(borderId);
  threshold->Update();

  // Visualize
  auto colors = vtkSmartPointer<vtkNamedColors>::New();
  vtkColor3d outsideColor = colors->GetColor3d("Crimson");
  vtkColor3d insideColor = colors->GetColor3d("Banana");
  vtkColor3d borderColor = colors->GetColor3d("Mint");
  vtkColor3d surfaceColor = colors->GetColor3d("Peacock");
  vtkColor3d backgroundColor = colors->GetColor3d("Silver");

  // Outside
  auto outsideMapper = vtkSmartPointer<vtkDataSetMapper>::New();
  outsideMapper->SetInputData(dynamic_cast<vtkUnstructuredGrid*>(
      vtkMultiBlockDataSet::SafeDownCast(
          threshold->GetOutput()->GetBlock(outsideId))
          ->GetBlock(0)));
  outsideMapper->ScalarVisibilityOff();

  auto outsideActor = vtkSmartPointer<vtkActor>::New();
  outsideActor->SetMapper(outsideMapper);
  outsideActor->GetProperty()->SetDiffuseColor(outsideColor.GetData());
  outsideActor->GetProperty()->SetSpecular(.6);
  outsideActor->GetProperty()->SetSpecularPower(30);

  // Inside
  auto insideMapper = vtkSmartPointer<vtkDataSetMapper>::New();
  insideMapper->SetInputData(dynamic_cast<vtkUnstructuredGrid*>(
      vtkMultiBlockDataSet::SafeDownCast(
          threshold->GetOutput()->GetBlock(insideId))
          ->GetBlock(0)));
  insideMapper->ScalarVisibilityOff();

  auto insideActor = vtkSmartPointer<vtkActor>::New();
  insideActor->SetMapper(insideMapper);
  insideActor->GetProperty()->SetDiffuseColor(insideColor.GetData());
  insideActor->GetProperty()->SetSpecular(.6);
  insideActor->GetProperty()->SetSpecularPower(30);
  insideActor->GetProperty()->EdgeVisibilityOn();

  // Border
  auto borderMapper = vtkSmartPointer<vtkDataSetMapper>::New();
  borderMapper->SetInputData(dynamic_cast<vtkUnstructuredGrid*>(
      vtkMultiBlockDataSet::SafeDownCast(
          threshold->GetOutput()->GetBlock(borderId))
          ->GetBlock(0)));
  borderMapper->ScalarVisibilityOff();

  auto borderActor = vtkSmartPointer<vtkActor>::New();
  borderActor->SetMapper(borderMapper);
  borderActor->GetProperty()->SetDiffuseColor(borderColor.GetData());
  borderActor->GetProperty()->SetSpecular(.6);
  borderActor->GetProperty()->SetSpecularPower(30);
  borderActor->GetProperty()->EdgeVisibilityOn();

  auto surfaceMapper = vtkSmartPointer<vtkDataSetMapper>::New();
  surfaceMapper->SetInputData(polyData2);
  surfaceMapper->ScalarVisibilityOff();

  // Surface of object containing cell
  auto surfaceActor = vtkSmartPointer<vtkActor>::New();
  surfaceActor->SetMapper(surfaceMapper);
  surfaceActor->GetProperty()->SetDiffuseColor(surfaceColor.GetData());
  surfaceActor->GetProperty()->SetOpacity(.1);

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);

  auto renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->SetBackground(backgroundColor.GetData());
  renderer->UseHiddenLineRemovalOn();

  renderer->AddActor(surfaceActor);
  renderer->AddActor(outsideActor);
  renderer->AddActor(insideActor);
  renderer->AddActor(borderActor);

  renderWindow->SetWindowName("CellsInsideObject");
  renderWindow->Render();
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->GetActiveCamera()->Dolly(1.25);
  renderWindow->Render();

  renderWindowInteractor->Start();

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
