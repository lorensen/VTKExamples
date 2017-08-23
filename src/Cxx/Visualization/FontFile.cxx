#include <vtkSmartPointer.h>
#include <vtkTextMapper.h>

#include <vtkActor2D.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTextProperty.h>

#include <vtksys/SystemTools.hxx>
#include <sstream>
#include <string>

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cerr << "Usage: " << argv[1] << " font.ttf" << std::endl;
    return EXIT_FAILURE;
  }
      

  std::string fontFile(argv[1]);
  std::stringstream str;
  str << "Font: "
      << vtksys::SystemTools::GetFilenameWithoutExtension(std::string(argv[1]))
      << "\n"
      << "Sample multiline\ntext rendered\nusing FreeTypeTools.";
  
  int width = 640;
  int height = 480;

  vtkSmartPointer<vtkTextMapper> mapper = 
    vtkSmartPointer<vtkTextMapper>::New();

  vtkSmartPointer<vtkActor2D> actor =
    vtkSmartPointer<vtkActor2D>::New();
  actor->SetPosition(width / 2, height / 2);
  actor->SetMapper(mapper);
  mapper->GetTextProperty()->BoldOff();;
  mapper->GetTextProperty()->SetFontSize(50);
  mapper->GetTextProperty()->SetColor(1.0, 1.0, 1.0);
  mapper->GetTextProperty()->SetJustificationToCentered();
  mapper->GetTextProperty()->SetVerticalJustificationToCentered();
  mapper->GetTextProperty()->SetFontFamily(VTK_FONT_FILE);
  mapper->GetTextProperty()->SetFontFile(fontFile.c_str());
  mapper->SetInput(str.str().c_str());

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(.5, .6, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();

  renderWindow->SetSize(width, height);
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);

  renderWindow->Render();
  interactor->Initialize();
  interactor->Start();

  return EXIT_SUCCESS;
}
