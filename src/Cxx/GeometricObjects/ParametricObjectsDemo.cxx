#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkCamera.h>
#include <vtkMinimalStandardRandomSequence.h>
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
  std::array<unsigned char , 4> bkg{{26, 51, 102, 255}};
    colors->SetColor("BkgColor", bkg.data());

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
  vtkSmartPointer<vtkMinimalStandardRandomSequence> rng =
    vtkSmartPointer<vtkMinimalStandardRandomSequence>::New();
  rng->SetSeed(8775070); // For testing.
  for (auto i = 0; i < 10; ++i)
  {
    rng->Next();
    auto x = rng->GetRangeValue(0.0, 1.0);
    rng->Next();
    auto y = rng->GetRangeValue(0.0, 1.0);
    rng->Next();
    auto z = rng->GetRangeValue(0.0, 1.0);
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
  textProperty->SetFontSize(12);
  textProperty->SetJustificationToCentered();

  vtkSmartPointer<vtkProperty> backProperty =
    vtkSmartPointer<vtkProperty>::New();
  backProperty->SetColor(colors->GetColor3d("Tomato").GetData());

  // Create a parametric function source, renderer, mapper, and actor
  // for each object
  for (auto i = 0; i < parametricObjects.size(); i++)
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
    actors[i]->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());
    actors[i]->GetProperty()->SetSpecular(.5);
    actors[i]->GetProperty()->SetSpecularPower(20);
    actors[i]->SetBackfaceProperty(backProperty);

    textmappers.push_back(vtkSmartPointer<vtkTextMapper>::New());
    textmappers[i]->SetInput(parametricObjects[i]->GetClassName());
    textmappers[i]->SetTextProperty(textProperty);

    textactors.push_back(vtkSmartPointer<vtkActor2D>::New());
    textactors[i]->SetMapper(textmappers[i]);
    textactors[i]->SetPosition(100, 16);
  
    renderers.push_back(vtkSmartPointer<vtkRenderer>::New());
    renderers[i]->AddActor(actors[i]);
    renderers[i]->AddActor(textactors[i]);
    renderers[i]->SetBackground(colors->GetColor3d("BkgColor").GetData());
  }

  // Setup the viewports
  auto xGridDimensions = 4;
  auto yGridDimensions = 4;
  auto rendererSize = 200;
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetWindowName("Parametric Objects Demonstration");
  renderWindow->SetSize(rendererSize * xGridDimensions,
                        rendererSize * yGridDimensions);

  for(auto row = 0; row < yGridDimensions; row++)
  {
    for(auto col = 0; col < xGridDimensions; col++)
    {
      int index = row * xGridDimensions + col;

      // (xmin, ymin, xmax, ymax)
      double viewport[4] = {
        static_cast<double>(col) / xGridDimensions,
        static_cast<double>(yGridDimensions - (row + 1))/ yGridDimensions,
        static_cast<double>(col + 1) / xGridDimensions,
        static_cast<double>(yGridDimensions - row) / yGridDimensions
      };

      if(index > int(actors.size()) - 1)
      {
        // Add a renderer even if there is no actor.
        // This makes the render window background all the same color.
        vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
        ren->SetBackground(colors->GetColor3d("BkgColor").GetData());
        ren->SetViewport(viewport);
        renderWindow->AddRenderer(ren);
        continue;
      }

      renderers[index]->SetViewport(viewport);
      renderers[index]->ResetCamera();
      renderers[index]->GetActiveCamera()->Azimuth(30);
      renderers[index]->GetActiveCamera()->Elevation(-30);
      renderers[index]->ResetCameraClippingRange();
      renderWindow->AddRenderer(renderers[index]);
    }
  }

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
