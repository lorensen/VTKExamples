#ifndef __vtkTestB_h
#define __vtkTestB_h

#include "vtkDataObject.h"

class vtkTestB : public vtkDataObject
{
  public:
    static vtkTestB* New();
    vtkTypeRevisionMacro(vtkTestB,vtkDataObject);
    void PrintSelf( ostream& os, vtkIndent indent );

    vtkGetMacro(Value, double);
    vtkSetMacro(Value, double);
    
  protected:
    vtkTestB();
    ~vtkTestB();

  private:
    vtkTestB( const vtkTestB& ); // Not implemented.
    void operator = ( const vtkTestB& ); // Not implemented.
    
    double Value;
};

#endif 
