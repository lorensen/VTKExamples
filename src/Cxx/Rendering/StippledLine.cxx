#include <vtkDoubleArray.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkPolyData.h>
#include <vtkMapper.h>
#include <vtkPolyDataMapper.h>
#include <vtkPointData.h>
#include <vtkImageData.h>
#include <vtkLineSource.h>
#include <vtkTexture.h>

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkNamedColors.h>

namespace
{
void StippledLine(vtkSmartPointer<vtkActor> &actor,
                  int LineStipplePattern = 0xFFFF,
                  int LineStippleRepeat = 1);
}

int main (int, char *[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
    
  vtkSmartPointer<vtkLineSource> lines =
    vtkSmartPointer<vtkLineSource>::New();
  // Create two points, P0 and P1
  double p0[3] = {1.0, 0.0, 0.0};
  double p1[3] = {5.0, 0.0, 0.0};

  lines->SetResolution(11);
  lines->SetPoint1(p0);
  lines->SetPoint2(p1);
  lines->Update();
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(lines->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetLineWidth(5);
  actor->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());

  StippledLine(actor, 0xA1A1, 2);

  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  ren1->SetBackground(colors->GetColor3d("SlateGray").GetData());
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->SetSize(640, 480);

  renWin->AddRenderer(ren1);
  vtkSmartPointer<vtkRenderWindowInteractor>
    iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);
  ren1->AddActor(actor);

  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}

namespace
{
void StippledLine(vtkSmartPointer<vtkActor> &actor,
                  int lineStipplePattern,
                  int lineStippleRepeat)
{
  vtkSmartPointer<vtkDoubleArray> tcoords =
    vtkSmartPointer<vtkDoubleArray>::New();
  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  vtkSmartPointer<vtkTexture> texture =
    vtkSmartPointer<vtkTexture>::New();

  // Create texture
  int dimension = 16 * lineStippleRepeat;

  image->SetDimensions(dimension,1,1);
  image->AllocateScalars(VTK_UNSIGNED_CHAR, 4);
  image->SetExtent(0, dimension - 1, 0, 0, 0, 0);
  unsigned char  *pixel;
  pixel = static_cast<unsigned char *>(image->GetScalarPointer());
  unsigned char on = 255;
  unsigned char off = 0;
  for (int i = 0; i < 16; ++i)
  {
    unsigned int mask = (1 << i);
    unsigned int bit = (lineStipplePattern & mask) >> i;
    unsigned char value = static_cast<unsigned char>(bit);
    if (value == 0)
    {
      for (int j = 0; j < lineStippleRepeat; ++j)
      {
        *pixel       = on;
        *(pixel + 1) = on;
        *(pixel + 2 )= on;
        *(pixel + 3) = off;
        pixel += 4;
      }
    }
    else
    {
      for (int j = 0; j < lineStippleRepeat; ++j)
      {
        *pixel       = on;
        *(pixel + 1) = on;
        *(pixel + 2 )= on;
        *(pixel + 3) = on;
        pixel += 4;
      }
    }
  }
  vtkPolyData *polyData = dynamic_cast<vtkPolyData*>(actor->GetMapper()->GetInput());

  // Create texture coordnates
  tcoords->SetNumberOfComponents(1);
  tcoords->SetNumberOfTuples(polyData->GetNumberOfPoints());
  for (int i = 0; i < polyData->GetNumberOfPoints(); ++i)
  {
    double value = static_cast<double>(i) * .5;
    tcoords->SetTypedTuple(i, &value);
  }

  polyData->GetPointData()->SetTCoords(tcoords);
  texture->SetInputData(image);
  texture->InterpolateOff();
  texture->RepeatOn();

  actor->SetTexture(texture);
}
}
