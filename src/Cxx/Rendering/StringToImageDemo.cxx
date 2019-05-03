#include <vtkSmartPointer.h>

#include <vtkImageCanvasSource2D.h>
#include <vtkFreeTypeTools.h>
#include <vtkImageBlend.h>
#include <vtkImageData.h>
#include <vtkImageIterator.h>

#include <vtkTextProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtkImageViewer2.h>

#include <vtkNamedColors.h>
#include <vtkStdString.h>

#include <array>
#include <random>

int main (int argc,  char *argv[])
{
  vtkStdString text;
  if (argc < 2)
  {
    text = "Old Guys Rule";
  }
  else
  {
    text = argv[1];
  }

  // Create a blank, black image
  auto drawing = vtkSmartPointer<vtkImageCanvasSource2D>::New();
  drawing->SetScalarTypeToUnsignedChar();
  drawing->SetNumberOfScalarComponents(3);
  drawing->SetExtent(0, 640, 0, 480, 0, 0);
  drawing->SetDrawColor(0, 0, 0);
  drawing->FillBox(0, 629, 0, 479);

  // Create an image that will hold the final image
  auto final = vtkSmartPointer<vtkImageBlend>::New();
  final->AddInputConnection(drawing->GetOutputPort());
  final->SetOpacity(0, 1.0);
  final->Update();

  // Create an image of the string
  int dpi = 150;
  int fontSize = 24;
  vtkFreeTypeTools *freeType = vtkFreeTypeTools::GetInstance();
  freeType->ScaleToPowerTwoOff();

  // Setup a property for the strings containing fixed parameters
  auto colors = vtkSmartPointer<vtkNamedColors>::New();
  auto textProperty = vtkSmartPointer<vtkTextProperty>::New();
  textProperty->SetColor(colors->GetColor3d("Tomato").GetData());
  textProperty->SetVerticalJustificationToCentered();
  textProperty->SetJustificationToCentered();

  // Distributions for random parameters
  std::mt19937 mt(4355412); //Standard mersenne_twister_engine
  std::uniform_int_distribution<> extentXDist(0, 640);
  std::uniform_int_distribution<> extentYDist(0, 480);
  std::uniform_int_distribution<> fontDist(6, 42);
  std::uniform_real_distribution<double> orientationDist(-90, 90);

  // For each string, create an image and see if it overlaps with other images,
  // if so, skip it
  int tried = 600;
  int accepted = 0;
  for (int i = 0; i < tried; ++i)
  {
    int fontSize = fontDist(mt);
    textProperty->SetOrientation(orientationDist(mt));
    textProperty->SetFontSize(fontSize);

    auto textImage = vtkSmartPointer<vtkImageData>::New();
    freeType->RenderString(textProperty, text, dpi, textImage.GetPointer());

    // Set the extent of the text image
    std::array<int, 4> bb;
    freeType->GetBoundingBox(textProperty, text, dpi, bb.data());
    int offsetX = extentXDist(mt);
    int offsetY = extentYDist(mt);
    // Make sure the text image will fit on the final image
    if (offsetX + bb[1] - bb[0] < 639 &&
        offsetY + bb[3] - bb[2] < 479)
    {
      textImage->SetExtent(offsetX, offsetX + bb[1] - bb[0],
                           offsetY, offsetY + bb[3] - bb[2],
                           0, 0);
      auto image = vtkSmartPointer<vtkImageData>::New();
      final->Update();

      // Does the text image overlap with images on the final image 
      vtkImageIterator<unsigned char> finalIt(final->GetOutput(), textImage->GetExtent());
      unsigned char R;
      bool good = true;
      while( !finalIt.IsAtEnd())
      {
        auto finalSpan = finalIt.BeginSpan();
        while(finalSpan != finalIt.EndSpan())
        {
          R = *finalSpan++; finalSpan++; finalSpan++;
          if (R != 0)
          {
            good = false;
            break;
          }
        }
        if (!good)
        {
          break;
        }
        finalIt.NextSpan();
      }
      if (good)
      {
        accepted++;
        image->DeepCopy(textImage);
        final->AddInputData(image);
        final->SetOpacity(i + 1, 1.0); // text: 100% opaque
        final->Update();
      }
    }
  }
  std::cout << "Tried " << tried << ", but only accepted " << accepted << std::endl;
  // Display the result
  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

  auto imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputData(final->GetOutput());
  imageViewer->SetSize(640, 512);
  imageViewer->SetupInteractor(interactor);
  imageViewer->GetRenderer()->SetBackground(colors->GetColor3d("Wheat").GetData());
  imageViewer->GetRenderer()->ResetCamera();
  vtkCamera* camera = imageViewer->GetRenderer()->GetActiveCamera();
  camera->ParallelProjectionOn();
  camera->SetParallelScale(640 * .4);
  imageViewer->GetRenderWindow()->Render();
  interactor->Initialize();
  interactor->Start();

  return EXIT_SUCCESS;
}
