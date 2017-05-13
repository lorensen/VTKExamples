[VTKExamples](Home)/[Cxx](Cxx)/IO/IndividualVRML

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/IO/TestIndividualVRML.png" width="256" />

### Description
This example shows how to obtain each object of a scene and get it's initial transformation.
The selected actor is represented in wireframe. To run this example,

IndividualVRML filename actorname

The .wrl file must contain a Shape with a DEF name.

**IndividualVRML.cxx**
```c++
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVRMLImporter.h>
#include <vtkDataSet.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include "vtkTransform.h"
#include "vtkAxesActor.h"

int main ( int argc, char *argv[])
{
  if(argc != 3)
  {
    std::cout << "Required arguments: Filename Actorname" << std::endl;
    return EXIT_FAILURE;
  }

  std::string filename = argv[1];
  std::cout << "Showing " << argv[2] << " from " << filename << std::endl;

  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // VRML Import
  vtkSmartPointer<vtkVRMLImporter> importer = vtkSmartPointer<vtkVRMLImporter>::New();
  importer->SetFileName ( filename.c_str() );
  importer->Read();
  importer->SetRenderWindow(renderWindow);
  importer->Update();

  // ----------------------------------------------------------
  vtkObject* defActor = importer->GetVRMLDEFObject(argv[2]);
  if (defActor == NULL)
  {
    std::cout << "Cannot locate actor " << argv[2]
              << " in " << filename << std::endl;
    importer->Print(std::cout);
    return EXIT_FAILURE;
  }

  vtkActor* actor = static_cast <vtkActor*> (defActor);
  double color[3] = {0.89,0.81,0.34};
  actor->GetProperty()->SetColor(color);
  actor->GetProperty()->SetRepresentationToWireframe();

  vtkSmartPointer<vtkTransform> transform =
    vtkSmartPointer<vtkTransform>::New();

  transform->Translate(actor->GetCenter()[0],
                       actor->GetCenter()[1],
                       actor->GetCenter()[2]);
  // axes
  vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();

  double l[3];
  l[0] = (actor->GetBounds()[1] - actor->GetBounds()[0]) * 1.5;
  l[1] = (actor->GetBounds()[3] - actor->GetBounds()[2]) * 1.5;
  l[2] = (actor->GetBounds()[5] - actor->GetBounds()[4]) * 1.5;

  axes->SetTotalLength(l);
  axes->SetUserTransform(transform);
  renderer->AddActor(axes);
  renderer->SetBackground( .2, .3, .7);

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(IndividualVRML)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(IndividualVRML MACOSX_BUNDLE IndividualVRML.cxx)
 
target_link_libraries(IndividualVRML ${VTK_LIBRARIES})
```

**Download and Build IndividualVRML**

Click [here to download IndividualVRML](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/IndividualVRML.tar) and its *CMakeLists.txt* file.
Once the *tarball IndividualVRML.tar* has been downloaded and extracted,
```
cd IndividualVRML/build 
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
./IndividualVRML
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

