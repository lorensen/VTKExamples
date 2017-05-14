// .NAME vtkTestMultipleInputPortsFilter
// .SECTION Description
// vtkTestMultipleInputPortsFilter

#ifndef __vtkTestMultipleInputPortsFilter_h
#define __vtkTestMultipleInputPortsFilter_h

#include "vtkPolyDataAlgorithm.h"

class vtkTestMultipleInputPortsFilter : public vtkPolyDataAlgorithm
{
public:
  static vtkTestMultipleInputPortsFilter *New();
  vtkTypeMacro(vtkTestMultipleInputPortsFilter,vtkPolyDataAlgorithm);

protected:
  vtkTestMultipleInputPortsFilter();
  ~vtkTestMultipleInputPortsFilter() VTK_OVERRIDE {}

  int FillInputPortInformation( int port, vtkInformation* info ) VTK_OVERRIDE;
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *) VTK_OVERRIDE;

private:
  vtkTestMultipleInputPortsFilter(const vtkTestMultipleInputPortsFilter&) VTK_DELETE_FUNCTION;
  void operator=(const vtkTestMultipleInputPortsFilter&) VTK_DELETE_FUNCTION;

};

#endif
