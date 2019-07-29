/*
The purpose of this is to demonstrate how to get the Gaussian and Mean
curvatures of a surface.

Two different surfaces are used in this demonstration with each
surface coloured according to its Gaussian and Mean curvatures.

The first surface is a superquadric surface, this demonstrates the use
of extra filters that are needed to get a nice smooth surface.

The second surface is a parametric surface, in this case the surface
has already been triangulated so no extra processing is necessary.

In order to get a nice coloured image, a vtkColorTransferFunction has
been used to generate a set of colours for the vtkLookUp tables. We
have used a diverging colour space.  Because of the symmetry of the
ranges selected for the lookup tables, the white colouration
represents a midpoint value whilst the blue represents values less
than the midopoint value and red represents colours greater than the
midpoint value.

In the case of the Random Hills Gaussian Curvature surface, this
colouration shows the nature of the surface quite nicely. The blue
areas are saddle points (negative Gaussian curvature) and the red
areas have a positive Gaussian curvature.  In the case of the mean
curvature the blue colouration is representing negative curvature
perpendicular to one of the principal axes.

This example also demonstrates the use of std::vector and the linking
of the elements of the vector together to form a pipeline.
*/

#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkCleanPolyData.h>
#include <vtkColorTransferFunction.h>
#include <vtkCurvatures.h>
#include <vtkLookupTable.h>
#include <vtkNamedColors.h>
#include <vtkParametricFunctionSource.h>
#include <vtkParametricRandomHills.h>
#include <vtkPolyDataAlgorithm.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkSuperquadricSource.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>
#include <vtkTransform.h>
#include <vtkTransformFilter.h>
#include <vtkTriangleFilter.h>

#include <array>
#include <vector>

int main(int, char* argv[])
{
  auto colors = vtkSmartPointer<vtkNamedColors>::New();
  // We are going to handle two different sources.
  // The first source is a superquadric source.
  auto torus = vtkSmartPointer<vtkSuperquadricSource>::New();
  torus->SetCenter(0.0, 0.0, 0.0);
  torus->SetScale(1.0, 1.0, 1.0);
  torus->SetPhiResolution(64);
  torus->SetThetaResolution(64);
  torus->SetThetaRoundness(1);
  torus->SetThickness(0.5);
  torus->SetSize(0.5);
  torus->SetToroidal(1);

  // Rotate the torus towards the observer (around the x-axis)
  auto torusT = vtkSmartPointer<vtkTransform>::New();
  torusT->RotateX(55);

  auto torusTF = vtkSmartPointer<vtkTransformFilter>::New();
  torusTF->SetInputConnection(torus->GetOutputPort());
  torusTF->SetTransform(torusT);

  // The quadric is made of strips, so pass it through a triangle filter as
  // the curvature filter only operates on polys
  auto tri = vtkSmartPointer<vtkTriangleFilter>::New();
  tri->SetInputConnection(torusTF->GetOutputPort());

  // The quadric has nasty discontinuities from the way the edges are generated
  // so let's pass it though a CleanPolyDataFilter and merge any points which
  // are coincident, or very close
  auto cleaner = vtkSmartPointer<vtkCleanPolyData>::New();
  cleaner->SetInputConnection(tri->GetOutputPort());
  cleaner->SetTolerance(0.005);

  // The next source will be a parametric function
  auto rh = vtkSmartPointer<vtkParametricRandomHills>::New();
  auto rhFnSrc = vtkSmartPointer<vtkParametricFunctionSource>::New();
  rhFnSrc->SetParametricFunction(rh);

  // Now we have the sources, lets put them into a vector
  std::vector<vtkSmartPointer<vtkPolyDataAlgorithm>> sources;
  sources.push_back(cleaner);
  sources.push_back(cleaner);
  sources.push_back(rhFnSrc);
  sources.push_back(rhFnSrc);

  // Colour transfer function.
  auto ctf = vtkSmartPointer<vtkColorTransferFunction>::New();
  ctf->SetColorSpaceToDiverging();
  ctf->AddRGBPoint(0.0, colors->GetColor3d("MidnightBlue").GetRed(),
                   colors->GetColor3d("MidnightBlue").GetGreen(),
                   colors->GetColor3d("MidnightBlue").GetBlue());
  ctf->AddRGBPoint(1.0, colors->GetColor3d("DarkOrange").GetRed(),
                   colors->GetColor3d("DarkOrange").GetGreen(),
                   colors->GetColor3d("DarkOrange").GetBlue());

  // Lookup table.
  std::vector<vtkSmartPointer<vtkLookupTable>> luts;
  for (auto idx = 0; idx < sources.size(); ++idx)
  {
    auto lut = vtkSmartPointer<vtkLookupTable>::New();
    lut->SetNumberOfColors(256);
    for (auto i = 0; i < lut->GetNumberOfColors(); ++i)
    {
      std::array<double, 4> color;
      ctf->GetColor(double(i) / lut->GetNumberOfColors(), color.data());
      color[3] = 1.0;
      lut->SetTableValue(i, color.data());
    }
    if (idx == 0)
    {
      lut->SetRange(-10, 10);
    }
    else if (idx == 1)
    {
      lut->SetRange(0, 4);
    }
    else if (idx == 2)
    {
      lut->SetRange(-1, 1);
    }
    else
    {
      lut->SetRange(-1, 1);
    }
    lut->Build();
    luts.push_back(lut);
  }

  std::vector<vtkSmartPointer<vtkCurvatures>> curvatures;
  for (auto idx = 0; idx < sources.size(); ++idx)
  {
    curvatures.push_back(vtkSmartPointer<vtkCurvatures>::New());
    if (idx % 2 == 0)
    {
      curvatures[idx]->SetCurvatureTypeToGaussian();
    }
    else
    {
      curvatures[idx]->SetCurvatureTypeToMean();
    }
  }
  std::vector<vtkSmartPointer<vtkRenderer>> renderers;
  std::vector<vtkSmartPointer<vtkActor>> actors;
  std::vector<vtkSmartPointer<vtkPolyDataMapper>> mappers;
  std::vector<vtkSmartPointer<vtkTextMapper>> textmappers;
  std::vector<vtkSmartPointer<vtkActor2D>> textactors;
  for (auto idx = 0; idx < sources.size(); ++idx)
  {
    mappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
    actors.push_back(vtkSmartPointer<vtkActor>::New());
    textmappers.push_back(vtkSmartPointer<vtkTextMapper>::New());
    textactors.push_back(vtkSmartPointer<vtkActor2D>::New());
    renderers.push_back(vtkSmartPointer<vtkRenderer>::New());
  }

  // Create a common text property.
  auto textProperty = vtkSmartPointer<vtkTextProperty>::New();
  textProperty->SetFontSize(24);
  textProperty->SetJustificationToCentered();

  std::vector<std::string> names;
  names.push_back("Torus - Gaussian Curvature");
  names.push_back("Torus - Mean Curvature");
  names.push_back("Random Hills - Gaussian Curvature");
  names.push_back("Random Hills - Mean Curvature");
  // Link the pipeline together.
  for (auto idx = 0; idx < sources.size(); ++idx)
  {
    curvatures[idx]->SetInputConnection(sources[idx]->GetOutputPort());

    mappers[idx]->SetInputConnection(curvatures[idx]->GetOutputPort());
    mappers[idx]->SetLookupTable(luts[idx]);
    mappers[idx]->SetUseLookupTableScalarRange(1);

    actors[idx]->SetMapper(mappers[idx]);

    textmappers[idx]->SetInput(names[idx].c_str());
    textmappers[idx]->SetTextProperty(textProperty);

    textactors[idx]->SetMapper(textmappers[idx]);
    textactors[idx]->SetPosition(250, 16);
  }

  // Create the RenderWindow
  //
  auto rendererSize = 512;
  auto gridDimensions = 2;

  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(rendererSize * gridDimensions,
                        rendererSize * gridDimensions);

  // Add and position the renders to the render window.
  for (auto row = 0; row < gridDimensions; ++row)
  {
    for (auto col = 0; col < gridDimensions; ++col)
    {
      auto idx = row * gridDimensions + col;
      renderers[idx]->SetViewport(
          double(col) / gridDimensions,
          double(gridDimensions - (row + 1)) / gridDimensions,
          double(col + 1) / gridDimensions,
          double(gridDimensions - row) / gridDimensions);
      renderWindow->AddRenderer(renderers[idx]);

      renderers[idx]->AddActor(actors[idx]);
      renderers[idx]->AddActor(textactors[idx]);
      renderers[idx]->SetBackground(
          colors->GetColor3d("CornflowerBlue").GetData());
    }
  }

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderWindow->Render();

  interactor->Start();

  return EXIT_SUCCESS;
}
