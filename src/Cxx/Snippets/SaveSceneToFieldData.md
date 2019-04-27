### Description

Given a vtkDataSet, vtkActor and vtkCamera, save necessary variables in the vtkDataSet's vtkFieldData to recreate a scene to a file.

!!! note
    The snippet currently just saves the vtkCamera variables.

To use the snippet, click the *Copy to clipboard* at the upper right of the code blocks.

### Declaration Section

``` c++
namespace
{
void SaveSceneToFieldData(vtkDataSet *data,
                          vtkActor *actor,
                          vtkCamera *camera);
}
```

### Implementation Section

``` c++
#include <sstream>

namespace
{
void SaveSceneToFieldData(vtkDataSet *data,
                          vtkActor *actor,
                          vtkCamera *camera)
{
  std::ostringstream buffer;
  double vector[3];
  double scalar;

  camera->GetFocalPoint(vector);
  buffer << "Camera:FocalPoint "
         << vector[0] << ", "
         << vector[1] << ", "
         << vector[2] << std::endl;
  camera->GetPosition(vector);
  buffer << "Camera:Position "
           << vector[0] << ", "
           << vector[1] << ", "
           << vector[2] << std::endl;
  camera->GetViewUp(vector);
  buffer << "Camera:ViewUp "
           << vector[0] << ", "
           << vector[1] << ", "
           << vector[2] << std::endl;
  scalar = camera->GetViewAngle();
  buffer << "Camera:ViewAngle "
           << scalar << std::endl;
  camera->GetClippingRange(vector);
  buffer << "Camera:ClippingRange "
           << vector[0] << ", "
           << vector[1] << std::endl;
  vtkSmartPointer<vtkStringArray> cameraArray = 
    vtkSmartPointer<vtkStringArray>::New();
  cameraArray->SetNumberOfValues(1);
  cameraArray->SetValue(0, buffer.str());
  cameraArray->SetName("Camera");
  data->GetFieldData()->AddArray(cameraArray);
}
} // namespace

```
