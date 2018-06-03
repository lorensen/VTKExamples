#include <vtkSmartPointer.h>
#include <vtkDiscretizableColorTransferFunction.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkDiscretizableColorTransferFunction> discretizableColorTransferFunction = 
    vtkSmartPointer<vtkDiscretizableColorTransferFunction>::New();
  
  discretizableColorTransferFunction->DiscretizeOn();
  discretizableColorTransferFunction->SetNumberOfValues(2);
  
  discretizableColorTransferFunction->AddRGBPoint(0.0, 1, 0, 0);
  discretizableColorTransferFunction->AddRGBPoint(10.0, 0, 1, 0);
  discretizableColorTransferFunction->Build();
  
  double color[3];
  discretizableColorTransferFunction->GetColor(1.0, color);
  std::cout << color[0] << " " << color[1] << " " << color[2] << std::endl;
  
  discretizableColorTransferFunction->GetColor(5.0, color);
  std::cout << color[0] << " " << color[1] << " " << color[2] << std::endl;
  
  return EXIT_SUCCESS;
}
