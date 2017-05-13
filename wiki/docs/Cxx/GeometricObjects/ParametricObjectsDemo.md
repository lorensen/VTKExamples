[VTKExamples](/index/)/[Cxx](/Cxx)/GeometricObjects/ParametricObjectsDemo

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/GeometricObjects/TestParametricObjectsDemo.png?raw=true" width="256" />

### Description
See [Parametric Equations for Surfaces](http://www.vtk.org/img/ParametricSurfaces.pdf) by Andrew Maclean for an excellent description of these beautiful parametric surfaces.

This example also demonstrates how to manipulate lists of VTK objects using vectors. Notice how parameters of the various Parametric Objects are accessed and set in the parametricObjects vector.

**ParametricObjectsDemo.cxx**
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

#include <vtkParametricTorus.h>
#include <vtkParametricBoy.h>
#include <vtkParametricConicSpiral.h>
#include <vtkParametricCrossCap.h>
#include <vtkParametricDini.h>
#include <vtkParametricEllipsoid.h>
#include <vtkParametricEnneper.h>
#include <vtkParametricFigure8Klein.h>
#include <vtkParametricKlein.h>
#include <vtkParametricMobius.h>
#include <vtkParametricRandomHills.h>
#include <vtkParametricRoman.h>
#include <vtkParametricSpline.h>
#include <vtkParametricSuperEllipsoid.h>
#include <vtkParametricSuperToroid.h>
#include <vtkParametricTorus.h>

#include <vector>

int main(int, char *[])
{
  // Select one of the following (matching the selection above)
  std::vector<vtkSmartPointer<vtkParametricFunction> > parametricObjects;

  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricBoy>::New());
  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricConicSpiral>::New());
  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricCrossCap>::New());
  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricDini>::New());

  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricEllipsoid>::New());
  static_cast<vtkParametricEllipsoid *>(
    parametricObjects.back().GetPointer())->SetXRadius(.5);
  static_cast<vtkParametricEllipsoid *>(
    parametricObjects.back().GetPointer())->SetYRadius(2.0);

  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricEnneper>::New());
  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricFigure8Klein>::New());
  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricKlein>::New());
  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricMobius>::New());
  static_cast<vtkParametricMobius *>(
    parametricObjects.back().GetPointer())->SetRadius(2.0);
  static_cast<vtkParametricMobius *>(
    parametricObjects.back().GetPointer())->SetMinimumV(-0.5);
  static_cast<vtkParametricMobius *>(
    parametricObjects.back().GetPointer())->SetMaximumV(0.5);

  vtkSmartPointer<vtkParametricRandomHills> randomHills =
    vtkSmartPointer<vtkParametricRandomHills>::New();
  randomHills->AllowRandomGenerationOff();
  parametricObjects.push_back(randomHills);

  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricRoman>::New());

  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricSuperEllipsoid>::New());
  static_cast<vtkParametricSuperEllipsoid *>(
    parametricObjects.back().GetPointer())->SetN1(.50);
  static_cast<vtkParametricSuperEllipsoid *>(
    parametricObjects.back().GetPointer())->SetN2(.1);

  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricSuperToroid>::New());
  static_cast<vtkParametricSuperToroid *>(
    parametricObjects.back().GetPointer())->SetN1(.2);
  static_cast<vtkParametricSuperToroid *>(
    parametricObjects.back().GetPointer())->SetN2(3.0);

  parametricObjects.push_back(
    vtkSmartPointer<vtkParametricTorus>::New());

  // The spline needs points
  vtkSmartPointer<vtkParametricSpline> spline =
    vtkSmartPointer<vtkParametricSpline>::New();
  vtkSmartPointer<vtkPoints> inputPoints =
    vtkSmartPointer<vtkPoints>::New();
  vtkMath::RandomSeed(8775070);
  for (int p = 0; p < 10; p++)
  {
    double x = vtkMath::Random(0.0, 1.0);
    double y = vtkMath::Random(0.0, 1.0);
    double z = vtkMath::Random(0.0, 1.0);
    inputPoints->InsertNextPoint(x, y, z);
  }
  spline->SetPoints(inputPoints);
  parametricObjects.push_back(spline);

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
    parametricFunctionSources[i]->SetUResolution(51);
    parametricFunctionSources[i]->SetVResolution(51);
    parametricFunctionSources[i]->SetWResolution(51);
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
  unsigned int gridDimensions = 4;

  // Need a renderer even if there is no actor
  for(size_t i = parametricObjects.size();
      i < gridDimensions * gridDimensions;
      i++)
  {
    renderers.push_back(vtkSmartPointer<vtkRenderer>::New());
  }

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  int rendererSize = 200;
  renderWindow->SetSize(
    rendererSize*gridDimensions, rendererSize*gridDimensions);

  for(int row = 0; row < static_cast<int>(gridDimensions); row++)
  {
    for(int col = 0; col < static_cast<int>(gridDimensions); col++)
    {
      int index = row*gridDimensions + col;

      // (xmin, ymin, xmax, ymax)
      double viewport[4] =
        {static_cast<double>(col) * rendererSize / (gridDimensions * rendererSize),
         static_cast<double>(gridDimensions - (row+1)) * rendererSize / (gridDimensions * rendererSize),
         static_cast<double>(col+1)*rendererSize / (gridDimensions * rendererSize),
         static_cast<double>(gridDimensions - row) * rendererSize / (gridDimensions * rendererSize)};

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
 
PROJECT(ParametricObjectsDemo)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ParametricObjectsDemo MACOSX_BUNDLE ParametricObjectsDemo.cxx)
 
target_link_libraries(ParametricObjectsDemo ${VTK_LIBRARIES})
```

**Download and Build ParametricObjectsDemo**

Click [here to download ParametricObjectsDemo](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ParametricObjectsDemo.tar) and its *CMakeLists.txt* file.
Once the *tarball ParametricObjectsDemo.tar* has been downloaded and extracted,
```
cd ParametricObjectsDemo/build 
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
./ParametricObjectsDemo
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

