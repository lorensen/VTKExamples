// .NAME vtkTestMultipleInputPortsFilter
// .SECTION Description
// vtkTestMultipleInputPortsFilter

#ifndef __vtkTestMultipleInputPortsFilter_h
#define __vtkTestMultipleInputPortsFilter_h

#include <vtkPolyDataAlgorithm.h>

class vtkTestMultipleInputPortsFilter : public vtkPolyDataAlgorithm
{
public:
  static vtkTestMultipleInputPortsFilter *New();
  vtkTypeMacro(vtkTestMultipleInputPortsFilter,vtkPolyDataAlgorithm);

protected:
  vtkTestMultipleInputPortsFilter();
  ~vtkTestMultipleInputPortsFilter() {}

  int FillInputPortInformation( int port, vtkInformation* info ) override;
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *) override;

private:
  vtkTestMultipleInputPortsFilter(const vtkTestMultipleInputPortsFilter&) = delete;
  void operator=(const vtkTestMultipleInputPortsFilter&) = delete;

};

#endif
