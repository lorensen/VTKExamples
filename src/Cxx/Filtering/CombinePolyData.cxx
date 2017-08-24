#include <vtkSmartPointer.h>
#include <vtkAppendPolyData.h>

#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkConeSource.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkCleanPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkNamedColors.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> input1 =
    vtkSmartPointer<vtkPolyData>::New();
  vtkSmartPointer<vtkPolyData> input2 =
    vtkSmartPointer<vtkPolyData>::New();

  if(argc == 1) //command line arguments not specified
  {
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetCenter(5,0,0);
    sphereSource->Update();

    input1->ShallowCopy(sphereSource->GetOutput());

    vtkSmartPointer<vtkConeSource> coneSource =
      vtkSmartPointer<vtkConeSource>::New();
    coneSource->Update();

    input2->ShallowCopy(coneSource->GetOutput());
  }
  else
  {
    if(argc != 3)
    {
      std::cout << "argc = " << argc << std::endl;
      std::cout << "Required arguments: File1 File2" << std::endl;
      return EXIT_FAILURE;
    }
    std::string inputFilename1 = argv[1];
    std::string inputFilename2 = argv[2];
    vtkSmartPointer<vtkXMLPolyDataReader> reader1 =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader1->SetFileName(inputFilename1.c_str());
    reader1->Update();
    input1->ShallowCopy(reader1->GetOutput());

    vtkSmartPointer<vtkXMLPolyDataReader> reader2 =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader2->SetFileName(inputFilename2.c_str());
    reader2->Update();
    input2->ShallowCopy(reader2->GetOutput());
  }

  //Append the two meshes
  vtkSmartPointer<vtkAppendPolyData> appendFilter =
    vtkSmartPointer<vtkAppendPolyData>::New();
  appendFilter->AddInputData(input1);
  appendFilter->AddInputData(input2);

  // Remove any duplicate points.
  vtkSmartPointer<vtkCleanPolyData> cleanFilter =
    vtkSmartPointer<vtkCleanPolyData>::New();
  cleanFilter->SetInputConnection(appendFilter->GetOutputPort());
  cleanFilter->Update();

  //Create a mapper and actor
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(cleanFilter->GetOutputPort());

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

  //Add the actors to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("Crimson").GetData());

  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
