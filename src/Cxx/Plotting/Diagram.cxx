#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkObjectFactory.h>
#include <vtkContext2D.h>
#include <vtkContextItem.h>
#include <vtkContextActor.h>
#include <vtkContextScene.h>
#include <vtkPen.h>
#include <vtkBrush.h>
#include <vtkTextProperty.h>
#include <vtkOpenGLContextDevice2D.h>
#include <vtkStdString.h>
#include <vtkColorSeries.h>
#include <vtkNamedColors.h>

//----------------------------------------------------------------------------
class APIDiagram : public vtkContextItem
{
public:
  static APIDiagram *New();
  vtkTypeMacro(APIDiagram, vtkContextItem);
  APIDiagram()
  {
    this->ColorSeries = vtkSmartPointer<vtkColorSeries>::New();
    this->ColorSchemeName = "Brewer Diverging Spectral (7)";
    this->ColorSeries->SetColorSchemeByName(this->ColorSchemeName);
  }
  // Paint event for the chart, called whenever the chart needs to be drawn
  virtual bool Paint(vtkContext2D *painter);
  void SetColorSchemeName (std::string seriesName)
  {
    this->ColorSeries->SetColorSchemeByName(seriesName);
    if (this->ColorSeries->GetColorScheme() > vtkColorSeries::BREWER_QUALITATIVE_SET3)
    {
      this->PrintColorSchemes();
    }
  }
  void PrintColorSchemes(ostream& os = std::cout)
  {
    int saveId = this->ColorSeries->GetColorScheme();
    for (unsigned int i = 0; i < vtkColorSeries::BREWER_QUALITATIVE_SET3; ++i)
    {
      this->ColorSeries->SetColorScheme(i);
      os << this->ColorSeries->GetColorSchemeName() << std::endl;
    }
    this->ColorSeries->SetColorScheme(saveId);
  }
protected:
  vtkSmartPointer<vtkColorSeries> ColorSeries;
  std::string ColorSchemeName;
};

//----------------------------------------------------------------------------
int main( int argc, char *argv[] )
{
  std::string colorSchemeName = "Brewer Diverging Brown-Blue-Green (7)";
  if (argc > 1)
  {
    colorSchemeName = std::string(argv[1]);
  }

  // Set up a 2D chart actor, APIDiagram object andn add them to the renderer
  vtkNew<APIDiagram>  diagram;
  diagram->SetColorSchemeName(colorSchemeName);

  vtkNew<vtkContextActor>  actor;
  actor->GetScene()->AddItem(diagram);

  vtkNew<vtkNamedColors> colors;
  vtkNew<vtkRenderer>  renderer;
  renderer->SetBackground(colors->GetColor3d("Tan").GetData());

  vtkNew<vtkRenderWindow>  renderWindow;
  renderWindow->SetSize(800, 600);
  renderWindow->AddRenderer(renderer);
  renderer->AddActor(actor);

  vtkNew<vtkRenderWindowInteractor>  interactor;
  interactor->SetRenderWindow(renderWindow);
  renderWindow->SetMultiSamples(0);
  renderWindow->Render();

  interactor->Start();

  return EXIT_SUCCESS;
}

// Make our new derived class to draw a diagram
vtkStandardNewMacro(APIDiagram);
// This function draws our API diagram
bool APIDiagram::Paint(vtkContext2D *painter)
{
  // Drawing a hard wired diagram 800x600 as a demonstration of the 2D API
  painter->GetTextProp()->SetVerticalJustificationToCentered();
  painter->GetTextProp()->SetJustificationToCentered();
  painter->GetTextProp()->SetColor(0.0, 0.0, 0.0);
  painter->GetTextProp()->SetFontSize(24);
  painter->GetPen()->SetColor(0, 0, 0);

  unsigned int c = 0;
  painter->GetBrush()->SetColor((this->ColorSeries->GetColorRepeating(c)).GetData());
  c++;

  painter->DrawRect(100, 50, 200, 100);
  painter->DrawString(200, 100, "OpenGL");

  painter->GetBrush()->SetColor((this->ColorSeries->GetColorRepeating(c)).GetData());
  c++;
  painter->DrawRect(300, 50, 200, 100);
  painter->DrawString(400, 100, "Others?");

  painter->GetBrush()->SetColor((this->ColorSeries->GetColorRepeating(c)).GetData());
  c++;
  painter->DrawRect(500, 50, 200, 100);
  painter->DrawString(600, 100, "Others?");

  painter->GetBrush()->SetColor((this->ColorSeries->GetColorRepeating(c)).GetData());
  c++;
  painter->DrawRect(100, 150, 600, 100);
  painter->DrawString(400, 200, "2D API");

  painter->GetBrush()->SetColor((this->ColorSeries->GetColorRepeating(c)).GetData());
  c++;
  painter->DrawRect(100, 250, 600, 200);
  painter->DrawString(400, 400, "Canvas API");

  painter->GetBrush()->SetColor((this->ColorSeries->GetColorRepeating(c)).GetData());
  c++;
  painter->DrawRect(100, 250, 300, 100);
  painter->DrawString(250, 300, "Point Mark");

  painter->GetBrush()->SetColor((this->ColorSeries->GetColorRepeating(c)).GetData());
  painter->DrawRect(100, 450, 600, 100);
  painter->DrawString(400, 500, "Canvas View");

return true;
}
