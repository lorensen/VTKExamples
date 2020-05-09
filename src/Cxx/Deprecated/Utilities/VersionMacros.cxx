#include <vtkPolyData.h>
#include <vtkVersion.h> // NOTE: without this include, the VTK_[]_VERSION are not defined!

// These functions allow you to output the version defines at compile time
#define STR(x) STR2(x)
#define STR2(x) #x

int main(int, char *[])
{
  #if VTK_MAJOR_VERSION>5 || (VTK_MAJOR_VERSION==5 && VTK_MINOR_VERSION>4)
    #pragma message(STR(VTK_MAJOR_VERSION))
  #endif

  return EXIT_SUCCESS;
}
