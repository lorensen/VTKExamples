#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkExodusIIWriter.h>
#include <vtkTimeSourceExample.h>
 
int main(int, char *[])
{
             
  vtkSmartPointer<vtkTimeSourceExample> timeSource = 
    vtkSmartPointer<vtkTimeSourceExample>::New();
               
  vtkSmartPointer<vtkExodusIIWriter> exodusWriter = 
    vtkSmartPointer<vtkExodusIIWriter>::New();
  exodusWriter->SetFileName("output.exii");
  exodusWriter->SetInputConnection (timeSource->GetOutputPort());
  exodusWriter->WriteAllTimeStepsOn ();
  exodusWriter->Write();
                       
  return EXIT_SUCCESS;
}
