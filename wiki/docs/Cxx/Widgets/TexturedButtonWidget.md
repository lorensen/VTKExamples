[VTKExamples](/home/)/[Cxx](/Cxx)/Widgets/TexturedButtonWidget

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Widgets/TestTexturedButtonWidget.png?raw=true" width="256" />

### Description
This example creates a textured 2D button. The button is placed in the upper right of the display.

**TexturedButtonWidget.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkImageData.h>

#include <vtkCoordinate.h>
#include <vtkSphereSource.h>
#include <vtkButtonWidget.h>
#include <vtkTexturedButtonRepresentation2D.h>

static void CreateImage(vtkSmartPointer<vtkImageData> image,
                        unsigned char *color1,
                        unsigned char *color2);

int main(int, char *[])
{
  // Create two images for texture
  vtkSmartPointer<vtkImageData> image1 =
    vtkSmartPointer<vtkImageData>::New();
  vtkSmartPointer<vtkImageData> image2 =
    vtkSmartPointer<vtkImageData>::New();
  unsigned char banana[3] = { 227, 207, 87 };
  unsigned char tomato[3] = { 255, 99, 71 };
  CreateImage(image1, banana, tomato);
  CreateImage(image2, tomato, banana);

  // Create some geometry
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Create the widget and its representation
  vtkSmartPointer<vtkTexturedButtonRepresentation2D> buttonRepresentation =
    vtkSmartPointer<vtkTexturedButtonRepresentation2D>::New();
  buttonRepresentation->SetNumberOfStates(2);
  buttonRepresentation->SetButtonTexture(0, image1);
  buttonRepresentation->SetButtonTexture(1, image2);

  vtkSmartPointer<vtkButtonWidget> buttonWidget =
    vtkSmartPointer<vtkButtonWidget>::New();
  buttonWidget->SetInteractor(renderWindowInteractor);
  buttonWidget->SetRepresentation(buttonRepresentation);

  // Add the actors to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(.1, .2, .5);

  renderWindow->SetSize(640, 480);
  renderWindow->Render();

  // Place the widget. Must be done after a render so that the
  // viewport is defined.
  // Here the widget placement is in normalized display coordinates
  vtkSmartPointer<vtkCoordinate> upperRight =
    vtkSmartPointer<vtkCoordinate>::New();
  upperRight->SetCoordinateSystemToNormalizedDisplay();
  upperRight->SetValue(1.0, 1.0);

  double bds[6];
  double sz = 50.0;
  bds[0] = upperRight->GetComputedDisplayValue(renderer)[0] - sz;
  bds[1] = bds[0] + sz;
  bds[2] = upperRight->GetComputedDisplayValue(renderer)[1] - sz;
  bds[3] = bds[2] + sz;
  bds[4] = bds[5] = 0.0;

  // Scale to 1, default is .5
  buttonRepresentation->SetPlaceFactor(1);
  buttonRepresentation->PlaceWidget(bds);

  buttonWidget->On();

  // Begin mouse interaction
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

void CreateImage(vtkSmartPointer<vtkImageData> image,
                 unsigned char* color1,
                 unsigned char* color2)
{
  // Specify the size of the image data
  image->SetDimensions(10, 10, 1);
#if VTK_MAJOR_VERSION <= 5
  image->SetNumberOfScalarComponents(3);
  image->SetScalarTypeToUnsignedChar();
#else
  image->AllocateScalars(VTK_UNSIGNED_CHAR, 3);
#endif
  int* dims = image->GetDimensions();

  // Fill the image with
  for (int y = 0; y < dims[1]; y++)
  {
    for (int x = 0; x < dims[0]; x++)
    {
      unsigned char* pixel =
        static_cast<unsigned char*>(image->GetScalarPointer(x, y, 0));
      if (x < 5)
      {
        pixel[0] = color1[0];
        pixel[1] = color1[1];
        pixel[2] = color1[2];
      }
      else
      {
        pixel[0] = color2[0];
        pixel[1] = color2[1];
        pixel[2] = color2[2];
      }
    }
  }
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(TexturedButtonWidget)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(TexturedButtonWidget MACOSX_BUNDLE TexturedButtonWidget.cxx)
 
target_link_libraries(TexturedButtonWidget ${VTK_LIBRARIES})
```

**Download and Build TexturedButtonWidget**

Click [here to download TexturedButtonWidget](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/TexturedButtonWidget.tar) and its *CMakeLists.txt* file.
Once the *tarball TexturedButtonWidget.tar* has been downloaded and extracted,
```
cd TexturedButtonWidget/build 
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
./TexturedButtonWidget
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

