#include <vtkDataArray.h>
#include <vtkImageActor.h>
#include <vtkImageCast.h>
#include <vtkImageData.h>
#include <vtkImageGaussianSmooth.h>
#include <vtkImageMapper3D.h>
#include <vtkImageMathematics.h>
#include <vtkImageMedian3D.h>
#include <vtkImageNoiseSource.h>
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

namespace
{
void AddShotNoise(vtkSmartPointer<vtkImageData> &inputImage,
                  vtkSmartPointer<vtkImageData> &outputImage,
                  double amplitude,
                  double noiseFraction,
                  int extent[6]);
}
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
  vtkSmartPointer<vtkImageReader2> reader;
  reader.TakeReference(
    readerFactory->CreateImageReader2(argv[1]));
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

  // Work with double images
  vtkSmartPointer<vtkImageCast> cast =
    vtkSmartPointer<vtkImageCast>::New();
  cast->SetInputConnection(reader->GetOutputPort());
  cast->SetOutputScalarTypeToDouble();
  cast->Update();

  vtkSmartPointer<vtkImageData> originalData =
    vtkSmartPointer<vtkImageData>::New();
  originalData->DeepCopy(cast->GetOutput());

  vtkSmartPointer<vtkImageData> noisyData =
    vtkSmartPointer<vtkImageData>::New();

  AddShotNoise(originalData, noisyData,
               2000.0, .1, reader->GetOutput()->GetExtent());
  vtkSmartPointer<vtkImageMedian3D> median =
    vtkSmartPointer<vtkImageMedian3D>::New();
  median->SetInputData(noisyData);
  median->SetKernelSize(5, 5, 1);

  vtkSmartPointer<vtkImageGaussianSmooth> gaussian =
    vtkSmartPointer<vtkImageGaussianSmooth>::New();
  gaussian->SetDimensionality(2);
  gaussian->SetInputData(noisyData);
  gaussian->SetStandardDeviations(2.0, 2.0);
  gaussian->SetRadiusFactors(2.0, 2.0);

  int colorWindow = (scalarRange[1] - scalarRange[0]) * .8;
  int colorLevel = colorWindow / 2;
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputData(originalData);
  originalActor->GetProperty()->SetColorWindow(colorWindow);
  originalActor->GetProperty()->SetColorLevel(colorLevel);
  originalActor->GetProperty()->SetInterpolationTypeToNearest();
  originalActor->SetZSlice(middleSlice);

  vtkSmartPointer<vtkImageActor> noisyActor =
    vtkSmartPointer<vtkImageActor>::New();
  noisyActor->GetMapper()->SetInputData(noisyData);
  noisyActor->GetProperty()->SetColorWindow(colorWindow);
  noisyActor->GetProperty()->SetColorLevel(colorLevel);
  noisyActor->GetProperty()->SetInterpolationTypeToNearest();
  noisyActor->SetZSlice(middleSlice);

  vtkSmartPointer<vtkImageActor> gaussianActor =
    vtkSmartPointer<vtkImageActor>::New();
  gaussianActor->GetMapper()->SetInputConnection(gaussian->GetOutputPort());
  gaussianActor->GetProperty()->SetColorWindow(colorWindow);
  gaussianActor->GetProperty()->SetColorLevel(colorLevel);
  gaussianActor->GetProperty()->SetInterpolationTypeToNearest();
  gaussianActor->SetZSlice(middleSlice);

  vtkSmartPointer<vtkImageActor> medianActor =
    vtkSmartPointer<vtkImageActor>::New();
  medianActor->GetMapper()->SetInputConnection(median->GetOutputPort());
  medianActor->GetProperty()->SetColorWindow(colorWindow);
  medianActor->GetProperty()->SetColorLevel(colorLevel);
  medianActor->GetProperty()->SetInterpolationTypeToNearest();
  medianActor->SetZSlice(middleSlice);

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->AddActor(originalActor);
  vtkSmartPointer<vtkRenderer> noisyRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  noisyRenderer->AddActor(noisyActor);
  vtkSmartPointer<vtkRenderer> gaussRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  gaussRenderer->AddActor(gaussianActor);
  vtkSmartPointer<vtkRenderer> medianRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  medianRenderer->AddActor(medianActor);

  std::vector<vtkSmartPointer<vtkRenderer> > renderers;
  renderers.push_back(originalRenderer);
  renderers.push_back(noisyRenderer);
  renderers.push_back(gaussRenderer);
  renderers.push_back(medianRenderer);

  // Setup viewports for the renderers
  int rendererSize = 400;
  unsigned int xGridDimensions = 2;
  unsigned int yGridDimensions = 2;

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
  for (size_t r = 1; r < renderers.size(); ++r)
  {
    renderers[r]->SetActiveCamera(renderers[0]->GetActiveCamera());
  }
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
namespace
{
void AddShotNoise(vtkSmartPointer<vtkImageData> &inputImage,
                  vtkSmartPointer<vtkImageData> &outputImage,
                  double noiseAmplitude,
                  double noiseFraction,
                  int extent[6])
{
  vtkSmartPointer<vtkImageNoiseSource> shotNoiseSource =
    vtkSmartPointer<vtkImageNoiseSource>::New();
  shotNoiseSource->SetWholeExtent(extent);
  shotNoiseSource->SetMinimum(0.0);
  shotNoiseSource->SetMaximum(1.0);
  
  vtkSmartPointer<vtkImageThreshold> shotNoiseThresh1 =
    vtkSmartPointer<vtkImageThreshold>::New();
  shotNoiseThresh1->SetInputConnection(shotNoiseSource->GetOutputPort());
  shotNoiseThresh1->ThresholdByLower(1.0 - noiseFraction);
  shotNoiseThresh1->SetInValue(0);
  shotNoiseThresh1->SetOutValue(noiseAmplitude);

  vtkSmartPointer<vtkImageThreshold> shotNoiseThresh2 =
    vtkSmartPointer<vtkImageThreshold>::New();
  shotNoiseThresh2->SetInputConnection(shotNoiseSource->GetOutputPort());
  shotNoiseThresh2->ThresholdByLower(noiseFraction);
  shotNoiseThresh2->SetInValue(1.0 - noiseAmplitude);
  shotNoiseThresh2->SetOutValue(0.0);

  vtkSmartPointer<vtkImageMathematics> shotNoise =
    vtkSmartPointer<vtkImageMathematics>::New();
  shotNoise->SetInputConnection(0, shotNoiseThresh1->GetOutputPort());
  shotNoise->SetInputConnection(1, shotNoiseThresh2->GetOutputPort());
  shotNoise->SetOperationToAdd();

  vtkSmartPointer<vtkImageMathematics> add =
    vtkSmartPointer<vtkImageMathematics>::New();
  add->SetInputData(0, inputImage);
  add->SetInputConnection(1, shotNoise->GetOutputPort());
  add->SetOperationToAdd();
  add->Update();
  outputImage->DeepCopy(add->GetOutput());
}
}
