// This program draws a checkerboard and clips it with two planes.

#include <vtkSmartPointer.h>

#include <vtkClipVolume.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCellData.h>
#include <vtkDataSetMapper.h>
#include <vtkDoubleArray.h>
#include <vtkExecutive.h>
#include <vtkImageData.h>
#include <vtkImageMapToColors.h>
#include <vtkInteractorStyleSwitch.h>
#include <vtkLookupTable.h>
#include <vtkMapper.h>
#include <vtkPlanes.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkProperty.h>
#include <vtkImageData.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRenderStepsPass.h>

#include <vtkNamedColors.h>
#include <vtkColor.h>

#define IMAGESIZE 64		// number of checkerboard squares on a side
#define CUBESIZE 20.0		// physical linear dimension of entire system

// Color for the checkerboard image
#define IMAGE_R 0.7
#define IMAGE_G 0.7
#define IMAGE_B 0.7
#define IMAGE_A 1.0
#define DIM 0.5			// amount to dim the dark squares by

// Offsets for clipping planes with normals in the X and Y directions
#define XOFFSET 8
#define YOFFSET 8

///////////////////

// Make a image data.A checkerboard pattern is used for
// simplicity.

vtkSmartPointer<vtkImageData> makeImage(int n, vtkColor3d fillColor, vtkColor3d checkerColor) {
  vtkSmartPointer<vtkImageData> image0 = vtkSmartPointer<vtkImageData>::New();
  image0->SetDimensions(n, n, n);
  image0->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
  image0->SetSpacing(CUBESIZE/n, CUBESIZE/n, CUBESIZE/n);
  int checkerSize = n / 8;
  for(int z=0; z<n; z++) {
    for(int y=0; y<n; y++) {
      for(int x=0; x<n; x++) {
	unsigned char *ptr = (unsigned char*) image0->GetScalarPointer(x, y, z);
	*ptr = (x/checkerSize+y/checkerSize+z/checkerSize)%2; // checkerboard
      }
    }
  }
  
  vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();
  lut->SetNumberOfTableValues(2);
  lut->SetTableRange(0, 1);
  lut->SetTableValue(0, fillColor.GetRed(), fillColor.GetGreen(), fillColor.GetBlue(), 1.0);
  lut->SetTableValue(1, checkerColor.GetRed(), checkerColor.GetGreen(), checkerColor.GetBlue(), 1.0);

  vtkSmartPointer<vtkImageMapToColors> map =
    vtkSmartPointer<vtkImageMapToColors>::New();
  map->SetLookupTable(lut);
  map->SetOutputFormatToRGBA();
  map->SetInputData(image0);
  map->GetExecutive()->Update();
  vtkImageData *image = map->GetOutput();

  vtkPointData *pointData = image->GetPointData();
  return image;
}

/////////////////////
////////////////////

int main(int, char *[]) {

  vtkMapper::SetResolveCoincidentTopologyToPolygonOffset();
  
  // Define colors
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
  vtkColor3d backgroundColor = colors->GetColor3d("Wheat");
  vtkColor3d checkerColor = colors->GetColor3d("Tomato");
  vtkColor3d fillColor = colors->GetColor3d("Banana");

  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(backgroundColor.GetData());

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleSwitch> style =
    vtkSmartPointer<vtkInteractorStyleSwitch>::New();
  interactor->SetInteractorStyle(style);
  interactor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkImageData> image = makeImage(IMAGESIZE, fillColor, checkerColor);

  // Clipping planes in the X and Y direction.
  vtkSmartPointer<vtkDoubleArray> normals
    = vtkSmartPointer<vtkDoubleArray>::New();
  vtkSmartPointer<vtkPoints> clipPts = vtkSmartPointer<vtkPoints>::New();
  normals->SetNumberOfComponents(3);
  double xnorm[3] = {-1., 0., 0.};
  double ynorm[3] = {0., -1., 0.};
  double xpt[3] = {XOFFSET, 0., 0.};
  double ypt[3] = {0., YOFFSET, 0.};
  normals->InsertNextTuple(xnorm);
  normals->InsertNextTuple(ynorm);
  clipPts->InsertNextPoint(xpt);
  clipPts->InsertNextPoint(ypt);
  vtkSmartPointer<vtkPlanes> clipPlanes = vtkSmartPointer<vtkPlanes>::New();
  clipPlanes->SetNormals(normals);
  clipPlanes->SetPoints(clipPts);

  vtkSmartPointer<vtkClipVolume> clipper =
    vtkSmartPointer<vtkClipVolume>::New();
  clipper->SetClipFunction(clipPlanes);
  clipper->SetInputData(image);

  vtkSmartPointer<vtkDataSetMapper> imageMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  vtkSmartPointer<vtkActor> imageActor = vtkSmartPointer<vtkActor>::New();
  imageActor->SetMapper(imageMapper);
  renderer->AddViewProp(imageActor);
  imageMapper->SetInputConnection(clipper->GetOutputPort());

  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(120);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->ResetCameraClippingRange();
  renderWindow->Render();
  
  interactor->Start();
  return 0;
}
