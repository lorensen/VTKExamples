# Description

Given a filename, render window and optionally a rgba value, take a screenshot of the render window and write it to a file. The extension of the filename determines what writer to use.

To use the snippet, click the *Copy to clipboard* at the upper left of the code blocks.

## C++

### Declaration Section

```c++

#include <vtkBMPWriter.h>
#include <vtkImageWriter.h>
#include <vtkJPEGWriter.h>
#include <vtkPNGWriter.h>
#include <vtkPNMWriter.h>
#include <vtkPostScriptWriter.h>
#include <vtkTIFFWriter.h>
#include <vtkWindowToImageFilter.h>

#include <algorithm>
#include <locale>
#include <string>

namespace
{
/**
 * Write the render window view to an image file.
 * 
 * Image types supported are:
 *  BMP, JPEG, PNM, PNG, PostScript, TIFF.
 * The default parameters are used for all writers, change as needed.
 * 
 * @param fileName The file name, if no extension then PNG is assumed.
 * @param renWin The render window.
 * @param rgba Used to set the buffer type.
 * 
 */
void WriteImage(std::string const& fileName, vtkRenderWindow* renWin,
                bool rgba = true);


}

```

### Implementation Section

``` c++

namespace
{
void WriteImage(std::string const& fileName, vtkRenderWindow* renWin, bool rgba)
{
  if (!fileName.empty())
  {
    std::string fn = fileName;
    std::string ext;
    auto found = fn.find_last_of(".");
    if (found == std::string::npos)
    {
      ext = ".png";
      fn += ext;
    }
    else
    {
      ext = fileName.substr(found, fileName.size());
    }
    std::locale loc;
    std::transform(ext.begin(), ext.end(), ext.begin(),
                   [=](char const& c) { return std::tolower(c, loc); });
    auto writer = vtkSmartPointer<vtkImageWriter>::New();
    if (ext == ".bmp")
    {
      writer = vtkSmartPointer<vtkBMPWriter>::New();
    }
    else if (ext == ".jpg")
    {
      writer = vtkSmartPointer<vtkJPEGWriter>::New();
    }
    else if (ext == ".pnm")
    {
      writer = vtkSmartPointer<vtkPNMWriter>::New();
    }
    else if (ext == ".ps")
    {
      if (rgba)
      {
        rgba = false;
      }
      writer = vtkSmartPointer<vtkPostScriptWriter>::New();
    }
    else if (ext == ".tiff")
    {
      writer = vtkSmartPointer<vtkTIFFWriter>::New();
    }
    else
    {
      writer = vtkSmartPointer<vtkPNGWriter>::New();
    }
    auto window_to_image_filter =
        vtkSmartPointer<vtkWindowToImageFilter>::New();
    window_to_image_filter->SetInput(renWin);
    window_to_image_filter->SetScale(1); // image quality
    if (rgba)
    {
      window_to_image_filter->SetInputBufferTypeToRGBA();
    }
    else
    {
      window_to_image_filter->SetInputBufferTypeToRGB();
    }
    // Read from the front buffer.
    window_to_image_filter->ReadFrontBufferOff();
    window_to_image_filter->Update();

    writer->SetFileName(fn.c_str());
    writer->SetInputConnection(window_to_image_filter->GetOutputPort());
    writer->Write();
  }
  else
  {
    std::cerr << "No filename provided." << std::endl;
  }

  return;
}
} // namespace

```

### Usage

``` c++

  WriteImage(f, renWin, false);
  
```
