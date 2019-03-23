#ifndef __vtkTestAlgorithmSource_h
#define __vtkTestAlgorithmSource_h

#include <vtkAlgorithm.h>

class vtkDataSet;
class vtkTest1;

class vtkTestAlgorithmSource : public vtkAlgorithm
{
public:
  static vtkTestAlgorithmSource *New();
  vtkTypeMacro(vtkTestAlgorithmSource,vtkAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  // Description:
  // Get the output data object for a port on this algorithm.
  vtkTest1* GetOutput();
  vtkTest1* GetOutput(int);
  virtual void SetOutput(vtkDataObject* d);

  // Description:
  // see vtkAlgorithm for details
  virtual int ProcessRequest(vtkInformation*,
                             vtkInformationVector**,
                             vtkInformationVector*) override;

protected:
  vtkTestAlgorithmSource();
  ~vtkTestAlgorithmSource();

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

  virtual int FillOutputPortInformation( int port, vtkInformation* info ) override;

private:
  vtkTestAlgorithmSource( const vtkTestAlgorithmSource& ); // Not implemented.
  void operator = ( const vtkTestAlgorithmSource& );  // Not implemented.
};

#endif
