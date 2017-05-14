// .NAME vtkTestMultipleInputConnectionsFilter
// .SECTION Description
// vtkTestMultipleInputConnectionsFilter

#ifndef __vtkTestMultipleInputConnectionsFilter_h
#define __vtkTestMultipleInputConnectionsFilter_h

#include "vtkPolyDataAlgorithm.h"

class vtkTestMultipleInputConnectionsFilter : public vtkPolyDataAlgorithm
{
public:
  vtkTypeMacro(vtkTestMultipleInputConnectionsFilter,vtkPolyDataAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  static vtkTestMultipleInputConnectionsFilter *New();

protected:
  vtkTestMultipleInputConnectionsFilter(){}
  ~vtkTestMultipleInputConnectionsFilter(){}

  int FillInputPortInformation( int port, vtkInformation* info );
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
  vtkTestMultipleInputConnectionsFilter(const vtkTestMultipleInputConnectionsFilter&);  // Not implemented.
  void operator=(const vtkTestMultipleInputConnectionsFilter&);  // Not implemented.

};

#endif
