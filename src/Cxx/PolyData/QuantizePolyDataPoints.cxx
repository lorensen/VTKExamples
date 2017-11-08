#include <vtkSmartPointer.h>
#include <vtkQuantizePolyDataPoints.h>

#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkSphereSource.h>
#include <vtkGlyph3DMapper.h>
#include <vtkCamera.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPointSource> pointSource =
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(100);
  pointSource->Update();

  std::cout << "There are " << pointSource->GetNumberOfPoints()
            << " points." << std::endl;

  vtkSmartPointer<vtkQuantizePolyDataPoints> quantizeFilter =
    vtkSmartPointer<vtkQuantizePolyDataPoints>::New();
  quantizeFilter->SetInputConnection(pointSource->GetOutputPort());
  quantizeFilter->SetQFactor(.1);
  quantizeFilter->Update();

  vtkPolyData* quantized = quantizeFilter->GetOutput();
  std::cout << "There are " << quantized->GetNumberOfPoints()
            << " quantized points." << std::endl;

  for(vtkIdType i = 0; i < pointSource->GetOutput()->GetNumberOfPoints(); i++)
  {
    double pOrig[3];
    double pQuantized[3];
    pointSource->GetOutput()->GetPoint(i,pOrig);
    quantized->GetPoints()->GetPoint(i,pQuantized);

    std::cout << "Point " << i << " : ("
              << pOrig[0] << ", " << pOrig[1] << ", " << pOrig[2] << ")"
              << " (" << pQuantized[0] << ", " << pQuantized[1] << ", " << pQuantized[2]
              << ")" << std::endl;
  }

  double radius = .02;
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetRadius(radius);

  vtkSmartPointer<vtkGlyph3DMapper> inputMapper =
    vtkSmartPointer<vtkGlyph3DMapper>::New();
  inputMapper->SetInputConnection(pointSource->GetOutputPort());
  inputMapper->SetSourceConnection(sphereSource->GetOutputPort());
  inputMapper->ScalarVisibilityOff();
  inputMapper->ScalingOff();

  vtkSmartPointer<vtkActor> inputActor =
    vtkSmartPointer<vtkActor>::New();
  inputActor->SetMapper(inputMapper);

  vtkSmartPointer<vtkGlyph3DMapper> quantizedMapper =
    vtkSmartPointer<vtkGlyph3DMapper>::New();
  quantizedMapper->SetInputConnection(quantizeFilter->GetOutputPort());
  quantizedMapper->SetSourceConnection(sphereSource->GetOutputPort());
  quantizedMapper->ScalarVisibilityOff();
  quantizedMapper->ScalingOff();

  vtkSmartPointer<vtkActor> quantizedActor =
    vtkSmartPointer<vtkActor>::New();
  quantizedActor->SetMapper(quantizedMapper);

  // There will be one render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(640, 360);

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
  rightRenderer->AddActor(quantizedActor);

  leftRenderer->ResetCamera();

  rightRenderer->SetActiveCamera(leftRenderer->GetActiveCamera());

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
