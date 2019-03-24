#ifndef __vtkTest1_h
#define __vtkTest1_h

#include <vtkDataObject.h>

class vtkTest1 : public vtkDataObject
{
public:
  static vtkTest1* New();
  vtkTypeMacro(vtkTest1,vtkDataObject);
  void PrintSelf( ostream& os, vtkIndent indent ) override;

  vtkGetMacro(Value, double);
  
protected:
  vtkTest1();
  ~vtkTest1();

private:
  vtkTest1( const vtkTest1& ); // Not implemented.
  void operator = ( const vtkTest1& ); // Not implemented.
    
  double Value;
};

#endif 
