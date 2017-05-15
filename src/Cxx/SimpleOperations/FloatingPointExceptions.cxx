#include <vtkFloatingPointExceptions.h>

// Avoid the "potential divide by 0" warning from the Microsoft
// compiler, since this example intentionally divides by 0
#ifdef _MSC_VER
#pragma warning (disable: 4723)
#endif

int main(int, char *[])
{
  // Disabled by default with gcc or visual studio.
  // Enabled by default by Borland CC.
  vtkFloatingPointExceptions::Enable(); 

  double x = 0.0;
  double y = 1.0/x; // floating-point exception

  std::cout << "x: " << x << " y: " << y << std::endl;

  return EXIT_SUCCESS;
}
