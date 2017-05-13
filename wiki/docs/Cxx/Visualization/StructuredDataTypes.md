[VTKExamples](/home/)/[Cxx](/Cxx)/Visualization/StructuredDataTypes

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestStructuredDataTypes.png?raw=true" width="256" />

**StructuredDataTypes.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTransform.h>
#include <vtkDoubleArray.h>
#include <vtkImageData.h>
#include <vtkRectilinearGrid.h>
#include <vtkStructuredGrid.h>
#include <vtkXMLImageDataWriter.h>
#include <vtkXMLRectilinearGridWriter.h>
#include <vtkXMLStructuredGridWriter.h>

static void ImageData(vtkImageData* data, const int gridSize);
static void RectilinearGrid(vtkRectilinearGrid* data, const int gridSize);
static void StructuredGrid(vtkStructuredGrid* data, const int gridSize);

int main(int, char *[])
{
  int gridSize = 5;
  vtkSmartPointer<vtkImageData> imageData =
    vtkSmartPointer<vtkImageData>::New();
  ImageData(imageData, gridSize);
  vtkSmartPointer<vtkDataSetMapper> imageDataMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  imageDataMapper->SetInputConnection(imageData->GetProducerPort());
#else
  imageDataMapper->SetInputData(imageData);
  imageDataMapper->ScalarVisibilityOff();
#endif
  vtkSmartPointer<vtkActor> imageDataActor =
    vtkSmartPointer<vtkActor>::New();
  imageDataActor->GetProperty()->SetRepresentationToWireframe();
  imageDataActor->SetMapper(imageDataMapper);

  vtkSmartPointer<vtkRectilinearGrid> rectilinearGrid =
    vtkSmartPointer<vtkRectilinearGrid>::New();
  RectilinearGrid(rectilinearGrid, gridSize);
  vtkSmartPointer<vtkDataSetMapper> rectilinearGridMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  rectilinearGridMapper->SetInputConnection(rectilinearGrid->GetProducerPort());
#else
  rectilinearGridMapper->SetInputData(rectilinearGrid);
#endif
  vtkSmartPointer<vtkActor> rectilinearGridActor =
    vtkSmartPointer<vtkActor>::New();
  rectilinearGridActor->GetProperty()->SetRepresentationToWireframe();
  rectilinearGridActor->SetMapper(rectilinearGridMapper);

  vtkSmartPointer<vtkStructuredGrid> structuredGrid =
    vtkSmartPointer<vtkStructuredGrid>::New();
  StructuredGrid(structuredGrid, gridSize);
  vtkSmartPointer<vtkDataSetMapper> structuredGridMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  structuredGridMapper->SetInputConnection(structuredGrid->GetProducerPort());
#else
  structuredGridMapper->SetInputData(structuredGrid);
#endif
  vtkSmartPointer<vtkActor> structuredGridActor =
    vtkSmartPointer<vtkActor>::New();
  structuredGridActor->GetProperty()->SetRepresentationToWireframe();
  structuredGridActor->SetMapper(structuredGridMapper);

  // There will be one render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);

  // And one interactor
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.33, 1.0};
  double centerViewport[4] = {0.33, 0.0, 0.66, 1.0};
  double rightViewport[4] = {0.66, 0.0, 1.0, 1.0};

  // Setup three renderers
  vtkSmartPointer<vtkRenderer> leftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(leftRenderer);
  leftRenderer->SetViewport(leftViewport);
  leftRenderer->SetBackground(.6, .5, .4);

  vtkSmartPointer<vtkRenderer> centerRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(centerRenderer);
  centerRenderer->SetViewport(centerViewport);
  centerRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> rightRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(rightRenderer);
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->SetBackground(.5, .4, .6);

  // Add the image on the left, rectilinear in the center, structured on the right
  leftRenderer->AddActor(imageDataActor);
  centerRenderer->AddActor(rectilinearGridActor);
  rightRenderer->AddActor(structuredGridActor);

  leftRenderer->ResetCamera();
  centerRenderer->ResetCamera();
  rightRenderer->ResetCamera();
  //rightRenderer->GetActiveCamera()->Azimuth(30);
  //rightRenderer->GetActiveCamera()->Elevation(30);

  renderWindow->Render();
  interactor->Start();
  return EXIT_SUCCESS;
}

void ImageData(vtkImageData* data, const int gridSize)
{

  data->SetExtent(0,gridSize-1,0,gridSize-1,0,gridSize-1);
#if VTK_MAJOR_VERSION <= 5
  data->SetNumberOfScalarComponents(1);
  data->SetScalarTypeToDouble();
#else
  data->AllocateScalars(VTK_DOUBLE,1);
#endif
  vtkSmartPointer<vtkXMLImageDataWriter> writer =
    vtkSmartPointer<vtkXMLImageDataWriter>::New();
  writer->SetFileName("imagedata.vti");
#if VTK_MAJOR_VERSION <= 5
  writer->SetInputConnection(data->GetProducerPort());
#else
  writer->SetInputData(data);
#endif
  writer->Write();
}

void RectilinearGrid(vtkRectilinearGrid* data, const int gridSize)
{

  data->SetExtent(0,gridSize-1,0,gridSize-1,0,gridSize-1);

  vtkSmartPointer<vtkDoubleArray> xCoords =
    vtkSmartPointer<vtkDoubleArray>::New();
  xCoords->SetNumberOfComponents(1);
  vtkSmartPointer<vtkDoubleArray> yCoords =
    vtkSmartPointer<vtkDoubleArray>::New();
  yCoords->SetNumberOfComponents(1);
  vtkSmartPointer<vtkDoubleArray> zCoords =
    vtkSmartPointer<vtkDoubleArray>::New();
  zCoords->SetNumberOfComponents(1);

  for(int i = 0; i < gridSize; i++)
  {
    if(i == 0)
    {
      xCoords->InsertNextValue(0);
      yCoords->InsertNextValue(0);
      zCoords->InsertNextValue(0);
      continue;
    }
    double oldX = xCoords->GetValue(i-1);
    double oldY = xCoords->GetValue(i-1);
    double oldZ = xCoords->GetValue(i-1);
    xCoords->InsertNextValue(oldX + i*i);
    yCoords->InsertNextValue(oldY + i*i);
    zCoords->InsertNextValue(oldZ + i*i);
  }

  data->SetXCoordinates(xCoords);
  data->SetYCoordinates(yCoords);
  data->SetZCoordinates(zCoords);

  vtkSmartPointer<vtkXMLRectilinearGridWriter> writer =
    vtkSmartPointer<vtkXMLRectilinearGridWriter>::New();
  writer->SetFileName("rectilineargrid.vtr");
#if VTK_MAJOR_VERSION <= 5
  writer->SetInputConnection(data->GetProducerPort());
#else
  writer->SetInputData(data);
#endif
  writer->Write();
}

void StructuredGrid(vtkStructuredGrid* data, const int gridSize)
{
  data->SetExtent(0,gridSize-1,0,gridSize-1,0,gridSize-1);
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();

  vtkSmartPointer<vtkTransform> transform =
    vtkSmartPointer<vtkTransform>::New();
  transform->RotateZ(30);

  for(int k = 0; k < gridSize; k++)
  {
    for(int j = 0; j < gridSize; j++)
    {
      for(int i = 0; i < gridSize; i++)
      {
        double p[4];
        p[0] = i;
        p[1] = j;
        p[2] = k;
        p[3] = 1;
        double pout[4];
        transform->MultiplyPoint(p, pout);

        points->InsertNextPoint(pout[0], pout[1], pout[2]);
      }
    }
  }

  data->SetPoints(points);

  vtkSmartPointer<vtkXMLStructuredGridWriter> writer =
    vtkSmartPointer<vtkXMLStructuredGridWriter>::New();
  writer->SetFileName("structuredgrid.vts");
#if VTK_MAJOR_VERSION <= 5
  writer->SetInputConnection(data->GetProducerPort());
#else
  writer->SetInputData(data);
#endif
  writer->Write();
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(StructuredDataTypes)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(StructuredDataTypes MACOSX_BUNDLE StructuredDataTypes.cxx)
 
target_link_libraries(StructuredDataTypes ${VTK_LIBRARIES})
```

**Download and Build StructuredDataTypes**

Click [here to download StructuredDataTypes](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/StructuredDataTypes.tar) and its *CMakeLists.txt* file.
Once the *tarball StructuredDataTypes.tar* has been downloaded and extracted,
```
cd StructuredDataTypes/build 
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
./StructuredDataTypes
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

