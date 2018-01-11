#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCellType.h>
#include <vtkDataSetMapper.h>
#include <vtkNamedColors.h>
#include <vtkPoints.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkUnstructuredGrid.h>

int main( int, char *[] )
{
  int i;
  static double x[27][3]={{0,0,0}, {1,0,0}, {2,0,0}, {0,1,0}, {1,1,0}, {2,1,0},
                          {0,0,1}, {1,0,1}, {2,0,1}, {0,1,1}, {1,1,1}, {2,1,1},
                          {0,1,2}, {1,1,2}, {2,1,2}, {0,1,3}, {1,1,3}, {2,1,3},
                          {0,1,4}, {1,1,4}, {2,1,4}, {0,1,5}, {1,1,5}, {2,1,5},
                          {0,1,6}, {1,1,6}, {2,1,6}};
  static vtkIdType pts[12][8]={{0, 1, 4, 3, 6, 7, 10, 9},
                               {1, 2, 5, 4, 7, 8, 11, 10},
                               {6, 10, 9, 12, 0, 0, 0, 0},
                               {8, 11, 10, 14, 0, 0, 0, 0},
                               {16, 17, 14, 13, 12, 15, 0, 0},
                               {18, 15, 19, 16, 20, 17, 0, 0},
                               {22, 23, 20, 19, 0, 0, 0, 0},
                               {21, 22, 18, 0, 0, 0, 0, 0},
                               {22, 19, 18, 0, 0, 0, 0, 0},
                               {23, 26, 0, 0, 0, 0, 0, 0},
                               {21, 24, 0, 0, 0, 0, 0, 0},
                               {25, 0, 0, 0, 0, 0, 0, 0}};

  
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  for (i=0; i<27; i++) points->InsertPoint(i,x[i]);
  
  vtkSmartPointer<vtkUnstructuredGrid> ugrid =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ugrid->Allocate(100);
  ugrid->InsertNextCell(VTK_HEXAHEDRON, 8, pts[0]);
  ugrid->InsertNextCell(VTK_HEXAHEDRON, 8, pts[1]);
  ugrid->InsertNextCell(VTK_TETRA, 4, pts[2]);
  ugrid->InsertNextCell(VTK_TETRA, 4, pts[3]);
  ugrid->InsertNextCell(VTK_POLYGON, 6, pts[4]);
  ugrid->InsertNextCell(VTK_TRIANGLE_STRIP, 6, pts[5]);
  ugrid->InsertNextCell(VTK_QUAD, 4, pts[6]);
  ugrid->InsertNextCell(VTK_TRIANGLE, 3, pts[7]);
  ugrid->InsertNextCell(VTK_TRIANGLE, 3, pts[8]);
  ugrid->InsertNextCell(VTK_LINE, 2, pts[9]);
  ugrid->InsertNextCell(VTK_LINE, 2, pts[10]);
  ugrid->InsertNextCell(VTK_VERTEX, 1, pts[11]);

  ugrid->SetPoints(points);

  vtkSmartPointer<vtkDataSetMapper> ugridMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  ugridMapper->SetInputData(ugrid);

  vtkSmartPointer<vtkActor> ugridActor =
    vtkSmartPointer<vtkActor>::New();
  ugridActor->SetMapper(ugridMapper);
  ugridActor->GetProperty()->SetColor(colors->GetColor3d("Peacock").GetData());
  ugridActor->GetProperty()->EdgeVisibilityOn();

  renderer->AddActor(ugridActor);
  renderer->SetBackground(colors->GetColor3d("Beige").GetData());

  renderer->ResetCamera();
  renderer->GetActiveCamera()->Elevation(60.0);
  renderer->GetActiveCamera()->Azimuth(30.0);
  renderer->GetActiveCamera()->Dolly(1.2);
  
  renWin->SetSize(640, 480);

  // interact with data
  renWin->Render();

  iren->Start();

  return EXIT_SUCCESS;
}
