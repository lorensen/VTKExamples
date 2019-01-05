## Requirements
Although education of new users is the main motivation, the VTK Examples should also:

1. Encourage good programming style
2. Promote the proper and modern way to use VTK and write VTK programs
3. Facilitate the nightly compilation and testing of examples that reside in the VTKExamples repository.

These requirements must be met without compromising the main goal of user education.

## Guidelines

All examples should follow the VTK programming style and there should be a single blank line at the end of the example

### C++

* The indentation style can be characterized as the [AllmannStyle](https://en.wikipedia.org/wiki/Indent_style#Allman_style). The curly brace (scope delimiter) is on a separate line and aligns with the control statement, The control block is indented by two spaces (**no tabs**).

    Example:

```c++
if (this->Locator == locator)
{
  return;
}
for (i = 0; i < this->Source->GetNumberOfPoints(); i++)
{
  p1 = this->Source->GetPoint(i);
  [...]
}
```

* Where appropriate, explicitly use the std:: namespace:

```c++
    std::cout << "Print something" << std::endl;
```

    rather than

```c++
    cout << "Print something" << endl;
```

* All includes from the toolkit should use <> notation. This follows C++ programming conventions.

    For example: `#include <vtkContourFilter.h>` is preferred over `#include "vtkContourFilter.h"`

* The main program must have the following signature:

    ```c++
    int main (int argc, char *argv[])
    ```

    or, if argc and argv are not referenced in the code,

    ```c++
    int main (int, char *[])
    ```

* If arguments are required, a check similar to the following should be made at the start of the main program.

```c++
if (argc != 3)
{
  std::cerr << "Usage: " << argv[0] << "Alpha InputFile OutputFile" << std::endl;
  return EXIT_FAILURE;
}
```

* An example should **never call exit()**. If the main program executes successfully, it should

```c++
return EXIT_SUCCESS;
```

    otherwise

```c++
return EXIT_FAILURE;
```

* The use of SmartPointers is preferred in VTK examples.

```c++
vtkSmartPointer<vtkCutter> cutter = vtkSmartPointer<vtkCutter>::New();
```

    or

```c++
vtkNew<vtkCutter> cutter;
```

is preferred over

```c++
vtkCutter *cutter = vtkCutter::New();
```

* When building pipelines, the new `SetInputConnection()`, `GetOutputPort()` methods should be used instead of `SetInput()`, `GetOutput()`

* Input/Output filenames

    When possible, filenames should be passed on the command line. This gives the examples utility beyond the data that is used in the specific example.

* If there are just a few parameters for the example, these should be passed in as arguments. This increases the utility of the example and facilitates testing.

    For example, this program

```c++
Delaunay3DAlpha Alpha InputPolydataFileName(.vtp) OutputUnstructuredGridFilename(.vtu)
```

would use the arguments in this manner

```c++
reader->SetFileName (argv[2]);
delaunay3D->SetAlpha(atof(argv[1]));
writer->SetFileName ( argv[3] );
```

* Always provide a background for the renderers. Avoid setting the background to white.

* Use [vtkNamedColors](http://www.vtk.org/doc/nightly/html/classvtkNamedColors.html) for setting colors of actors and renderer backgrounds. [This html file](http://htmlpreview.github.io/?https://github.com/lorensen/VTKExamples/blob/master/src/Python/Visualization/VTKNamedColorPatches.html) shows the colors that are available.

    For example,

```c++
#include <vtkNamedColors.h>

  vtkSmartPointer<vtkNamedColors> namedColors =
    vtkSmartPointer<vtkNamedColors>::New();

    renderer->SetBackground(namedColors->GetColor3d("Khaki").GetData());
```

is preferred over

```c++
    renderer->SetBackground(0.9412, 0.9020, 0.5490);
```

* Use admonitons to warn/cite/info, etc. [Here is a summary of admonitions](https://lorensen.github.io/VTKExamples/site/Instructions/ForAdministrators/#admonition).

### Python

In general Python submissions should follow the VTK Programming style and the comments outlined for C++ above (with language appropriate modification).

Python code styling follows [PEP 8 -- Style Guide for Python Code](https://www.python.org/dev/peps/pep-0008/)

Python code should follow the following layout:

```Python
#!/usr/bin/env python

#import vtk

def main():
    """
    Get parmaters (if needed)
    Instantiate your classes, call them and any defs.
    """


if __name__ == '__main__':
    main()

```

* Input/Output filenames and parameters.

    Use this snippet [GetProgramParameters](https://lorensen.github.io/VTKExamples/site/Python/Snippets/GetProgramParameters/) 

### Java
In general Python submissions should follow the VTK Programming style and the comments outlined for C++ above (with language appropriate modification).

For Java code layout, look at [CylinderExample](https://lorensen.github.io/VTKExamples/site/Java/GeometricObjects/CylinderExample/)

Java code styling follows the usual style as implemented in the IDEs.

However note:
 - No Tabs
 - Indentation must be two spaces
