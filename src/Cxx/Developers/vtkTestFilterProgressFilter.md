### Description
<source lang="cpp">
#ifndef __vtkTestFilterProgressFilter_h
#define __vtkTestFilterProgressFilter_h
 
#include <vtkPolyDataAlgorithm.h>
 
class vtkTestFilterProgressFilter : public vtkPolyDataAlgorithm 
{
public:
  static vtkTestFilterProgressFilter *New();
  vtkTypeMacro(vtkTestFilterProgressFilter,vtkAlgorithm);

protected:
  vtkTestFilterProgressFilterr();
  ~vtkTestFilterProgressFilter() VTK_OVERRIDE {}
 
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *) VTK_OVERRIDE; 
 
  static void ProgressFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData);
  
private:
  vtkTestFilterProgressFilter(const vtkTestFilterProgressFilter&) VTK_DELETE_FUNCTION;
  void operator=(const vtkTestFilterProgressFilterr&) VTK_DELETE_FUNCTION;
 
};

#endif
</source>
