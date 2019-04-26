### Description

Given a color, find a contrasting color. If the given color is "light", use the lightColor otherwise use the darkColor.

To use the snippet, click the *Copy to clipboard* at the upper right of the code blocks.

### Declaration Section

``` c++
#include <vtkNamedColors.h>
#include <vtkMath.h>
namespace
{
// Given a color, find a contrasting color. If the given color is "light",
// use the lightColor otherwise use the darkColor
void ChooseContrastingColor(double *rgbIn,
                            double *rgbOut,
                            const double threshold = .5,
                            const std::string lightColor = "white",
                            const std::string darkColor = "black");
}
```

### Implementation Section

``` c++
namespace
{
void ChooseContrastingColor(double *rgbIn,
                            double *rgbOut,
                            const double threshold,
                            const std::string lightColor,
                            const std::string darkColor)
{
  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  double hsv[3];
  // If the value is <= threshold, use a light color, otherwise use a dark color
  vtkMath::RGBToHSV(rgbIn, hsv);
  if (hsv[2] <= threshold)
  {
    colors->GetColor(lightColor.c_str(), rgbOut[0], rgbOut[1], rgbOut[2]);
  }
  else
  {
    colors->GetColor(darkColor.c_str(), rgbOut[0], rgbOut[1], rgbOut[2]);
  }
}
}  // namespace

```
