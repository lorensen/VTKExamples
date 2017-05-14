#include "vtkTest.h"

#include "vtkObjectFactory.h"

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

void vtkTest::ShallowCopy(vtkTest* t)
{
  this->Value = t->GetValue(); 
}
