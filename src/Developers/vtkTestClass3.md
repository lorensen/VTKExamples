### Description
<source lang="cpp">
#ifndef __vtkTestClass_h
#define __vtkTestClass_h

#include "vtkPolyDataAlgorithm.h"

class vtkTestClass : public vtkPolyDataAlgorithm
{
public:
  vtkTypeMacro(vtkTestClass,vtkPolyDataAlgorithm);
  static vtkTestClass *New();

  vtkSetVector3Macro(TestVector,double);
  vtkGetVector3Macro(TestVector,double);
  
protected:
  vtkTestClass();
  ~vtkTestClass(){}
 int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
  vtkTestClass(const vtkTestClass&);  // Not implemented.
  void operator=(const vtkTestClass&);  // Not implemented.

  double TestVector[](3);
};

#endif

</source>
