#include <vtkSmartPointer.h>
#include <vtkCoordinate.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkRenderWindow> rendererWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  rendererWindow->AddRenderer(renderer);
  rendererWindow->Render();
  
  vtkSmartPointer<vtkCoordinate> coordinate = 
    vtkSmartPointer<vtkCoordinate>::New();
  coordinate->SetCoordinateSystemToNormalizedDisplay();
  coordinate->SetValue(.5,.5,0);
  std::cout << *coordinate << std::endl;
  std::cout << coordinate->GetCoordinateSystemAsString() << std::endl;
  
  int* val;
  val = coordinate->GetComputedDisplayValue(renderer);
  std::cout << "Val: " << val[0] << " " << val[1] << std::endl;
  
  return EXIT_SUCCESS;
}
