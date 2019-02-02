#include <vtkImageData.h>
#include <vtkImageMapper.h>
#include <vtkImageProperty.h>
#include <vtkImageSliceMapper.h>
#include <vtkImageSlice.h>
#include <vtkImageStack.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

static void CreateColorImage(vtkImageData*, const int corner, const unsigned int channel);

int main(int, char *[])
{
  // Image 1
  vtkSmartPointer<vtkImageData> image1 = vtkSmartPointer<vtkImageData>::New();
  CreateColorImage(image1, 1, 0);

  vtkSmartPointer<vtkImageSliceMapper> imageSliceMapper1 = vtkSmartPointer<vtkImageSliceMapper>::New();
  imageSliceMapper1->SetInputData(image1);

  vtkSmartPointer<vtkImageSlice> imageSlice1 = vtkSmartPointer<vtkImageSlice>::New();
  imageSlice1->SetMapper(imageSliceMapper1);
  imageSlice1->GetProperty()->SetOpacity(.5);

  // Image 2
  vtkSmartPointer<vtkImageData> image2 = vtkSmartPointer<vtkImageData>::New();
  CreateColorImage(image2, 4, 1);

  vtkSmartPointer<vtkImageSliceMapper> imageSliceMapper2 = vtkSmartPointer<vtkImageSliceMapper>::New();
  imageSliceMapper2->SetInputData(image2);

  vtkSmartPointer<vtkImageSlice> imageSlice2 = vtkSmartPointer<vtkImageSlice>::New();
  imageSlice2->SetMapper(imageSliceMapper2);
  imageSlice2->GetProperty()->SetOpacity(.5);

  // Stack
  vtkSmartPointer<vtkImageStack> imageStack = vtkSmartPointer<vtkImageStack>::New();
  imageStack->AddImage(imageSlice1);
  imageStack->AddImage(imageSlice2);
  //imageStack->SetActiveLayer(1);

  // Setup renderers
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddViewProp(imageStack);
  renderer->ResetCamera();

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // Setup render window interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();

  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  // Render and start interaction
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindow->Render();
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

void CreateColorImage(vtkImageData* image, const int corner, const unsigned int channel)
{
  image->SetDimensions(10, 10, 1);
  image->AllocateScalars(VTK_UNSIGNED_CHAR,3);

  for(unsigned int x = 0; x < 10; x++)
  {
    for(unsigned int y = 0; y < 10; y++)
    {
      unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(x,y,0));
      pixel[0] = 0;
      pixel[1] = 0;
      pixel[2] = 0;
    }
  }

  for(int x = corner; x < corner+3; x++)
  {
    for(int y = corner; y < corner+3; y++)
    {
      unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(x,y,0));
      pixel[channel] = 255;
    }
  }
}
