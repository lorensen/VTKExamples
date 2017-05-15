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

int main(int, char *[])
{
  vtkSmartPointer<vtkPointSource> pointSource =
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(10);
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

  vtkSmartPointer<vtkPolyDataMapper> inputMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  inputMapper->SetInputConnection(pointSource->GetOutputPort());
  vtkSmartPointer<vtkActor> inputActor =
    vtkSmartPointer<vtkActor>::New();
  inputActor->SetMapper(inputMapper);

  vtkSmartPointer<vtkPolyDataMapper> quantizedMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  quantizedMapper->SetInputConnection(quantizeFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> quantizedActor =
    vtkSmartPointer<vtkActor>::New();
  quantizedActor->SetMapper(quantizedMapper);

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
  rightRenderer->AddActor(quantizedActor);

  leftRenderer->ResetCamera();

  rightRenderer->ResetCamera();

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
