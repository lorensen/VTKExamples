#include "vtkTestB.h"

#include "vtkObjectFactory.h"

vtkStandardNewMacro(vtkTestB);
vtkCxxRevisionMacro(vtkTestB,"$Revision: 1.46 $");

vtkTestB::vtkTestB()
{
  this->Value = 4.5;
}

vtkTestB::~vtkTestB()
{

}

void vtkTestB::PrintSelf( ostream& os, vtkIndent indent )
{
  this->Superclass::PrintSelf( os, indent );
}
