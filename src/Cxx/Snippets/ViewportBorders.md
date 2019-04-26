### Description

Draw the borders of a vtkRenderer's viewports.

To use the snippet, click the *Copy to clipboard* at the upper left of the code blocks.

### Declaration Section

``` c++
#include <vtkRenderer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolyLines.h>
#include <vtkPolyData.h>
#include <vtkCoordinate.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkActor2D.h>
#include <vtkProperty.h>
#include <vtkProperty2D.h>

namespace
{
void ViewportBorders(vtkSmartPointer<vtkRenderer> &renderer,
                     double *color,
                     bool last = false);
}
```

### Implementation Section

``` c++
namespace
{
// Draw the borders of a renderer's viewport
void ViewportBorders(vtkSmartPointer<vtkRenderer> &renderer,
                     double *color,
                     bool last)
{
  // points start at upper right and proceed anti-clockwise
  auto points = vtkSmartPointer<vtkPoints>::New();
  points->SetNumberOfPoints(4);
  points->InsertPoint(0, 1, 1, 0);
  points->InsertPoint(1, 0, 1, 0);
  points->InsertPoint(2, 0, 0, 0);
  points->InsertPoint(3, 1, 0, 0);

  // create cells, and lines
  auto cells =  vtkSmartPointer<vtkCellArray>::New();
  cells->Initialize(); 

  auto lines = vtkSmartPointer<vtkPolyLine>::New();

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
  auto poly = vtkSmartPointer<vtkPolyData>::New();
  poly->Initialize(); 
  poly->SetPoints(points); 
  poly->SetLines(cells); 

  // use normalized viewport coordinates since
  // they are independent of window size
  auto coordinate = vtkSmartPointer<vtkCoordinate>::New();
  coordinate->SetCoordinateSystemToNormalizedViewport(); 

  auto mapper = vtkSmartPointer<vtkPolyDataMapper2D>::New();
  mapper->SetInputData(poly); 
  mapper->SetTransformCoordinate(coordinate); 

  auto actor = vtkSmartPointer<vtkActor2D>::New();
  actor->SetMapper(mapper); 
  actor->GetProperty()->SetColor(color);
  // line width should be at least 2 to be visible at extremes

  actor->GetProperty()->SetLineWidth(4.0); // Line Width 

  renderer->AddViewProp(actor);
}
} // namespace

```