#include <vtkSmartPointer.h>
#include <vtkFunctionParser.h>


int main(int, char *[])
{
  vtkSmartPointer<vtkFunctionParser> functionParser = 
      vtkSmartPointer<vtkFunctionParser>::New();
  functionParser->SetFunction("a+b");
  
  functionParser->SetScalarVariableValue( "a", 2);
  functionParser->SetScalarVariableValue( "b", 3);
    
  double result = functionParser->GetScalarResult();
  
  std::cout << "result: " << result << std::endl;
  
  return EXIT_SUCCESS;
}
