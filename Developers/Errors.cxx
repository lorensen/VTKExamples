#include <vtkSmartPointer.h>
#include <vtkDataObject.h>
#include <vtkObjectFactory.h>

class TestClass : public vtkDataObject
{
  public:
  static TestClass *New();
  vtkTypeMacro(TestClass,vtkDataObject);
  TestClass()
  {
    vtkErrorMacro(<< "Test error.");
  }
};

vtkStandardNewMacro(TestClass);

int main(int argc, char *argv[])
{
  vtkSmartPointer<TestClass> test =
      vtkSmartPointer<TestClass>::New();

  return EXIT_SUCCESS;
}
