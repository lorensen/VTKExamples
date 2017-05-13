#ifndef __vtkImageAlgorithmSource_h
#define __vtkImageAlgorithmSource_h

#include "vtkImageAlgorithm.h"

class vtkImageAlgorithmSource : public vtkImageAlgorithm 
{
public:
  vtkTypeMacro(vtkImageAlgorithmSource,vtkImageAlgorithm);

  static vtkImageAlgorithmSource *New();
	
protected:
  vtkImageAlgorithmSource();

  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
  vtkImageAlgorithmSource(const vtkImageAlgorithmSource&);  // Not implemented.
  void operator=(const vtkImageAlgorithmSource&);  // Not implemented.

};

#endif
