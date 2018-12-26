# Description

Given a filename, render window and optionally a rgba value, take a screenshot of the render window and write it to a file.

After using it, remove the function and the corresponding call.

Typical usage would be:

```Java
  // ...
  renWin.Render();
  // After creating the test image, this line must be removed.
  writeImage(renWin, "Test<Name of the Java File>.png");

  iren.Initialize();
  iren.Start();
```

These imports are needed.

```Java
// For writing an image
import vtk.vtkPNGWriter;
import vtk.vtkWindowToImageFilter;
```

To use the snippet, click the *Copy to clipboard* at the upper left of the code blocks.

## Java

### Declaration Section

```Java

/**
  * Write the render window to a PNG file.
  * <p>
  * After creating the image, this function should be removed.
  *
  * @param renWin The render window
  * @param fn     The name of the image file.
  */
public static void writeImage(vtkRenderWindow renWin, String fn) {
  vtkWindowToImageFilter windowToImageFilter = new vtkWindowToImageFilter();
  windowToImageFilter.SetInput(renWin);
  windowToImageFilter.SetScale(1);
  windowToImageFilter.SetInputBufferTypeToRGB();

  windowToImageFilter.ReadFrontBufferOff();
  windowToImageFilter.Update();

  vtkPNGWriter writer = new vtkPNGWriter();
  writer.SetFileName(fn);
  writer.SetInputConnection(windowToImageFilter.GetOutputPort());
  writer.Write();
}


```

### Usage

```Java

  // After creating the test image, this line must be removed.
  writeImage(renWin, "Test<Name of the Java File>.png");
  
```
