#include <vtkProperty.h>
#include <vtkCellArray.h>
#include<vtkPolyDataMapper.h>
#include<vtkDelaunay3D.h>
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkUnstructuredGrid.h>
#include <vtkVertexGlyphFilter.h>

int main(int , char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> bigSphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  bigSphereSource->SetCenter(0.0, 0.0, 0.0);
  bigSphereSource->SetRadius(4);
  bigSphereSource->SetThetaResolution(20);
  bigSphereSource->SetPhiResolution(20);
  bigSphereSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> bigSphereMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  bigSphereMapper->SetInputConnection(bigSphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> bigSphereActor =
    vtkSmartPointer<vtkActor>::New();
  bigSphereActor->SetMapper(bigSphereMapper);
  bigSphereActor->GetProperty()->SetOpacity(.5);

  vtkSmartPointer<vtkSphereSource> smallSphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  smallSphereSource->SetCenter(1, 2, 1);
  smallSphereSource->SetRadius(2);
  smallSphereSource->SetThetaResolution(20);
  smallSphereSource->SetPhiResolution(20);
  smallSphereSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> smallSphereMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  smallSphereMapper->SetInputConnection(smallSphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> smallSphereActor =
    vtkSmartPointer<vtkActor>::New();
  smallSphereActor->SetMapper(smallSphereMapper);

  vtkSmartPointer<vtkPoints> pointsInside = vtkSmartPointer<vtkPoints>::New();
  vtkSmartPointer<vtkPolyData> polyDataInside = vtkSmartPointer<vtkPolyData>::New();
  double point[3];

  vtkSmartPointer<vtkDelaunay3D> delaunay3D = vtkSmartPointer<vtkDelaunay3D>::New();
  delaunay3D->SetInputConnection (bigSphereSource->GetOutputPort());
  delaunay3D->Update();

  for(vtkIdType i = 0; i < smallSphereSource->GetOutput()->GetNumberOfPoints(); i++)
  {
    smallSphereSource->GetOutput()->GetPoint(i,point);

    double pcoords[3];
    // The number of weights >= max number of nodes in each cell
    double weights[4];

    int subId;
    vtkIdType cellId = delaunay3D->GetOutput()->FindCell(point,NULL, 0, .1,subId, pcoords, weights);

    if (cellId>=0)
    {
      std::cout << "In cell " << cellId << std::endl;
      std::cout << "inside" << std::endl;
      pointsInside->InsertNextPoint(point);
    }
    else
    {
      std::cout << "outside" << std::endl;
    }
  }

  polyDataInside->SetPoints(pointsInside);

  vtkSmartPointer<vtkVertexGlyphFilter> vertexGlyphFilter = vtkSmartPointer<vtkVertexGlyphFilter>::New();
  vertexGlyphFilter->SetInputData(polyDataInside);
  vertexGlyphFilter->Update();

  // Mapper and actor for points inside
  vtkSmartPointer<vtkPolyDataMapper> pointsInsideMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  pointsInsideMapper->SetInputConnection(vertexGlyphFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> pointsInsideActor = vtkSmartPointer<vtkActor>::New();
  pointsInsideActor->SetMapper(pointsInsideMapper);
  pointsInsideActor->GetProperty()->SetPointSize(6);
  pointsInsideActor->GetProperty()->SetColor(1,0,1);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(smallSphereActor);
  renderer->AddActor(bigSphereActor);
  renderer->AddActor(pointsInsideActor);
  renderer->SetBackground(.3, .6, .3); // Background color green
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
