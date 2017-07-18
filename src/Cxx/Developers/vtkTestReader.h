#ifndef __vtkTestReader_h
#define __vtkTestReader_h

#include <vtkPolyDataAlgorithm.h>

class vtkTestReader : public vtkPolyDataAlgorithm 
{
public:
  vtkTypeMacro(vtkTestReader,vtkPolyDataAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  static vtkTestReader *New();
	
protected:
  vtkTestReader();
  ~vtkTestReader();
  
  int FillOutputPortInformation( int port, vtkInformation* info );
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
  vtkTestReader(const vtkTestReader&);  // Not implemented.
  void operator=(const vtkTestReader&);  // Not implemented.

  char* FileName;
};

#endif
