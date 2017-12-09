#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkCamera.h>
#include <vtkMath.h>
#include <vtkNamedColors.h>
#include <vtkParametricFunctionSource.h>
#include <vtkPoints.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>

#include <vtkParametricBohemianDome.h>
#include <vtkParametricBour.h>
#include <vtkParametricCatalanMinimal.h>
#include <vtkParametricFunction.h>
#include <vtkParametricHenneberg.h>
#include <vtkParametricKuen.h>
#include <vtkParametricPluckerConoid.h>
#include <vtkParametricPseudosphere.h>

#include <array>
#include <vector>

int main(int, char* [])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Set the background color.
  auto SetColor = [&colors](std::array<double, 3>& v,
                            std::string const& colorName) {
    auto const scaleFactor = 256.0;
    std::transform(std::begin(v), std::end(v), std::begin(v),
                   [=](double const& n) { return n / scaleFactor; });
    colors->SetColor(colorName, v.data());
    return;
  };
  std::array<double, 3> bkg{{25, 51, 102}};
  SetColor(bkg, "BkgColor");

  std::vector<vtkSmartPointer<vtkParametricFunction>> parametricObjects;
  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricBohemianDome>::New());
  static_cast<vtkParametricBohemianDome*>(parametricObjects.back().GetPointer())
    ->SetA(5.0);
  static_cast<vtkParametricBohemianDome*>(parametricObjects.back().GetPointer())
    ->SetB(1.0);
  static_cast<vtkParametricBohemianDome*>(parametricObjects.back().GetPointer())
    ->SetC(2.0);
  parametricObjects.push_back(vtkSmartPointer<vtkParametricBour>::New());
  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricCatalanMinimal>::New());
  parametricObjects.push_back(vtkSmartPointer<vtkParametricHenneberg>::New());
  parametricObjects.push_back(vtkSmartPointer<vtkParametricKuen>::New());
  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricPluckerConoid>::New());
  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricPseudosphere>::New());

  std::vector<vtkSmartPointer<vtkParametricFunctionSource>>
    parametricFunctionSources;
  std::vector<vtkSmartPointer<vtkRenderer>> renderers;
  std::vector<vtkSmartPointer<vtkPolyDataMapper>> mappers;
  std::vector<vtkSmartPointer<vtkActor>> actors;
  std::vector<vtkSmartPointer<vtkTextMapper>> textmappers;
  std::vector<vtkSmartPointer<vtkActor2D>> textactors;

  // Create one text property for all
  vtkSmartPointer<vtkTextProperty> textProperty =
    vtkSmartPointer<vtkTextProperty>::New();
  textProperty->SetFontSize(10);
  textProperty->SetJustificationToCentered();

  vtkSmartPointer<vtkProperty> backProperty =
    vtkSmartPointer<vtkProperty>::New();
  backProperty->SetColor(colors->GetColor3d("Red").GetData());

  // Create a parametric function source, renderer, mapper, and actor
  // for each object
  for (unsigned int i = 0; i < parametricObjects.size(); i++)
  {
    parametricFunctionSources.push_back(
      vtkSmartPointer<vtkParametricFunctionSource>::New());
    parametricFunctionSources[i]->SetParametricFunction(parametricObjects[i]);
    parametricFunctionSources[i]->Update();

    mappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
    mappers[i]->SetInputConnection(
      parametricFunctionSources[i]->GetOutputPort());

    actors.push_back(vtkSmartPointer<vtkActor>::New());
    actors[i]->SetMapper(mappers[i]);
    actors[i]->GetProperty()->SetColor(colors->GetColor3d("White").GetData());
    actors[i]->SetBackfaceProperty(backProperty);

    textmappers.push_back(vtkSmartPointer<vtkTextMapper>::New());
    textmappers[i]->SetInput(parametricObjects[i]->GetClassName());
    textmappers[i]->SetTextProperty(textProperty);

    textactors.push_back(vtkSmartPointer<vtkActor2D>::New());
    textactors[i]->SetMapper(textmappers[i]);
    textactors[i]->SetPosition(100, 16);
    renderers.push_back(vtkSmartPointer<vtkRenderer>::New());
  }

  auto gridDimensionsX = 4;
  auto gridDimensionsY = 2;

  // Need a renderer even if there is no actor
  for (auto i = static_cast<int>(parametricObjects.size());
       i < gridDimensionsX * gridDimensionsY; i++)
  {
    renderers.push_back(vtkSmartPointer<vtkRenderer>::New());
  }

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  int rendererSize = 200;
  renderWindow->SetSize(rendererSize * gridDimensionsX,
                        rendererSize * gridDimensionsY);

  for (auto row = 0; row < gridDimensionsY; ++row)
  {
    for (auto col = 0; col < gridDimensionsX; ++col)
    {
      auto index = row * gridDimensionsX + col;
      auto x0 = double(col) / gridDimensionsX;
      auto y0 = double(gridDimensionsY - row - 1) / gridDimensionsY;
      auto x1 = double(col + 1) / gridDimensionsX;
      auto y1 = double(gridDimensionsY - row) / gridDimensionsY;
      renderWindow->AddRenderer(renderers[index]);
      renderers[index]->SetViewport(x0, y0, x1, y1);

      if (index > static_cast<int>(parametricObjects.size() - 1))
      {
        continue;
      }

      renderers[index]->AddActor(actors[index]);
      renderers[index]->AddActor(textactors[index]);
      renderers[index]->SetBackground(colors->GetColor3d("BkgColor").GetData());
      renderers[index]->ResetCamera();
      renderers[index]->GetActiveCamera()->Azimuth(30);
      renderers[index]->GetActiveCamera()->Elevation(-30);
      renderers[index]->GetActiveCamera()->Zoom(0.9);
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
