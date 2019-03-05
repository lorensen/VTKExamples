#include <vtkNew.h>
#include <vtkCMLMoleculeReader.h>

#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkMolecule.h>
#include <vtkMoleculeMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>

#include <vtkNamedColors.h>

int main(int argc, char *argv[])
{
  std::string fname(argv[1]);
  vtkNew<vtkCMLMoleculeReader> cmlSource;

  cmlSource->SetFileName(fname.c_str());

  vtkNew<vtkMoleculeMapper> molmapper;
  molmapper->SetInputConnection(cmlSource->GetOutputPort());

  molmapper->UseBallAndStickSettings();

  vtkNew<vtkNamedColors> colors;

  vtkNew<vtkActor> actor;
  actor->SetMapper(molmapper);
  actor->GetProperty()->SetDiffuse(.7);
  actor->GetProperty()->SetSpecular(.5);
  actor->GetProperty()->SetSpecularPower(20.0);

  vtkNew<vtkRenderer> ren;
  vtkNew<vtkRenderWindow> renderWindow;
  renderWindow->AddRenderer(ren);
  vtkNew<vtkRenderWindowInteractor> iren;
  iren->SetRenderWindow(renderWindow);

  ren->AddActor(actor);

  ren->SetBackground(0.0,0.0,0.0);
  renderWindow->SetSize(640, 480);
  renderWindow->Render();
  ren->GetActiveCamera()->Zoom(2.0);
  ren->SetBackground(colors->GetColor3d("Silver").GetData());

  // Finally render the scene
  renderWindow->SetMultiSamples(0);
  renderWindow->GetInteractor()->Initialize();
  renderWindow->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
