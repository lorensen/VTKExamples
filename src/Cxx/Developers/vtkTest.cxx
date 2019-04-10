#include "vtkTest.h"

#include <vtkObjectFactory.h>

vtkStandardNewMacro(vtkTest);

vtkTest::vtkTest()
{
  this->Value = 0.0;
}

vtkTest::~vtkTest()
{

}

void vtkTest::PrintSelf( ostream& os, vtkIndent indent )
{
  this->Superclass::PrintSelf( os, indent );
}

void vtkTest::ShallowCopy(vtkDataObject* t)
{
  vtkTest *m = dynamic_cast<vtkTest*>(t);
  this->Value = m->GetValue();
}
