#include <vtkSmartPointer.h>

#include <vtkMath.h>
#include <vtkNamedColors.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>

#include <sstream>
#include <string>
#include <vtksys/SystemTools.hxx>

namespace {
// Given a color, find a contrasting color. If the goven color is "light",
// use the lightColor otherwise use the darkColor
void ChooseContrastingColor(double* rgbIn, double* rgbOut,
                            const double threshold = .5,
                            const std::string& lightColor = "white",
                            const std::string& darkColor = "black");
} // namespace

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cerr << "Usage: " << argv[0]
              << " font.ttf [backColor] [lightColor] [darkColor]" << std::endl;
    return EXIT_FAILURE;
  }

  // Defaults
  double threshold(.8);
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
      << "Background: " << backColor << "\n"
      << "Light Color: " << lightColor << "\n"
      << "Dark Color: " << darkColor;

  int width = 640;
  int height = 480;

  auto colors =
    vtkSmartPointer<vtkNamedColors>::New();

  auto actor =
    vtkSmartPointer<vtkTextActor>::New();
  actor->GetTextProperty()->SetJustificationToCentered();
  actor->GetTextProperty()->SetVerticalJustificationToCentered();
  actor->SetTextScaleModeToViewport();
  actor->SetInput(str.str().c_str());
  actor->SetPosition(width / 2, height / 2);
  actor->GetTextProperty()->BoldOff();
  actor->GetTextProperty()->SetFontSize(40);
  actor->GetTextProperty()->SetFontFamily(VTK_FONT_FILE);
  actor->GetTextProperty()->SetFontFile(fontFile.c_str());

  auto renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(colors->GetColor3d(backColor.c_str()).GetData());

  // Compute a good color for text on the renderer background
  double rgb[3];
  ChooseContrastingColor(renderer->GetBackground(), rgb, threshold, lightColor,
                         darkColor);
  std::cout << rgb[0] << "," << rgb[1] << "," << rgb[2] << std::endl;
  actor->GetTextProperty()->SetColor(rgb);

  auto renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();

  renderWindow->SetSize(width, height);
  renderWindow->AddRenderer(renderer);

  auto interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);

  renderWindow->Render();
  interactor->Initialize();
  interactor->Start();

  return EXIT_SUCCESS;
}

namespace {
void ChooseContrastingColor(double* rgbIn, double* rgbOut,
                            const double threshold,
                            const std::string& lightColor,
                            const std::string& darkColor)
{
  auto colors =
    vtkSmartPointer<vtkNamedColors>::New();

  double hsv[3];
  // If the value is <= threshold, use a light color, otherwise use a dark color
  vtkMath::RGBToHSV(rgbIn, hsv);
  if (hsv[2] <= threshold)
  {
    colors->GetColor(lightColor.c_str(), rgbOut[0], rgbOut[1], rgbOut[2]);
  }
  else
  {
    colors->GetColor(darkColor.c_str(), rgbOut[0], rgbOut[1], rgbOut[2]);
  }
}
} // namespace
