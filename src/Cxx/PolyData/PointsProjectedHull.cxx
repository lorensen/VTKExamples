#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkGlyph3DMapper.h>
#include <vtkPointSource.h>
#include <vtkPoints.h>
#include <vtkPointsProjectedHull.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyLine.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkTubeFilter.h>
#include <vtkXMLPolyDataWriter.h>

#include <vtkNamedColors.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetPhiResolution(21);
  sphere->SetThetaResolution(21);
  sphere->SetRadius(.01);

  vtkSmartPointer<vtkPointSource> pointSource =
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(40);
  pointSource->Update();

  // Setup actor and mapper
  vtkSmartPointer<vtkGlyph3DMapper> pointMapper =
    vtkSmartPointer<vtkGlyph3DMapper>::New();
  pointMapper->SetInputConnection(pointSource->GetOutputPort());
  pointMapper->SetSourceConnection(sphere->GetOutputPort());

  vtkSmartPointer<vtkActor> pointActor =
    vtkSmartPointer<vtkActor>::New();
  pointActor->SetMapper(pointMapper);
  pointActor->GetProperty()->SetColor(colors->GetColor3d("Peacock").GetData());

  vtkSmartPointer<vtkPointsProjectedHull> points =
    vtkSmartPointer<vtkPointsProjectedHull>::New();
  points->DeepCopy(pointSource->GetOutput()->GetPoints());

  int xSize = points->GetSizeCCWHullX();
  std::cout << "xSize: " << xSize << std::endl;

  double* pts = new double[xSize*2];

  points->GetCCWHullX(pts,xSize);

  vtkSmartPointer<vtkPoints> xHullPoints =
    vtkSmartPointer<vtkPoints>::New();
  for(int i = 0; i < xSize; i++)
  {
    double yval = pts[2*i];
    double zval = pts[2*i + 1];
    std::cout << "(y,z) value of point " << i << " : ("
              << yval << " , " << zval << ")" << std::endl;
    xHullPoints->InsertNextPoint(0.0, yval, zval);
  }
  // Insert the first point again to close the loop
  xHullPoints->InsertNextPoint(0.0, pts[0], pts[1]);

  // Display the x hull
  vtkSmartPointer<vtkPolyLine> xPolyLine =
    vtkSmartPointer<vtkPolyLine>::New();
  xPolyLine->GetPointIds()->SetNumberOfIds(xHullPoints->GetNumberOfPoints());

  for(vtkIdType i = 0; i < xHullPoints->GetNumberOfPoints(); i++)
  {
    xPolyLine->GetPointIds()->SetId(i,i);
  }

  // Create a cell array to store the lines in and add the lines to it
  vtkSmartPointer<vtkCellArray> cells =
    vtkSmartPointer<vtkCellArray>::New();
  cells->InsertNextCell(xPolyLine);

  // Create a polydata to store everything in
  vtkSmartPointer<vtkPolyData> polyData =
    vtkSmartPointer<vtkPolyData>::New();

  // Add the points to the dataset
  polyData->SetPoints(xHullPoints);

  // Add the lines to the dataset
  polyData->SetLines(cells);

  // Create tubes around the lines
  vtkSmartPointer<vtkTubeFilter> tubes =
    vtkSmartPointer<vtkTubeFilter>::New();
  tubes->SetInputData(polyData);
  tubes->SetRadius(.005);
  tubes->SetNumberOfSides(21);

  // Setup actor and mapper
  vtkSmartPointer<vtkPolyDataMapper> xHullMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  xHullMapper->SetInputConnection(tubes->GetOutputPort());

  vtkSmartPointer<vtkActor> xHullActor =
    vtkSmartPointer<vtkActor>::New();
  xHullActor->SetMapper(xHullMapper);
  xHullActor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());

  // Setup render window, renderer, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->SetBackground(colors->GetColor3d("Burlywood").GetData());
  renderer->AddActor(xHullActor);
  renderer->AddActor(pointActor);

  // Rotate camera
  renderer->GetActiveCamera()->Azimuth(90);
  renderer->ResetCamera();

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
