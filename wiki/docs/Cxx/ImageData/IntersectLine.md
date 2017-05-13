[VTKExamples](/home/)/[Cxx](/Cxx)/ImageData/IntersectLine

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/ImageData/TestIntersectLine.png?raw=true" width="256" />

### Description
This example demonstrates a (rather manual) way of finding which cells of a vtkImageData a finite line intersects. Note that this is not exact - a cell-centric approach is used. That is, a discrete line (DDA-like http://en.wikipedia.org/wiki/Digital_differential_analyzer_%28graphics_algorithm%29) is followed on the cell grid between the cells that contain the intersection points of the line with the bounding box of the image. These are all not necessarily the exact same cells as the line actually intersects, but it gives a reasonable "path" of cells through the image which might be suitable for some applications.

**IntersectLine.cxx**
```c++
#include <vtkVersion.h>

#include <vtkActor.h>
#include <vtkBox.h>
#include <vtkCellData.h>
#include <vtkDataSetMapper.h>
#include <vtkIdList.h>
#include <vtkImageData.h>
#include <vtkIntArray.h>
#include <vtkMath.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkShrinkFilter.h>
#include <vtkSmartPointer.h>
#include <vtkThreshold.h>
#include <vtkUnstructuredGrid.h>
#include <vtkVersion.h>

#include <algorithm>
#include <cmath>

static vtkIdType FindCell(vtkImageData* grid, double point[3]);
static std::vector<vtkIdType> IntersectImage(vtkImageData* image, double p0[3], double p1[3]);

int main(int, char *[])
{
  // Create a 3x4x5 grid of points (60), which will define a 2x3x4
  // (24) grid of cubes
  vtkSmartPointer<vtkImageData> grid =
    vtkSmartPointer<vtkImageData>::New();

  // Create the grid data structure
  grid->SetDimensions(3, 4, 5);

  std::cout << "There are "
            << grid->GetNumberOfPoints() << " points before shrinking."
            << std::endl;
  std::cout << "There are "
            << grid->GetNumberOfCells() << " cells before shrinking."
            << std::endl;

  // Define a ray
  double rayOrigin[3] = {-5.0, 0, 0};
  double rayDirection[3] = {1.0, 0, 0};
  double rayEndPoint[3];
  for(size_t i = 0; i < 3; ++i)
  {
    rayEndPoint[i] = rayOrigin[i] + rayDirection[i] * 1000; // 1000 is an arbitrary constant that should be much larger than the size of the scene (to create an "infinite" ray)
  }
  std::vector<vtkIdType> intersectedCells = IntersectImage(grid, rayOrigin, rayEndPoint);

  vtkSmartPointer<vtkShrinkFilter> shrinkFilter =
    vtkSmartPointer<vtkShrinkFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  shrinkFilter->SetInput(grid);
#else
  shrinkFilter->SetInputData(grid);
#endif
  shrinkFilter->SetShrinkFactor(.8);
  shrinkFilter->Update();

  // Setup visibility array. Cells with visibility > 1 will be
  // visible, and < 1 will be invisible.
  vtkSmartPointer<vtkIntArray> visibilityArray =
    vtkSmartPointer<vtkIntArray>::New();
  visibilityArray->SetNumberOfComponents(1);
  visibilityArray->SetName("Visibility");

  // Initially, set all cells to visible
  for(vtkIdType cellId = 0; cellId < shrinkFilter->GetOutput()->GetNumberOfCells(); ++cellId)
  {
    visibilityArray->InsertNextValue(10);
  }

  // Set the intersected cells to invisible
  for(size_t i = 0; i < intersectedCells.size(); ++i)
  {
    visibilityArray->SetTuple1(intersectedCells[i], 0);
  }

  shrinkFilter->GetOutput()->GetCellData()->AddArray(visibilityArray);

  // Threshold
  vtkSmartPointer<vtkThreshold> threshold =
    vtkSmartPointer<vtkThreshold>::New();
#if VTK_MAJOR_VERSION <= 5
  threshold->SetInput(shrinkFilter->GetOutput());
#else
  threshold->SetInputData(shrinkFilter->GetOutput());
#endif
  threshold->ThresholdByUpper(1); // Criterion is cells whose scalars are greater or equal to threshold.

  threshold->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_CELLS, "Visibility");
  threshold->Update();

  vtkUnstructuredGrid* thresholdedPolydata = threshold->GetOutput();
  std::cout << "There are " << thresholdedPolydata->GetNumberOfCells()
            << " cells after thresholding." << std::endl;

  /////////// Standard visualization setup //////////////
    // Create a mapper and actor
    vtkSmartPointer<vtkDataSetMapper> mapper =
      vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputConnection(threshold->GetOutputPort());
    vtkSmartPointer<vtkActor> actor =
      vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // Create a renderer, render window, and interactor
    vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->SetMultiSamples(0);
    renderWindow->AddRenderer(renderer);
    renderWindow->SetWindowName("Space Carving");
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // Add the actor to the scene
    renderer->AddActor(actor);
    renderer->SetBackground(.2, .3, .4);

    // Render and interact
    renderWindow->Render();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}

vtkIdType FindCell(vtkImageData* grid, double point[3])
{
  double pcoords[3];
  double weights[8];

  int subId;

  // The third parameter is an "initial guess" of the cellId
  vtkIdType cellId = grid->FindCell(point, NULL, 0, .1, subId, pcoords, weights);
  return cellId;
}

// Intersect a finite line (with end points p0 and p1) with all of the
// cells of a vtkImageData
std::vector<vtkIdType> IntersectImage(vtkImageData* image, double p0[3], double p1[3])
{
  // Intersect a ray with the bounding box of the grid. There should
  // be two points (an entrance and an exit)

  // Define a box
  double bounds[6];
  image->GetBounds(bounds);

  // The two points of intersection of the bounding box with the line
  // will be stored here
  double entrancePoint[3];
  double exitPoint[3];

  // We do not need the results stored in these variables, but they
  // are required for the function call.
  int entryPlane[6];
  int exitPlane[6];

  double t0, t1; // the [0,1] normalized distances to the intersections along the ray

  int hit = vtkBox::IntersectWithLine(bounds,
                                      p0,
                                      p1,
                                      t0,
                                      t1,
                                      entrancePoint,
                                      exitPoint,
                                      *entryPlane,
                                      *exitPlane);

  std::vector<vtkIdType> intersectedCells;

  if(!hit)
  {
    std::cout << "Not hit!" << std::endl;
    return intersectedCells;
  }
  else
  {
    std::cout << "Entry point: " << entrancePoint[0] << " " << entrancePoint[1] << " " << entrancePoint[2] << std::endl;
    std::cout << "Exit point: " << exitPoint[0] << " " << exitPoint[1] << " " << exitPoint[2] << std::endl;
  }

  // This simple algorithm was adapted from
  // http://www.cb.uu.se/~cris/blog/index.php/archives/400

  int dim[3];
  image->GetDimensions(dim);

  // Make sure to include the first cell that the line hits
  vtkIdType startCellId = FindCell(image, entrancePoint);
  intersectedCells.push_back(startCellId);

  double p[3];
  p[0] = entrancePoint[0];
  p[1] = entrancePoint[1];
  p[2] = entrancePoint[2];

  double d[3];
  d[0] = exitPoint[0] - entrancePoint[0];
  d[1] = exitPoint[1] - entrancePoint[1];
  d[2] = exitPoint[2] - entrancePoint[2];

   double N = std::max(std::max(
              std::abs(d[0]), std::abs(d[1])),std::abs(d[2]));

  double s[3];
  s[0] = d[0]/N;
  s[1] = d[1]/N;
  s[2] = d[2]/N;

  for(size_t i = 0; i < N; ++i)
  {
    int ijk[3];
    ijk[0] = vtkMath::Round(p[0]);
    ijk[1] = vtkMath::Round(p[1]);
    ijk[2] = vtkMath::Round(p[2]);

    for(unsigned int index = 0; index < 3; ++index)
    {
      if(ijk[index] > dim[index] - 2)
      {
        ijk[index] = dim[index] - 2;
      }
    }

    vtkIdType cellId = vtkStructuredData::ComputeCellId (dim, ijk);
    intersectedCells.push_back(cellId);
    p[0] += s[0];
    p[1] += s[1];
    p[2] += s[2];
  }

  // Make sure to include the last cell that the line hits
  vtkIdType endCellId = FindCell(image, exitPoint);
  intersectedCells.push_back(endCellId);

  return intersectedCells;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(IntersectLine)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(IntersectLine MACOSX_BUNDLE IntersectLine.cxx)
 
target_link_libraries(IntersectLine ${VTK_LIBRARIES})
```

**Download and Build IntersectLine**

Click [here to download IntersectLine](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/IntersectLine.tar) and its *CMakeLists.txt* file.
Once the *tarball IntersectLine.tar* has been downloaded and extracted,
```
cd IntersectLine/build 
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
./IntersectLine
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

