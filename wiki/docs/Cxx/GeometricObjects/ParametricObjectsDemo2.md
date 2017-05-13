[VTKExamples](Home)/[Cxx](Cxx)/GeometricObjects/ParametricObjectsDemo2

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/GeometricObjects/TestParametricObjectsDemo2.png" width="256" />

**ParametricObjectsDemo2.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkCamera.h>
#include <vtkPolyDataMapper.h>
#include <vtkTextMapper.h>
#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkProperty.h>
#include <vtkTextProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkParametricFunctionSource.h>
#include <vtkMath.h>
#include <vtkPoints.h>

#include "vtkParametricBohemianDome.h"
#include "vtkParametricBour.h"
#include "vtkParametricCatalanMinimal.h"
#include "vtkParametricFunction.h"
#include "vtkParametricHenneberg.h"
#include "vtkParametricKuen.h"
#include "vtkParametricPluckerConoid.h"
#include "vtkParametricPseudosphere.h"

#include <vector>

int main(int, char *[])
{
  // Select one of the following (matching the selection above)
  std::vector<vtkSmartPointer<vtkParametricFunction> > parametricObjects;

  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricBohemianDome>::New());
  static_cast<vtkParametricBohemianDome*>(
    parametricObjects.back().GetPointer())->SetA(5.0);
  static_cast<vtkParametricBohemianDome*>(
    parametricObjects.back().GetPointer())->SetB(1.0);
  static_cast<vtkParametricBohemianDome*>(
    parametricObjects.back().GetPointer())->SetC(2.0);
  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricBour>::New());
  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricCatalanMinimal>::New());
  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricHenneberg>::New());
  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricKuen>::New());
  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricPluckerConoid>::New());
  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricPseudosphere>::New());

  std::vector<vtkSmartPointer<vtkParametricFunctionSource> >
    parametricFunctionSources;
  std::vector<vtkSmartPointer<vtkRenderer> >
    renderers;
  std::vector<vtkSmartPointer<vtkPolyDataMapper> >
    mappers;
  std::vector<vtkSmartPointer<vtkActor> >
    actors;
  std::vector<vtkSmartPointer<vtkTextMapper> >
    textmappers;
  std::vector<vtkSmartPointer<vtkActor2D> >
    textactors;

  // Create one text property for all
  vtkSmartPointer<vtkTextProperty> textProperty =
    vtkSmartPointer<vtkTextProperty>::New();
  textProperty->SetFontSize(10);
  textProperty->SetJustificationToCentered();

  vtkSmartPointer<vtkProperty> backProperty =
    vtkSmartPointer<vtkProperty>::New();
  backProperty->SetColor(1.0, 0.0, 0.0);

  // Create a parametric function source, renderer, mapper, and actor
  // for each object
  for(unsigned int i = 0; i < parametricObjects.size(); i++)
  {
    parametricFunctionSources.push_back(
      vtkSmartPointer<vtkParametricFunctionSource>::New());
    parametricFunctionSources[i]->SetParametricFunction(parametricObjects[i]);
    parametricFunctionSources[i]->Update();

    mappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
    mappers[i]->SetInputConnection(
      parametricFunctionSources[i]->GetOutputPort());

    actors.push_back(vtkSmartPointer<vtkActor>::New());
    actors[i]->SetMapper(mappers[i]);
    actors[i]->SetBackfaceProperty(backProperty);

    textmappers.push_back(vtkSmartPointer<vtkTextMapper>::New());
    textmappers[i]->SetInput(parametricObjects[i]->GetClassName());
    textmappers[i]->SetTextProperty(textProperty);

    textactors.push_back(vtkSmartPointer<vtkActor2D>::New());
    textactors[i]->SetMapper(textmappers[i]);
    textactors[i]->SetPosition(100, 16);
    renderers.push_back(vtkSmartPointer<vtkRenderer>::New());
  }
  unsigned int gridXDimensions = 4;
  unsigned int gridYDimensions = 2;

  // Need a renderer even if there is no actor
  for(size_t i = parametricObjects.size();
      i < gridXDimensions * gridYDimensions;
      i++)
  {
    renderers.push_back(vtkSmartPointer<vtkRenderer>::New());
  }

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  int rendererSize = 200;
  renderWindow->SetSize(
    rendererSize*gridXDimensions, rendererSize*gridYDimensions);

  for(int row = 0; row < static_cast<int>(gridYDimensions); row++)
  {
    for(int col = 0; col < static_cast<int>(gridXDimensions); col++)
    {
      int index = row*gridXDimensions + col;

      // (xmin, ymin, xmax, ymax)
      double viewport[4] =
        {static_cast<double>(col) * rendererSize / (gridXDimensions * rendererSize),
         static_cast<double>(gridYDimensions - (row+1)) * rendererSize / (gridYDimensions * rendererSize),
         static_cast<double>(col+1)*rendererSize / (gridXDimensions * rendererSize),
         static_cast<double>(gridYDimensions - row) * rendererSize / (gridYDimensions * rendererSize)};
      renderWindow->AddRenderer(renderers[index]);
      renderers[index]->SetViewport(viewport);
      if(index > static_cast<int>(parametricObjects.size() - 1))
      {
        continue;
      }
      renderers[index]->AddActor(actors[index]);
      renderers[index]->AddActor(textactors[index]);
      renderers[index]->SetBackground(.2, .3, .4);
      renderers[index]->ResetCamera();
      renderers[index]->GetActiveCamera()->Azimuth(30);
      renderers[index]->GetActiveCamera()->Elevation(-30);
      renderers[index]->GetActiveCamera()->Zoom(0.9);
      renderers[index]->ResetCameraClippingRange();
    }
  }

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ParametricObjectsDemo2)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ParametricObjectsDemo2 MACOSX_BUNDLE ParametricObjectsDemo2.cxx)
 
target_link_libraries(ParametricObjectsDemo2 ${VTK_LIBRARIES})
```

**Download and Build ParametricObjectsDemo2**

Click [here to download ParametricObjectsDemo2](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ParametricObjectsDemo2.tar) and its *CMakeLists.txt* file.
Once the *tarball ParametricObjectsDemo2.tar* has been downloaded and extracted,
```
cd ParametricObjectsDemo2/build 
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
./ParametricObjectsDemo2
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

