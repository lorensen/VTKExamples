#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkCubeSource.h>
#include <vtkSmartPointer.h>
#include <vtkSelectEnclosedPoints.h>
#include <vtkIntArray.h>
#include <vtkDataArray.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVertexGlyphFilter.h>


int main(int, char *argv[])
{
  //cube centered in origin, 1cm side.
  vtkSmartPointer<vtkCubeSource> cubeSource =
    vtkSmartPointer<vtkCubeSource>::New();
  cubeSource->Update();

  vtkPolyData* cube = cubeSource->GetOutput();

  double testInside[3] = {0.0, 0.0, 0.0};
  double testOutside[3] = {0.7, 0.0, 0.0};
  double testBorderOutside[3] = {0.5, 0.0, 0.0};
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(testInside);
  points->InsertNextPoint(testOutside);
  points->InsertNextPoint(testBorderOutside);

  vtkSmartPointer<vtkPolyData> pointsPolydata =
    vtkSmartPointer<vtkPolyData>::New();
  pointsPolydata->SetPoints(points);

  //Points inside test
  vtkSmartPointer<vtkSelectEnclosedPoints> selectEnclosedPoints =
    vtkSmartPointer<vtkSelectEnclosedPoints>::New();
  selectEnclosedPoints->SetInputData(pointsPolydata);
  selectEnclosedPoints->SetSurfaceData(cube);
  selectEnclosedPoints->Update();

  for(unsigned int i = 0; i < 2; i++)
  {
    std::cout << "Point " << i << ": " << selectEnclosedPoints->IsInside(i) << std::endl;
  }

  vtkDataArray* insideArray =
    dynamic_cast<vtkDataArray*>(selectEnclosedPoints->GetOutput()->GetPointData()->GetArray("SelectedPoints"));

  for(vtkIdType i = 0; i < insideArray->GetNumberOfTuples(); i++)
  {
    std::cout << i << " : " << insideArray->GetComponent(i,0) << std::endl;
  }


  //RENDERING PART

  //Cube mapper, actor
  vtkSmartPointer<vtkPolyDataMapper> cubeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cubeMapper->SetInputConnection(cubeSource->GetOutputPort());

  vtkSmartPointer<vtkActor> cubeActor =
    vtkSmartPointer<vtkActor>::New();
  cubeActor->SetMapper(cubeMapper);
  cubeActor->GetProperty()->SetOpacity(0.5);

  //Points mapper, actor
  //First, apply vtkVertexGlyphFilter to make cells around points, vtk only render cells.
  vtkSmartPointer<vtkVertexGlyphFilter> vertexGlyphFilter =
  vtkSmartPointer<vtkVertexGlyphFilter>::New();
  vertexGlyphFilter->AddInputData(pointsPolydata);
  vertexGlyphFilter->Update();

 vtkSmartPointer<vtkPolyDataMapper> pointsMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  pointsMapper->SetInputConnection(vertexGlyphFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> pointsActor =
    vtkSmartPointer<vtkActor>::New();
  pointsActor->SetMapper(pointsMapper);
  pointsActor->GetProperty()->SetPointSize(5);
  pointsActor->GetProperty()->SetColor(0.0,0.0,1);

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actor to the scene
  renderer->AddActor(cubeActor);
  renderer->AddActor(pointsActor);
  renderer->SetBackground(.0, 1,.0);

  // Render and interact
  renderWindow->SetWindowName(argv[0]);
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
