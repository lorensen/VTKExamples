#include <vtkSmartPointer.h>
#include <vtkPolyDataSilhouette.h>

#include <vtkXMLPolyDataReader.h>
#include <vtkCleanPolyData.h>
#include <vtkProperty.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkCamera.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSphereSource.h>

#include <vtkNamedColors.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> polyData;
  if (argc < 2)
  {
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->Update();

    polyData = sphereSource->GetOutput();
  }
  else
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(argv[1]);

    vtkSmartPointer<vtkCleanPolyData> clean =
      vtkSmartPointer<vtkCleanPolyData>::New();
    clean->SetInputConnection(reader->GetOutputPort());
    clean->Update();

    polyData = clean->GetOutput();
  }

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  //create mapper and actor for original model
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(polyData);
  mapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetInterpolationToFlat();
  actor->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());

  //create renderer and renderWindow
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  renderer->AddActor(actor); //view the original model

  //Compute the silhouette
  vtkSmartPointer<vtkPolyDataSilhouette> silhouette =
    vtkSmartPointer<vtkPolyDataSilhouette>::New();
  silhouette->SetInputData(polyData);
  silhouette->SetCamera(renderer->GetActiveCamera());
  silhouette->SetEnableFeatureAngle(0);

  //create mapper and actor for silouette
  vtkSmartPointer<vtkPolyDataMapper> mapper2 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper2->SetInputConnection(silhouette->GetOutputPort());

  vtkSmartPointer<vtkActor> actor2 =
    vtkSmartPointer<vtkActor>::New();
  actor2->SetMapper(mapper2);
  actor2->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());
  actor2->GetProperty()->SetLineWidth(5);

  renderer->AddActor(actor2);
  renderer->SetBackground(colors->GetColor3d("Silver").GetData());
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->GetActiveCamera()->Dolly(1.5);;
  renderer->ResetCameraClippingRange();

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renderWindow);

  //render and interact
  renderWindow->SetSize(640, 480);
  renderWindow->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
