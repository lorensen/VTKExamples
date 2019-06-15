#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkTransformTextureCoords.h>
#include <vtkTexture.h>
#include <vtkTextureMapToSphere.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageReader.h>
#include <vtkTexturedSphereSource.h>

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
      std::cout << "Usage: " << argv[0]
                << " texture(.png/.ppm) e.g. earth.ppm"
                << " [translate]" <<std::endl;
      return EXIT_FAILURE;
  }
  double translate[3];
  if (argc > 2)
  {
      translate[0] = atof(argv[2]);
  }
  else
  {
      translate[0] = 0.0;
  }
  translate[1] = 0.0;
  translate[2] = 0.0;
  std::cout << translate[0] << ", "
            << translate[1] << ", "
            << translate[2] << "\n";
  // Create a sphere with texture coordinates
  vtkSmartPointer<vtkTexturedSphereSource> source =
    vtkSmartPointer<vtkTexturedSphereSource>::New();

  // Read texture file
  vtkSmartPointer<vtkImageReader2Factory> readerFactory =
    vtkSmartPointer<vtkImageReader2Factory>::New();
  vtkSmartPointer<vtkImageReader2> imageReader;
  imageReader.TakeReference(
    readerFactory->CreateImageReader2(argv[1]));
  imageReader->SetFileName(argv[1]);

  // Create texture
  vtkSmartPointer<vtkTexture> texture =
    vtkSmartPointer<vtkTexture>::New();
  texture->SetInputConnection(imageReader->GetOutputPort());

  vtkSmartPointer<vtkTransformTextureCoords> transformTexture =
    vtkSmartPointer<vtkTransformTextureCoords>::New();
  transformTexture->SetInputConnection(source->GetOutputPort());
  transformTexture->SetPosition(translate);

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(transformTexture->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper( mapper );
  actor->SetTexture( texture );

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->SetBackground(.1, .2, .3);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer( renderer );

  vtkSmartPointer<vtkRenderWindowInteractor> renWinInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renWinInteractor->SetRenderWindow( renderWindow );

  renderWindow->Render();
  renWinInteractor->Start();

  return EXIT_SUCCESS;
}
