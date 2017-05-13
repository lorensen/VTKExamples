### Description
<source lang="cpp">
#ifndef __vtkTestMultipleOutputPortsSource_h
#define __vtkTestMultipleOutputPortsSource_h

#include "vtkAlgorithm.h"

class vtkDataSet;
class vtkTestA;
class vtkTestB;

class vtkTestMultipleOutputPortsSource : public vtkAlgorithm
{
  public:
    static vtkTestMultipleOutputPortsSource *New();
    vtkTypeRevisionMacro(vtkTestMultipleOutputPortsSource,vtkAlgorithm);
    void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Get the output data object for a port on this algorithm.
    vtkTestA* GetOutputA();
    vtkTestB* GetOutputB();
    
    virtual void SetOutput(vtkDataObject* d);

  // Description:
  // see vtkAlgorithm for details
    virtual int ProcessRequest(vtkInformation*,
                               vtkInformationVector**,
                               vtkInformationVector*);

  protected:
    vtkTestMultipleOutputPortsSource();
    ~vtkTestMultipleOutputPortsSource();

  // Description:
  // This is called by the superclass.
  // This is the method you should override.
    virtual int RequestDataObject(
                                  vtkInformation* request,
                                  vtkInformationVector** inputVector,
                                  vtkInformationVector* outputVector );

  // convenience method
    virtual int RequestInformation(
                                   vtkInformation* request,
                                   vtkInformationVector** inputVector,
                                   vtkInformationVector* outputVector );

  // Description:
  // This is called by the superclass.
  // This is the method you should override.
    virtual int RequestData(
                            vtkInformation* request,
                            vtkInformationVector** inputVector,
                            vtkInformationVector* outputVector );

  // Description:
  // This is called by the superclass.
  // This is the method you should override.
    virtual int RequestUpdateExtent(
                                    vtkInformation*,
                                    vtkInformationVector**,
                                    vtkInformationVector* );

    virtual int FillOutputPortInformation( int port, vtkInformation* info );

  private:
    vtkTestMultipleOutputPortsSource( const vtkTestMultipleOutputPortsSource& ); // Not implemented.
    void operator = ( const vtkTestMultipleOutputPortsSource& );  // Not implemented.
    
};

#endif
</source>
