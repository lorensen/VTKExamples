[VTKExamples](Home)/[Cxx](Cxx)//vtkglut

### Description
This page illustrates how to use the new method '''vtkRenderWindow::InitializeFromCurrentContext()''' to associate a vtkRenderWindow instance to an existing window and activated OpenGL context.

By using this method, VTK do not create the rendering container nor the OpenGL context but inherit from the one created somewhere else.
This allows a vtkRenderWindow and thus VTK to be easily embedded in an existing graphical application.


The following code shows how to embed a VTK RenderWindow in a very simple GLUT based application which shows a vtkCone in rotation.

It has been successfully tested under Linux, Windows & MacOS X.

The interaction part is not shown here but it works as usual, you just need to pass the GLUT events to your VTK interactor.

**vtkglut.cxx**
```c++
#ifndef __APPLE_CC__
#include <GL/glut.h>
#else
#include <glut.h>
#endif
#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkNew.h"

vtkNew<vtkRenderer> ren;
vtkNew<vtkRenderWindow> renWin;

void Reshape( int width, int height )
{ 	 
  renWin->SetSize( width, height );
} 	 

void Draw()
{ 	
  renWin->Render();
  ren->GetActiveCamera()->Azimuth( 1 );
  glutPostRedisplay();
}

int main( int argc, char **argv )
{
  // GLUT initialization
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
  glutCreateWindow( "VTK-GLUT Example") ;
  glutReshapeFunc( Reshape );
  glutDisplayFunc( Draw );

  // Creation of a simple VTK pipeline
  vtkNew<vtkConeSource> cone;

  vtkNew<vtkPolyDataMapper> coneMapper;
  coneMapper->SetInputConnection( cone->GetOutputPort() );

  vtkNew<vtkActor> coneActor;
  coneActor->SetMapper( coneMapper.GetPointer() );

  ren->AddActor( coneActor.GetPointer() );
  renWin->AddRenderer( ren.GetPointer() );

  // Here is the trick: we ask the RenderWindow to join the current OpenGL context created by GLUT
  renWin->InitializeFromCurrentContext();
  
  // Let's start the main GLUT rendering loop
  glutMainLoop();
 
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(vtkglut)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(vtkglut MACOSX_BUNDLE vtkglut.cxx)
 
target_link_libraries(vtkglut ${VTK_LIBRARIES})
```

**Download and Build vtkglut**

Click [here to download vtkglut](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/vtkglut.tar) and its *CMakeLists.txt* file.
Once the *tarball vtkglut.tar* has been downloaded and extracted,
```
cd vtkglut/build 
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
./vtkglut
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

