### Description

Given a vtkDataSet, vtkActor and vtkCamera, restore the necessary variables in the vtkDataSet's vtkFieldData to recreate a scene to a file.

!!! note
    The snippet currently just saves the vtkCamera variables.

To use the snippet, click the *Copy to clipboard* at the upper right of the code blocks.

### Declaration Section

``` c++
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkDataSet.h>
#include <vtkFieldData.h>
#include <vtkStringArray.h>
#include <vtksys/RegularExpression.hxx>

namespace
{
void RestoreSceneFromFieldData(vtkDataSet *data,
                               vtkActor *actor,
                               vtkCamera *camera);
}
```

### Implementation Section

``` c++
namespace
{
void  RestoreSceneFromFieldData(vtkDataSet *data,
                               vtkActor *actor,
                               vtkCamera *camera)
{

  std::istringstream buffer;

  // Get the saved camera information from the field data
  if (vtkStringArray::SafeDownCast(
        data->GetFieldData()->GetAbstractArray("Camera")))
  {
    buffer.str(vtkStringArray::SafeDownCast(
                 data->GetFieldData()->GetAbstractArray("Camera"))->GetValue(0));
  }
  else
  {
    return;
  }

  std::string line;
  double vector[3];
  double scalar;

  vtksys::RegularExpression reCP("^Camera:Position");
  vtksys::RegularExpression reCFP("^Camera:FocalPoint");
  vtksys::RegularExpression reCVU("^Camera:ViewUp");
  vtksys::RegularExpression reCVA("^Camera:ViewAngle");
  vtksys::RegularExpression reCCR("^Camera:ClippingRange");
  vtksys::RegularExpression floatNumber(
      "[^0-9\\.\\-]*([0-9e\\.\\-]*[^,])[^0-9\\.\\-]*([0-9e\\.\\-]*[^,])[^0-9\\.\\-]*([0-9e\\.\\-]*[^,])");
  vtksys::RegularExpression floatScalar("[^0-9\\.\\-]*([0-9\\.\\-e]*[^,])");

  while (std::getline(buffer,line))
  {
    if (reCFP.find(line))
    {
      std::string rest(line, reCFP.end());
      if (floatNumber.find(rest))
      {
        camera->SetFocalPoint(
          atof(floatNumber.match(1).c_str()),
          atof(floatNumber.match(2).c_str()),
          atof(floatNumber.match(3).c_str()));
      }
    }
    else if (reCP.find(line))
    {
      std::string rest(line, reCP.end());
      if (floatNumber.find(rest))
      {
        camera->SetPosition(
          atof(floatNumber.match(1).c_str()),
          atof(floatNumber.match(2).c_str()),
          atof(floatNumber.match(3).c_str()));
      }
    }
    else if (reCVU.find(line))
    {
      std::string rest(line, reCVU.end());
      if (floatNumber.find(rest))
      {
        camera->SetViewUp(
          atof(floatNumber.match(1).c_str()),
          atof(floatNumber.match(2).c_str()),
          atof(floatNumber.match(3).c_str()));
      }
    }
    else if (reCVA.find(line))
    {
      std::string rest(line, reCVA.end());
      if (floatScalar.find(rest))
      {
        camera->SetViewAngle(
          atof(floatScalar.match(1).c_str()));
      }
    }
    else if (reCCR.find(line))
    {
      std::string rest(line, reCCR.end());
      if (floatNumber.find(rest))
      {
        camera->SetClippingRange(
          atof(floatNumber.match(1).c_str()),
          atof(floatNumber.match(2).c_str()));
      }
    }
    else
    {
      std::cout << "Unrecognized line: " << line << std::endl;
    }
  }
}
} // namespace

```
