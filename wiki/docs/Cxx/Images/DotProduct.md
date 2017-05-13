[VTKExamples](Home)/[Cxx](Cxx)/Images/DotProduct

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Images/TestDotProduct.png" width="256" />

### Description
This example demonstrates how to take the pixel-wise dot product of two vector images. The output is a scalar image.

Two images, each 2x2x1, are created and filled with 3-vectors. The dot product of each pair of corresponding pixels is produced by the vtkImageDotProduct filter and output to the screen.

**DotProduct.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkImageMathematics.h>
#include <vtkImageCast.h>
#include <vtkImageMapper3D.h>
#include <vtkImageActor.h>
#include <vtkPointData.h>
#include <vtkImageData.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageDotProduct.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkGlyph3DMapper.h>
#include <vtkArrowSource.h>
#include <vtkXMLImageDataWriter.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageData> image1 = 
    vtkSmartPointer<vtkImageData>::New();
  image1->SetExtent(0, 1, 0, 1, 0, 0);
#if VTK_MAJOR_VERSION <= 5
  image1->SetNumberOfScalarComponents(3);
  image1->SetScalarTypeToFloat();
#else
  image1->AllocateScalars(VTK_FLOAT,3);
#endif  

  int coord[3]; float* pixel;
  
  // Fill the image with vectors
  coord[0] = 0; coord[1] = 0; coord[2] = 0;
  pixel = static_cast<float*>(image1->GetScalarPointer(coord));
  pixel[0] = 1.0; pixel[1] = 0.0; pixel[2] = 0.0;
  
  coord[0] = 0; coord[1] = 1; coord[2] = 0;
  pixel = static_cast<float*>(image1->GetScalarPointer(coord));
  pixel[0] = 0.0; pixel[1] = 1.0; pixel[2] = 0.0;
  
  coord[0] = 1; coord[1] = 0; coord[2] = 0;
  pixel = static_cast<float*>(image1->GetScalarPointer(coord));
  pixel[0] = 1.0; pixel[1] = 0.0; pixel[2] = 0.0;
  
  coord[0] = 1; coord[1] = 1; coord[2] = 0;
  pixel = static_cast<float*>(image1->GetScalarPointer(coord));
  pixel[0] = 0.0; pixel[1] = 1.0; pixel[2] = 0.0;

  vtkSmartPointer<vtkXMLImageDataWriter> writer =
    vtkSmartPointer<vtkXMLImageDataWriter>::New();
#if VTK_MAJOR_VERSION <= 5
  writer->SetInputConnection(image1->GetProducerPort());
#else
  writer->SetInputData(image1);
#endif
  writer->SetFileName("test.vti");
  writer->Write();
  
  // Create another image
  vtkSmartPointer<vtkImageData> image2 = 
    vtkSmartPointer<vtkImageData>::New();
  image2->SetExtent(0, 1, 0, 1, 0, 0);
#if VTK_MAJOR_VERSION <= 5
  image2->SetNumberOfScalarComponents(3);
  image2->SetScalarTypeToFloat();
#else
  image2->AllocateScalars(VTK_FLOAT,3);
#endif
  // Fill the image with vectors
  coord[0] = 0; coord[1] = 0; coord[2] = 0;
  pixel = static_cast<float*>(image2->GetScalarPointer(coord));
  pixel[0] = 1.0; pixel[1] = 0.0; pixel[2] = 0.0;
  
  coord[0] = 0; coord[1] = 1; coord[2] = 0;
  pixel = static_cast<float*>(image2->GetScalarPointer(coord));
  pixel[0] = 1.0; pixel[1] = 0.0; pixel[2] = 0.0;
  
  coord[0] = 1; coord[1] = 0; coord[2] = 0;
  pixel = static_cast<float*>(image2->GetScalarPointer(coord));
  pixel[0] = 0.5; pixel[1] = 0.0; pixel[2] = 0.0;
  
  coord[0] = 1; coord[1] = 1; coord[2] = 0;
  pixel = static_cast<float*>(image2->GetScalarPointer(coord));
  pixel[0] = 0.5; pixel[1] = 0.0; pixel[2] = 0.0;
  
  // Compute the dot product of the images pixel wise
  vtkSmartPointer<vtkImageDotProduct> dotProductFilter = 
    vtkSmartPointer<vtkImageDotProduct>::New();
#if VTK_MAJOR_VERSION <= 5
  dotProductFilter->SetInput1(image1);
  dotProductFilter->SetInput2(image2);
#else
  dotProductFilter->SetInput1Data(image1);
  dotProductFilter->SetInput2Data(image2);
#endif
  dotProductFilter->Update();
  std::cout << "output is of type: " << dotProductFilter->GetOutput()->GetScalarTypeAsString() << std::endl;

  vtkSmartPointer<vtkImageMathematics> imageMath =
    vtkSmartPointer<vtkImageMathematics>::New();
  imageMath->SetOperationToMultiplyByK();
  imageMath->SetConstantK(255.0);
  imageMath->SetInputConnection(dotProductFilter->GetOutputPort());
  imageMath->Update();

  vtkSmartPointer<vtkImageCast> imageCast =
    vtkSmartPointer<vtkImageCast>::New();
  imageCast->SetOutputScalarTypeToUnsignedChar();
  imageCast->SetInputConnection(imageMath->GetOutputPort());
  imageCast->Update();
  
  vtkSmartPointer<vtkImageActor> dotProductActor =
    vtkSmartPointer<vtkImageActor>::New();
  dotProductActor->GetMapper()->SetInputConnection(imageCast->GetOutputPort());
  
  // Display output to the terminal
  for(vtkIdType i = 0; i < 2; i++)
    { 
    for(vtkIdType j = 0; j < 2; j++)
      {
      coord[0] = i; coord[1] = j; coord[2] = 0;
      pixel = static_cast<float*>(dotProductFilter->GetOutput()->GetScalarPointer(coord));
      std::cout << "Pixel (" << i << ", " << j << ") : " << pixel[0] << std::endl;
      }
    }

  image1->GetPointData()->SetActiveVectors("ImageScalars");
  image2->GetPointData()->SetActiveVectors("ImageScalars");
  
  vtkSmartPointer<vtkArrowSource> arrowSource =
    vtkSmartPointer<vtkArrowSource>::New();

  vtkSmartPointer<vtkGlyph3DMapper> glyph3Dmapper1 =
    vtkSmartPointer<vtkGlyph3DMapper>::New();
  glyph3Dmapper1->SetSourceConnection(arrowSource->GetOutputPort());
#if VTK_MAJOR_VERSION <= 5
  glyph3Dmapper1->SetInputConnection(image1->GetProducerPort());
#else
  glyph3Dmapper1->SetInputData(image1);
#endif
  glyph3Dmapper1->Update();

  vtkSmartPointer<vtkActor> actor1 =
    vtkSmartPointer<vtkActor>::New();
  actor1->SetMapper(glyph3Dmapper1);

  vtkSmartPointer<vtkGlyph3DMapper> glyph3Dmapper2 =
    vtkSmartPointer<vtkGlyph3DMapper>::New();
  glyph3Dmapper2->SetSourceConnection(arrowSource->GetOutputPort());
#if VTK_MAJOR_VERSION <= 5
  glyph3Dmapper2->SetInputConnection(image2->GetProducerPort());
#else
  glyph3Dmapper2->SetInputData(image2);
#endif
  glyph3Dmapper2->Update();

  vtkSmartPointer<vtkActor> actor2 =
    vtkSmartPointer<vtkActor>::New();
  actor2->SetMapper(glyph3Dmapper2);

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.33, 1.0};
  double centerViewport[4] = {0.33, 0.0, 0.66, 1.0};
  double rightViewport[4] = {0.66, 0.0, 1.0, 1.0};
  
  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> leftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  leftRenderer->SetViewport(leftViewport);

  vtkSmartPointer<vtkRenderer> centerRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  centerRenderer->SetViewport(centerViewport);

  vtkSmartPointer<vtkRenderer> rightRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  rightRenderer->SetViewport(rightViewport);
  
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(leftRenderer);
  renderWindow->AddRenderer(centerRenderer);
  renderWindow->AddRenderer(rightRenderer);
  
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actor to the scene
  leftRenderer->AddActor(actor1);
  centerRenderer->AddActor(actor2);
  rightRenderer->AddActor(dotProductActor);

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DotProduct)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DotProduct MACOSX_BUNDLE DotProduct.cxx)
 
target_link_libraries(DotProduct ${VTK_LIBRARIES})
```

**Download and Build DotProduct**

Click [here to download DotProduct](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DotProduct.tar) and its *CMakeLists.txt* file.
Once the *tarball DotProduct.tar* has been downloaded and extracted,
```
cd DotProduct/build 
```
If VTK is installed:
```
cmake ..
```
If VTK is not installed but compiled on your system, you will need to specify the path to your VTK build:
```
cmake -DVTK_DIR:PATH=/home/me/vtk_build ..
```
Build the project:
```
make
```
and run it:
```
./DotProduct
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

