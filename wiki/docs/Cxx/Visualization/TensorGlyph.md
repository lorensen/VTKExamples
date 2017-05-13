[VTKExamples](/home/)/[Cxx](/Cxx)/Visualization/TensorGlyph

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestTensorGlyph.png?raw=true" width="256" />

### Description
This example demonstrates how to apply a rotation+scaling matrix to each point in a data set. We use a cube as the glyph so that simple rotations are easy to interpret.
Specifically, we glyph one point with no rotation/scaling, and a second point with a rotation of 45 degrees around the x axis.

**TensorGlyph.cxx**
```c++
#include <vtkVersion.h>

#include <vtkActor.h>
#include <vtkCellArray.h>
#include <vtkDoubleArray.h>
#include <vtkMath.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPointSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyData.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkTensorGlyph.h>
#include <vtkVertexGlyphFilter.h>

int main(int, char *[])
{
    // Setup points
    vtkSmartPointer<vtkPoints> points =
      vtkSmartPointer<vtkPoints>::New();
    points->InsertNextPoint(0.0, 0.0, 0.0);
    points->InsertNextPoint(5.0, 0.0, 0.0);

    vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
    polyData->SetPoints(points);

    vtkSmartPointer<vtkDoubleArray> tensors = vtkSmartPointer<vtkDoubleArray>::New();
    tensors->SetNumberOfTuples(2);
    tensors->SetNumberOfComponents(9);

    tensors->InsertTuple9(0,1,0,0,0,1,0,0,0,1);
    tensors->InsertTuple9(1,1,0,0,0,.7,.7,0,-.7,.7); // column major

    polyData->GetPointData()->SetTensors(tensors);

    vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
    cubeSource->Update();

    vtkSmartPointer<vtkTensorGlyph> tensorGlyph = vtkSmartPointer<vtkTensorGlyph>::New();
#if VTK_MAJOR_VERSION <= 5
    tensorGlyph->SetInput(polyData);
#else
    tensorGlyph->SetInputData(polyData);
#endif
    tensorGlyph->SetSourceConnection(cubeSource->GetOutputPort());
    tensorGlyph->ColorGlyphsOff();
    tensorGlyph->ThreeGlyphsOff();
    tensorGlyph->ExtractEigenvaluesOff();
    tensorGlyph->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
    mapper->SetInput(tensorGlyph->GetOutput());
#else
    mapper->SetInputData(tensorGlyph->GetOutput());
#endif

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
	
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer( renderer );
 
    vtkSmartPointer<vtkRenderWindowInteractor> interactor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow( renderWindow );
    renderWindow->Render();
    interactor->Start();

    return 0;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(TensorGlyph)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(TensorGlyph MACOSX_BUNDLE TensorGlyph.cxx)
 
target_link_libraries(TensorGlyph ${VTK_LIBRARIES})
```

**Download and Build TensorGlyph**

Click [here to download TensorGlyph](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/TensorGlyph.tar) and its *CMakeLists.txt* file.
Once the *tarball TensorGlyph.tar* has been downloaded and extracted,
```
cd TensorGlyph/build 
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
./TensorGlyph
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

