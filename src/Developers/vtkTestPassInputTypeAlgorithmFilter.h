// .NAME vtkTestPassInputTypeAlgorithmFilter
// .SECTION Description
// vtkTestPassInputTypeAlgorithmFilter

#ifndef __vtkTestPassInputTypeAlgorithmFilter_h
#define __vtkTestPassInputTypeAlgorithmFilter_h

#include "vtkPassInputTypeAlgorithm.h"

class vtkTestPassInputTypeAlgorithmFilter : public vtkPassInputTypeAlgorithm 
{
public:
  vtkTypeMacro(vtkTestPassInputTypeAlgorithmFilter,vtkPassInputTypeAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  static vtkTestPassInputTypeAlgorithmFilter *New();
	
protected:
  vtkTestPassInputTypeAlgorithmFilter(){}
  ~vtkTestPassInputTypeAlgorithmFilter(){}
  
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
  vtkTestPassInputTypeAlgorithmFilter(const vtkTestPassInputTypeAlgorithmFilter&);  // Not implemented.
  void operator=(const vtkTestPassInputTypeAlgorithmFilter&);  // Not implemented.

};

#endif
