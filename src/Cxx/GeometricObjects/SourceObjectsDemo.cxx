#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkCamera.h>
#include <vtkConeSource.h>
#include <vtkCubeSource.h>
#include <vtkCylinderSource.h>
#include <vtkDiskSource.h>
#include <vtkLineSource.h>
#include <vtkMath.h>
#include <vtkNamedColors.h>
#include <vtkPlaneSource.h>
#include <vtkPoints.h>
#include <vtkPointSource.h>
#include <vtkPolyDataAlgorithm.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>
#include <vtkTextSource.h>

#include <array>
#include <vector>

int main(int, char* [])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Set the background color.
  std::array<unsigned char , 4> bkg{{51, 77, 102, 255}};
    colors->SetColor("BkgColor", bkg.data());

  std::vector<vtkSmartPointer<vtkPolyDataAlgorithm>> sourceObjects;
  sourceObjects.push_back(vtkSmartPointer<vtkSphereSource>::New());
  static_cast<vtkSphereSource *>(sourceObjects.back().GetPointer())
    ->SetPhiResolution(21);
  static_cast<vtkSphereSource *>(sourceObjects.back().GetPointer())
    ->SetThetaResolution(21);

  sourceObjects.push_back(vtkSmartPointer<vtkConeSource>::New());
  static_cast<vtkConeSource *>(sourceObjects.back().GetPointer())
    ->SetResolution(51);

  sourceObjects.push_back(vtkSmartPointer<vtkCylinderSource>::New());
  static_cast<vtkCylinderSource *>(sourceObjects.back().GetPointer())
    ->SetResolution(51);

  sourceObjects.push_back(vtkSmartPointer<vtkCubeSource>::New());
  sourceObjects.push_back(vtkSmartPointer<vtkPlaneSource>::New());
  sourceObjects.push_back(vtkSmartPointer<vtkTextSource>::New());
  static_cast<vtkTextSource *>(sourceObjects.back().GetPointer())
    ->SetText("Hello");
  static_cast<vtkTextSource *>(sourceObjects.back().GetPointer())
    ->BackingOff();

  sourceObjects.push_back(vtkSmartPointer<vtkPointSource>::New());
  static_cast<vtkPointSource *>(sourceObjects.back().GetPointer())
    ->SetNumberOfPoints(500);

  sourceObjects.push_back(vtkSmartPointer<vtkDiskSource>::New());
  static_cast<vtkDiskSource *>(sourceObjects.back().GetPointer())
    ->SetCircumferentialResolution(51);

  sourceObjects.push_back(vtkSmartPointer<vtkLineSource>::New());

  std::vector<vtkSmartPointer<vtkRenderer>> renderers;
  std::vector<vtkSmartPointer<vtkPolyDataMapper>> mappers;
  std::vector<vtkSmartPointer<vtkActor>> actors;
  std::vector<vtkSmartPointer<vtkTextMapper>> textmappers;
  std::vector<vtkSmartPointer<vtkActor2D>> textactors;

  // Create one text property for all
  vtkSmartPointer<vtkTextProperty> textProperty =
    vtkSmartPointer<vtkTextProperty>::New();
  textProperty->SetFontSize(16);
  textProperty->SetJustificationToCentered();

  vtkSmartPointer<vtkProperty> backProperty =
    vtkSmartPointer<vtkProperty>::New();
  backProperty->SetColor(colors->GetColor3d("Red").GetData());

  // Create a source, renderer, mapper, and actor
  // for each object
  for (unsigned int i = 0; i < sourceObjects.size(); i++)
  {
    mappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
    mappers[i]->SetInputConnection(
      sourceObjects[i]->GetOutputPort());

    actors.push_back(vtkSmartPointer<vtkActor>::New());
    actors[i]->SetMapper(mappers[i]);
    actors[i]->GetProperty()->SetColor(colors->GetColor3d("Seashell").GetData());
    actors[i]->SetBackfaceProperty(backProperty);

    textmappers.push_back(vtkSmartPointer<vtkTextMapper>::New());
    textmappers[i]->SetInput(sourceObjects[i]->GetClassName());
    textmappers[i]->SetTextProperty(textProperty);

    textactors.push_back(vtkSmartPointer<vtkActor2D>::New());
    textactors[i]->SetMapper(textmappers[i]);
    textactors[i]->SetPosition(120, 16);
    renderers.push_back(vtkSmartPointer<vtkRenderer>::New());
  }

  auto gridDimensions = 3;

  // Need a renderer even if there is no actor
  for (auto i = static_cast<int>(sourceObjects.size());
       i < gridDimensions * gridDimensions; ++i)
  {
    renderers.push_back(vtkSmartPointer<vtkRenderer>::New());
  }

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetWindowName("Source Objects Demo");

  int rendererSize = 300;
  renderWindow->SetSize(rendererSize * gridDimensions,
                        rendererSize * gridDimensions);

  for (auto row = 0; row < gridDimensions; row++)
  {
    for (auto col = 0; col < gridDimensions; col++)
    {
      auto index = row * gridDimensions + col;
      auto x0 = double(col) / gridDimensions;
      auto y0 = double(gridDimensions - row - 1) / gridDimensions;
      auto x1 = double(col + 1) / gridDimensions;
      auto y1 = double(gridDimensions - row) / gridDimensions;
      renderWindow->AddRenderer(renderers[index]);
      renderers[index]->SetViewport(x0, y0, x1, y1);

      if (index > static_cast<int>(sourceObjects.size() - 1))
      {
        continue;
      }

      renderers[index]->AddActor(actors[index]);
      renderers[index]->AddActor(textactors[index]);
      renderers[index]->SetBackground(colors->GetColor3d("BkgColor").GetData());
      renderers[index]->ResetCamera();
      renderers[index]->GetActiveCamera()->Azimuth(30);
      renderers[index]->GetActiveCamera()->Elevation(30);
      renderers[index]->GetActiveCamera()->Zoom(0.8);
      renderers[index]->ResetCameraClippingRange();
    }
  }

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
