#include <vtkSmartPointer.h>
#include <vtkTextMapper.h>

#include <vtkActor2D.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTextProperty.h>
#include <vtkMath.h>

#include <vtksys/SystemTools.hxx>
#include <sstream>
#include <string>

#include <vtkNamedColors.h>
namespace
{
// Given a color, find a contrasting color. If the goven color is "light",
// use the lightColor otherwise use the darkColor
void ChooseContrastingColor(double *rgbIn,
                            double *rgbOut,
                            const std::string lightColor = "white",
                            const std::string darkColor = "black");
}
 
int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cerr << "Usage: " << argv[1] << " font.ttf" << std::endl;
    return EXIT_FAILURE;
  }

  // Defaults
  std::string backColor = "SlateGray";
  std::string lightColor = "White";
  std::string darkColor = "Black";
  if (argc > 2)
  {
    backColor = argv[2];
  }
  if (argc > 3)
  {
    lightColor = argv[3];
  }
  if (argc > 4)
  {
    darkColor = argv[4];
  }

  std::string fontFile(argv[1]);
  std::stringstream str;
  str << "Font: "
      << vtksys::SystemTools::GetFilenameWithoutExtension(std::string(argv[1]))
      << "\n"
      << "Background: " << backColor
      << "\n"
      << "Light Color: " << lightColor
      << "\n"
      << "Dark Color: " << darkColor;
  
  int width = 640;
  int height = 480;

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkTextMapper> mapper = 
    vtkSmartPointer<vtkTextMapper>::New();

  vtkSmartPointer<vtkActor2D> actor =
    vtkSmartPointer<vtkActor2D>::New();
  actor->SetPosition(width / 2, height / 2);
  actor->SetMapper(mapper);
  mapper->GetTextProperty()->BoldOff();
  mapper->GetTextProperty()->SetFontSize(50);
  mapper->GetTextProperty()->SetJustificationToCentered();
  mapper->GetTextProperty()->SetVerticalJustificationToCentered();
  mapper->GetTextProperty()->SetFontFamily(VTK_FONT_FILE);
  mapper->GetTextProperty()->SetFontFile(fontFile.c_str());
  mapper->SetInput(str.str().c_str());

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(colors->GetColor3d(backColor.c_str()).GetData());

  // Compute a good color for text on the renderer background
  double rgb[3];
  ChooseContrastingColor(renderer->GetBackground(),
                         rgb,
                         lightColor,
                         darkColor);
  mapper->GetTextProperty()->SetColor(rgb);

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

namespace
{
void ChooseContrastingColor(double *rgbIn,
                            double *rgbOut,
                            const std::string lightColor,
                            const std::string darkColor)
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  double hsv[3];
  // If the value is <= .5, use a light color, otherwise use a dark color
  vtkMath::RGBToHSV(rgbIn, hsv);
  if (hsv[2] <= .5)
  {
    colors->GetColor(lightColor.c_str(), rgbOut[0], rgbOut[1], rgbOut[2]);
  }
  else
  {
    colors->GetColor(darkColor.c_str(), rgbOut[0], rgbOut[1], rgbOut[2]);
  }
}
}
