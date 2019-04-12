#include <vtkSmartPointer.h>
#include <vtkImageMapToColors.h>

#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>
#include <vtkLookupTable.h>
#include <vtkImageMapper3D.h>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>

int main(int argc, char* argv[])
{
  // Verify input arguments
  if ( argc != 2 )
  {
    std::cout << "Usage: " << argv[0]
              << " Filename(.jpg)" << std::endl;
    return EXIT_FAILURE;
  }

  // Read the image
  vtkSmartPointer<vtkImageReader2Factory> readerFactory =
    vtkSmartPointer<vtkImageReader2Factory>::New();
  vtkSmartPointer<vtkImageReader2> reader;
  reader.TakeReference(
    readerFactory->CreateImageReader2(argv[1]));
  reader->SetFileName(argv[1]);
  reader->Update();

  vtkImageData* image = reader->GetOutput();

  // Create a mask - half of the image should be transparent and the other half opaque
  vtkSmartPointer<vtkImageData> maskImage =
    vtkSmartPointer<vtkImageData>::New();
  int extent[6];
  image->GetExtent(extent);
  maskImage->SetExtent(extent);
  maskImage->AllocateScalars(VTK_DOUBLE,1);

  for (int y = extent[2]; y < extent[3]; y++)
  {
    for (int x = extent[0]; x < extent[1]; x++)
    {
      double* pixel = static_cast<double*>(maskImage->GetScalarPointer(x,y,0));
      if(y > (extent[3]-extent[2])/2.0)
      {
        pixel[0] = 0.0;
      }
      else
      {
        pixel[0] = 1.0;
      }
    }
  }

  vtkSmartPointer<vtkLookupTable> lookupTable =
    vtkSmartPointer<vtkLookupTable>::New();
  lookupTable->SetNumberOfTableValues(2);
  lookupTable->SetRange(0.0,1.0);
  lookupTable->SetTableValue( 0, 0.0, 0.0, 0.0, 0.0 ); //label 0 is transparent
  lookupTable->SetTableValue( 1, 0.0, 1.0, 0.0, 1.0 ); //label 1 is opaque and green
  lookupTable->Build();

  vtkSmartPointer<vtkImageMapToColors> mapTransparency =
    vtkSmartPointer<vtkImageMapToColors>::New();
  mapTransparency->SetLookupTable(lookupTable);
  mapTransparency->PassAlphaToOutputOn();
  mapTransparency->SetInputData(maskImage);


  // Create actors
  vtkSmartPointer<vtkImageActor> imageActor =
    vtkSmartPointer<vtkImageActor>::New();
  imageActor->GetMapper()->SetInputData(image);

  vtkSmartPointer<vtkImageActor> maskActor =
    vtkSmartPointer<vtkImageActor>::New();
  maskActor->GetMapper()->SetInputConnection(
    mapTransparency->GetOutputPort());

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(imageActor);
  renderer->AddActor(maskActor);
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
