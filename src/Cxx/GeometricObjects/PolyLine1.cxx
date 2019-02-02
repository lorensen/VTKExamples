#include <vtkActor.h>
#include <vtkCellArray.h>
#include <vtkMath.h>
#include <vtkNamedColors.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <algorithm>
#include <array>
#include <cmath>
#include <vector>

int main(int, char* [])
{

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Set the background color.
  std::array<unsigned char , 4> bkg{{26, 51, 102, 255}};
    colors->SetColor("BkgColor", bkg.data());

  // vtkPoints represents 3D points. The data model for vtkPoints is an array of
  // vx-vy-vz triplets accessible by (point or cell) id.
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->SetNumberOfPoints(6);
  double c = std::cos(vtkMath::Pi() / 6); // helper variable
  points->SetPoint(0, 0.0, -1.0, 0.0);
  points->SetPoint(1, c, -0.5, 0.0);
  points->SetPoint(2, c, 0.5, 0.0);
  points->SetPoint(3, 0.0, 1.0, 0.0);
  points->SetPoint(4, -c, 0.5, 0.0);
  points->SetPoint(5, -c, -0.5, 0.0);

  // vtkCellArray is a supporting object that explicitly represents cell
  // connectivity.
  // The cell array structure is a raw integer list of the form:
  // (n,id1,id2,...,idn, n,id1,id2,...,idn, ...) where n is the number of points
  // in
  // the cell, and id is a zero-offset index into an associated point list.
  vtkSmartPointer<vtkCellArray> lines =
    vtkSmartPointer<vtkCellArray>::New();
  lines->InsertNextCell(7);
  lines->InsertCellPoint(0);
  lines->InsertCellPoint(1);
  lines->InsertCellPoint(2);
  lines->InsertCellPoint(3);
  lines->InsertCellPoint(4);
  lines->InsertCellPoint(5);
  lines->InsertCellPoint(0);

  // vtkPolyData is a data object that is a concrete implementation of
  // vtkDataSet.
  // vtkPolyData represents a geometric structure consisting of vertices, lines,
  // polygons, and/or triangle strips
  vtkSmartPointer<vtkPolyData> polygon =
    vtkSmartPointer<vtkPolyData>::New();
  polygon->SetPoints(points);
  polygon->SetLines(lines);

  // vtkPolyDataMapper is a class that maps polygonal data (i.e., vtkPolyData)
  // to graphics primitives
  vtkSmartPointer<vtkPolyDataMapper> polygonMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  polygonMapper->SetInputData(polygon);
  polygonMapper->Update();

  // Create an actor to represent the polygon. The actor orchestrates rendering
  // of
  // the mapper's graphics primitives. An actor also refers to properties via a
  // vtkProperty instance, and includes an internal transformation matrix. We
  // set this actor's mapper to be polygonMapper which we created above.
  vtkSmartPointer<vtkActor> polygonActor =
    vtkSmartPointer<vtkActor>::New();
  polygonActor->SetMapper(polygonMapper);
  polygonActor->GetProperty()->SetColor(
    colors->GetColor3d("AliceBlue").GetData());

  // Create the Renderer and assign actors to it. A renderer is like a
  // viewport. It is part or all of a window on the screen and it is
  // responsible for drawing the actors it has.  We also set the
  // background color here.
  vtkSmartPointer<vtkRenderer> ren =
    vtkSmartPointer<vtkRenderer>::New();
  ren->AddActor(polygonActor);
  ren->SetBackground(colors->GetColor3d("BkgColor").GetData());

  // Automatically set up the camera based on the visible actors.
  // The camera will reposition itself to view the center point of the actors,
  // and move along its initial view plane normal
  // (i.e., vector defined from camera position to focal point) so that all of
  // the
  // actors can be seen.
  ren->ResetCamera();

  // Finally we create the render window which will show up on the screen
  // We put our renderer into the render window using AddRenderer. We
  // also set the size to be 300 pixels by 300.
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->SetWindowName("OrderedPolyLine");
  renWin->AddRenderer(ren);
  renWin->SetSize(300, 300);

  // The vtkRenderWindowInteractor class watches for events (e.g., keypress,
  // mouse) in the vtkRenderWindow. These events are translated into
  // event invocations that VTK understands (see VTK/Common/vtkCommand.h
  // for all events that VTK processes). Then observers of these VTK
  // events can process them as appropriate.
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);
  renWin->Render();
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;

}
