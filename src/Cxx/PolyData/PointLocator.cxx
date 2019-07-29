#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkNamedColors.h>
#include <vtkObjectFactory.h>
#include <vtkPointLocator.h>
#include <vtkPointSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

class KeyPressInteractorStyle3 : public vtkInteractorStyleTrackballCamera
{
public:
  static KeyPressInteractorStyle3* New();

  KeyPressInteractorStyle3() : PointsPerBucket(1)
  {
    pointLocator = nullptr;
    renderWindow = nullptr;
    polydata = nullptr;
  }

  virtual void OnChar()
  {
    vtkRenderWindowInteractor* rwi = this->Interactor;
    char ch = rwi->GetKeyCode();

    switch (ch)
    {
    case 'n':
      cout << "Next." << endl;
      this->PointsPerBucket++;
      break;
    case 'p':
      cout << "Previous." << endl;
      if (this->PointsPerBucket > 1)
      {
        this->PointsPerBucket--;
      }
      break;
    default:
      std::cout << "An unhandled key was pressed." << std::endl;
      break;
    }

    std::cout << "PointsPerBucket = " << this->PointsPerBucket << std::endl;

    // Create the tree
    pointLocator->SetNumberOfPointsPerBucket(this->PointsPerBucket);
    pointLocator->BuildLocator();
    pointLocator->GenerateRepresentation(1, polydata);

    renderWindow->Render();

    // Forward events
    vtkInteractorStyleTrackballCamera::OnChar();
  }

  vtkPointLocator* pointLocator;
  vtkRenderWindow* renderWindow;
  vtkPolyData* polydata;

private:
  unsigned int PointsPerBucket;
};

vtkStandardNewMacro(KeyPressInteractorStyle3);

int main(int, char*[])
{
  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  auto pointSource = vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(4000);
  pointSource->Update();

  // Create the tree
  auto pointLocator = vtkSmartPointer<vtkPointLocator>::New();
  pointLocator->SetDataSet(pointSource->GetOutput());
  pointLocator->AutomaticOn();
  pointLocator->SetNumberOfPointsPerBucket(2);
  pointLocator->BuildLocator();

  std::cout << "There are " << pointLocator->GetLevel() << " levels."
            << std::endl;
  std::cout << "There are " << pointLocator->GetNumberOfPointsPerBucket()
            << " points per bucket." << endl;

  auto polydata = vtkSmartPointer<vtkPolyData>::New();
  pointLocator->GenerateRepresentation(pointLocator->GetLevel(), polydata);

  // Visualize
  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(polydata);

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(colors->GetColor3d("Peru").GetData());

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  auto renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkSmartPointer<KeyPressInteractorStyle3> style =
      vtkSmartPointer<KeyPressInteractorStyle3>::New();
  style->pointLocator = pointLocator;
  style->renderWindow = renderWindow;
  style->polydata = polydata;

  renderWindowInteractor->SetInteractorStyle(style);

  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("Beige").GetData());
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Elevation(60.0);
  renderer->GetActiveCamera()->Azimuth(30.0);
  renderWindow->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
