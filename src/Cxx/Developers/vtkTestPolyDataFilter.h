#ifndef __vtkTestPolyDataFilter_h
#define __vtkTestPolyDataFilter_h

#include <vtkPolyDataAlgorithm.h>

class vtkTestPolyDataFilter : public vtkPolyDataAlgorithm 
{
public:
  vtkTypeMacro(vtkTestPolyDataFilter,vtkPolyDataAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  static vtkTestPolyDataFilter *New();
	
protected:
  vtkTestPolyDataFilter();
  ~vtkTestPolyDataFilter();
  
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
  vtkTestPolyDataFilter(const vtkTestPolyDataFilter&);  // Not implemented.
  void operator=(const vtkTestPolyDataFilter&);  // Not implemented.

};

#endif
