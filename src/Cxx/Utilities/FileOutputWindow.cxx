#include <vtkFileOutputWindow.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkSmartPointer.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkFileOutputWindow> fileOutputWindow = 
      vtkSmartPointer<vtkFileOutputWindow>::New();
  fileOutputWindow->SetFileName( "output.txt" );

  // Note that the SetInstance function is a static member of vtkOutputWindow.
  vtkOutputWindow::SetInstance(fileOutputWindow);

  // This causes an error intentionally (file name not specified) - this error will be written to the file output.txt
  vtkSmartPointer<vtkXMLPolyDataReader> reader = 
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->Update();

  return EXIT_SUCCESS;
}
