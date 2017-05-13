[VTKExamples](/home/)/[Cxx](/Cxx)/Visualization/TextureMapQuad

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestTextureMapQuad.png?raw=true" width="256" />

### Description
This example defines 4 points (coplanar) and textures them using the input image.

**TextureMapQuad.cxx**
```c++
#include <vtkVersion.h>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkCellArray.h>
#include <vtkJPEGReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkTexture.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkFloatArray.h>
#include <vtkPolygon.h>
#include <string>

int main ( int argc, char *argv[] )
{
  // Parse command line arguments
  if ( argc != 2 )
  {
    std::cerr << "Usage:" << argv[0] << " Filename" << std::endl;
    return EXIT_FAILURE;
  }

  std::string inputFilename = argv[1];

  // Read the image which will be the texture
  vtkSmartPointer<vtkJPEGReader> jPEGReader =
    vtkSmartPointer<vtkJPEGReader>::New();
  jPEGReader->SetFileName ( inputFilename.c_str() );

  // Create a plane
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.0, 0.0, 0.0);
  points->InsertNextPoint(1.0, 0.0, 0.0);
  points->InsertNextPoint(1.0, 1.0, 0.0);
  points->InsertNextPoint(0.0, 2.0, 0.0);

  vtkSmartPointer<vtkCellArray> polygons =
    vtkSmartPointer<vtkCellArray>::New();
  vtkSmartPointer<vtkPolygon> polygon =
    vtkSmartPointer<vtkPolygon>::New();
  polygon->GetPointIds()->SetNumberOfIds(4); //make a quad
  polygon->GetPointIds()->SetId(0, 0);
  polygon->GetPointIds()->SetId(1, 1);
  polygon->GetPointIds()->SetId(2, 2);
  polygon->GetPointIds()->SetId(3, 3);

  polygons->InsertNextCell(polygon);

  vtkSmartPointer<vtkPolyData> quad =
    vtkSmartPointer<vtkPolyData>::New();
  quad->SetPoints(points);
  quad->SetPolys(polygons);

  vtkSmartPointer<vtkFloatArray> textureCoordinates =
    vtkSmartPointer<vtkFloatArray>::New();
  textureCoordinates->SetNumberOfComponents(3);
  textureCoordinates->SetName("TextureCoordinates");

  float tuple[3] = {0.0, 0.0, 0.0};
  textureCoordinates->InsertNextTuple(tuple);
  tuple[0] = 1.0; tuple[1] = 0.0; tuple[2] = 0.0;
  textureCoordinates->InsertNextTuple(tuple);
  tuple[0] = 1.0; tuple[1] = 1.0; tuple[2] = 0.0;
  textureCoordinates->InsertNextTuple(tuple);
  tuple[0] = 0.0; tuple[1] = 2.0; tuple[2] = 0.0;
  textureCoordinates->InsertNextTuple(tuple);

  quad->GetPointData()->SetTCoords(textureCoordinates);

  // Apply the texture
  vtkSmartPointer<vtkTexture> texture =
    vtkSmartPointer<vtkTexture>::New();
  texture->SetInputConnection(jPEGReader->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  mapper->SetInput(quad);
#else
  mapper->SetInputData(quad);
#endif

  vtkSmartPointer<vtkActor> texturedQuad =
    vtkSmartPointer<vtkActor>::New();
  texturedQuad->SetMapper(mapper);
  texturedQuad->SetTexture(texture);

  // Visualize the textured plane
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(texturedQuad);
  renderer->SetBackground(1,1,1); // Background color white
  renderer->ResetCamera();

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderWindow->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(TextureMapQuad)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(TextureMapQuad MACOSX_BUNDLE TextureMapQuad.cxx)
 
target_link_libraries(TextureMapQuad ${VTK_LIBRARIES})
```

**Download and Build TextureMapQuad**

Click [here to download TextureMapQuad](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/TextureMapQuad.tar) and its *CMakeLists.txt* file.
Once the *tarball TextureMapQuad.tar* has been downloaded and extracted,
```
cd TextureMapQuad/build 
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
./TextureMapQuad
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

