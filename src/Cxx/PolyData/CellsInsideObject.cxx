#include <vtkSmartPointer.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkSelectEnclosedPoints.h>
#include <vtkMultiThreshold.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkUnstructuredGrid.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkTransform.h>

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkSphereSource.h>

#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

#include <vtkNamedColors.h>
#include <vtksys/SystemTools.hxx>

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);
}

int main (int argc, char *argv[])
{
  // Read the polyData's
  auto polyData1 =
    ReadPolyData(argc > 1 ? argv[1] : "");;
  auto polyData =
    ReadPolyData(argc > 2 ? argv[2] : "");;

  auto polyData2 = vtkSmartPointer<vtkPolyData>::New();
  auto transform = vtkSmartPointer<vtkTransform>::New();
  auto transformPD = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  // if only one polydata is present, generate a second polydata by
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
  auto select =
    vtkSmartPointer<vtkSelectEnclosedPoints>::New();
  select->SetInputData(polyData1);
  select->SetSurfaceData(polyData2);

  // Extract two meshes, one inside and one outside
  auto threshold =
    vtkSmartPointer<vtkMultiThreshold>::New();
  threshold->AddBandpassIntervalSet(
    0, 0,
    vtkDataObject::FIELD_ASSOCIATION_POINTS, "SelectedPoints",
    0, 0);
  threshold->AddBandpassIntervalSet(
    1, 1,
    vtkDataObject::FIELD_ASSOCIATION_POINTS, "SelectedPoints",
    0, 1);
  threshold->SetInputConnection(select->GetOutputPort());
  threshold->OutputSet(0);
  threshold->OutputSet(1);
  threshold->Update();

  // Visualize
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Outside
  vtkSmartPointer<vtkDataSetMapper> mapper1 =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper1->SetInputData(
    vtkUnstructuredGrid::SafeDownCast(vtkMultiBlockDataSet::SafeDownCast(threshold->GetOutput()->GetBlock(0))->GetBlock(0)));
  mapper1->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> actor1 =
    vtkSmartPointer<vtkActor>::New();
  actor1->SetMapper(mapper1);
  actor1->GetProperty()->SetDiffuseColor(colors->GetColor3d("Crimson").GetData());
  actor1->GetProperty()->SetSpecular(.6);
  actor1->GetProperty()->SetSpecularPower(30);
;

  // Inside
  vtkSmartPointer<vtkDataSetMapper> mapper2 =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper2->SetInputData(
    vtkUnstructuredGrid::SafeDownCast(vtkMultiBlockDataSet::SafeDownCast(threshold->GetOutput()->GetBlock(1))->GetBlock(0)));
  mapper2->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> actor2 =
    vtkSmartPointer<vtkActor>::New();
  actor2->SetMapper(mapper2);
  actor2->GetProperty()->SetDiffuseColor(colors->GetColor3d("Banana").GetData());
  actor2->GetProperty()->SetSpecular(.6);
  actor2->GetProperty()->SetSpecularPower(30);
;
  vtkSmartPointer<vtkDataSetMapper> surfaceMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  surfaceMapper->SetInputData(polyData2);
  surfaceMapper->ScalarVisibilityOff();

  // Surface of object containing cels
  vtkSmartPointer<vtkActor> surfaceActor =
    vtkSmartPointer<vtkActor>::New();
  surfaceActor->SetMapper(surfaceMapper);
  surfaceActor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Peacock").GetData());
  surfaceActor->GetProperty()->SetOpacity(.1);

;

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(surfaceActor);
  renderer->AddActor(actor1);
  renderer->AddActor(actor2);
  renderer->SetBackground(colors->GetColor3d("Silver").GetData());
  renderer->UseHiddenLineRemovalOn();

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName)
{
  vtkSmartPointer<vtkPolyData> polyData;
  std::string extension = vtksys::SystemTools::GetFilenameLastExtension(std::string(fileName));
  if (extension == ".ply")
  {
    vtkSmartPointer<vtkPLYReader> reader =
      vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtp")
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".obj")
  {
    vtkSmartPointer<vtkOBJReader> reader =
      vtkSmartPointer<vtkOBJReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".stl")
  {
    vtkSmartPointer<vtkSTLReader> reader =
      vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtk")
  {
    vtkSmartPointer<vtkPolyDataReader> reader =
      vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".g")
  {
    vtkSmartPointer<vtkBYUReader> reader =
      vtkSmartPointer<vtkBYUReader>::New();
    reader->SetGeometryFileName (fileName);
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
}
