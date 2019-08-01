//
/*
 * Create an iso-surface of the Lorenz attractor.
 *
 * Here we visualize a Lorenz strange attractor by integrating the Lorenz
 * equations in a volume. The number of visits in each voxel is recorded as a
 * scalar function. The surface is extracted via marching cubes using a visit
 * value of 50. The number of integration steps is 10 million, in a volume of
 * dimensions 200 x 200 * x 200. The surface roughness is caused by the discrete
 * nature of the evaluation function.
 */

#include <vtkActor.h>
#include <vtkContourFilter.h>
#include <vtkMath.h>
#include <vtkNamedColors.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkShortArray.h>
#include <vtkStructuredPoints.h>

int main(int, char*[])
{
  double Pr = 10.0; // The Lorenz parameters
  double b = 2.667;
  double r = 28.0;
  double x, y, z;       // starting (and current) x, y, z
  double h = 0.01;      // integration step size
  int resolution = 200; // slice resolution
  int iter = 10000000;  // number of iterations
  double xmin = -30.0;  // x, y, z range for voxels
  double xmax = 30.0;
  double ymin = -30.0;
  double ymax = 30.0;
  double zmin = -10.0;
  double zmax = 60.0;

  void options(int, char**);

  // take a stab at an integration step size
  auto xIncr = resolution / (xmax - xmin);
  auto yIncr = resolution / (ymax - ymin);
  auto zIncr = resolution / (zmax - zmin);

  printf("The Lorenz Attractor\n");
  printf("	Pr = %f\n", Pr);
  printf("	b = %f\n", b);
  printf("	r = %f\n", r);
  printf("	integration step size = %f\n", h);
  printf("	slice resolution = %d\n", resolution);
  printf("	# of iterations = %d\n", iter);
  printf("	specified range:\n");
  printf("		x: %f, %f\n", xmin, xmax);
  printf("		y: %f, %f\n", ymin, ymax);
  printf("		z: %f, %f\n", zmin, zmax);

  x = vtkMath::Random(xmin, xmax);
  y = vtkMath::Random(ymin, ymax);
  z = vtkMath::Random(zmin, zmax);
  printf("	starting at %f, %f, %f\n", x, y, z);

  // allocate memory for the slices
  auto sliceSize = resolution * resolution;
  auto numPts = sliceSize * resolution;
  auto scalars =
    vtkSmartPointer<vtkShortArray>::New();
  auto s = scalars->WritePointer(0, numPts);
  for (auto i = 0; i < numPts; i++)
  {
    s[i] = 0;
  }
  for (auto j = 0; j < iter; j++)
  {
    // integrate to next time step
    auto xx = x + h * Pr * (y - x);
    auto yy = y + h * (x * (r - z) - y);
    auto zz = z + h * (x * y - (b * z));

    x = xx;
    y = yy;
    z = zz;

    // calculate voxel index
    if (x < xmax && x > xmin && y < ymax && y > ymin && z < zmax && z > zmin)
    {
      auto xxx = static_cast<short>(static_cast<double>(xx - xmin) * xIncr);
      auto yyy = static_cast<short>(static_cast<double>(yy - ymin) * yIncr);
      auto zzz = static_cast<short>(static_cast<double>(zz - zmin) * zIncr);
      auto index = xxx + yyy * resolution + zzz * sliceSize;
      s[index] += 1;
    }
  }

  auto colors =
    vtkSmartPointer<vtkNamedColors>::New();

  auto volume =
    vtkSmartPointer<vtkStructuredPoints>::New();
  volume->GetPointData()->SetScalars(scalars);
  volume->SetDimensions(resolution, resolution, resolution);
  volume->SetOrigin(xmin, ymin, zmin);
  volume->SetSpacing((xmax - xmin) / resolution, (ymax - ymin) / resolution,
                     (zmax - zmin) / resolution);

  printf("	contouring...\n");
  // do the graphics dance
  auto renderer =
    vtkSmartPointer<vtkRenderer>::New();
  auto renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(renderer);

  auto iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // create iso-surface
  auto contour =
    vtkSmartPointer<vtkContourFilter>::New();
  contour->SetInputData(volume);
  contour->SetValue(0, 50);

  // create mapper
  auto mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(contour->GetOutputPort());
  mapper->ScalarVisibilityOff();

  // create actor
  auto actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(colors->GetColor3d("PaleTurquoise").GetData());

  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("PeachPuff").GetData());

  renWin->SetSize(640, 480);

  // interact with data
  renWin->Render();

  iren->Start();

  return EXIT_SUCCESS;
}
