#ifndef __vtkTestFilterProgressFilter_h
#define __vtkTestFilterProgressFilter_h

#include <vtkPolyDataAlgorithm.h>

class vtkTestFilterProgressFilter : public vtkPolyDataAlgorithm
{
public:
  static vtkTestFilterProgressFilter *New();
  vtkTypeMacro(vtkTestFilterProgressFilter,vtkAlgorithm);

protected:
  vtkTestFilterProgressFilter();
  ~vtkTestFilterProgressFilter() override;

  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *) override;

  static void ProgressFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData);

private:
  vtkTestFilterProgressFilter(const vtkTestFilterProgressFilter&) = delete;
  void operator=(const vtkTestFilterProgressFilterr&) = delete;

};

#endif
