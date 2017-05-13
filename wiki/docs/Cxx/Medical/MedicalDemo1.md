[VTKExamples](/home/)/[Cxx](/Cxx)/Medical/MedicalDemo1

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Medical/TestMedicalDemo1.png?raw=true" width="256" />

**MedicalDemo1.cxx**
```c++
// Derived from VTK/Examples/Cxx/Medical1.cxx
// This example reads a volume dataset, extracts an isosurface that
// represents the skin and displays it.
//

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMetaImageReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkOutlineFilter.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkMarchingCubes.h>
#include <vtkSmartPointer.h>

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    cout << "Usage: " << argv[0] << " file.mhd" << endl;
    return EXIT_FAILURE;
  }

  // Create the renderer, the render window, and the interactor. The renderer
  // draws into the render window, the interactor enables mouse- and
  // keyboard-based interaction with the data within the render window.
  //
  vtkSmartPointer<vtkRenderer> aRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(aRenderer);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  vtkSmartPointer<vtkMetaImageReader> reader =
    vtkSmartPointer<vtkMetaImageReader>::New();
  reader->SetFileName (argv[1]);

  // An isosurface, or contour value of 500 is known to correspond to the
  // skin of the patient.
  vtkSmartPointer<vtkMarchingCubes> skinExtractor =
    vtkSmartPointer<vtkMarchingCubes>::New();
  skinExtractor->SetInputConnection(reader->GetOutputPort());
  skinExtractor->SetValue(0, 500);

  vtkSmartPointer<vtkPolyDataMapper> skinMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  skinMapper->SetInputConnection(skinExtractor->GetOutputPort());
  skinMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> skin =
    vtkSmartPointer<vtkActor>::New();
  skin->SetMapper(skinMapper);
  skin->GetProperty()->SetDiffuseColor(1, .49, .25);

  // An outline provides context around the data.
  //
  vtkSmartPointer<vtkOutlineFilter> outlineData =
    vtkSmartPointer<vtkOutlineFilter>::New();
  outlineData->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> mapOutline =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapOutline->SetInputConnection(outlineData->GetOutputPort());

  vtkSmartPointer<vtkActor> outline =
    vtkSmartPointer<vtkActor>::New();
  outline->SetMapper(mapOutline);
  outline->GetProperty()->SetColor(0,0,0);

  // It is convenient to create an initial view of the data. The FocalPoint
  // and Position form a vector direction. Later on (ResetCamera() method)
  // this vector is used to position the camera to look at the data in
  // this direction.
  vtkSmartPointer<vtkCamera> aCamera =
    vtkSmartPointer<vtkCamera>::New();
  aCamera->SetViewUp (0, 0, -1);
  aCamera->SetPosition (0, -1, 0);
  aCamera->SetFocalPoint (0, 0, 0);
  aCamera->ComputeViewPlaneNormal();
  aCamera->Azimuth(30.0);
  aCamera->Elevation(30.0);

  // Actors are added to the renderer. An initial camera view is created.
  // The Dolly() method moves the camera towards the FocalPoint,
  // thereby enlarging the image.
  aRenderer->AddActor(outline);
  aRenderer->AddActor(skin);
  aRenderer->SetActiveCamera(aCamera);
  aRenderer->ResetCamera ();
  aCamera->Dolly(1.5);

  // Set a background color for the renderer and set the size of the
  // render window (expressed in pixels).
  aRenderer->SetBackground(.2, .3, .4);
  renWin->SetSize(640, 480);

  // Note that when camera movement occurs (as it does in the Dolly()
  // method), the clipping planes often need adjusting. Clipping planes
  // consist of two planes: near and far along the view direction. The
  // near plane clips out objects in front of the plane; the far plane
  // clips out objects behind the plane. This way only what is drawn
  // between the planes is actually rendered.
  aRenderer->ResetCameraClippingRange ();

  // Initialize the event loop and then start it.
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(MedicalDemo1)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(MedicalDemo1 MACOSX_BUNDLE MedicalDemo1.cxx)
 
target_link_libraries(MedicalDemo1 ${VTK_LIBRARIES})
```

**Download and Build MedicalDemo1**

Click [here to download MedicalDemo1](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/MedicalDemo1.tar) and its *CMakeLists.txt* file.
Once the *tarball MedicalDemo1.tar* has been downloaded and extracted,
```
cd MedicalDemo1/build 
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
./MedicalDemo1
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

