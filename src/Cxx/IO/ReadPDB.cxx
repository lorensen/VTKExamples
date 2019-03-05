#include <vtkSmartPointer.h>
#include <vtkPDBReader.h>

#include <cmath>
#include <vtkGlyph3D.h>
#include <vtkLODActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkTubeFilter.h>
#include <vtkNamedColors.h>

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cerr << "Usage: " << argv[0] << " Filename(.pdb)" << std::endl;
    return EXIT_FAILURE;
  }
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkPDBReader> pdb =
    vtkSmartPointer<vtkPDBReader>::New();
  pdb->SetFileName(argv[1]);
  pdb->SetHBScale(1.0);
  pdb->SetBScale(1.0);
  pdb->Update();
  std::cout <<"# of atoms is: " << pdb->GetNumberOfAtoms() << std::endl;

  double resolution = std::sqrt(300000.0 / pdb->GetNumberOfAtoms());
  if (resolution > 20)
  {
    resolution = 20;
  }
  if (resolution < 4)
  {
    resolution = 4;
  }
  std::cout <<"Resolution is: " << resolution << std::endl;
  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetCenter(0, 0, 0);
  sphere->SetRadius(1);
  sphere->SetThetaResolution(static_cast<int>(resolution));
  sphere->SetPhiResolution(static_cast<int>(resolution));

  vtkSmartPointer<vtkGlyph3D> glyph =
    vtkSmartPointer<vtkGlyph3D>::New();
  glyph->SetInputConnection(pdb->GetOutputPort());
  glyph->SetOrient(1);
  glyph->SetColorMode(1);
  // glyph->ScalingOn();
  glyph->SetScaleMode(2);
  glyph->SetScaleFactor(.25);
  glyph->SetSourceConnection(sphere->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> atomMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  atomMapper->SetInputConnection(glyph->GetOutputPort());
  atomMapper->UseLookupTableScalarRangeOff();
  atomMapper->ScalarVisibilityOn();
  atomMapper->SetScalarModeToDefault();

  vtkSmartPointer<vtkLODActor> atom =
    vtkSmartPointer<vtkLODActor>::New();
  atom->SetMapper(atomMapper);
  atom->GetProperty()->SetRepresentationToSurface();
  atom->GetProperty()->SetInterpolationToGouraud();
  atom->GetProperty()->SetAmbient(0.1);
  atom->GetProperty()->SetDiffuse(0.7);
  atom->GetProperty()->SetSpecular(0.5);
  atom->GetProperty()->SetSpecularPower(80);
  atom->GetProperty()->SetSpecularColor(colors->GetColor3d("White").GetData());
  atom->SetNumberOfCloudPoints(30000);

  renderer->AddActor(atom);

  vtkSmartPointer<vtkTubeFilter> tube =
    vtkSmartPointer<vtkTubeFilter>::New();
  tube->SetInputConnection(pdb->GetOutputPort());
  tube->SetNumberOfSides(static_cast<int>(resolution));
  tube->CappingOff();
  tube->SetRadius(0.2);
  tube->SetVaryRadius(0);
  tube->SetRadiusFactor(10);

  vtkSmartPointer<vtkPolyDataMapper> bondMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  bondMapper->SetInputConnection(tube->GetOutputPort());
  bondMapper->UseLookupTableScalarRangeOff();
  bondMapper->ScalarVisibilityOff();
  bondMapper->SetScalarModeToDefault();

  vtkSmartPointer<vtkLODActor> bond =
    vtkSmartPointer<vtkLODActor>::New();
  bond->SetMapper(bondMapper);
  bond->GetProperty()->SetRepresentationToSurface();
  bond->GetProperty()->SetInterpolationToGouraud();
  bond->GetProperty()->SetAmbient(0.1);
  bond->GetProperty()->SetDiffuse(0.7);
  bond->GetProperty()->SetSpecular(0.5);
  bond->GetProperty()->SetSpecularPower(80);
  bond->GetProperty()->SetSpecularColor(colors->GetColor3d("White").GetData());

  renderer->AddActor(bond);

  renderWindow->Render();
  interactor->Initialize();
  interactor->Start();

  return EXIT_SUCCESS;
}
