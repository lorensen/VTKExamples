#include <vtkCamera.h>
#include <vtkDataArray.h>
#include <vtkImageActor.h>
#include <vtkImageCast.h>
#include <vtkImageData.h>
#include <vtkImageLaplacian.h>
#include <vtkImageMapper3D.h>
#include <vtkImageMapToWindowLevelColors.h>
#include <vtkImageMathematics.h>
#include <vtkImageProperty.h>
#include <vtkImageReader2.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageThreshold.h>
#include <vtkInteractorStyleImage.h>
#include <vtkPointData.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vector>

int main (int argc, char *argv[])
{
  // Verify input arguments
  if ( argc != 2 )
  {
    std::cout << "Usage: " << argv[0]
              << " Filename" << std::endl;
    return EXIT_FAILURE;
  }

  // Read the image
  vtkSmartPointer<vtkImageReader2Factory> readerFactory =
    vtkSmartPointer<vtkImageReader2Factory>::New();
  vtkImageReader2 *reader = readerFactory->CreateImageReader2(argv[1]);
  reader->SetFileName(argv[1]);
  reader->Update();

  int scalarRange[2];
  scalarRange[0] =
    reader->GetOutput()->GetPointData()->GetScalars()->GetRange()[0];
  scalarRange[1] =
    reader->GetOutput()->GetPointData()->GetScalars()->GetRange()[1];
  std::cout << "Range: "
            << scalarRange[0] << ", " << scalarRange[1]
            << std::endl;
  int middleSlice = (reader->GetOutput()->GetExtent()[5] -
                     reader->GetOutput()->GetExtent()[4]) / 2;

  middleSlice = 22;

  // Work with triple images
  vtkSmartPointer<vtkImageCast> cast =
    vtkSmartPointer<vtkImageCast>::New();
  cast->SetInputConnection(reader->GetOutputPort());
  cast->SetOutputScalarTypeToDouble();
  cast->Update();

  vtkSmartPointer<vtkImageLaplacian> laplacian =
    vtkSmartPointer<vtkImageLaplacian>::New();
  laplacian->SetInputConnection(cast->GetOutputPort());
  laplacian->SetDimensionality(3);

  vtkSmartPointer<vtkImageMathematics> enhance =
    vtkSmartPointer<vtkImageMathematics>::New();
  enhance->SetInputConnection(0, cast->GetOutputPort());
  enhance->SetInputConnection(1, laplacian->GetOutputPort());
  enhance->SetOperationToSubtract();

  int colorWindow = (scalarRange[1] - scalarRange[0]);
  int colorLevel = colorWindow / 2;

  // Map the image through the lookup table
  vtkSmartPointer<vtkImageMapToWindowLevelColors> originalColor =
    vtkSmartPointer<vtkImageMapToWindowLevelColors>::New();
  originalColor->SetWindow(colorWindow);
  originalColor->SetLevel(colorLevel);
  originalColor->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(originalColor->GetOutputPort());
  originalActor->GetProperty()->SetInterpolationTypeToNearest();
  originalActor->SetDisplayExtent(
    reader->GetDataExtent()[0], reader->GetDataExtent()[1],
    reader->GetDataExtent()[2], reader->GetDataExtent()[3],
    middleSlice, middleSlice);

  vtkSmartPointer<vtkImageMapToWindowLevelColors> laplacianColor =
    vtkSmartPointer<vtkImageMapToWindowLevelColors>::New();
  laplacianColor->SetWindow(1000);
  laplacianColor->SetLevel(0);
  laplacianColor->SetInputConnection(laplacian->GetOutputPort());

  vtkSmartPointer<vtkImageActor> laplacianActor =
    vtkSmartPointer<vtkImageActor>::New();
  laplacianActor->GetMapper()->SetInputConnection(laplacianColor->GetOutputPort());
  laplacianActor->GetProperty()->SetInterpolationTypeToNearest();
  laplacianActor->SetDisplayExtent(originalActor->GetDisplayExtent());

  vtkSmartPointer<vtkImageMapToWindowLevelColors> enhancedColor =
    vtkSmartPointer<vtkImageMapToWindowLevelColors>::New();
  enhancedColor->SetWindow(colorWindow);
  enhancedColor->SetLevel(colorLevel);
  enhancedColor->SetInputConnection(enhance->GetOutputPort());

  vtkSmartPointer<vtkImageActor> enhancedActor =
    vtkSmartPointer<vtkImageActor>::New();
  enhancedActor->GetMapper()->SetInputConnection(enhancedColor->GetOutputPort());
  enhancedActor->GetProperty()->SetInterpolationTypeToNearest();
  enhancedActor->SetDisplayExtent(originalActor->GetDisplayExtent());

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->AddActor(originalActor);
  vtkSmartPointer<vtkRenderer> laplacianRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  laplacianRenderer->AddActor(laplacianActor);
  vtkSmartPointer<vtkRenderer> enhancedRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  enhancedRenderer->AddActor(enhancedActor);

  std::vector<vtkSmartPointer<vtkRenderer> > renderers;
  renderers.push_back(originalRenderer);
  renderers.push_back(laplacianRenderer);
  renderers.push_back(enhancedRenderer);

  // Setup viewports for the renderers
  int rendererSize = 400;
  unsigned int xGridDimensions = 3;
  unsigned int yGridDimensions = 1;

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(
    rendererSize * xGridDimensions, rendererSize * yGridDimensions);
  for (int row = 0; row < static_cast<int>(yGridDimensions); row++)
  {
    for (int col = 0; col < static_cast<int>(xGridDimensions); col++)
    {
      int index = row * xGridDimensions + col;
      // (xmin, ymin, xmax, ymax)
       double viewport[4] = {
         static_cast<double>(col) / xGridDimensions,
         static_cast<double>(yGridDimensions - (row + 1)) / yGridDimensions,
         static_cast<double>(col + 1) / xGridDimensions,
         static_cast<double>(yGridDimensions - row) / yGridDimensions};
      renderers[index]->SetViewport(viewport);
      renderWindow->AddRenderer(renderers[index]);
    }
  }

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Renderers share one camera
  renderWindow->Render();
  renderers[0]->GetActiveCamera()->Dolly(1.5);
  renderers[0]->ResetCameraClippingRange();

  for (size_t r = 1; r < renderers.size(); ++r)
  {
    renderers[r]->SetActiveCamera(renderers[0]->GetActiveCamera());
  }
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  reader->Delete();

  return EXIT_SUCCESS;
}
