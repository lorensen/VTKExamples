[VTKExamples](Home)/[Cxx](Cxx)/Visualization/LODProp3D

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Visualization/TestLODProp3D.png" width="256" />

### Description
If you have a fast graphics card, you may not see a difference.

**LODProp3D.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkLODProp3D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkCallbackCommand.h>
#include <vtkProperty.h>

void RefreshCallback( vtkObject* vtkNotUsed(caller),
                      long unsigned int vtkNotUsed(eventId),
                      void* clientData,
                      void* vtkNotUsed(callData) )
{
  vtkSmartPointer<vtkLODProp3D> lodProp = 
    static_cast<vtkLODProp3D*>(clientData);
  std::cout << "Last rendered LOD: " << lodProp->GetLastRenderedLODID() << std::endl;
}

int main (int, char *[])
{
  // High res sphere
  vtkSmartPointer<vtkSphereSource> highResSphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  int res = 100;
  highResSphereSource->SetThetaResolution(res);
  highResSphereSource->SetPhiResolution(res);
  highResSphereSource->Update();
  
  vtkSmartPointer<vtkPolyDataMapper> highResMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  highResMapper->SetInputConnection(highResSphereSource->GetOutputPort());
  
  // Low res sphere
  vtkSmartPointer<vtkSphereSource> lowResSphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
    
  vtkSmartPointer<vtkPolyDataMapper> lowResMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  lowResMapper->SetInputConnection(lowResSphereSource->GetOutputPort());
  
  vtkSmartPointer<vtkProperty> propertyLowRes = 
    vtkSmartPointer<vtkProperty>::New();
  propertyLowRes->SetDiffuseColor(0.89, 0.81, 0.34);
  propertyLowRes->SetInterpolationToFlat();

  vtkSmartPointer<vtkProperty> propertyHighRes = 
    vtkSmartPointer<vtkProperty>::New();
  propertyHighRes->SetDiffuseColor(1.0, 0.3882, 0.2784);
  propertyHighRes->SetInterpolationToFlat();

  vtkSmartPointer<vtkLODProp3D> prop = 
      vtkSmartPointer<vtkLODProp3D>::New();
  prop->AddLOD(lowResMapper, propertyLowRes, 0.0);
  prop->AddLOD(highResMapper, propertyHighRes, 0.0);
  
  std::cout << "There are " << prop->GetNumberOfLODs() << " LODs" << std::endl;
    
  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  //prop->SetAllocatedRenderTime(1e-6,renderer);
  prop->SetAllocatedRenderTime(1e-10,renderer);
      
  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the scene
  renderer->AddActor(prop);
  
  vtkSmartPointer<vtkCallbackCommand> refreshCallback =
    vtkSmartPointer<vtkCallbackCommand>::New();
  refreshCallback->SetCallback (RefreshCallback);
  refreshCallback->SetClientData(prop);

  renderWindow->AddObserver(vtkCommand::ModifiedEvent,refreshCallback);
  
  renderWindow->Render();

  // Begin mouse interaction
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(LODProp3D)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(LODProp3D MACOSX_BUNDLE LODProp3D.cxx)
 
target_link_libraries(LODProp3D ${VTK_LIBRARIES})
```

**Download and Build LODProp3D**

Click [here to download LODProp3D](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/LODProp3D.tar) and its *CMakeLists.txt* file.
Once the *tarball LODProp3D.tar* has been downloaded and extracted,
```
cd LODProp3D/build 
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
./LODProp3D
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

