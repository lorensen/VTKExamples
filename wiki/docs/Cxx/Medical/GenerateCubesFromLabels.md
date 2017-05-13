[VTKExamples](/home/)/[Cxx](/Cxx)/Medical/GenerateCubesFromLabels

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Medical/TestGenerateCubesFromLabels.png?raw=true" width="256" />

### Description
Sometimes it is helpful to view the results of a segmentation without any post processing. This example converts the point data from a labeled volume into cell data. The surfaces are displayed as polydata. If you want to created smoothed polydata models from your segmented volumes, see the example [models from labeled volume data (Discrete MarchingCubes)]]. The input volume must be in [[ MetaIO/Documentation| META format]]([VTK/Examples/Medical/Cxx/GenerateModelsFromLabels|Create).

**GenerateCubesFromLabels.cxx**
```c++
//
// GenerateCubesFromLabels
//   Usage: GenerateCubesFromLabels InputVolume Startlabel Endlabel
//          where
//          InputVolume is a meta file containing a 3 volume of
//            discrete labels.
//          StartLabel is the first label to be processed
//          EndLabel is the last label to be processed
//          NOTE: There can be gaps in the labeling. If a label does
//          not exist in the volume, it will be skipped.
//
//
#include <vtkMetaImageReader.h>
#include <vtkImageAccumulate.h>
#include <vtkImageWrapPad.h>
#include <vtkMaskFields.h>
#include <vtkThreshold.h>
#include <vtkTransformFilter.h>
#include <vtkGeometryFilter.h>
#include <vtkSmartPointer.h>
#include <vtkTransform.h>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkUnstructuredGrid.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>

int main (int argc, char *argv[])
{
  if(argc < 4)
  {
    std::cout << "Usage: " << argv[0] << " InputVolume StartLabel EndLabel" << std::endl;
    return EXIT_FAILURE;
  }

  // Define all of the variables
  unsigned int startLabel = atoi(argv[2]);
  unsigned int endLabel = atoi(argv[3]);

  // Generate cubes from labels
  // 1) Read the meta file
  // 2) Convert point data to cell data
  // 3) Convert to geometry and display

  vtkSmartPointer<vtkMetaImageReader> reader =
    vtkSmartPointer<vtkMetaImageReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  // Pad the volume so that we can change the point data into cell
  // data.
  int *extent = reader->GetOutput()->GetExtent();
  vtkSmartPointer<vtkImageWrapPad> pad =
    vtkSmartPointer<vtkImageWrapPad>::New();
  pad->SetInputConnection(reader->GetOutputPort());
  pad->SetOutputWholeExtent(extent[0], extent[1] + 1,
                            extent[2], extent[3] + 1,
                            extent[4], extent[5] + 1);
  pad->Update();

  // Copy the scalar point data of the volume into the scalar cell data
  pad->GetOutput()->GetCellData()->SetScalars(
    reader->GetOutput()->GetPointData()->GetScalars());

  vtkSmartPointer<vtkThreshold> selector =
    vtkSmartPointer<vtkThreshold>::New();
  selector->SetInputArrayToProcess(0, 0, 0,
                                   vtkDataObject::FIELD_ASSOCIATION_CELLS,
                                   vtkDataSetAttributes::SCALARS);
  selector->SetInputConnection(pad->GetOutputPort());
  selector->ThresholdBetween(startLabel, endLabel);
  selector->Update();

  // Shift the geometry by 1/2
  vtkSmartPointer<vtkTransform> transform =
    vtkSmartPointer<vtkTransform>::New();
  transform->Translate (-.5, -.5, -.5);

  vtkSmartPointer<vtkTransformFilter> transformModel =
    vtkSmartPointer<vtkTransformFilter>::New();
  transformModel->SetTransform(transform);
  transformModel->SetInputConnection(selector->GetOutputPort());

  vtkSmartPointer<vtkGeometryFilter> geometry =
    vtkSmartPointer<vtkGeometryFilter>::New();
  geometry->SetInputConnection(transformModel->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(geometry->GetOutputPort());
  mapper->SetScalarRange(startLabel, endLabel);
  mapper->SetScalarModeToUseCellData();
  mapper->SetColorModeToMapScalars();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(.1, .2, .3);

  renderWindow->Render();
  renderWindowInteractor->Start();
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(GenerateCubesFromLabels)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(GenerateCubesFromLabels MACOSX_BUNDLE GenerateCubesFromLabels.cxx)
 
target_link_libraries(GenerateCubesFromLabels ${VTK_LIBRARIES})
```

**Download and Build GenerateCubesFromLabels**

Click [here to download GenerateCubesFromLabels](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/GenerateCubesFromLabels.tar) and its *CMakeLists.txt* file.
Once the *tarball GenerateCubesFromLabels.tar* has been downloaded and extracted,
```
cd GenerateCubesFromLabels/build 
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
./GenerateCubesFromLabels
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

