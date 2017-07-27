#include <vtkSmartPointer.h>
#include <vtkVRMLImporter.h>

#include <vtkActor.h>
#include <vtkActorCollection.h>
#include <vtkCamera.h>
#include <vtkMapper.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

#include <vtkNamedColors.h>

int main ( int argc, char *argv[])
{
  if(argc < 2)
  {
    std::cout << "Required arguments: Filename" << std::endl;
    return EXIT_FAILURE;
  }

  std::string filename = argv[1];
  std::cout << "Reading " << filename << std::endl;

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // VRML Import
  vtkSmartPointer<vtkVRMLImporter> importer =
    vtkSmartPointer<vtkVRMLImporter>::New();
  importer->SetFileName ( filename.c_str() );
  importer->SetRenderWindow(renderWindow);
  importer->Update();

  vtkSmartPointer<vtkActorCollection> actors =
    vtkSmartPointer<vtkActorCollection>::New();
  actors = renderer->GetActors();
  std::cout << "There are " << actors->GetNumberOfItems() << " actors" << std::endl;
  int m = 0;
  actors->InitTraversal();
  for (vtkIdType a = 0; a < actors->GetNumberOfItems(); ++a)
  {
    vtkActor * actor = actors->GetNextActor();

    // The importer shininess parameter is between 0 and 1. VTK specular power is usually 10-100.
    // Also, the default for the specular factor for VRML is 1, while VTK's is 0
    double specularPower = actor->GetProperty()->GetSpecularPower();
    actor->GetProperty()->SetSpecularPower(specularPower * 100.0);
    actor->GetProperty()->SetSpecular(1.0);

    // The VRML default ambient intensity is .2
    double ambientIntensity = actor->GetProperty()->GetAmbient();
    if (ambientIntensity == 0.0)
    {
      actor->GetProperty()->SetAmbient(.2);
    }
    vtkPolyDataMapper *mapper = vtkPolyDataMapper::SafeDownCast(actor->GetMapper());
    vtkPolyData *dataSet = vtkPolyData::SafeDownCast(mapper->GetInput());
    if (!dataSet->GetPointData()->GetNormals())
    {
      vtkSmartPointer<vtkPolyDataNormals> normals =
        vtkSmartPointer<vtkPolyDataNormals>::New();
      normals->SetInputData(dataSet);
      normals->Update();
      mapper->SetInputData(normals->GetOutput());
    }
  }

  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->GetActiveCamera()->Dolly(1.4);
  renderer->ResetCameraClippingRange();

  renderer->SetBackground(colors->GetColor3d("PaleGreen").GetData());
  renderWindow->SetSize(640, 480);
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
