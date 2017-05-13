[VTKExamples](/index/)/[Cxx](/Cxx)/ImageData/GetCellCenter

### Description
Unfortunately this function is not built in directly, but rather quite convoluted to call. This is an easy to use wrapper.

**GetCellCenter.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkCell.h>
#include <vtkImageData.h>

static void GetCellCenter(vtkImageData* imageData, const unsigned int cellId,
                          double center[3]);

int main(int, char *[])
{
  // Create an image data
  vtkSmartPointer<vtkImageData> imageData = vtkSmartPointer<vtkImageData>::New();

  // Specify the size of the image data
  imageData->SetDimensions(3,3,2); // This will cause 18 points and 4 cells
  imageData->SetSpacing(1.0, 1.0, 1.0);
  imageData->SetOrigin(0.0, 0.0, 0.0);

  std::cout << "Number of points: " << imageData->GetNumberOfPoints() << std::endl;
  std::cout << "Number of cells: " << imageData->GetNumberOfCells() << std::endl;

  double center[3] = {0,0,0};
  for(vtkIdType cellId = 0; cellId < imageData->GetNumberOfCells(); ++cellId)
  {
    GetCellCenter(imageData, cellId, center);

    std::cout << "Cell " << cellId << " center: " << center[0] << " "
              << center[1] << " " << center[2] << std::endl;
  }

  return EXIT_SUCCESS;
}

void GetCellCenter(vtkImageData* imageData, const unsigned int cellId, double center[3])
{
  double pcoords[3] = {0,0,0};
  double *weights = new double [imageData->GetMaxCellSize()];
  vtkCell* cell = imageData->GetCell(cellId);
  int subId = cell->GetParametricCenter(pcoords);
  cell->EvaluateLocation(subId, pcoords, center, weights);
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(GetCellCenter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(GetCellCenter MACOSX_BUNDLE GetCellCenter.cxx)
 
target_link_libraries(GetCellCenter ${VTK_LIBRARIES})
```

**Download and Build GetCellCenter**

Click [here to download GetCellCenter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/GetCellCenter.tar) and its *CMakeLists.txt* file.
Once the *tarball GetCellCenter.tar* has been downloaded and extracted,
```
cd GetCellCenter/build 
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
./GetCellCenter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

