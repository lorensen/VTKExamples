#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkProgrammableFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

struct params
{
  vtkPolyData* data;
  vtkProgrammableFilter* filter;
};

void AdjustPoints(void* arguments)
{
  params* input = static_cast<params*>(arguments);

  vtkPoints* inPts = input->data->GetPoints();
  vtkIdType numPts = inPts->GetNumberOfPoints();
  vtkSmartPointer<vtkPoints> newPts =
      vtkSmartPointer<vtkPoints>::New();
  newPts->SetNumberOfPoints(numPts);

  for(vtkIdType i = 0; i < numPts/2; i++)
  {
    double p[3];
    inPts->GetPoint(i, p);
    p[0] = p[0] + .5;
    p[1] = p[1] + .5;
    p[2] = p[2] + .5;
    newPts->SetPoint(i, p);
  }

  for(vtkIdType i = numPts/2; i < numPts; i++)
  {
    double p[3];
    inPts->GetPoint(i, p);
    p[0] = p[0] - .5;
    p[1] = p[1] - .5;
    p[2] = p[2] - .5;
    newPts->SetPoint(i, p);
  }

  input->filter->GetPolyDataOutput()->CopyStructure(input->data);
  input->filter->GetPolyDataOutput()->SetPoints(newPts);

}

int main(int, char *[])
{
  //Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkProgrammableFilter> programmableFilter =
      vtkSmartPointer<vtkProgrammableFilter>::New();
  programmableFilter->SetInputConnection(sphereSource->GetOutputPort());

  params myParams;
  myParams.data = sphereSource->GetOutput();
  myParams.filter = programmableFilter;

  programmableFilter->SetExecuteMethod(AdjustPoints, &myParams);
  programmableFilter->Update();

  //Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(programmableFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> actor =
      vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  //Add the actor to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(.4, .5, .6); // Background color white

  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
