#include <vtkSmartPointer.h>
#include <vtkLookupTable.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageMapToColors.h>
#include <vtkJPEGReader.h>
#include <vtkPointData.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>

static void CreateImage(vtkSmartPointer<vtkImageData> image);

int main(int, char*[])
{
  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  CreateImage(image);

  // Create actor
  vtkSmartPointer<vtkImageActor> imageActor =
    vtkSmartPointer<vtkImageActor>::New();
  imageActor->GetMapper()->SetInputData(image);

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(imageActor);
  renderer->ResetCamera();

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindow->Render();
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

void CreateImage(vtkSmartPointer<vtkImageData> image)
{
  // Specify the size of the image data
  image->SetDimensions(10,10,1);
  image->AllocateScalars(VTK_UNSIGNED_CHAR,4);

  int* dims = image->GetDimensions();
  // int dims[3]; // can't do this

  std::cout << "Dims: " << " x: " << dims[0] << " y: " << dims[1] << " z: " << dims[2] << std::endl;

  // Fill every entry of the image with "2"
  for (int y = 0; y < dims[1]; y++)
  {
    for (int x = 0; x < dims[0]; x++)
    {

      unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(x,y,0));
      pixel[0] = 255;
      pixel[1] = 255;
      pixel[2] = 255;
      if(x<5)
      {
        pixel[3] = 0;
      }
      else
      {
        pixel[3] = 255;
      }
    }
  }

}
