#include <vtkSmartPointer.h>
#include <vtkDensifyPointCloudFilter.h>

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>

#include <vtkPointSource.h>
#include <vtkSphereSource.h>
#include <vtkGlyph3DMapper.h>

#include <vtkPolyDataMapper.h>
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
  vtkSmartPointer<vtkPolyData> polyData = ReadPolyData(argc > 1 ? argv[1] : "");;

  double bounds[6];
  polyData->GetBounds(bounds);
  double range[3];
  for (int i = 0; i < 3; ++i)
  {
    range[i] = bounds[2*i + 1] - bounds[2*i];
  }
  std::cout << "Range: "
            << range[0] << ", "
            << range[1] << ", "
            << range[2] << std::endl;

  double maxRange = std::max(std::max(range[0], range[1]), range[2]);

  std::cout << "# of original points: " << polyData->GetNumberOfPoints() << std::endl;
  vtkSmartPointer<vtkDensifyPointCloudFilter> densify =
    vtkSmartPointer<vtkDensifyPointCloudFilter>::New();
  densify->SetInputData(polyData);
  densify->SetMaximumNumberOfIterations(5);
  densify->SetTargetDistance(maxRange * .03);
  densify->SetNumberOfClosestPoints(10);
  densify->Update();
  std::cout << "# of densified points: " << densify->GetOutput()->GetNumberOfPoints() << std::endl;

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
///
  double radius = maxRange * .01;
  vtkSmartPointer<vtkSphereSource> sphereSource1 =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource1->SetRadius(radius);

  vtkSmartPointer<vtkGlyph3DMapper> glyph3D1 =
    vtkSmartPointer<vtkGlyph3DMapper>::New();
  glyph3D1->SetInputData(polyData);
  glyph3D1->SetSourceConnection(sphereSource1->GetOutputPort());
  glyph3D1->ScalarVisibilityOff();
  glyph3D1->ScalingOff();

  vtkSmartPointer<vtkActor> glyph3DActor1 =
    vtkSmartPointer<vtkActor>::New();
  glyph3DActor1->SetMapper(glyph3D1);
  glyph3DActor1->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());

////
  vtkSmartPointer<vtkSphereSource> sphereSource2 =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource2->SetRadius(radius * .75);

  vtkSmartPointer<vtkGlyph3DMapper> glyph3D2 =
    vtkSmartPointer<vtkGlyph3DMapper>::New();
  glyph3D2->SetInputConnection(densify->GetOutputPort());
  glyph3D2->SetSourceConnection(sphereSource2->GetOutputPort());
  glyph3D2->ScalarVisibilityOff();
  glyph3D2->ScalingOff();

  vtkSmartPointer<vtkActor> glyph3DActor2 =
    vtkSmartPointer<vtkActor>::New();
  glyph3DActor2->SetMapper(glyph3D2);
  glyph3DActor2->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());

  // Create graphics stuff
  //
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  ren1->SetBackground(colors->GetColor3d("SlateGray").GetData());

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);
  renWin->SetSize(512,512);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);
  
  // Add the actors to the renderer, set the background and size
  //
  ren1->AddActor(glyph3DActor1);
  ren1->AddActor(glyph3DActor2);

  // Generate an interesting view
  //
  ren1->GetActiveCamera()->SetPosition (1, 0, 0);
  ren1->GetActiveCamera()->SetFocalPoint (0, 1, 0);
  ren1->GetActiveCamera()->SetViewUp (0, 0, 1);
  ren1->ResetCamera();
  ren1->GetActiveCamera()->Dolly(1.0);
  ren1->ResetCameraClippingRange();

  renWin->Render();
  iren->Initialize();
  iren->Start();

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
  else if (extension == ".vtk")
  {
    vtkSmartPointer<vtkPolyDataReader> reader =
      vtkSmartPointer<vtkPolyDataReader>::New();
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
    vtkSmartPointer<vtkPointSource> points =
      vtkSmartPointer<vtkPointSource>::New();
    points->SetNumberOfPoints(100000);
    points->SetRadius(10.0);
    points->SetCenter(vtkMath::Random(-100, 100),
                      vtkMath::Random(-100, 100),
                      vtkMath::Random(-100, 100));
    points->SetDistributionToShell();
    points->Update();
    polyData = points->GetOutput();
  }
  return polyData;
}
}
