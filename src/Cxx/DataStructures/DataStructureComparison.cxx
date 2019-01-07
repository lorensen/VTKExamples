#include <vtkSmartPointer.h>
#include <vtkPointSource.h>
#include <vtkObjectFactory.h>
#include <vtkRendererCollection.h>
#include <vtkPolyData.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkSphereSource.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkInteractorStyleTrackballCamera.h>

#include <vtkKdTreePointLocator.h>
#include <vtkOctreePointLocator.h>
#include <vtkOBBTree.h>
#include <vtkModifiedBSPTree.h>

#include <vector>

class KeyPressInteractorStyle : public vtkInteractorStyleTrackballCamera
{
  public:
    static KeyPressInteractorStyle* New();
    vtkSmartPointer<vtkPolyData> data;
    std::vector<vtkRenderer*> renderers;
    std::vector<vtkSmartPointer<vtkLocator> > trees;
    std::vector<vtkSmartPointer<vtkPolyDataMapper> > mappers;
    std::vector<vtkSmartPointer<vtkActor> > actors;

    vtkSmartPointer<vtkPolyDataMapper> meshMapper;
    vtkSmartPointer<vtkActor> meshActor;

    void Initialize()
    {
      this->meshMapper->SetInputData(this->data);
      for(unsigned int i = 0; i < 4; i++)
      {
	vtkSmartPointer<vtkPolyDataMapper> mapper =
	  vtkSmartPointer<vtkPolyDataMapper>::New();
	this->mappers.push_back(mapper);
	vtkSmartPointer<vtkActor> actor =
	  vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetRepresentationToWireframe();
	this->actors.push_back(actor);
	this->renderers[i]->AddActor(actor);

        this->renderers[i]->AddActor(meshActor);
      }
      this->Level = 1;
      std::cout << "Level = " << this->Level << std::endl;
      this->ReDraw();
    }

    KeyPressInteractorStyle()
    {
      this->Level = 1;

      vtkSmartPointer<vtkLocator> tree0 = vtkSmartPointer<vtkKdTreePointLocator>::New();
      this->trees.push_back(tree0);
      vtkSmartPointer<vtkLocator> tree1 = vtkSmartPointer<vtkOBBTree>::New();
      this->trees.push_back(tree1);
      vtkSmartPointer<vtkLocator> tree2 = vtkSmartPointer<vtkOctreePointLocator>::New();
      this->trees.push_back(tree2);
      vtkSmartPointer<vtkLocator> tree3 = vtkSmartPointer<vtkModifiedBSPTree>::New();
      this->trees.push_back(tree3);

      this->meshMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
      this->meshActor = vtkSmartPointer<vtkActor>::New();
      this->meshActor->SetMapper(this->meshMapper);

    }

    virtual void OnChar()
    {
      char ch = this->Interactor->GetKeyCode() ;

      switch (ch)
      {
        case 'n':
          this->Level++;
          break;
        case 'p':
          if(this->Level > 1)
          {
            this->Level--;
          }
          break ;
        default:
          std::cout << "An unhandled key was pressed." << std::endl;
          break;
      }

       this->ReDraw();

      // forward events
      if(ch != 'p') //don't forward the "pick" command
      {
	vtkInteractorStyleTrackballCamera::OnChar();
      }
    }

 void ReDraw()
 {

   std::cout << "Level " << this->Level << std::endl;
  for(unsigned i = 0; i < 4; i++)
  {

    vtkSmartPointer<vtkLocator> tree = this->trees[i];
    //vtkRenderer* renderer = this->renderers[i];

    tree->SetDataSet(data);
    tree->BuildLocator();

    vtkSmartPointer<vtkPolyData> polydata =
      vtkSmartPointer<vtkPolyData>::New();
    std::cout << "Tree " << i << " has " << tree->GetLevel() << " levels." << std::endl;

    if(this->Level > tree->GetLevel())
    {
      tree->GenerateRepresentation(tree->GetLevel(), polydata);
    }
    else
    {
      tree->GenerateRepresentation(this->Level, polydata);
    }

    this->mappers[i]->SetInputData(polydata);
  }

    this->Interactor->GetRenderWindow()->Render();

 }

  private:
    int Level;

};

vtkStandardNewMacro(KeyPressInteractorStyle);

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> originalMesh =
    vtkSmartPointer<vtkPolyData>::New();

  if(argc > 1) //If a file name is specified, open and use the file.
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();
    originalMesh->ShallowCopy(reader->GetOutput());
  }
  else //If a file name is not specified, create a sphere
  {
    //vtkSmartPointer<vtkSphereSource> sphereSource =
      //vtkSmartPointer<vtkSphereSource>::New();
    vtkSmartPointer<vtkPointSource> sphereSource =
      vtkSmartPointer<vtkPointSource>::New();
      sphereSource->SetNumberOfPoints(1000);

    sphereSource->Update();
    originalMesh->ShallowCopy(sphereSource->GetOutput());
  }

  double numberOfViewports = 4.;

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(200* numberOfViewports,200); //(width, height)
  renderWindow->SetWindowName("Multiple ViewPorts");

  vtkSmartPointer<KeyPressInteractorStyle> style =
    vtkSmartPointer<KeyPressInteractorStyle>::New();
  style->data = originalMesh;

  vtkSmartPointer<vtkCamera> camera =
    vtkSmartPointer<vtkCamera>::New();

  for(unsigned int i = 0; i < 4; i++)
  {
    vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(renderer);
    style->renderers.push_back(renderer);
    renderer->SetViewport(static_cast<double>(i)/numberOfViewports,0,
			  static_cast<double>(i+1)/numberOfViewports,1);
    renderer->SetBackground(.2, .3, .4);
    renderer->SetActiveCamera(camera);
  }

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->SetInteractorStyle(style);
  style->Initialize();
  style->renderers[0]->ResetCamera();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
