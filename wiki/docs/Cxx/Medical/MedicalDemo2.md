[VTKExamples](/home/)/[Cxx](/Cxx)/Medical/MedicalDemo2

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Medical/TestMedicalDemo2.png?raw=true" width="256" />

**MedicalDemo2.cxx**
```c++
// Derived from VTK/Examples/Cxx/Medical2.cxx
// This example reads a volume dataset, extracts two isosurfaces that
// represent the skin and bone, and then displays them.
//

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMetaImageReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkOutlineFilter.h>
#include <vtkCamera.h>
#include <vtkPolyDataMapper.h>
#include <vtkStripper.h>
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

  // The following reader is used to read a series of 2D slices (images)
  // that compose the volume. The slice dimensions are set, and the
  // pixel spacing. The data Endianness must also be specified. The reader
  // usese the FilePrefix in combination with the slice number to construct
  // filenames using the format FilePrefix.%d. (In this case the FilePrefix
  // is the root name of the file: quarter.)
  vtkSmartPointer<vtkMetaImageReader> reader =
    vtkSmartPointer<vtkMetaImageReader>::New();
  reader->SetFileName (argv[1]);

  // An isosurface, or contour value of 500 is known to correspond to the
  // skin of the patient.
  // The triangle stripper is used to create triangle strips from the
  // isosurface; these render much faster on many systems.
  vtkSmartPointer<vtkMarchingCubes> skinExtractor =
    vtkSmartPointer<vtkMarchingCubes>::New();
  skinExtractor->SetInputConnection(reader->GetOutputPort());
  skinExtractor->SetValue(0, 500);

  vtkSmartPointer<vtkStripper> skinStripper =
    vtkSmartPointer<vtkStripper>::New();
  skinStripper->SetInputConnection(skinExtractor->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> skinMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  skinMapper->SetInputConnection(skinStripper->GetOutputPort());
  skinMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> skin =
    vtkSmartPointer<vtkActor>::New();
  skin->SetMapper(skinMapper);
  skin->GetProperty()->SetDiffuseColor(1, .49, .25);
  skin->GetProperty()->SetSpecular(.3);
  skin->GetProperty()->SetSpecularPower(20);
  skin->GetProperty()->SetOpacity(.5);

  // An isosurface, or contour value of 1150 is known to correspond to the
  // skin of the patient.
  // The triangle stripper is used to create triangle strips from the
  // isosurface; these render much faster on may systems.
  vtkSmartPointer<vtkMarchingCubes> boneExtractor =
    vtkSmartPointer<vtkMarchingCubes>::New();
  boneExtractor->SetInputConnection(reader->GetOutputPort());
  boneExtractor->SetValue(0, 1150);

  vtkSmartPointer<vtkStripper> boneStripper =
    vtkSmartPointer<vtkStripper>::New();
  boneStripper->SetInputConnection(boneExtractor->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> boneMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  boneMapper->SetInputConnection(boneStripper->GetOutputPort());
  boneMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> bone =
    vtkSmartPointer<vtkActor>::New();
  bone->SetMapper(boneMapper);
  bone->GetProperty()->SetDiffuseColor(1, 1, .9412);

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
  vtkSmartPointer<vtkCamera> aCamera = vtkSmartPointer<vtkCamera>::New();
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
  aRenderer->AddActor(bone);
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
 
PROJECT(MedicalDemo2)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(MedicalDemo2 MACOSX_BUNDLE MedicalDemo2.cxx)
 
target_link_libraries(MedicalDemo2 ${VTK_LIBRARIES})
```

**Download and Build MedicalDemo2**

Click [here to download MedicalDemo2](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/MedicalDemo2.tar) and its *CMakeLists.txt* file.
Once the *tarball MedicalDemo2.tar* has been downloaded and extracted,
```
cd MedicalDemo2/build 
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
./MedicalDemo2
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

