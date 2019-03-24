#ifndef __vtkTestGraphAlgorithmSource_h
#define __vtkTestGraphAlgorithmSource_h

#include <vtkGraphAlgorithm.h>

class vtkTestGraphAlgorithmSource : public vtkGraphAlgorithm 
{
public:
  static vtkTestGraphAlgorithmSource *New();
  vtkTypeMacro(vtkTestGraphAlgorithmSource,vtkGraphAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent) override;
	
protected:
  vtkTestGraphAlgorithmSource();
  ~vtkTestGraphAlgorithmSource();
  
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *) override;
  
  int RequestDataObject(vtkInformation *, vtkInformationVector **, vtkInformationVector *) override;

private:
  vtkTestGraphAlgorithmSource(const vtkTestGraphAlgorithmSource&);  // Not implemented.
  void operator=(const vtkTestGraphAlgorithmSource&);  // Not implemented.

};

#endif
