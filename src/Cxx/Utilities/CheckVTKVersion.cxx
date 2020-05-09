#include <vtkVersion.h>

#ifdef VTK_VERSION_NUMBER
#if VTK_VERSION_NUMBER >= 90000000000ULL
#define VTK_VER_GE_90 1
#endif
#else
#define VTK_VERSION_NUMBER_NOT_DEFINED 1
#endif

namespace {
/**
 * Check the VTK version.
 *
 * @param major: Major version.
 * @param major: Minor version.
 * @param major: Build version.
 *
 * @return True if the requested VTK version is greater or equal to the actual
 * VTK version.
 */
bool VTKVersionOk(unsigned long long const& major,
                  unsigned long long const& minor,
                  unsigned long long const& build);

} // namespace

int main(int, char*[])
{
#ifdef VTK_VERSION_NUMBER
  std::cout << "Source version: " << vtkVersion::GetVTKSourceVersion()
            << std::endl;
  std::cout << "Major Version : " << vtkVersion::GetVTKMajorVersion()
            << std::endl;
  std::cout << "Minor Version : " << vtkVersion::GetVTKMinorVersion()
            << std::endl;
#elif VTK_VERSION_NUMBER_NOT_DEFINED
  std::cout << "VTK VTK_VERSION_NUMBER is not defined." << std::endl;
  std::cout << "VTK Major Version: " << VTK_MAJOR_VERSION << std::endl;
  std::cout << "VTK Minor Version: " << VTK_MINOR_VERSION << std::endl;
#endif

#ifdef VTK_VER_GE_90
  std::cout << "VTK Version is >= " << VTK_VERSION_NUMBER << std::endl;
#endif

  if (!VTKVersionOk(8, 90, 0))
  {
    std::cerr << "You need VTK version 8.90 or greater to run this program."
              << std::endl;
    return EXIT_FAILURE;
  }
  else
  {
    std::cout << "You have the needed VTK version" << endl;
  }

  return EXIT_SUCCESS;
}

namespace {
bool VTKVersionOk(unsigned long long const& major,
                  unsigned long long const& minor,
                  unsigned long long const& build)
{
  unsigned long long neededVersion =
      10000000000ULL * major + 100000000ULL * minor + build;
#ifndef VTK_VERSION_NUMBER
  auto ver = vtkSmartPointer<vtkVersion>();
  unsigned long long vtk_version_number =
      10000000000ULL * ver->GetVTKMajorVersion() +
      100000000ULL * ver->GetVTKMinorVersion() + ver->GetVTKBuildVersion();
  if (vtk_version_number >= neededVersion)
  {
    return true;
  }
  return false;
#else
  if (VTK_VERSION_NUMBER >= neededVersion)
  {
    return true;
  }
  return false;
#endif
}

} // namespace
