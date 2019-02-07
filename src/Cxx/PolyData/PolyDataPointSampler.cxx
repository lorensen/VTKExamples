#include <vtkSmartPointer.h>
#include <vtkPolyDataPointSampler.h>

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkPointSource.h>

#include <vtkSphereSource.h>
#include <vtkGlyph3D.h>

#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

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
  std::cout << "# of original points: " << polyData->GetNumberOfPoints() << std::endl;
  vtkSmartPointer<vtkPolyDataPointSampler> sample =
    vtkSmartPointer<vtkPolyDataPointSampler>::New();
  sample->SetInputData(polyData);
  sample->SetDistance(range[0] / 50);
  sample->Update();
  std::cout << "# of points after sampling: " << sample->GetOutput()->GetNumberOfPoints() << std::endl;

///
  double radius = range[0] * .01;
  vtkSmartPointer<vtkSphereSource> originalSource =
    vtkSmartPointer<vtkSphereSource>::New();
  originalSource->SetRadius(radius);

  vtkSmartPointer<vtkGlyph3D> originalGlyph3D =
    vtkSmartPointer<vtkGlyph3D>::New();
  originalGlyph3D->SetInputData(polyData);
  originalGlyph3D->SetSourceConnection(originalSource->GetOutputPort());
  originalGlyph3D->ScalingOff();
  originalGlyph3D->Update();
  vtkSmartPointer<vtkPolyDataMapper> originalMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  originalMapper->SetInputConnection(originalGlyph3D->GetOutputPort());
  originalMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> originalActor =
    vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);
  originalActor->GetProperty()->SetColor(0.8900, 0.8100, 0.3400);

////
  vtkSmartPointer<vtkSphereSource> sampleSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sampleSource->SetRadius(radius * .75);

  vtkSmartPointer<vtkGlyph3D> sampleGlyph3D =
    vtkSmartPointer<vtkGlyph3D>::New();
  sampleGlyph3D->SetInputConnection(sample->GetOutputPort());
  sampleGlyph3D->SetSourceConnection(sampleSource->GetOutputPort());
  sampleGlyph3D->ScalingOff();
  sampleGlyph3D->Update();

  vtkSmartPointer<vtkPolyDataMapper> sampleMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sampleMapper->SetInputConnection(sampleGlyph3D->GetOutputPort());
  sampleMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> sampleActor =
    vtkSmartPointer<vtkActor>::New();
  sampleActor->SetMapper(sampleMapper);
  sampleActor->GetProperty()->SetColor(1.0000, 0.4900, 0.2500);

  // Create graphics stuff
  //
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  ren1->SetBackground(.3, .4, .6);

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);
  renWin->SetSize(512,512);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);
  
  // Add the actors to the renderer, set the background and size
  //
  ren1->AddActor(originalActor);
  ren1->AddActor(sampleActor);

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
    vtkSmartPointer<vtkSphereSource> sphere =
      vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetRadius(1.0);
    sphere->SetPhiResolution(21);
    sphere->SetThetaResolution(41);
    sphere->Update();
    polyData = sphere->GetOutput();
  }
  return polyData;
}
}
