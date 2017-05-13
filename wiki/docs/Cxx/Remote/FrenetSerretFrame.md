[VTKExamples](/home/)/[Cxx](/Cxx)/Remote/FrenetSerretFrame

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Remote/TestFrenetSerretFrame.png?raw=true" width="256" />

### Description
This example requires the remote module ''SplineDrivenImageSampler.'' Check to see if the file ''SplineDrivenImageSlicer.remote.cmake'' exists in VTK/Remote. If it does not, copy [this file](https://gitlab.kitware.com/vtk/vtk/raw/master/Remote/SplineDrivenImageSlicer.remote.cmake) to ''VTK/Remote/SplineDrivenImageSlicer.remote.cmake''.

Next
1. reconfigure with cmake.
2. Then enable the module setting ''Module_SplineDrivenImageSlicer:BOOL=ON''
3. `make`

The classes used in this example are described in [A Spline-Driven Image Slicer](http://www.vtkjournal.org/browse/publication/838). In the example, the normal vectors are yellow, the tangent vectors are red and the binormal vectors are green.

**FrenetSerretFrame.cxx**
```c++
#include <vtkFrenetSerretFrame.h>

#include <vtkSmartPointer.h>

#include <vtkParametricSpline.h>
#include <vtkParametricFunctionSource.h>

#include <vtkSphereSource.h>
#include <vtkArrowSource.h>
#include <vtkGlyph3D.h>

#include <vtkPointSource.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>

#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>
#include <vtkCamera.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

static void MakeGlyphs(vtkPolyData *src, double size, vtkGlyph3D *glyph);

int main(int, char *[])
{
  // Generate  some random points
  int numberOfPoints = 8;
  vtkSmartPointer<vtkPointSource> pointSource = 
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(numberOfPoints);
  pointSource->Update();
  
  vtkPoints* points = pointSource->GetOutput()->GetPoints();
    
  vtkSmartPointer<vtkParametricSpline> spline = 
    vtkSmartPointer<vtkParametricSpline>::New();
  spline->SetPoints(points);
  
  vtkSmartPointer<vtkParametricFunctionSource> functionSource = 
    vtkSmartPointer<vtkParametricFunctionSource>::New();
  functionSource->SetParametricFunction(spline);
  functionSource->SetUResolution(10 * numberOfPoints);
  functionSource->SetVResolution(10 * numberOfPoints);
  functionSource->SetWResolution(10 * numberOfPoints);

  // Create the frame
  vtkSmartPointer<vtkFrenetSerretFrame> frame =
    vtkSmartPointer<vtkFrenetSerretFrame>::New();
  frame->SetInputConnection(functionSource->GetOutputPort());
  frame->ConsistentNormalsOn();
  frame->Update();

  vtkSmartPointer<vtkGlyph3D> glyph3DNormals =
    vtkSmartPointer<vtkGlyph3D>::New();
  vtkSmartPointer<vtkGlyph3D> glyph3DTangents =
    vtkSmartPointer<vtkGlyph3D>::New();
  vtkSmartPointer<vtkGlyph3D> glyph3DBinormals =
    vtkSmartPointer<vtkGlyph3D>::New();
  
  // for each vector, create a Glyph3D and DeepCopy the output
  double radius = .05;
  frame->GetOutput()->GetPointData()->SetActiveVectors("FSNormals");
  MakeGlyphs(frame->GetOutput(), radius, glyph3DNormals.GetPointer());
  vtkSmartPointer<vtkPolyData> normalsPolyData =
    vtkSmartPointer<vtkPolyData>::New();
  normalsPolyData->DeepCopy(glyph3DNormals->GetOutput());

  frame->GetOutput()->GetPointData()->SetActiveVectors("FSTangents");
  MakeGlyphs(frame->GetOutput(), radius, glyph3DTangents.GetPointer());
  vtkSmartPointer<vtkPolyData> tangentsPolyData =
    vtkSmartPointer<vtkPolyData>::New();
  tangentsPolyData->DeepCopy(glyph3DTangents->GetOutput());

  frame->GetOutput()->GetPointData()->SetActiveVectors("FSBinormals");
  MakeGlyphs(frame->GetOutput(), radius, glyph3DBinormals.GetPointer());
  vtkSmartPointer<vtkPolyData> binormalsPolyData =
    vtkSmartPointer<vtkPolyData>::New();
  binormalsPolyData->DeepCopy(glyph3DBinormals->GetOutput());

// Setup actors and mappers
  vtkSmartPointer<vtkPolyDataMapper> glyph3DNormalsMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  glyph3DNormalsMapper->SetInputData(normalsPolyData);

  vtkSmartPointer<vtkActor> glyph3DNormalsActor =
    vtkSmartPointer<vtkActor>::New();
  glyph3DNormalsActor->SetMapper(glyph3DNormalsMapper);
  glyph3DNormalsActor->GetProperty()->SetColor(0.8900, 0.8100, 0.3400);

  vtkSmartPointer<vtkPolyDataMapper> glyph3DTangentsMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  glyph3DTangentsMapper->SetInputData(tangentsPolyData);

  vtkSmartPointer<vtkActor> glyph3DTangentsActor =
    vtkSmartPointer<vtkActor>::New();
  glyph3DTangentsActor->SetMapper(glyph3DTangentsMapper);
  glyph3DTangentsActor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);

  vtkSmartPointer<vtkPolyDataMapper> glyph3DBinormalsMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  glyph3DBinormalsMapper->SetInputData(binormalsPolyData);

  vtkSmartPointer<vtkActor> glyph3DBinormalsActor =
    vtkSmartPointer<vtkActor>::New();
  glyph3DBinormalsActor->SetMapper(glyph3DBinormalsMapper);
  glyph3DBinormalsActor->GetProperty()->SetColor(0.1804,0.5451,0.3412);

  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(functionSource->GetOutputPort());
  
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  
  // Setup render window, renderer, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(glyph3DNormalsActor);
  renderer->AddActor(glyph3DTangentsActor);
  renderer->AddActor(glyph3DBinormalsActor);
  renderer->AddActor(actor);

  renderer->SetBackground(.4, .5, .7);

  // Pick a good view
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(120);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->GetActiveCamera()->Dolly(1.8);
  renderer->ResetCameraClippingRange();

  renderWindow->SetSize(640, 480);
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}

void MakeGlyphs(vtkPolyData *src, double size, vtkGlyph3D *glyph)
{
  // Source for the glyph filter
  vtkSmartPointer<vtkArrowSource> arrow =
    vtkSmartPointer<vtkArrowSource>::New();
  arrow->SetTipResolution(16);
  arrow->SetTipLength(.3);
  arrow->SetTipRadius(.1);

  glyph->SetSourceConnection(arrow->GetOutputPort());
  glyph->SetInputData(src);
  glyph->SetVectorModeToUseVector();
  glyph->SetScaleModeToScaleByVector();
  glyph->SetScaleFactor(size);
  glyph->OrientOn();
  glyph->Update();
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(FrenetSerretFrame)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(FrenetSerretFrame MACOSX_BUNDLE FrenetSerretFrame.cxx)
 
target_link_libraries(FrenetSerretFrame ${VTK_LIBRARIES})
```

**Download and Build FrenetSerretFrame**

Click [here to download FrenetSerretFrame](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/FrenetSerretFrame.tar) and its *CMakeLists.txt* file.
Once the *tarball FrenetSerretFrame.tar* has been downloaded and extracted,
```
cd FrenetSerretFrame/build 
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
./FrenetSerretFrame
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

