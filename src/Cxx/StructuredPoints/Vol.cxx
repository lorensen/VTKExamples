#include <vtkActor.h>
#include <vtkContourFilter.h>
#include <vtkDoubleArray.h>
#include <vtkNamedColors.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkStructuredPoints.h>

int main( int, char *[] )
{
  int i, j, k, kOffset, jOffset, offset;
  double x, y, z, s, sp;
  
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  vtkSmartPointer<vtkStructuredPoints> vol =
    vtkSmartPointer<vtkStructuredPoints>::New();
  vol->SetDimensions(26,26,26);
  vol->SetOrigin(-0.5,-0.5,-0.5);
  sp = 1.0/25.0;
  vol->SetSpacing(sp, sp, sp);

  vtkSmartPointer<vtkDoubleArray> scalars =
    vtkSmartPointer<vtkDoubleArray>::New();
  scalars->SetNumberOfComponents(1);
  scalars->SetNumberOfTuples(26*26*26);
  for (k=0; k<26; k++)
  {
    z = -0.5 + k*sp;
    kOffset = k * 26 * 26;
    for (j=0; j<26; j++) 
    {
      y = -0.5 + j*sp;
      jOffset = j * 26;
      for (i=0; i<26; i++) 
      {
        x = -0.5 + i*sp;
        s = x*x + y*y + z*z - (0.4*0.4);
        offset = i + jOffset + kOffset;
        scalars->InsertTuple(offset,&s);
      }
    }
  }
  vol->GetPointData()->SetScalars(scalars);

  vtkSmartPointer<vtkContourFilter> contour =
    vtkSmartPointer<vtkContourFilter>::New();
  contour->SetInputData(vol);
  contour->SetValue(0,0.0);

  vtkSmartPointer<vtkPolyDataMapper> volMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  volMapper->SetInputConnection(contour->GetOutputPort());
  volMapper->ScalarVisibilityOff();
  vtkSmartPointer<vtkActor> volActor =
    vtkSmartPointer<vtkActor>::New();
  volActor->SetMapper(volMapper);
  volActor->GetProperty()->EdgeVisibilityOn();
  volActor->GetProperty()->SetColor(colors->GetColor3d("Salmon").GetData());
  renderer->AddActor(volActor);
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
  renWin->SetSize(512,512);

  // interact with data
  renWin->Render();

  iren->Start();

  return EXIT_SUCCESS;
}
