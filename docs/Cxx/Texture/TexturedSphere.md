[VTKExamples](/index/)/[Cxx](/Cxx)/Texture/TexturedSphere

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Texture/TestTexturedSphere.png?raw=true" width="256" />

**TexturedSphere.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkTransformTextureCoords.h>
#include <vtkTexture.h>
#include <vtkTextureMapToSphere.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageReader.h>
#include <vtkTexturedSphereSource.h>

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
      std::cout << "Usage: " << argv[0]
                << " texture(.png)"
                << " [translate]" <<std::endl;
      return EXIT_FAILURE;
  }
  double translate[3];
  if (argc > 2)
  {
      translate[0] = atof(argv[2]);
  }
  else
  {
      translate[0] = 0.0;
  }
  translate[1] = 0.0;
  translate[2] = 0.0;
  std::cout << translate[0] << ", "
            << translate[1] << ", "
            << translate[2] << "\n";
  // Create a sphere with texture coordinates
  vtkSmartPointer<vtkTexturedSphereSource> source =
    vtkSmartPointer<vtkTexturedSphereSource>::New();

  // Read texture file
  vtkSmartPointer<vtkImageReader2Factory> readerFactory =
    vtkSmartPointer<vtkImageReader2Factory>::New();
  vtkImageReader2 *imageReader =
    readerFactory->CreateImageReader2(argv[1]);
  imageReader->SetFileName(argv[1]);

  // Create texture
  vtkSmartPointer<vtkTexture> texture =
    vtkSmartPointer<vtkTexture>::New();
  texture->SetInputConnection(imageReader->GetOutputPort());

  vtkSmartPointer<vtkTransformTextureCoords> transformTexture =
    vtkSmartPointer<vtkTransformTextureCoords>::New();
  transformTexture->SetInputConnection(source->GetOutputPort());
  transformTexture->SetPosition(translate);

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(transformTexture->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper( mapper );
  actor->SetTexture( texture );

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->SetBackground(.1, .2, .3);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer( renderer );

  vtkSmartPointer<vtkRenderWindowInteractor> renWinInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renWinInteractor->SetRenderWindow( renderWindow );

  renderWindow->Render();
  renWinInteractor->Start();

  imageReader->Delete();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(TexturedSphere)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(TexturedSphere MACOSX_BUNDLE TexturedSphere.cxx)
 
target_link_libraries(TexturedSphere ${VTK_LIBRARIES})
```

**Download and Build TexturedSphere**

Click [here to download TexturedSphere](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/TexturedSphere.tar) and its *CMakeLists.txt* file.
Once the *tarball TexturedSphere.tar* has been downloaded and extracted,
```
cd TexturedSphere/build 
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
./TexturedSphere
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

