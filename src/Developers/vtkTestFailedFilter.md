### Description
<source lang="cpp">
// .NAME vtkTestFailedFilter
// .SECTION Description
// vtkTestFailedFilter

#ifndef __vtkTestFailedFilter_h
#define __vtkTestFailedFilter_h

#include "vtkPolyDataAlgorithm.h"

class vtkTestFailedFilter : public vtkPolyDataAlgorithm
{
public:
  vtkTypeMacro(vtkTestFailedFilter,vtkPolyDataAlgorithm);
  static vtkTestFailedFilter *New();

protected:
  vtkTestFailedFilter(){}
  ~vtkTestFailedFilter(){}

  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
  vtkTestFailedFilter(const vtkTestFailedFilter&);  // Not implemented.
  void operator=(const vtkTestFailedFilter&);  // Not implemented.

};

#endif

</source>
