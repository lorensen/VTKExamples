#include <vtkNamedColors.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Create a rendering window and renderer.
  vtkSmartPointer<vtkRenderer> ren =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->SetWindowName("Regular Polygon Source");
  renWin->AddRenderer(ren);

  // Create a render window interactor.
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Create a text actor.
  vtkSmartPointer<vtkTextActor> txt =
    vtkSmartPointer<vtkTextActor>::New();
  txt->SetInput("Hello World!");
  vtkTextProperty *txtprop = txt->GetTextProperty();
  txtprop->SetFontFamilyToArial();
  txtprop->BoldOn();
  txtprop->SetFontSize(36);
  txtprop->ShadowOn();
  txtprop->SetShadowOffset(4, 4);
  txtprop->SetColor(colors->GetColor3d("Cornsilk").GetData());
  txt->SetDisplayPosition(20, 30);

  // Assign actor to the renderer.
  ren->AddActor(txt);
  ren->SetBackground(colors->GetColor3d("DarkGreen").GetData());

  // Enable user interface interactor.
  iren->Initialize();
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
