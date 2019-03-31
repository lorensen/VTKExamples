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
  std::array<unsigned char , 4> bkg{{26, 51, 102, 255}};
    colors->SetColor("BkgColor", bkg.data());

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
  auto yGridDimensions = 2;
  auto rendererSize = 200;
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetWindowName("Parametric Objects Demonstration2");
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
