#include "vtkTestA.h"

#include "vtkObjectFactory.h"

vtkStandardNewMacro(vtkTestA);
vtkCxxRevisionMacro(vtkTestA,"$Revision: 1.46 $");

vtkTestA::vtkTestA()
{
  this->Value = 4.5;
}

vtkTestA::~vtkTestA()
{

}

void vtkTestA::PrintSelf( ostream& os, vtkIndent indent )
{
  this->Superclass::PrintSelf( os, indent );
}
