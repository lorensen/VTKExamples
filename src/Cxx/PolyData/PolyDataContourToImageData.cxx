#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkImageData.h>
#include <vtkSphereSource.h>
#include <vtkMetaImageWriter.h>
#include <vtkPolyDataToImageStencil.h>
#include <vtkImageStencil.h>
#include <vtkPointData.h>
#include <vtkCutter.h>
#include <vtkPlane.h>
#include <vtkStripper.h>
#include <vtkLinearExtrusionFilter.h>
#include <vtkXMLPolyDataWriter.h>

// This example generates a sphere, cuts it with a plane and, therefore,
// generates a circlular contour (vtkPolyData). Subsequently a binary
// image representation (vtkImageData) is extracted from it. Internally
// vtkPolyDataToImageStencil and vtkLinearExtrusionFilter are
// utilized. Both the circular poly data (circle.vtp) and the resultant
// image (labelImage.mhd) are saved to disk.

int main(int, char *[])
{
  // 3D source sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetPhiResolution(30);
  sphereSource->SetThetaResolution(30);
  sphereSource->SetCenter(40, 40, 0);
  sphereSource->SetRadius(20);

  // generate circle by cutting the sphere with an implicit plane
  // (through its center, axis-aligned)
  vtkSmartPointer<vtkCutter> circleCutter =
    vtkSmartPointer<vtkCutter>::New();
  circleCutter->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkPlane> cutPlane =
    vtkSmartPointer<vtkPlane>::New();
  cutPlane->SetOrigin(sphereSource->GetCenter());
  cutPlane->SetNormal(0, 0, 1);
  circleCutter->SetCutFunction(cutPlane);

  vtkSmartPointer<vtkStripper> stripper =
    vtkSmartPointer<vtkStripper>::New();
  stripper->SetInputConnection(circleCutter->GetOutputPort()); // valid circle
  stripper->Update();

  // that's our circle
  vtkSmartPointer<vtkPolyData> circle = stripper->GetOutput();

  // write circle out
  vtkSmartPointer<vtkXMLPolyDataWriter> polyDataWriter =
      vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  polyDataWriter->SetInputData(circle);
  polyDataWriter->SetFileName("circle.vtp");
  polyDataWriter->SetCompressorTypeToNone();
  polyDataWriter->SetDataModeToAscii();
  polyDataWriter->Write();

  // prepare the binary image's voxel grid
  vtkSmartPointer<vtkImageData> whiteImage =
      vtkSmartPointer<vtkImageData>::New();
  double bounds[6];
  circle->GetBounds(bounds);
  double spacing[3]; // desired volume spacing
  spacing[0] = 0.5;
  spacing[1] = 0.5;
  spacing[2] = 0.5;
  whiteImage->SetSpacing(spacing);

  // compute dimensions
  int dim[3];
  for (int i = 0; i < 3; i++)
  {
    dim[i] = static_cast<int>(ceil((bounds[i * 2 + 1] - bounds[i * 2]) /
        spacing[i])) + 1;
    if (dim[i] < 1)
      dim[i] = 1;
  }
  whiteImage->SetDimensions(dim);
  whiteImage->SetExtent(0, dim[0] - 1, 0, dim[1] - 1, 0, dim[2] - 1);
  double origin[3];

  // NOTE: I am not sure whether or not we had to add some offset!
  origin[0] = bounds[0];// + spacing[0] / 2;
  origin[1] = bounds[2];// + spacing[1] / 2;
  origin[2] = bounds[4];// + spacing[2] / 2;
  whiteImage->SetOrigin(origin);
  whiteImage->AllocateScalars(VTK_UNSIGNED_CHAR,1);

  // fill the image with foreground voxels:
  unsigned char inval = 255;
  unsigned char outval = 0;
  vtkIdType count = whiteImage->GetNumberOfPoints();
  for (vtkIdType i = 0; i < count; ++i)
  {
    whiteImage->GetPointData()->GetScalars()->SetTuple1(i, inval);
  }

  // sweep polygonal data (this is the important thing with contours!)
  vtkSmartPointer<vtkLinearExtrusionFilter> extruder =
      vtkSmartPointer<vtkLinearExtrusionFilter>::New();
  extruder->SetInputData(circle);
  extruder->SetScaleFactor(1.);
  extruder->SetExtrusionTypeToVectorExtrusion();
  extruder->SetVector(0, 0, 1);
  extruder->Update();

  // polygonal data --> image stencil:
  vtkSmartPointer<vtkPolyDataToImageStencil> pol2stenc =
    vtkSmartPointer<vtkPolyDataToImageStencil>::New();
  pol2stenc->SetTolerance(0); // important if extruder->SetVector(0, 0, 1) !!!
  pol2stenc->SetInputConnection(extruder->GetOutputPort());
  pol2stenc->SetOutputOrigin(origin);
  pol2stenc->SetOutputSpacing(spacing);
  pol2stenc->SetOutputWholeExtent(whiteImage->GetExtent());
  pol2stenc->Update();

  // cut the corresponding white image and set the background:
  vtkSmartPointer<vtkImageStencil> imgstenc =
    vtkSmartPointer<vtkImageStencil>::New();
  imgstenc->SetInputData(whiteImage);
  imgstenc->SetStencilConnection(pol2stenc->GetOutputPort());
  imgstenc->ReverseStencilOff();
  imgstenc->SetBackgroundValue(outval);
  imgstenc->Update();
  imgstenc->GetOutput()->Print(std::cout);

  vtkSmartPointer<vtkMetaImageWriter> imageWriter =
    vtkSmartPointer<vtkMetaImageWriter>::New();
  imageWriter->SetFileName("labelImage.mhd");
  imageWriter->SetInputConnection(imgstenc->GetOutputPort());
  imageWriter->Write();

  return EXIT_SUCCESS;
}
