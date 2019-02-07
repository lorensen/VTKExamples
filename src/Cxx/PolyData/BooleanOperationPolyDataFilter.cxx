#include <vtkSmartPointer.h>
#include <vtkBooleanOperationPolyDataFilter.h>

#include <vtkCleanPolyData.h>
#include <vtkTriangleFilter.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkNamedColors.h>

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>

#include <vtkSphereSource.h>
#include <vtksys/SystemTools.hxx>

#include <vtkCamera.h>
namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);
void PositionCamera(vtkSmartPointer<vtkRenderer> &renderer,
                    double *viewUp,
                    double *position);
}

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> input1;
  vtkSmartPointer<vtkPolyData> input2;

  std::string operation("intersection");

  if (argc == 4)
  {
    vtkSmartPointer<vtkPolyData> poly1;
    poly1 = ReadPolyData(argv[1]);
    vtkSmartPointer<vtkTriangleFilter> tri1 =
      vtkSmartPointer<vtkTriangleFilter>::New();
    tri1->SetInputData(poly1);
    vtkSmartPointer<vtkCleanPolyData> clean1 =
      vtkSmartPointer<vtkCleanPolyData>::New();
    clean1->SetInputConnection(tri1->GetOutputPort());
    clean1->Update();
    input1 = clean1->GetOutput();

    vtkSmartPointer<vtkPolyData> poly2;
    poly2 = ReadPolyData(argv[3]);
    vtkSmartPointer<vtkTriangleFilter> tri2 =
      vtkSmartPointer<vtkTriangleFilter>::New();
    tri2->SetInputData(poly2);
    tri2->Update();
    vtkSmartPointer<vtkCleanPolyData> clean2 =
      vtkSmartPointer<vtkCleanPolyData>::New();
    clean2->SetInputConnection(tri2->GetOutputPort());
    clean2->Update();
    input2 = clean2->GetOutput();
    operation = argv[2];
  }
  else
  {
    vtkSmartPointer<vtkSphereSource> sphereSource1 =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource1->SetCenter(.25, 0, 0);
    sphereSource1->SetPhiResolution(21);
    sphereSource1->SetThetaResolution(21);
    sphereSource1->Update();
    input1 = sphereSource1->GetOutput();

    vtkSmartPointer<vtkSphereSource> sphereSource2 =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource2->Update();
    input2 = sphereSource2->GetOutput();

    if (argc == 2)
    {
      operation = argv[1];
    }
  }

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkPolyDataMapper> input1Mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  input1Mapper->SetInputData( input1 );
  input1Mapper->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> input1Actor =
    vtkSmartPointer<vtkActor>::New();
  input1Actor->SetMapper( input1Mapper );
  input1Actor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Tomato").GetData());
  input1Actor->GetProperty()->SetSpecular(.6);
  input1Actor->GetProperty()->SetSpecularPower(20);
  input1Actor->SetPosition(
    input1->GetBounds()[1]-input1->GetBounds()[0],
    0, 0);
  vtkSmartPointer<vtkPolyDataMapper> input2Mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  input2Mapper->SetInputData( input2 );
  input2Mapper->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> input2Actor =
    vtkSmartPointer<vtkActor>::New();
  input2Actor->SetMapper( input2Mapper );
  input2Actor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Mint").GetData());
  input2Actor->GetProperty()->SetSpecular(.6);
  input2Actor->GetProperty()->SetSpecularPower(20);
  input2Actor->SetPosition(
    -(input1->GetBounds()[1]-input1->GetBounds()[0]),
    0, 0);
  vtkSmartPointer<vtkBooleanOperationPolyDataFilter> booleanOperation =
    vtkSmartPointer<vtkBooleanOperationPolyDataFilter>::New();
  if (operation == "union")
  {
      booleanOperation->SetOperationToUnion();
  }
  else if (operation == "intersection")
  {
      booleanOperation->SetOperationToIntersection();
  }
  else if (operation == "difference")
  {
      booleanOperation->SetOperationToDifference();
  }
  else
  {
    std::cout << "Unknown operation: " << operation << std::endl;
    return EXIT_FAILURE;
  }
  booleanOperation->SetInputData( 0, input1 );
  booleanOperation->SetInputData( 1, input2 );

  vtkSmartPointer<vtkPolyDataMapper> booleanOperationMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  booleanOperationMapper->SetInputConnection( booleanOperation->GetOutputPort() );
  booleanOperationMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> booleanOperationActor =
    vtkSmartPointer<vtkActor>::New();
  booleanOperationActor->SetMapper( booleanOperationMapper );
  booleanOperationActor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Banana").GetData());
  booleanOperationActor->GetProperty()->SetSpecular(.6);
  booleanOperationActor->GetProperty()->SetSpecularPower(20);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddViewProp(input1Actor);
  renderer->AddViewProp(input2Actor);
  renderer->AddViewProp(booleanOperationActor);
  renderer->SetBackground(colors->GetColor3d("Silver").GetData());
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer( renderer );
  renderWindow->SetSize(640, 480);
  double viewUp[3] = {0.0, 0.0, 1.0};
  double position[3] = {0.0, -1.0, 0.0};
  PositionCamera(renderer, viewUp, position);
  renderer->GetActiveCamera()->Dolly(1.5);
  renderer->ResetCameraClippingRange();

  vtkSmartPointer<vtkRenderWindowInteractor> renWinInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renWinInteractor->SetRenderWindow( renderWindow );

  renderWindow->Render();
  renWinInteractor->Start();

  return EXIT_SUCCESS;
}
namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName)
{
  vtkSmartPointer<vtkPolyData> polyData;
  std::string extension = vtksys::SystemTools::GetFilenameExtension(std::string(fileName));
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

void PositionCamera(vtkSmartPointer<vtkRenderer> &renderer,
                    double *viewUp,
                    double *position)
{
  renderer->GetActiveCamera()->SetFocalPoint(0.0, 0.0, 0.0);
  renderer->GetActiveCamera()->SetViewUp(viewUp);
  renderer->GetActiveCamera()->SetPosition(position);
  renderer->ResetCamera();
  return;
}
}
