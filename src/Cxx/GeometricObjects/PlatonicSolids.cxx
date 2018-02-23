#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkLookupTable.h>
#include <vtkNamedColors.h>
#include <vtkPlatonicSolidSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkTextActor.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>

#include <string>
#include <vector>

int main(int, char* [])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Each face has a different cell scalar
  // Here we create a lookup table with a different colour
  // for each face. The colors have been carefully
  // chosen so that adjacent cells are colored distinctly.
  vtkSmartPointer<vtkLookupTable> lut =
    vtkSmartPointer<vtkLookupTable>::New();
  lut->SetNumberOfTableValues(20);
  lut->SetTableRange(0.0, 19.0);
  lut->Build();
  lut->SetTableValue(0, 0.1, 0.1, 0.1);
  lut->SetTableValue(1, 0, 0, 1);
  lut->SetTableValue(2, 0, 1, 0);
  lut->SetTableValue(3, 0, 1, 1);
  lut->SetTableValue(4, 1, 0, 0);
  lut->SetTableValue(5, 1, 0, 1);
  lut->SetTableValue(6, 1, 1, 0);
  lut->SetTableValue(7, 0.9, 0.7, 0.9);
  lut->SetTableValue(8, 0.5, 0.5, 0.5);
  lut->SetTableValue(9, 0.0, 0.0, 0.7);
  lut->SetTableValue(10, 0.5, 0.7, 0.5);
  lut->SetTableValue(11, 0, 0.7, 0.7);
  lut->SetTableValue(12, 0.7, 0, 0);
  lut->SetTableValue(13, 0.7, 0, 0.7);
  lut->SetTableValue(14, 0.7, 0.7, 0);
  lut->SetTableValue(15, 0, 0, 0.4);
  lut->SetTableValue(16, 0, 0.4, 0);
  lut->SetTableValue(17, 0, 0.4, 0.4);
  lut->SetTableValue(18, 0.4, 0, 0);
  lut->SetTableValue(19, 0.4, 0, 0.4);

  std::vector<vtkSmartPointer<vtkPolyDataMapper>> mappers;
  std::vector<vtkSmartPointer<vtkActor>> actors;
  std::vector<vtkSmartPointer<vtkTextMapper>> textMappers;
  std::vector<vtkSmartPointer<vtkActor2D>> textActors;
  std::vector<vtkSmartPointer<vtkRenderer>> renderers;

  // Create a common text property.
  vtkSmartPointer<vtkTextProperty> textProperty =
    vtkSmartPointer<vtkTextProperty>::New();
  textProperty->SetFontSize(16);
  textProperty->SetJustificationToCentered();

  // Create the render window and interactor.
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->SetWindowName("Platonic Solids");
  vtkSmartPointer<vtkRenderWindowInteractor> iRen =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iRen->SetRenderWindow(renWin);

  // There are five platonic solids.
  std::vector<std::string> names{"Tetrahedron", "Cube", "Octahedron",
                                 "Icosahedron", "Dodecahedron"};
  std::vector<vtkSmartPointer<vtkPlatonicSolidSource>> PlatonicSolids;
  for (auto i = 0; i < names.size(); ++i)
  {
    PlatonicSolids.push_back(vtkSmartPointer<vtkPlatonicSolidSource>::New());
    PlatonicSolids[i]->SetSolidType(i);

    mappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
    mappers[i]->SetInputConnection(PlatonicSolids[i]->GetOutputPort());
    mappers[i]->SetLookupTable(lut);
    mappers[i]->SetScalarRange(0, 19);

    actors.push_back(vtkSmartPointer<vtkActor>::New());
    actors[i]->SetMapper(mappers[i]);

    textMappers.push_back(vtkSmartPointer<vtkTextMapper>::New());
    textMappers[i]->SetInput(names[i].c_str());
    textMappers[i]->SetTextProperty(textProperty);

    textActors.push_back(vtkSmartPointer<vtkActor2D>::New());
    textActors[i]->SetMapper(textMappers[i]);
    textActors[i]->SetPosition(120, 16);

    renderers.push_back(vtkSmartPointer<vtkRenderer>::New());
    renderers[i]->AddActor(actors[i]);
    renderers[i]->AddViewProp(textActors[i]);

    renWin->AddRenderer(renderers[i]);
  }

  // Setup the viewports
  auto xGridDimensions = 3;
  auto yGridDimensions = 2;
  auto rendererSize = 300;
  renWin->SetSize(rendererSize * xGridDimensions,
                  rendererSize * yGridDimensions);
  for (auto row = 0; row < yGridDimensions; ++row)
  {
    for (auto col = 0; col < xGridDimensions; ++col)
    {
      auto index = row * xGridDimensions + col;

      // (xmin, ymin, xmax, ymax)
      double viewport[4] = {
        static_cast<double>(col) / xGridDimensions,
        static_cast<double>(yGridDimensions - (row + 1)) / yGridDimensions,
        static_cast<double>(col + 1) / xGridDimensions,
        static_cast<double>(yGridDimensions - row) / yGridDimensions};
      if (index > (actors.size() - 1))
      {
        // Add a renderer even if there is no actor.
        // This makes the render window background all the same color.
        vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
        ren->SetBackground(colors->GetColor3d("SlateGray").GetData());
        ren->SetViewport(viewport);
        renWin->AddRenderer(ren);
        continue;
      }

      renderers[index]->SetViewport(viewport);
      renderers[index]->SetBackground(
        colors->GetColor3d("SlateGray").GetData());
      renderers[index]->ResetCamera();
      renderers[index]->GetActiveCamera()->Azimuth(4.5);
      renderers[index]->GetActiveCamera()->Elevation(-18);
      renderers[index]->ResetCameraClippingRange();
    }
  }

  iRen->Initialize();
  renWin->Render();
  iRen->Start();

  return EXIT_SUCCESS;
}
