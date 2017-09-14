###Description
This example uses a simple algorithm to choose a color that "contrasts" with another color. The *ChooseContrastingColor* procedure converts the input [RGB](https://en.wikipedia.org/wiki/RGB_color_model) value to [HSV](https://en.wikipedia.org/wiki/Color_model#HSV_and_HSL_representations) using vtkMath::RGBToHSV. If the value is <= .5, the light color is chosen as the contrasting color. Otherwise, the dark color is chosen. The default light color is white and the default dark color is black. Any color from vtkNamedColors can be specified for the light and dark colors.

To run the example with your own arguments:
``` bash
ChooseTextColor fontFile [background] [lightColor] [darkColor]
```

!!! info
    [VTKNamedColorPatches](http://htmlpreview.github.com/?https://github.com/lorensen/VTKExamples/blob/master/src/Python/Visualization/VTKNamedColorPatches.html) shows the availabel colors.

!!! info
    The *ChooseContrastingColor* procedure is reusable, Cut and paste the declarations and code into other examples.

!!! tip
    There are many sources of TrueType fonts. [Here is one source](http://www.1001freefonts.com/).
