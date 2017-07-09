#include <vtkXMLPolyDataReader.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkTriangleFilter.h>
#include <vtkDecimatePro.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

#include <vtkNamedColors.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> inputPolyData;
  if(argc > 1)
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(argv[1]);
    vtkSmartPointer<vtkTriangleFilter> triangles =
      vtkSmartPointer<vtkTriangleFilter>::New();
    triangles->SetInputConnection(reader->GetOutputPort());
    triangles->Update();
    inputPolyData = triangles->GetOutput();
  }
  else
  {
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetThetaResolution(30);
    sphereSource->SetPhiResolution(15);
    sphereSource->Update();
    inputPolyData = sphereSource->GetOutput();
  }
  
  float reduction = .9; // 90% reduction
  if (argc > 2)
  {
    reduction = atof(argv[2]);
  }
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
  std::cout << "Before decimation" << std::endl << "------------" << std::endl;
  std::cout << "There are " << inputPolyData->GetNumberOfPoints() << " points." << std::endl;
  std::cout << "There are " << inputPolyData->GetNumberOfPolys() << " polygons." << std::endl;

  vtkSmartPointer<vtkDecimatePro> decimate =
    vtkSmartPointer<vtkDecimatePro>::New();
  decimate->SetInputData(inputPolyData);
  decimate->SetTargetReduction(reduction);
  decimate->PreserveTopologyOn();
  decimate->Update();

  vtkSmartPointer<vtkPolyData> decimated =
    vtkSmartPointer<vtkPolyData>::New();
  decimated->ShallowCopy(decimate->GetOutput());

  std::cout << "After decimation" << std::endl << "------------" << std::endl;

  std::cout << "There are " << decimated->GetNumberOfPoints() << " points." << std::endl;
  std::cout << "There are " << decimated->GetNumberOfPolys() << " polygons." << std::endl;
  std::cout << "Reduction: " <<
    static_cast<double>((inputPolyData->GetNumberOfPolys() - decimated->GetNumberOfPolys())) /
    static_cast<double>(inputPolyData->GetNumberOfPolys()) << std::endl;

  vtkSmartPointer<vtkPolyDataMapper> inputMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  inputMapper->SetInputData(inputPolyData);

  vtkSmartPointer<vtkProperty> backFace =
    vtkSmartPointer<vtkProperty>::New();
  backFace->SetColor(colors->GetColor3d("gold").GetData());

  vtkSmartPointer<vtkActor> inputActor =
    vtkSmartPointer<vtkActor>::New();
  inputActor->SetMapper(inputMapper);
  inputActor->GetProperty()->SetInterpolationToFlat();
  inputActor->GetProperty()->SetColor(colors->GetColor3d("flesh").GetData());
  inputActor->SetBackfaceProperty(backFace);

  vtkSmartPointer<vtkPolyDataMapper> decimatedMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  decimatedMapper->SetInputData(decimated);

  vtkSmartPointer<vtkActor> decimatedActor =
    vtkSmartPointer<vtkActor>::New();
  decimatedActor->SetMapper(decimatedMapper);
  decimatedActor->GetProperty()->SetColor(colors->GetColor3d("flesh").GetData());
  decimatedActor->GetProperty()->SetInterpolationToFlat();
  decimatedActor->SetBackfaceProperty(backFace);

  // There will be one render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);

  // And one interactor
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup both renderers
  vtkSmartPointer<vtkRenderer> leftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(leftRenderer);
  leftRenderer->SetViewport(leftViewport);
  leftRenderer->SetBackground(.6, .5, .4);

  vtkSmartPointer<vtkRenderer> rightRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(rightRenderer);
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->SetBackground(.4, .5, .6);

  // Add the sphere to the left and the cube to the right
  leftRenderer->AddActor(inputActor);
  rightRenderer->AddActor(decimatedActor);

  // Shared camera
  // Shared camera looking down the -y axis
  vtkSmartPointer<vtkCamera> camera =
    vtkSmartPointer<vtkCamera>::New();
  camera->SetPosition (0, -1, 0);
  camera->SetFocalPoint (0, 0, 0);
  camera->SetViewUp (0, 0, 1);
  camera->Elevation(30);
  camera->Azimuth(30);

  leftRenderer->SetActiveCamera(camera);
  rightRenderer->SetActiveCamera(camera);

  leftRenderer->ResetCamera();
  leftRenderer->ResetCameraClippingRange();

  renderWindow->Render();
  interactor->Start();
  
  return EXIT_SUCCESS;
}
