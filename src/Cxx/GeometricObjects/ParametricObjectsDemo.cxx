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

#include <vtkParametricBoy.h>
#include <vtkParametricConicSpiral.h>
#include <vtkParametricCrossCap.h>
#include <vtkParametricDini.h>
#include <vtkParametricEllipsoid.h>
#include <vtkParametricEnneper.h>
#include <vtkParametricFigure8Klein.h>
#include <vtkParametricKlein.h>
#include <vtkParametricMobius.h>
#include <vtkParametricRandomHills.h>
#include <vtkParametricRoman.h>
#include <vtkParametricSpline.h>
#include <vtkParametricSuperEllipsoid.h>
#include <vtkParametricSuperToroid.h>
#include <vtkParametricTorus.h>

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

  // Select one of the following (matching the selection above)
  std::vector<vtkSmartPointer<vtkParametricFunction>> parametricObjects;

  parametricObjects.push_back(vtkSmartPointer<vtkParametricBoy>::New());
  parametricObjects.push_back(vtkSmartPointer<vtkParametricConicSpiral>::New());
  parametricObjects.push_back(vtkSmartPointer<vtkParametricCrossCap>::New());
  parametricObjects.push_back(vtkSmartPointer<vtkParametricDini>::New());

  parametricObjects.push_back(vtkSmartPointer<vtkParametricEllipsoid>::New());
  static_cast<vtkParametricEllipsoid*>(parametricObjects.back().GetPointer())
    ->SetXRadius(.5);
  static_cast<vtkParametricEllipsoid*>(parametricObjects.back().GetPointer())
    ->SetYRadius(2.0);

  parametricObjects.push_back(vtkSmartPointer<vtkParametricEnneper>::New());
  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricFigure8Klein>::New());
  parametricObjects.push_back(vtkSmartPointer<vtkParametricKlein>::New());
  parametricObjects.push_back(vtkSmartPointer<vtkParametricMobius>::New());
  static_cast<vtkParametricMobius*>(parametricObjects.back().GetPointer())
    ->SetRadius(2.0);
  static_cast<vtkParametricMobius*>(parametricObjects.back().GetPointer())
    ->SetMinimumV(-0.5);
  static_cast<vtkParametricMobius*>(parametricObjects.back().GetPointer())
    ->SetMaximumV(0.5);

  vtkSmartPointer<vtkParametricRandomHills> randomHills =
    vtkSmartPointer<vtkParametricRandomHills>::New();
  randomHills->AllowRandomGenerationOff();
  parametricObjects.push_back(randomHills);

  parametricObjects.push_back(vtkSmartPointer<vtkParametricRoman>::New());

  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricSuperEllipsoid>::New());
  static_cast<vtkParametricSuperEllipsoid*>(
    parametricObjects.back().GetPointer())
    ->SetN1(.50);
  static_cast<vtkParametricSuperEllipsoid*>(
    parametricObjects.back().GetPointer())
    ->SetN2(.1);

  parametricObjects.push_back(vtkSmartPointer<vtkParametricSuperToroid>::New());
  static_cast<vtkParametricSuperToroid*>(parametricObjects.back().GetPointer())
    ->SetN1(.2);
  static_cast<vtkParametricSuperToroid*>(parametricObjects.back().GetPointer())
    ->SetN2(3.0);

  parametricObjects.push_back(vtkSmartPointer<vtkParametricTorus>::New());

  // The spline needs points
  vtkSmartPointer<vtkParametricSpline> spline =
    vtkSmartPointer<vtkParametricSpline>::New();
  vtkSmartPointer<vtkPoints> inputPoints = vtkSmartPointer<vtkPoints>::New();
  vtkMath::RandomSeed(8775070);
  for (int p = 0; p < 10; p++)
  {
    double x = vtkMath::Random(0.0, 1.0);
    double y = vtkMath::Random(0.0, 1.0);
    double z = vtkMath::Random(0.0, 1.0);
    inputPoints->InsertNextPoint(x, y, z);
  }
  spline->SetPoints(inputPoints);
  parametricObjects.push_back(spline);

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
    parametricFunctionSources[i]->SetUResolution(51);
    parametricFunctionSources[i]->SetVResolution(51);
    parametricFunctionSources[i]->SetWResolution(51);
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

  auto gridDimensions = 4;

  // Need a renderer even if there is no actor
  for (auto i = static_cast<int>(parametricObjects.size());
       i < gridDimensions * gridDimensions; i++)
  {
    renderers.push_back(vtkSmartPointer<vtkRenderer>::New());
  }

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  int rendererSize = 200;
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
