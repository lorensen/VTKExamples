#ifndef __vtkImageAlgorithmFilter_h
#define __vtkImageAlgorithmFilter_h

#include <vtkImageAlgorithm.h>

class vtkImageAlgorithmFilter : public vtkImageAlgorithm 
{
public:
  static vtkImageAlgorithmFilter *New();
  vtkTypeMacro(vtkImageAlgorithmFilter,vtkImageAlgorithm);

  vtkImageAlgorithmFilter(){}
  
protected:

  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
  vtkImageAlgorithmFilter(const vtkImageAlgorithmFilter&);  // Not implemented.
  void operator=(const vtkImageAlgorithmFilter&);  // Not implemented.
};

#endif
