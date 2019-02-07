#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageMapper.h>
#include <vtkImageSliceMapper.h>
#include <vtkImageSlice.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkImageTranslateExtent.h>

static void CreateColorImage(vtkImageData* const);

int main(int, char *[])
{
  vtkSmartPointer<vtkImageData> colorImage = vtkSmartPointer<vtkImageData>::New();
  CreateColorImage(colorImage); // This image has (0,0) at the bottom left corner

  int extent[6];
  colorImage->GetExtent(extent);
  std::cout << "Old extent: " << extent[0] << " " << extent[1] << " " << extent[2] << " " << extent[3] << " " << extent[4] << " " << extent[5] << std::endl;

  // This moves the (0,0) position in the image to the center of the image
//  int extent[6];
//  colorImage->GetExtent(extent);
//  colorImage->SetExtent(extent[0] - (extent[1] - extent[0])/2, extent[0] + (extent[1] - extent[0])/2,
//                        extent[2] - (extent[3] - extent[2])/2, extent[2] + (extent[3] - extent[2])/2,
//                        extent[4] - (extent[5] - extent[4])/2, extent[4] + (extent[5] - extent[4])/2);

  int dimensions[3];
  colorImage->GetDimensions(dimensions);

  vtkSmartPointer<vtkImageTranslateExtent> translateExtent =
    vtkSmartPointer<vtkImageTranslateExtent>::New();
  translateExtent->SetTranslation(-dimensions[0]/2,-dimensions[1]/2,0);
  translateExtent->SetInputData(colorImage);
  translateExtent->Update();
  colorImage->DeepCopy(translateExtent->GetOutput());

  colorImage->GetExtent(extent);
  std::cout << "New extent: " << extent[0] << " " << extent[1] << " " << extent[2] << " " << extent[3] << " " << extent[4] << " " << extent[5] << std::endl;

  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(1.0);
  sphereSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> sphereActor =
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);

  vtkSmartPointer<vtkImageSliceMapper> imageSliceMapper = vtkSmartPointer<vtkImageSliceMapper>::New();
  imageSliceMapper->SetInputData(colorImage);

  vtkSmartPointer<vtkImageSlice> imageSlice = vtkSmartPointer<vtkImageSlice>::New();
  imageSlice->SetMapper(imageSliceMapper);
  imageSlice->SetPosition(0,0,0);

  // Setup renderers
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddViewProp(imageSlice);
  renderer->AddViewProp(sphereActor);
  renderer->ResetCamera();

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(300, 300);
  renderWindow->AddRenderer(renderer);

  // Setup render window interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();

  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  // Render and start interaction
  renderWindow->Render();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

void CreateColorImage(vtkImageData* const image)
{
  image->SetDimensions(10, 10, 1);
  image->AllocateScalars(VTK_UNSIGNED_CHAR,3);

  for(unsigned int x = 0; x < 10; x++)
  {
    for(unsigned int y = 0; y < 10; y++)
    {
      unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(x,y,0));
      pixel[0] = 255;
      pixel[1] = 0;
      pixel[2] = 255;
    }
  }
}
