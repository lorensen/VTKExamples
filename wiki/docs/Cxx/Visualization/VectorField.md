[VTKExamples](Home)/[Cxx](Cxx)/Visualization/VectorField

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Visualization/TestVectorField.png" width="256" />

**VectorField.cxx**
```c++
#include <vtkVersion.h>
#include <vtkArrowSource.h>
#include <vtkCellArray.h>
#include <vtkGlyph2D.h>
#include <vtkPointData.h>
#include <vtkImageData.h>
#include <vtkImageSliceMapper.h>
#include <vtkImageSlice.h>
#include <vtkInteractorStyleImage.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataWriter.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageData> image = vtkSmartPointer<vtkImageData>::New();

  // Specify the size of the image data
  image->SetDimensions(50,50,1);

#if VTK_MAJOR_VERSION <= 5
  image->SetNumberOfScalarComponents(2);
  image->SetScalarTypeToFloat();
  image->AllocateScalars();
#else
  image->AllocateScalars(VTK_FLOAT,2);
#endif
  int* dims = image->GetDimensions();

  // Zero the image
  for (int y = 0; y < dims[1]; y++)
  {
    for (int x = 0; x < dims[0]; x++)
    {
      float* pixel = static_cast<float*>(image->GetScalarPointer(x,y,0));
      pixel[0] = 0.0;
      pixel[1] = 0.0;
    }
  }

  {
  float* pixel = static_cast<float*>(image->GetScalarPointer(20,20,0));
  pixel[0] = -10.0;
  pixel[1] = 5.0;
  }

  {
  float* pixel = static_cast<float*>(image->GetScalarPointer(30,30,0));
  pixel[0] = 10.0;
  pixel[1] = 10.0;
  }

  // A better way to do this is (should be tested for compilablilty and correctness):
  // image->GetPointData()->SetActiveVectors(image->GetPointData()->GetScalars()->GetName().c_str());
  image->GetPointData()->SetActiveVectors("ImageScalars");

  // Setup the arrows
  vtkSmartPointer<vtkArrowSource> arrowSource = vtkSmartPointer<vtkArrowSource>::New();
  arrowSource->Update();

  vtkSmartPointer<vtkGlyph2D> glyphFilter = vtkSmartPointer<vtkGlyph2D>::New();
  glyphFilter->SetSourceConnection(arrowSource->GetOutputPort());
  glyphFilter->OrientOn();
  glyphFilter->SetVectorModeToUseVector();
#if VTK_MAJOR_VERSION <= 5
  glyphFilter->SetInputConnection(image->GetProducerPort());
#else
  glyphFilter->SetInputData(image);
#endif
  glyphFilter->Update();

  // Create actors
  vtkSmartPointer<vtkImageSliceMapper> imageMapper = vtkSmartPointer<vtkImageSliceMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  imageMapper->SetInputConnection(image->GetProducerPort());
#else
  imageMapper->SetInputData(image);
#endif

  vtkSmartPointer<vtkImageSlice> imageSlice = vtkSmartPointer<vtkImageSlice>::New();
  imageSlice->SetMapper(imageMapper);

  vtkSmartPointer<vtkPolyDataMapper> vectorMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  vectorMapper->SetInputConnection(glyphFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> vectorActor = vtkSmartPointer<vtkActor>::New();
  vectorActor->SetMapper(vectorMapper);

  // Setup renderer
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddViewProp(imageSlice);
  renderer->AddViewProp(vectorActor);
  renderer->ResetCamera();

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // Setup render window interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
  //renderWindowInteractor->SetInteractorStyle(style);

  // Render and start interaction
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(VectorField)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(VectorField MACOSX_BUNDLE VectorField.cxx)
 
target_link_libraries(VectorField ${VTK_LIBRARIES})
```

**Download and Build VectorField**

Click [here to download VectorField](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/VectorField.tar) and its *CMakeLists.txt* file.
Once the *tarball VectorField.tar* has been downloaded and extracted,
```
cd VectorField/build 
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
./VectorField
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

