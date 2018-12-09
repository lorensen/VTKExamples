#ifndef __vtkTestProgressReportFilter_h
#define __vtkTestProgressReportFilter_h

#include <vtkPolyDataAlgorithm.h>

class vtkTestProgressReportFilter : public vtkPolyDataAlgorithm
{
public:
  static vtkTestProgressReportFilter *New();
  vtkTypeMacro(vtkTestProgressReportFilter,vtkAlgorithm);

protected:
  vtkTestProgressReportFilter(){}
  ~vtkTestProgressReportFilter() {}

  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *) override;

private:
  vtkTestProgressReportFilter(const vtkTestProgressReportFilter&) = delete;
  void operator=(const vtkTestProgressReportFilter&) = delete;

};

#endif
