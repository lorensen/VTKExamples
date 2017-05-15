#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>
#include <vtkStripper.h>
#include <vtkCutter.h>
#include <vtkSplineFilter.h>
#include <vtkSpline.h>
#include <vtkPlane.h>
#include <vtkSphereSource.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkPolyData.h>
#include <vtkTubeFilter.h>
#include <vtkKochanekSpline.h>

int main (int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> polyData =
    vtkSmartPointer<vtkPolyData>::New();
  if (argc > 1)
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName ( argv[1] );
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    vtkSmartPointer<vtkSphereSource> modelSource =
      vtkSmartPointer<vtkSphereSource>::New();
    modelSource->Update();
    polyData = modelSource->GetOutput();
  }

  vtkSmartPointer<vtkPlane> plane =
    vtkSmartPointer<vtkPlane>::New();
  plane->SetNormal(0, 0, 1);

  vtkSmartPointer<vtkCutter> cutter =
    vtkSmartPointer<vtkCutter>::New();
#if VTK_MAJOR_VERSION <= 5
  cutter->SetInput(polyData);
#else
  cutter->SetInputData(polyData);
#endif
  cutter->SetCutFunction(plane);
  cutter->GenerateValues(1, 0.0, 0.0);

  vtkSmartPointer<vtkPolyDataMapper> modelMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  modelMapper->SetInput(polyData);
#else
  modelMapper->SetInputData(polyData);
#endif

  vtkSmartPointer<vtkActor> model =
    vtkSmartPointer<vtkActor>::New();
  model->SetMapper(modelMapper);

  vtkSmartPointer<vtkStripper> stripper =
    vtkSmartPointer<vtkStripper>::New();
  stripper->SetInputConnection(cutter->GetOutputPort());

  vtkSmartPointer<vtkKochanekSpline> spline =
    vtkSmartPointer<vtkKochanekSpline>::New();
  spline->SetDefaultTension(.5);

  vtkSmartPointer<vtkSplineFilter> sf =
    vtkSmartPointer<vtkSplineFilter>::New();
  sf->SetInputConnection(stripper->GetOutputPort());
  sf->SetSubdivideToSpecified();
  sf->SetNumberOfSubdivisions(50);
  sf->SetSpline(spline);
  sf->GetSpline()->ClosedOn();

  vtkSmartPointer<vtkTubeFilter> tubes =
    vtkSmartPointer<vtkTubeFilter>::New();
  tubes->SetInputConnection( sf->GetOutputPort());
  tubes->SetNumberOfSides(8);
  tubes->SetRadius(.02);

  vtkSmartPointer<vtkPolyDataMapper> linesMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  linesMapper->SetInputConnection(tubes->GetOutputPort());
  linesMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> lines =
    vtkSmartPointer<vtkActor>::New();
  lines->SetMapper(linesMapper);

  vtkSmartPointer<vtkRenderer> ren =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();

  renWin->AddRenderer(ren);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Add the actors to the renderer
  ren->AddActor(lines);
  ren->SetBackground(0.1, 0.2, 0.4);

  // This starts the event loop and as a side effect causes an initial
  // render.
  renWin->Render();
  iren->Start();


  // Extract the lines from the polydata
  vtkIdType numberOfLines = cutter->GetOutput()->GetNumberOfLines();


  std::cout << "-----------Lines without using vtkStripper" << std::endl;
  std::cout << "There are "
            << numberOfLines
            << " lines in the polydata" << std::endl;

  numberOfLines = stripper->GetOutput()->GetNumberOfLines();
  vtkPoints *points = stripper->GetOutput()->GetPoints();
  vtkCellArray *cells = stripper->GetOutput()->GetLines();

  std::cout << "-----------Lines using vtkStripper" << std::endl;
  std::cout << "There are "
            << numberOfLines
            << " lines in the polydata" << std::endl;

  vtkIdType *indices;
  vtkIdType numberOfPoints;
  unsigned int lineCount = 0;
  for (cells->InitTraversal();
       cells->GetNextCell(numberOfPoints, indices);
       lineCount++)
  {
    std::cout << "Line " << lineCount << ": " << std::endl;
    for (vtkIdType i = 0; i < numberOfPoints; i++)
    {
      double point[3];
      points->GetPoint(indices[i], point);
      std::cout << "\t("
                << point[0] << ", "
                << point[1] << ", "
                << point[2] << ")" << std::endl;
    }
  }
  return EXIT_SUCCESS;
}
