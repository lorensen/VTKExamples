[VTKExamples](/home/)/[Cxx](/Cxx)/Widgets/ContourWidget

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Widgets/TestContourWidget.png?raw=true" width="256" />

### Description
This example generates a set of points which lie on a circle, and the contour through these points. This contour can be interactively warped/modified by dragging the control points.

**ContourWidget.cxx**
```c++
#include <vtkSmartPointer.h>
// To setup the ContourWidget and its representation:
#include <vtkContourWidget.h>
#include <vtkProperty.h>
#include <vtkOrientedGlyphContourRepresentation.h>
// To create the geometry:
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkMath.h>
// Usual VTK pipeline elements:
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>

int main( int argc, char *argv[] )
{
    // Create the contour widget
    vtkSmartPointer<vtkContourWidget> contourWidget =
        vtkSmartPointer<vtkContourWidget>::New();

    // Override the default representation for the contour widget to customize its look
    vtkSmartPointer<vtkOrientedGlyphContourRepresentation> contourRepresentation =
        vtkSmartPointer<vtkOrientedGlyphContourRepresentation>::New();
    contourRepresentation->GetLinesProperty()->SetColor(1, 0, 0); // Set color to red
    contourWidget->SetRepresentation(contourRepresentation);

    // Generate a set of points arranged in a circle
    int numPts = 10;
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    for (int i = 0; i < numPts; i++)
    {
        // Create numPts points evenly spread around a circumference of radius 0.1
        const double angle = 2.0*vtkMath::Pi()*i/numPts;
        points->InsertPoint(static_cast<vtkIdType>(i), 0.1*cos(angle), 0.1*sin(angle), 0.0 );
    }

    // Create a cell array to connect the points into meaningful geometry
    vtkIdType* vertexIndices = new vtkIdType[numPts+1];
    for (int i = 0; i < numPts; i++) { vertexIndices[i] = static_cast<vtkIdType>(i); }
    // Set the last vertex to 0; this means the last line segment will join the 19th point (vertices[19])
    // with the first one (vertices[0]), thus closing the circle.
    vertexIndices[numPts] = 0;
    vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
    lines->InsertNextCell(numPts+1, vertexIndices);

    // Create polydata to hold the geometry just created, and populate it
    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
    polydata->SetPoints(points);
    polydata->SetLines(lines);

    // Create the renderer to visualize the scene
    vtkSmartPointer<vtkRenderer> renderer =
        vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(0.1, 0.2, 0.4); // Set a dark blue background (default is black)

    // Create the GUI window to hold the rendered scene
    vtkSmartPointer<vtkRenderWindow> renderWindow =
        vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    // Create the events manager for the renderer window
    vtkSmartPointer<vtkRenderWindowInteractor> interactor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);

    // Use the "trackball camera" interactor style, rather than the default "joystick camera"
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
      vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    interactor->SetInteractorStyle(style);

    // Set up the contour widget within the visualization pipeline just assembled
    contourWidget->SetInteractor(interactor);
    contourWidget->On(); // Turn on the interactor observer
    contourWidget->Initialize(polydata);
    renderer->ResetCamera(); // Reposition camera to fit the scene elements

    // Start the interaction
    interactor->Start();

    return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ContourWidget)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ContourWidget MACOSX_BUNDLE ContourWidget.cxx)
 
target_link_libraries(ContourWidget ${VTK_LIBRARIES})
```

**Download and Build ContourWidget**

Click [here to download ContourWidget](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ContourWidget.tar) and its *CMakeLists.txt* file.
Once the *tarball ContourWidget.tar* has been downloaded and extracted,
```
cd ContourWidget/build 
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
./ContourWidget
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

