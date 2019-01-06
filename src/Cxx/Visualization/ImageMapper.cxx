#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageMapper.h>
#include <vtkActor2D.h>
#include <vtkImageSlice.h>

static void CreateColorImage(vtkImageData*);

int main(int, char *[])
{
  vtkSmartPointer<vtkImageData> colorImage = vtkSmartPointer<vtkImageData>::New();
  CreateColorImage(colorImage);

  vtkSmartPointer<vtkImageMapper> imageMapper = vtkSmartPointer<vtkImageMapper>::New();
  imageMapper->SetInputData(colorImage);
  imageMapper->SetColorWindow(255);
  imageMapper->SetColorLevel(127.5);

  vtkSmartPointer<vtkActor2D> imageActor = vtkSmartPointer<vtkActor2D>::New();
  imageActor->SetMapper(imageMapper);
  imageActor->SetPosition(20, 20);

  // Setup renderers
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

  renderWindow->AddRenderer(renderer);

  // Setup render window interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

  vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  // Render and start interaction
  renderWindowInteractor->SetRenderWindow(renderWindow);

  //renderer->AddViewProp(imageActor);
  renderer->AddActor2D(imageActor);

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

void CreateColorImage(vtkImageData* image)
{
  unsigned int dim = 20;

  image->SetDimensions(dim, dim, 1);
  image->AllocateScalars(VTK_UNSIGNED_CHAR,3);

  for(unsigned int x = 0; x < dim; x++)
  {
    for(unsigned int y = 0; y < dim; y++)
    {
      unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(x,y,0));
      if(x < dim/2)
      {
	pixel[0] = 255;
	pixel[1] = 0;
      }
      else
      {
	pixel[0] = 0;
	pixel[1] = 255;
      }

      pixel[2] = 0;
    }
  }

  image->Modified();
}
