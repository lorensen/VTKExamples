#ifndef __vtkTestA_h
#define __vtkTestA_h

#include "vtkDataObject.h"

class vtkTestA : public vtkDataObject
{
  public:
    static vtkTestA* New();
    vtkTypeRevisionMacro(vtkTestA,vtkDataObject);
    void PrintSelf( ostream& os, vtkIndent indent );

    vtkGetMacro(Value, double);
    vtkSetMacro(Value, double);
    
  protected:
    vtkTestA();
    ~vtkTestA();

  private:
    vtkTestA( const vtkTestA& ); // Not implemented.
    void operator = ( const vtkTestA& ); // Not implemented.
    
    double Value;
};

#endif 
