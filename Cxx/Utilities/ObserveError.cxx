#include <string>

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkCommand.h>

class ErrorObserver : public vtkCommand
{
public:
  ErrorObserver():
    Error(false),
    Warning(false),
    ErrorMessage(""),
    WarningMessage("") {}
  static ErrorObserver *New()
  {
  return new ErrorObserver;
  }
  bool GetError() const
  {
  return this->Error;
  }
  bool GetWarning() const
  {
  return this->Warning;
  }
  void Clear()
  {
  this->Error = false;
  this->Warning = false;
  this->ErrorMessage = "";
  this->WarningMessage = "";
  }
  virtual void Execute(vtkObject *vtkNotUsed(caller),
                       unsigned long event,
                       void *calldata)
  {
  switch(event)
  {
    case vtkCommand::ErrorEvent:
      ErrorMessage = static_cast<char *>(calldata);
      this->Error = true;
      break;
    case vtkCommand::WarningEvent:
      WarningMessage = static_cast<char *>(calldata);
      this->Warning = true;
      break;
  }
  }
  std::string GetErrorMessage()
  {
  return ErrorMessage;
  }
std::string GetWarningMessage()
{
  return WarningMessage;
}
private:
  bool        Error;
  bool        Warning;
  std::string ErrorMessage;
  std::string WarningMessage;
};

int main (int, char *[])
{
  vtkSmartPointer<ErrorObserver>  errorObserver =
    vtkSmartPointer<ErrorObserver>::New();

  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  image->AddObserver(vtkCommand::ErrorEvent,errorObserver);
  image->AddObserver(vtkCommand::WarningEvent,errorObserver);
  image->GetCell(1);
  if (errorObserver->GetError())
  {
    std::cout << "Caught error! " << errorObserver->GetErrorMessage();
  }

  image->ShallowCopy(NULL);
  if (errorObserver->GetWarning())
  {
    std::cout << "Caught warning! " << errorObserver->GetWarningMessage();
  }

  return EXIT_SUCCESS;
}
