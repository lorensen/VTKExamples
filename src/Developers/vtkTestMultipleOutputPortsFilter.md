### Description
<source lang="cpp">
// .NAME vtkTestMultipleOutputPortsFilter
// .SECTION Description
// vtkTestMultipleOutputPortsFilter

#ifndef __vtkTestMultipleOutputPortsFilter_h
#define __vtkTestMultipleOutputPortsFilter_h

#include "vtkPolyDataAlgorithm.h"

class vtkTestMultipleOutputPortsFilter : public vtkPolyDataAlgorithm
{
public:
  vtkTypeMacro(vtkTestMultipleOutputPortsFilter,vtkPolyDataAlgorithm);
  static vtkTestMultipleOutputPortsFilter *New();

protected:
  vtkTestMultipleOutputPortsFilter();
  ~vtkTestMultipleOutputPortsFilter(){}

  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
  vtkTestMultipleOutputPortsFilter(const vtkTestMultipleOutputPortsFilter&);  // Not implemented.
  void operator=(const vtkTestMultipleOutputPortsFilter&);  // Not implemented.

};

#endif

</source>
