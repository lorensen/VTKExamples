#include <vtkActor.h>
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkLine.h>
#include <vtkNamedColors.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkUnsignedCharArray.h>

// For compatibility with new VTK generic data arrays
#ifdef vtkGenericDataArray_h
#define InsertNextTupleValue InsertNextTypedTuple
#endif

int main(int, char *[])
{
  // Create the polydata where we will store all the geometric data
  vtkSmartPointer<vtkPolyData> linesPolyData =
    vtkSmartPointer<vtkPolyData>::New();
  
  
  // Create three points
  double origin[3] = { 0.0, 0.0, 0.0 };
  double p0[3] = { 1.0, 0.0, 0.0 };
  double p1[3] = { 0.0, 1.0, 0.0 };
  
  // Create a vtkPoints container and store the points in it
  vtkSmartPointer<vtkPoints> pts =
    vtkSmartPointer<vtkPoints>::New();
  pts->InsertNextPoint(origin);
  pts->InsertNextPoint(p0);
  pts->InsertNextPoint(p1);
  
  // Add the points to the polydata container
  linesPolyData->SetPoints(pts);
  
  
  // Create the first line (between Origin and P0)
  vtkSmartPointer<vtkLine> line0 =
    vtkSmartPointer<vtkLine>::New();
  line0->GetPointIds()->SetId(0, 0); // the second 0 is the index of the Origin in linesPolyData's points
  line0->GetPointIds()->SetId(1, 1); // the second 1 is the index of P0 in linesPolyData's points
  
  // Create the second line (between Origin and P1)
  vtkSmartPointer<vtkLine> line1 =
    vtkSmartPointer<vtkLine>::New();
  line1->GetPointIds()->SetId(0, 0); // the second 0 is the index of the Origin in linesPolyData's points
  line1->GetPointIds()->SetId(1, 2); // 2 is the index of P1 in linesPolyData's points
  
  // Create a vtkCellArray container and store the lines in it
  vtkSmartPointer<vtkCellArray> lines =
    vtkSmartPointer<vtkCellArray>::New();
  lines->InsertNextCell(line0);
  lines->InsertNextCell(line1);
  
  // Add the lines to the polydata container
  linesPolyData->SetLines(lines);
  
  vtkSmartPointer<vtkNamedColors> namedColors =
    vtkSmartPointer<vtkNamedColors>::New();
  
  // Create a vtkUnsignedCharArray container and store the colors in it
  vtkSmartPointer<vtkUnsignedCharArray> colors =
    vtkSmartPointer<vtkUnsignedCharArray>::New();
  colors->SetNumberOfComponents(3);
  colors->InsertNextTupleValue(namedColors->GetColor3ub("Tomato").GetData());
  colors->InsertNextTupleValue(namedColors->GetColor3ub("Mint").GetData());
  
  // Color the lines.
  // SetScalars() automatically associates the values in the data array passed as parameter
  // to the elements in the same indices of the cell data array on which it is called.
  // This means the first component (red) of the colors array
  // is matched with the first component of the cell array (line 0)
  // and the second component (green) of the colors array
  // is matched with the second component of the cell array (line 1)
  linesPolyData->GetCellData()->SetScalars(colors);
  
  // Setup the visualization pipeline
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
   mapper->SetInputData(linesPolyData);
  
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetLineWidth(4);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->SetBackground(namedColors->GetColor3d("SlateGray").GetData());

  vtkSmartPointer<vtkRenderWindow> window =
    vtkSmartPointer<vtkRenderWindow>::New();
  window->SetWindowName("Colored Lines");
  window->AddRenderer(renderer);
  
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(window);
  
  // Visualize
  window->Render();
  interactor->Start();
  
  return EXIT_SUCCESS;
}
