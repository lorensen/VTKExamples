#include <vtkImageBlend.h>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkPNGWriter.h>
#include <vtkSmartPointer.h>
#include <vtkFreeTypeTools.h>
#include <vtkTextProperty.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkStdString.h>

int main(int argc, char* argv[])
{
  // Create a black image with a red circle of radius 50 centered at (60, 60)
  vtkSmartPointer<vtkImageCanvasSource2D> drawing =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  drawing->SetScalarTypeToUnsignedChar(); // PNGWriter requires unsigned char (or unsigned short)
  drawing->SetNumberOfScalarComponents(3);
  drawing->SetExtent(0, 150, 0, 120, 0, 0); // xmin, xmax, ymin, ymax, zmin, zmax
  drawing->SetDrawColor(0, 0, 255); // red
  drawing->FillBox(0, 150, 0, 120);
  drawing->SetDrawColor(255, 0, 0); // red
  drawing->DrawCircle(60, 60, 50); // parameters: x, y, radius
  // Create an image of text
  vtkFreeTypeTools *freeType = vtkFreeTypeTools::GetInstance();
  vtkSmartPointer<vtkTextProperty> textProperty = vtkSmartPointer<vtkTextProperty>::New();
  textProperty->SetColor(1.0, 1.0, 0.0); // yellow
  textProperty->SetFontSize(24);
  textProperty->SetOrientation(25);
  vtkStdString text("Test String");
  vtkSmartPointer<vtkImageData> textImage = vtkSmartPointer<vtkImageData>::New();
  freeType->RenderString(textProperty, text, 70, textImage.GetPointer());

  // Combine the images
  vtkSmartPointer<vtkImageBlend> blend =
    vtkSmartPointer<vtkImageBlend>::New();
  blend->AddInputConnection(drawing->GetOutputPort());
  blend->AddInputData(textImage);
  blend->SetOpacity(0, 1.0); // background image: 50% opaque
  blend->SetOpacity(1, 1.0); // text: 100% opaque
  blend->Update();

  vtkSmartPointer<vtkPNGWriter> writer =
    vtkSmartPointer<vtkPNGWriter>::New();
  writer->SetFileName("output.png");
  writer->SetInputConnection(blend->GetOutputPort());
  writer->Write();

  return EXIT_SUCCESS;
}
