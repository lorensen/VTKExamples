#include <vtkTimeStamp.h>

int main(int, char *[])
{
  vtkTimeStamp timeStamp;
  std::cout << "Time stamp: " << timeStamp << std::endl;
  timeStamp.Modified();
  std::cout << "Time stamp: " << timeStamp << std::endl;

  return EXIT_SUCCESS;
}
