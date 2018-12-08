#ifndef __vtkTestFilterSelfProgressFilter_h
#define __vtkTestFilterSelfProgressFilter_h

#include <vtkPolyDataAlgorithm.h>

class vtkTestFilterSelfProgressFilter : public vtkPolyDataAlgorithm
{
public:
  vtkTypeMacro(vtkTestFilterSelfProgressFilter,vtkAlgorithm);

  static vtkTestFilterSelfProgressFilter *New();

protected:
  vtkTestFilterSelfProgressFilter();
  ~vtkTestFilterSelfProgressFilter() {}

  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *) override;

  static void ProgressFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData);

private:
  vtkTestFilterSelfProgressFilter(const vtkTestFilterSelfProgressFilter&) = delete;
  void operator=(const vtkTestFilterSelfProgressFilter&) = delete;

};

#endif
