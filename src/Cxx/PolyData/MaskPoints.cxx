#include <vtkSmartPointer.h>
#include <vtkMaskPoints.h>
#include <vtkPointSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkVertexGlyphFilter.h>

int main(int, char*[])
{
  // Create a set of points
  vtkSmartPointer<vtkPointSource> pointsSource =
    vtkSmartPointer<vtkPointSource>::New();
  pointsSource->SetNumberOfPoints(40);
  pointsSource->Update();

  std::cout << "There are " << pointsSource->GetOutput()->GetNumberOfPoints()
            << " input points." << std::endl;

  // Create a point set
  vtkSmartPointer<vtkMaskPoints> maskPoints =
      vtkSmartPointer<vtkMaskPoints>::New();
  maskPoints->SetOnRatio(2); //keep every 2nd point (half the number of points)
  maskPoints->SetInputConnection(pointsSource->GetOutputPort());
  maskPoints->Update();

  vtkSmartPointer<vtkVertexGlyphFilter> glyphFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
  glyphFilter->SetInputConnection(maskPoints->GetOutputPort());
  glyphFilter->Update();
  
  std::cout << "There are " << maskPoints->GetOutput()->GetNumberOfPoints()
            << " masked points." << std::endl;

  vtkSmartPointer<vtkPolyDataMapper> inputMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  inputMapper->SetInputConnection(pointsSource->GetOutputPort());
  vtkSmartPointer<vtkActor> inputActor =
    vtkSmartPointer<vtkActor>::New();
  inputActor->SetMapper(inputMapper);

  vtkSmartPointer<vtkPolyDataMapper> maskedMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  maskedMapper->SetInputConnection(glyphFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> maskedActor =
    vtkSmartPointer<vtkActor>::New();
  maskedActor->SetMapper(maskedMapper);

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
  rightRenderer->AddActor(maskedActor);

  leftRenderer->ResetCamera();
  rightRenderer->ResetCamera();

  renderWindow->Render();
  interactor->Start();
  
  return EXIT_SUCCESS;
}
