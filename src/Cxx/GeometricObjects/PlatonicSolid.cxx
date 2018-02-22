#include <vtkSmartPointer.h>
#include <vtkPlatonicSolidSource.h>
#include <vtkLookupTable.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

#include <vector>
#include <string>
 
int main(int, char *[])
{
  // There are five platonic solids.
  std::vector<std::string> names{"Tetrahedron", "Cube", "Octahedron", "Icosahedron", "Dodecahedron"};
  std::vector<vtkSmartPointer<vtkPlatonicSolidSource>> PlatonicSolids;
  for (auto i = 0; i < 5; ++i)
  {
    PlatonicSolids.push_back(vtkSmartPointer<vtkPlatonicSolidSource>::New());
  }
   
  vtkSmartPointer<vtkPlatonicSolidSource> platonicSolidSource = 
    vtkSmartPointer<vtkPlatonicSolidSource>::New();
  platonicSolidSource->SetSolidTypeToOctahedron();

  // Each face has a different cell scalar
  vtkSmartPointer<vtkLookupTable> lut =
    vtkSmartPointer<vtkLookupTable>::New();
  lut->SetNumberOfTableValues(20);
  lut->SetTableRange(0.0, 19.0);
  lut->Build();
  lut->SetTableValue(0, 0, 0, 0);
  lut->SetTableValue(1, 0, 0, 1);
  lut->SetTableValue(2, 0, 1, 0);
  lut->SetTableValue(3, 0, 1, 1);
  lut->SetTableValue(4, 1, 0, 0);
  lut->SetTableValue(5, 1, 0, 1);
  lut->SetTableValue(6, 1, 1, 0);
  lut->SetTableValue(7, 1, 1, 1);
  lut->SetTableValue(8, 0.7, 0.7, 0.7);
  lut->SetTableValue(9, 0, 0, 0.7);
  lut->SetTableValue(10, 0, 0.7, 0);
  lut->SetTableValue(11, 0, 0.7, 0.7);
  lut->SetTableValue(12, 0.7, 0, 0);
  lut->SetTableValue(13, 0.7, 0, 0.7);
  lut->SetTableValue(14, 0.7, 0.7, 0);
  lut->SetTableValue(15, 0, 0, 0.4);
  lut->SetTableValue(16, 0, 0.4, 0);
  lut->SetTableValue(17, 0, 0.4, 0.4);
  lut->SetTableValue(18, 0.4, 0, 0);
  lut->SetTableValue(19, 0.4, 0, 0.4);

  //Create a mapper and actor.
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(platonicSolidSource->GetOutputPort());
  mapper->SetLookupTable(lut);
  mapper->SetScalarRange(0, 7);

  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  //Add the actors to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(.1, .2, .3);

  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
