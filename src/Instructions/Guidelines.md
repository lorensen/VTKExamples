[TOC]

## Requirements
Although education of new users in the main motivation, the VTK wiki examples should also:

1. Encourage good programming style
2. Promote the proper and modern way to use VTK and write VTK programs
3. Facilitate the nightly compilation and testing of examples that reside in the VTK wiki

These requirements must be met without compromising the main goal of user education.

## Guidelines

All examples should follow the VTK programming style.

* The indentation style can be characterized as the [Allmann
Style](https://en.wikipedia.org/wiki/Indent_style#Allman_style). The curly brace (scope delimiter) is on a separate line and aligns with the control statement, The control block is indented by two spaces (**no tabs**).

    Example:

    ```
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

    ```
    std::cout << "Print something" << std::endl;
    ```
    rather than

    ```
    cout << "Print something" << endl;
    ```

* All includes from the toolkit should use <> notation. This follows C++ programming conventions.

    For example: `#include <vtkContourFilter.h>` is preferred over `#include "vtkContourFilter.h"`

* The main program must have the following signature:

    ```
    int main (int argc, char *argv{})
    ```

    or, if argc and argv are not referenced in the code,

    ```
    int main (int, char *[])
    ```

* If arguments are required, a check similar to the following should be made at the start of the main program.

    ```
    if (argc != 3)
    {
      std::cerr << "Usage: " << argv[0] << "Alpha InputFile OutputFile" << std::endl;
      return EXIT_FAILURE;
    }
    ```

* An example should **never call exit()**. If the main program executes successfully, it should

    ```
    return EXIT_SUCCESS;
    ```

    otherwise

    ```
    return EXIT_FAILURE;
    ```

* The use of SmartPointers is preferred in VTK examples.

    ```
    vtkSmartPointer<vtkCutter> cutter = vtkSmartPointer<vtkCutter>::New();
    ```
    or

    ```
    vtkNew(vtkCutter> cutter;
    ```

    is preferred over

    ```
    vtkCutter *cutter = vtkCutter::New();
    ```

* When building pipelines, the new `SetInputConnection()`, `GetOutputPort()` methods should be used instead of `SetInput()`, `GetOutput()`

* Input/Output filenames

    When possible, filenames should be passed on the command line. This gives the examples utility beyond the data that is used in the specific example.

* If there are just a few parameters for the example, these should be passed in as arguments. This increases the utility of the example and facilitates testing.

    For example, this program

    ```
    Delaunay3DAlpha Alpha InputPolydataFileName(.vtp) OutputUnstructuredGridFilename(.vtu)
    ```

    would use the arguments in this manner

    ```
    reader->SetFileName (argv[2]);
    delaunay3D->SetAlpha(atof(argv[1]));
    writer->SetFileName ( argv[3] );
    ```
