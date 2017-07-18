#include "vtkTest1.h"

#include <vtkObjectFactory.h>

vtkStandardNewMacro(vtkTest1);

vtkTest1::vtkTest1()
{
  this->Value = 4.5;
}

vtkTest1::~vtkTest1()
{

}

void vtkTest1::PrintSelf( ostream& os, vtkIndent indent )
{
  this->Superclass::PrintSelf( os, indent );
}
