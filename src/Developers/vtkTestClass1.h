#ifndef __vtkTestClass_h
#define __vtkTestClass_h

#include "vtkDataObject.h"

class vtkMatrix3x3;

class vtkTestClass : public vtkDataObject
{
public:
  vtkTypeRevisionMacro(vtkTestClass,vtkDataObject);
  static vtkTestClass *New();
	
  vtkSetClampMacro(Value, int, 2, 8);
  vtkGetMacro(Value, int);
  
  
protected:
  vtkTestClass(){}
  ~vtkTestClass(){}
  
private:
  vtkTestClass(const vtkTestClass&);  // Not implemented.
  void operator=(const vtkTestClass&);  // Not implemented.

  int Value;
};

#endif
