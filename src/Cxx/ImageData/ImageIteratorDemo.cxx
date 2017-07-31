#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageIterator.h>

#include <vtkImageViewer2.h>
#include <vtkImageActor.h>
#include <vtkRenderWindow.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>

int main(int, char *[])
{
  // Create an image data
  vtkSmartPointer<vtkImageData> imageData =
      vtkSmartPointer<vtkImageData>::New();

  // Specify the size of the image data
  imageData->SetDimensions(100,200,30);
  imageData->AllocateScalars(VTK_UNSIGNED_CHAR,3);

  // Fill every entry of the image data with a color
  int* dims = imageData->GetDimensions();

  unsigned char *ptr = static_cast<unsigned char *>(imageData->GetScalarPointer(0, 0, 0));
  unsigned char r, g, b, a;
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
  colors->GetColor("Banana", r, g, b, a);
  for (int z=0; z<dims[2]; z++)
  {
    for (int y=0; y<dims[1]; y++)
    {
      for (int x=0; x<dims[0]; x++)
      {
        *ptr++ = r;
        *ptr++ = g;
        *ptr++ = b;
      }
    }
  }

  // Define the extent to be modified
  int extent[6];
  extent[0] = 20; extent[1] = 50;
  extent[2] = 30; extent[3] = 60;
  extent[4] = 10; extent[5] = 20;

  // Set the entries in the region to another color
  colors->GetColor("Tomato", r, g, b, a);
  vtkImageIterator<unsigned char> it(imageData, extent);
  unsigned int counter = 0;
  while(!it.IsAtEnd())
  {
    unsigned char *valIt = it.BeginSpan();
    unsigned char *valEnd = it.EndSpan();
    while (valIt != valEnd)
    {
      // Increment for each component
      *valIt++ = r;
      *valIt++ = g;
      *valIt++ = b;
    }
    it.NextSpan();
    ++counter;
  }
  std::cout << "# of spans: " << counter << std::endl;

  std::cout << "Increments: "
            << imageData->GetIncrements()[0] << ", "
            << imageData->GetIncrements()[1] << ", "
            << imageData->GetIncrements()[2] << std::endl;
  vtkIdType incX, incY, incZ;
  imageData->GetContinuousIncrements(extent, incX, incY, incZ);
  std::cout << "ContinuousIncrements: "
            << incX << ", " << incY << ", " << incZ << std::endl;

  // Visualize
  vtkSmartPointer<vtkImageViewer2> imageViewer =
    vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputData( imageData );

  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();
  style->SetInteractionModeToImageSlicing();

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetInteractorStyle(style);
  imageViewer->SetupInteractor(renderWindowInteractor);
  imageViewer->SetSlice((extent[5] - extent[4]) / 2 + extent[4]);

  imageViewer->GetRenderer()->SetBackground(colors->GetColor3d("Slate_grey").GetData());
  imageViewer->GetImageActor()->InterpolateOff();

  imageViewer->Render();
  imageViewer->GetRenderer()->ResetCamera();
  imageViewer->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
