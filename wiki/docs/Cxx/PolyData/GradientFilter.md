[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/GradientFilter

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestGradientFilter.png?raw=true" width="256" />

### Description
Computes the gradient of a scalar field defined on the points of a data set.

**GradientFilter.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkArrowSource.h>
#include <vtkAssignAttribute.h>
#include <vtkCamera.h>
#include <vtkExtractEdges.h>
#include <vtkGlyph3D.h>
#include <vtkGradientFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTubeFilter.h>
#include <vtkUnstructuredGridReader.h>

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cerr << "Usage: " << argv[0]
              << " Filename(.vtk)" << std::endl;
  }
  // Create the reader for the data.
  // This is the data that will be volume rendered.
  std::string filename = argv[1];
  std::cout << "Loading " << filename.c_str() << std::endl;
  vtkSmartPointer<vtkUnstructuredGridReader> reader =
    vtkSmartPointer<vtkUnstructuredGridReader>::New();
  reader->SetFileName(filename.c_str());

  vtkSmartPointer<vtkExtractEdges> edges =
    vtkSmartPointer<vtkExtractEdges>::New();
  edges->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkTubeFilter> tubes =
    vtkSmartPointer<vtkTubeFilter>::New();
  tubes->SetInputConnection(edges->GetOutputPort());
  tubes->SetRadius(0.0625);
  tubes->SetVaryRadiusToVaryRadiusOff();
  tubes->SetNumberOfSides(32);

  vtkSmartPointer<vtkPolyDataMapper> tubesMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  tubesMapper->SetInputConnection(tubes->GetOutputPort());
  tubesMapper->SetScalarRange(0.0, 26.0);

  vtkSmartPointer<vtkActor> tubesActor =
    vtkSmartPointer<vtkActor>::New();
  tubesActor->SetMapper(tubesMapper);

  vtkSmartPointer<vtkGradientFilter> gradients =
    vtkSmartPointer<vtkGradientFilter>::New();
  gradients->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkAssignAttribute> vectors =
    vtkSmartPointer<vtkAssignAttribute>::New();
  vectors->SetInputConnection(gradients->GetOutputPort());
  vectors->Assign("Gradients", vtkDataSetAttributes::VECTORS,
                  vtkAssignAttribute::POINT_DATA);

  vtkSmartPointer<vtkArrowSource> arrow =
    vtkSmartPointer<vtkArrowSource>::New();

  vtkSmartPointer<vtkGlyph3D> glyphs =
    vtkSmartPointer<vtkGlyph3D>::New();
  glyphs->SetInputConnection(0, vectors->GetOutputPort());
  glyphs->SetInputConnection(1, arrow->GetOutputPort());
  glyphs->ScalingOn();
  glyphs->SetScaleModeToScaleByVector();
  glyphs->SetScaleFactor(0.25);
  glyphs->OrientOn();
  glyphs->ClampingOff();
  glyphs->SetVectorModeToUseVector();
  glyphs->SetIndexModeToOff();

  vtkSmartPointer<vtkPolyDataMapper> glyphMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  glyphMapper->SetInputConnection(glyphs->GetOutputPort());
  glyphMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> glyphActor =
    vtkSmartPointer<vtkActor>::New();
  glyphActor->SetMapper(glyphMapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(tubesActor);
  renderer->AddActor(glyphActor);
  renderer->SetBackground(0.328125, 0.347656, 0.425781);

  vtkSmartPointer<vtkRenderWindow> renwin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renwin->AddRenderer(renderer);
  renwin->SetSize(350, 500);

  renderer->ResetCamera();
  vtkCamera *camera = renderer->GetActiveCamera();
  camera->Elevation(-80.0);
  camera->OrthogonalizeViewUp();
  camera->Azimuth(135.0);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renwin);
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(GradientFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(GradientFilter MACOSX_BUNDLE GradientFilter.cxx)
 
target_link_libraries(GradientFilter ${VTK_LIBRARIES})
```

**Download and Build GradientFilter**

Click [here to download GradientFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/GradientFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball GradientFilter.tar* has been downloaded and extracted,
```
cd GradientFilter/build 
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
./GradientFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

