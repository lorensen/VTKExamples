#include <vtkSmartPointer.h>

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkSphereSource.h>

#include <vtkMath.h>
#include <vtkCoordinate.h>
#include <vtkTextProperty.h>
#include <vtkTextActor.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

#include <vtkNamedColors.h>

#include <vtkNamedColors.h>
namespace
{
// Given a color, find a contrasting color. If the goven color is "light",
// use the lightColor otherwise use the darkColor
void ChooseContrastingColor(double *rgbIn,
                            double *rgbOut,
                            double threshold = .5,
                            const std::string lightColor = "white",
                            const std::string darkColor = "black");
}

namespace
{
void ViewportBorder(vtkSmartPointer<vtkRenderer> &renderer,
                    double *color,
                    bool last = false);
}
int main (int argc, char *argv[])
{
  vtkMath::RandomSeed(4355412); // for test result consistency

  double threshold = .5;
  std::string lightColor = "white";
  std::string darkColor = "black";
  if (argc > 1)
  {
    threshold = atof(argv[1]);
  }
  if (argc > 2)
  {
    lightColor = argv[2];
  }
  if (argc > 3)
  {
    darkColor = argv[3];
  }
  // Visualize
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  std::vector<vtkSmartPointer<vtkRenderer>> renderers;
  unsigned int xGridDimensions = 10;
  unsigned int yGridDimensions = 10;
  for (int i = 0; i < xGridDimensions  * yGridDimensions; ++i)
  {
    // Create textActors
    vtkSmartPointer<vtkTextActor> textActor =
      vtkSmartPointer<vtkTextActor>::New();
    textActor->GetTextProperty()->SetJustificationToCentered();
    textActor->GetTextProperty()->SetVerticalJustificationToCentered();
    textActor->SetInput("Text");
    textActor->SetPosition(50, 50);
    textActor->GetTextProperty()->BoldOff();
    textActor->GetTextProperty()->SetFontSize(20);

    // Setup renderer
    vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(textActor);;
    double hsv[3];
    hsv[0] = vtkMath::Random(0.0, 1.0);
    hsv[1] = vtkMath::Random(0.0, 1.0);
    hsv[2] = vtkMath::Random(0.0, 1.0);
    double rgb[3];
    vtkMath::HSVToRGB(hsv, rgb);
    renderer->SetBackground(rgb);
  // Compute a good color for text on the renderer background
  ChooseContrastingColor(renderer->GetBackground(),
                         rgb,
                         threshold,
                         lightColor,
                         darkColor);
  textActor->GetTextProperty()->SetColor(rgb);
    renderers.push_back(renderer);
    renderWindow->AddRenderer(renderer);
  }

  // Setup viewports for the renderers
  int rendererSize = 100;
  renderWindow->SetSize(
    rendererSize * xGridDimensions, rendererSize * yGridDimensions);
  int index;
  for (int row = 0; row < static_cast<int>(yGridDimensions); row++)
  {
    for (int col = 0; col < static_cast<int>(xGridDimensions); col++)
    {
      int index = row * xGridDimensions + col;
      // (xmin, ymin, xmax, ymax)
      double viewport[4] = {
        static_cast<double>(col) * rendererSize /
        (xGridDimensions * rendererSize),
        static_cast<double>(yGridDimensions - (row + 1)) * rendererSize /
        (yGridDimensions * rendererSize),
        static_cast<double>(col + 1) * rendererSize /
        (xGridDimensions * rendererSize),
        static_cast<double>(yGridDimensions - row) * rendererSize /
        (yGridDimensions * rendererSize)};
      renderers[index]->SetViewport(viewport);
      ViewportBorder(renderers[index],
                     colors->GetColor3d("White").GetData(),
                     col == xGridDimensions);
    }
  }
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

#include <vtkRenderer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkPolyLine.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkCoordinate.h>
#include <vtkActor2D.h>
#include <vtkProperty2D.h>
namespace
{
// draw the borders of a renderer's viewport
void ViewportBorder(vtkSmartPointer<vtkRenderer> &renderer,
                    double *color,
                    bool last)
{
  // points start at upper right and proceed anti-clockwise
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->SetNumberOfPoints(4);
  points->InsertPoint(0, 1, 1, 0);
  points->InsertPoint(1, 0, 1, 0);
  points->InsertPoint(2, 0, 0, 0);
  points->InsertPoint(3, 1, 0, 0);

  // create cells, and lines
  vtkSmartPointer<vtkCellArray> cells =
    vtkSmartPointer<vtkCellArray>::New();
  cells->Initialize(); 

  vtkSmartPointer<vtkPolyLine> lines =
    vtkSmartPointer<vtkPolyLine>::New();

  // only draw last line if this is the last viewport
  // this prevents double vertical lines at right border
  // if different colors are used for each border, then do
  // not specify last
  if (last)
  {
    lines->GetPointIds()->SetNumberOfIds(5);
  }
  else
  {
  lines->GetPointIds()->SetNumberOfIds(4);
  }
  for(unsigned int i = 0; i < 4; ++i)
  {
    lines->GetPointIds()->SetId(i,i);
  }
  if (last)
  {
    lines->GetPointIds()->SetId(4, 0);
  }
  cells->InsertNextCell(lines);

  // now make tge polydata and display it
  vtkSmartPointer<vtkPolyData> poly =
    vtkSmartPointer<vtkPolyData>::New();
  poly->Initialize(); 
  poly->SetPoints(points); 
  poly->SetLines(cells); 

  // use normalized viewport coordinates since
  // they are independent of window size
  vtkSmartPointer<vtkCoordinate> coordinate =
    vtkSmartPointer<vtkCoordinate>::New();
  coordinate->SetCoordinateSystemToNormalizedViewport(); 

  vtkSmartPointer<vtkPolyDataMapper2D> mapper =
    vtkSmartPointer<vtkPolyDataMapper2D>::New();
  mapper->SetInputData(poly); 
  mapper->SetTransformCoordinate(coordinate); 

  vtkSmartPointer<vtkActor2D> actor =
    vtkSmartPointer<vtkActor2D>::New();
  actor->SetMapper(mapper); 
  actor->GetProperty()->SetColor(color);
  // line width should be at least 2 to be visible at extremes

  actor->GetProperty()->SetLineWidth(4.0); // Line Width 

  renderer->AddViewProp(actor);
}
}
namespace
{
void ChooseContrastingColor(double *rgbIn,
                            double *rgbOut,
                            double threshold,
                            const std::string lightColor,
                            const std::string darkColor)
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  double hsv[3];
  // If the value is <= .5, use a light color, otherwise use a dark color
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
}
