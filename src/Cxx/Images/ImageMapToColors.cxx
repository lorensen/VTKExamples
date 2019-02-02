//
// Displays a "grayscale" image as a full color image via the
// vtkImageMapToColors filter, which uses a lookup table to
// map scalar values to colors
//
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageMapToColors.h>
#include <vtkImageProperty.h>
#include <vtkInteractorStyleImage.h>
#include <vtkLookupTable.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

int main(int, char*[])
{
  // Create a "grayscale" 16x16 image, 1-component pixels of type "double"
  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  int imageExtent[6] = { 0, 15, 0, 15, 0, 0 };
  image->SetExtent(imageExtent);
  image->AllocateScalars(VTK_DOUBLE, 1);

  double scalarvalue = 0.0;

  for (int y = imageExtent[2]; y <= imageExtent[3]; y++)
  {
    for (int x = imageExtent[0]; x <= imageExtent[1]; x++)
    {
      double* pixel = static_cast<double*>(image->GetScalarPointer(x, y, 0));
      pixel[0] = scalarvalue;
      scalarvalue += 1.0;
    }
  }

  // Map the scalar values in the image to colors with a lookup table:
  vtkSmartPointer<vtkLookupTable> lookupTable =
    vtkSmartPointer<vtkLookupTable>::New();
  lookupTable->SetNumberOfTableValues(256);
  lookupTable->SetRange(0.0, 255.0);
  lookupTable->Build();

  // Pass the original image and the lookup table to a filter to create
  // a color image:
  vtkSmartPointer<vtkImageMapToColors> scalarValuesToColors =
    vtkSmartPointer<vtkImageMapToColors>::New();
  scalarValuesToColors->SetLookupTable(lookupTable);
  scalarValuesToColors->PassAlphaToOutputOn();
  scalarValuesToColors->SetInputData(image);

  // Create an image actor
  vtkSmartPointer<vtkImageActor> imageActor =
    vtkSmartPointer<vtkImageActor>::New();
  imageActor->GetMapper()->SetInputConnection(
    scalarValuesToColors->GetOutputPort());
  imageActor->GetProperty()->SetInterpolationTypeToNearest();

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
