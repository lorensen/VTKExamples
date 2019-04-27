### Description

Given a filename, vtkActor and vtkCamera, save necessary variables to recreate a scene to a file.

!!! note
    The snippet currently just saves the vtkCamera variables.

To use the snippet, click the *Copy to clipboard* at the upper right of the code blocks.

### Declaration Section

``` c++
#include <vtkActor.h>
#include <vtkCamera.h>
namespace
{
void SaveSceneToFile(std::string fileName,
                     vtkActor *actor,
                     vtkCamera *camera);
}
```

### Implementation Section

``` c++
namespace
{
#include <fstream>

void SaveSceneToFile(std::string fileName,
                     vtkActor *actor,
                     vtkCamera *camera)
{
// Actor
//  Position, orientation, origin, scale, usrmatrix, usertransform
//Camera
//  FocalPoint, Position, ViewUp, ViewAngle, ClippingRange
  std::ofstream saveFile(fileName, std::ofstream::out);
  double vector[3];
  double scalar;

  camera->GetFocalPoint(vector);
  saveFile << "Camera:FocalPoint "
           << vector[0] << ", "
           << vector[1] << ", "
           << vector[2] << std::endl;
  camera->GetPosition(vector);
  saveFile << "Camera:Position "
           << vector[0] << ", "
           << vector[1] << ", "
           << vector[2] << std::endl;
  camera->GetViewUp(vector);
  saveFile << "Camera:ViewUp "
           << vector[0] << ", "
           << vector[1] << ", "
           << vector[2] << std::endl;
  scalar = camera->GetViewAngle();
  saveFile << "Camera:ViewAngle "
           << scalar << std::endl;
  camera->GetClippingRange(vector);
  saveFile << "Camera:ClippingRange "
           << vector[0] << ", "
           << vector[1] << std::endl;
  saveFile.close();
}
} // namespace

```
