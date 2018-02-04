#include <vtkColor.h>
#include <vtkColorSeries.h>
#include <vtkDataObject.h>
#include <vtkFieldData.h>
#include <vtkFloatArray.h>
#include <vtkIdList.h>
#include <vtkLegendBoxActor.h>
#include <vtkMath.h>
#include <vtkNamedColors.h>
#include <vtkPieChartActor.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkProperty2D.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkTextProperty.h>

#include <map>

int main( int /*argc*/, char * /*argv*/ [] )
{
  typedef std::map<std::string, int>  DataContainer;
  DataContainer movies;

  movies["Comedy"] = 27;
  movies["Action"] = 18;
  movies["Romance"] = 14;
  movies["Drama"] = 14;
  movies["Horror"] = 11;
  movies["Foreign"] = 8;
  movies["Scifi"] = 8;

  int numTuples = static_cast<int>(movies.size());

  vtkSmartPointer<vtkFloatArray> bitter  =
    vtkSmartPointer<vtkFloatArray>::New();
  bitter->SetNumberOfTuples(numTuples);

  DataContainer::iterator m;
  int i = 0;
  for (m = movies.begin(); m != movies.end(); ++m)
  {
    bitter->SetTuple1(i++, m->second);
  }


  vtkSmartPointer<vtkDataObject> dobj =
    vtkSmartPointer<vtkDataObject>::New();
  dobj->GetFieldData()->AddArray(bitter);

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkPieChartActor> actor =
    vtkSmartPointer<vtkPieChartActor>::New();
  actor->SetInputData(dobj);
  actor->SetTitle("Movie Watching");
  actor->GetPositionCoordinate()->SetValue(0.05,0.1,0.0);
  actor->GetPosition2Coordinate()->SetValue(0.95,0.85,0.0);
  actor->GetProperty()->SetColor(0, 0, 0);
  actor->GetProperty()->SetLineWidth(2);
  actor->GetLabelTextProperty()->SetFontSize(18);
  actor->GetLegendActor()->SetNumberOfEntries(numTuples);

  vtkSmartPointer<vtkColorSeries> colorSeries =
    vtkSmartPointer<vtkColorSeries>::New();
  colorSeries->SetColorScheme(vtkColorSeries::BREWER_QUALITATIVE_PASTEL2);
  i = 0;
  for (m = movies.begin(); m != movies.end(); ++m)
  {
    vtkColor3ub rgb = colorSeries->GetColorRepeating(i);
    actor->SetPieceColor(i,
                         static_cast<double>(rgb.GetRed()) / 255.0,
                         static_cast<double>(rgb.GetGreen()) / 255.0,
                         static_cast<double>(rgb.GetBlue()) / 255.0);
    actor->SetPieceLabel(i++, m->first.c_str());
  }
  actor->LegendVisibilityOn();
  // Set text colors (same as actor for backward compat with test)
  actor->GetTitleTextProperty()->SetColor(colors->GetColor3d("Banana").GetData());
  actor->GetTitleTextProperty()->SetFontSize(40);
  actor->GetLabelTextProperty()->SetColor(colors->GetColor3d("Bisque").GetData());
  actor->GetLabelTextProperty()->SetFontSize(24);

  // Create the RenderWindow, Renderer and both Actors
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  ren1->AddActor(actor);
  ren1->SetBackground(colors->GetColor3d("SlateGray").GetData());
  renWin->SetSize(1024, 512);

  // render the image
  renWin->Render();

  iren->Start();

  return EXIT_SUCCESS;
}
