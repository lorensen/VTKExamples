#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageMapper.h>
#include <vtkImageSliceMapper.h>
#include <vtkImageSlice.h>
#include <vtkImageProperty.h>

static void CreateRandomImage(vtkImageData* image, const unsigned int dimension);

int main(int, char *[])
{
  // Big image
  vtkSmartPointer<vtkImageData> image = vtkSmartPointer<vtkImageData>::New();
  CreateRandomImage(image, 50);

  vtkSmartPointer<vtkImageSliceMapper> imageSliceMapper = vtkSmartPointer<vtkImageSliceMapper>::New();
  imageSliceMapper->SetInputData(image);
  imageSliceMapper->BorderOn(); // This line tells the mapper to draw the full border pixels.
  vtkSmartPointer<vtkImageSlice> imageSlice = vtkSmartPointer<vtkImageSlice>::New();
  imageSlice->SetMapper(imageSliceMapper);
  imageSlice->GetProperty()->SetInterpolationTypeToNearest();

  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddViewProp(imageSlice);
  renderer->ResetCamera();

  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
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

void CreateRandomImage(vtkImageData* image, const unsigned int dimension)
{
  image->SetDimensions(dimension, dimension, 1);
  image->SetOrigin(.5,.5,0);
  image->AllocateScalars(VTK_UNSIGNED_CHAR,3);

  for(unsigned int x = 0; x < dimension; x++)
  {
    for(unsigned int y = 0; y < dimension; y++)
    {
      unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(x,y,0));
      pixel[0] = rand() % 255;
      pixel[1] = rand() % 255;
      pixel[2] = rand() % 255;
    }
  }

  image->Modified();
}
