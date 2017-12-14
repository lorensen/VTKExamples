#include <vtkSmartPointer.h>

#include <vtkImageReader2.h>
#include <vtkImageReader2Factory.h>

#include <vtkWindowLevelLookupTable.h>
#include <vtkImageMapToColors.h>
#include <vtkDataArray.h>
#include <vtkImageActor.h>
#include <vtkImageCast.h>
#include <vtkImageData.h>
#include <vtkImageLaplacian.h>
#include <vtkImageMapper3D.h>
#include <vtkImageMathematics.h>
#include <vtkImageProperty.h>
#include <vtkImageThreshold.h>
#include <vtkInteractorStyleImage.h>
#include <vtkPointData.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

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

  // Work with double images
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

  vtkSmartPointer<vtkWindowLevelLookupTable> wlut =
    vtkSmartPointer<vtkWindowLevelLookupTable>::New();
  wlut->SetWindow(colorWindow);
  wlut->SetLevel(colorLevel);
  wlut->Build();

  // Map the image through the lookup table
  vtkSmartPointer<vtkImageMapToColors> originalColor =
    vtkSmartPointer<vtkImageMapToColors>::New();
  originalColor->SetLookupTable(wlut);
  originalColor->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(originalColor->GetOutputPort());
  originalActor->GetProperty()->SetInterpolationTypeToNearest();
  originalActor->SetDisplayExtent(
    reader->GetDataExtent()[0], reader->GetDataExtent()[1],
    reader->GetDataExtent()[2], reader->GetDataExtent()[3],
    middleSlice, middleSlice);

  vtkSmartPointer<vtkWindowLevelLookupTable> wlut2 =
    vtkSmartPointer<vtkWindowLevelLookupTable>::New();
  wlut2->SetWindow(1000);
  wlut2->SetLevel(0);
  wlut2->Build();

  vtkSmartPointer<vtkImageMapToColors> laplacianColor =
    vtkSmartPointer<vtkImageMapToColors>::New();
  laplacianColor->SetLookupTable(wlut2);
  laplacianColor->SetInputConnection(laplacian->GetOutputPort());

  vtkSmartPointer<vtkImageActor> laplacianActor =
    vtkSmartPointer<vtkImageActor>::New();
  laplacianActor->GetMapper()->SetInputConnection(laplacianColor->GetOutputPort());
  laplacianActor->GetProperty()->SetInterpolationTypeToNearest();
  laplacianActor->SetDisplayExtent(originalActor->GetDisplayExtent());

  vtkSmartPointer<vtkImageMapToColors> enhancedColor =
    vtkSmartPointer<vtkImageMapToColors>::New();
  enhancedColor->SetLookupTable(wlut);
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
        static_cast<double>(col) * rendererSize /
        (xGridDimensions * rendererSize),
        static_cast<double>(yGridDimensions - (row + 1)) * rendererSize /
        (yGridDimensions * rendererSize),
        static_cast<double>(col + 1) * rendererSize /
        (xGridDimensions * rendererSize),
        static_cast<double>(yGridDimensions - row) * rendererSize /
        (yGridDimensions * rendererSize)};
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
