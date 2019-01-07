#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkActor2D.h>
#include <vtkMath.h>
#include <vtkProperty2D.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkXMLPolyDataReader.h>

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    std::cout << "Required parameters: Filename" << std::endl;
    return EXIT_FAILURE;
  }

  std::string inputFilename = argv[1];

  vtkSmartPointer<vtkXMLPolyDataReader> reader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();
  vtkPolyData* polydata = reader->GetOutput();
  //vtkPoints* Points = Polydata->GetPoints();

  vtkSmartPointer<vtkActor2D> actor =
    vtkSmartPointer<vtkActor2D>::New();
  double color[3] = {1,1,1};

  vtkSmartPointer<vtkPolyDataMapper2D> mapper =
    vtkSmartPointer<vtkPolyDataMapper2D>::New();
  mapper->SetInputData( polydata );
  mapper->ScalarVisibilityOff();
  actor->SetMapper( mapper );

  vtkProperty2D *property2D = actor->GetProperty();
  property2D->SetColor( color );
  property2D->SetPointSize( 2.0 );

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);

  // Renderer and RenderWindow
  renderer->SetBackground( 0, 0, 0);
  renderer->ResetCamera();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();

  renderWindow->SetSize( 200,200 );
  renderWindow->AddRenderer( renderer );
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow( renderWindow );

  renderWindow->Render();
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
