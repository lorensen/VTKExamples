#ifndef __vtkTestFilter_h
#define __vtkTestFilter_h

#include <vtkPolyDataAlgorithm.h>
#include <vtkSmartPointer.h>

class vtkTestFilter : public vtkPolyDataAlgorithm
{
public:
  vtkTypeMacro(vtkTestFilter,vtkPolyDataAlgorithm);
  static vtkTestFilter *New();

  vtkPolyData* GetIntermediateOutput() {return this->Output;}

  int RefreshEvent;
  
protected:
  vtkTestFilter();

  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

  void Iterate(unsigned int iteration);

  vtkSmartPointer<vtkPolyData> Output;
private:
  vtkTestFilter(const vtkTestFilter&);  // Not implemented.
  void operator=(const vtkTestFilter&);  // Not implemented.

};

#endif
