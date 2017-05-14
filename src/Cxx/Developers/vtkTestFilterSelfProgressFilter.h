#ifndef __vtkTestFilterSelfProgressFilter_h
#define __vtkTestFilterSelfProgressFilter_h
 
#include "vtkPolyDataAlgorithm.h"
 
class vtkTestFilterSelfProgressFilter : public vtkPolyDataAlgorithm 
{
public:
  vtkTypeMacro(vtkTestFilterSelfProgressFilter,vtkAlgorithm);
  
  static vtkTestFilterSelfProgressFilter *New();
 
protected:
  vtkTestFilterSelfProgressFilter();
  ~vtkTestFilterSelfProgressFilter(){}
 
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *) VTK_OVERRIDE; 
 
  static void ProgressFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData);
  
private:
  vtkTestFilterSelfProgressFilter(const vtkTestFilterSelfProgressFilter&);  // Not implemented.
  void operator=(const vtkTestFilterSelfProgressFilter&);  // Not implemented.
 
};
 
#endif
