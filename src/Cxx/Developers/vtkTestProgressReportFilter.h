#ifndef __vtkTestProgressReportFilter_h
#define __vtkTestProgressReportFilter_h
 
#include "vtkPolyDataAlgorithm.h"
 
class vtkTestProgressReportFilter : public vtkPolyDataAlgorithm
{
public:
  static vtkTestProgressReportFilter *New();
  vtkTypeMacro(vtkTestProgressReportFilter,vtkAlgorithm);
 
protected:
  vtkTestProgressReportFilter(){}
  ~vtkTestProgressReportFilter() VTK_OVERRIDE {}
 
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *) VTK_OVERRIDE;
 
private:
  vtkTestProgressReportFilter(const vtkTestProgressReportFilter&) VTK_DELETE_FUNCTION;
  void operator=(const vtkTestProgressReportFilter&) VTK_DELETE_FUNCTION;
 
};
 
#endif
