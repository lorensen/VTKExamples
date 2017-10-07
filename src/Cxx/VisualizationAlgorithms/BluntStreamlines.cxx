#include <vtkSmartPointer.h>
#include <vtkStreamTracer.h>

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMultiBlockPLOT3DReader.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkStructuredGridOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkStructuredGridGeometryFilter.h>
#include <vtkStructuredGrid.h>
#include <vtkPointData.h>
#include <vtkLineSource.h>
#include <vtkNamedColors.h>

int main(int argc, char *argv[] )
{
  if (argc != 3)
  {
    std::cout << "Usage: " << argv[0] << " bluntfinxyz.bin bluntfinq.bin" << std::endl;
    return EXIT_FAILURE;
  }

  double range[2], c[3];
  double maxVelocity = 0.0, maxTime = 0.0;
  
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderer> aren =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(aren);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  std::string xyzFilename = argv[1];
  std::string qFilename = argv[2];

  vtkSmartPointer<vtkMultiBlockPLOT3DReader> reader =
    vtkSmartPointer<vtkMultiBlockPLOT3DReader>::New();
  reader->SetXYZFileName(xyzFilename.c_str());
  reader->SetQFileName(qFilename.c_str());
  reader->Update(); //force a read to occur

  vtkStructuredGrid *pd =
    vtkStructuredGrid::SafeDownCast(reader->GetOutput()->GetBlock(0));
  pd->GetCenter(c);
  if ( pd->GetPointData()->GetScalars() )
  {
    pd->GetPointData()->GetScalars()->GetRange(range);
  }
  if ( pd->GetPointData()->GetVectors() )
  {
    maxVelocity = pd->GetPointData()->GetVectors()->GetMaxNorm();
    maxTime = 20.0*pd->GetLength()/maxVelocity ;
  }

  vtkSmartPointer<vtkStructuredGridOutlineFilter> outlineF =
    vtkSmartPointer<vtkStructuredGridOutlineFilter>::New();
  outlineF->SetInputData(pd);

  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outlineF->GetOutputPort());

  vtkSmartPointer<vtkActor> outline =
    vtkSmartPointer<vtkActor>::New();
  outline->SetMapper(outlineMapper);
  outline->GetProperty()->SetColor(colors->GetColor3d("Moccasin").GetData());
  outline->GetProperty()->SetLineWidth(2.0);

//
// Some geometry for context
//
  vtkSmartPointer<vtkStructuredGridGeometryFilter> wall =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  wall->SetInputData(pd);
  wall->SetExtent(0, 100, 0, 100, 0, 0);

  vtkSmartPointer<vtkPolyDataMapper> wallMap =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  wallMap->SetInputConnection(wall->GetOutputPort());
  wallMap->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> wallActor =
    vtkSmartPointer<vtkActor>::New();
  wallActor->SetMapper(wallMap);
  wallActor->GetProperty()->SetColor(colors->GetColor3d("Silver").GetData());

  vtkSmartPointer<vtkStructuredGridGeometryFilter> fin =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  fin->SetInputData(pd);
  fin->SetExtent(0,100,0,0,0,100);

  vtkSmartPointer<vtkPolyDataMapper> finMap =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  finMap->SetInputConnection(fin->GetOutputPort());
  finMap->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> finActor =
    vtkSmartPointer<vtkActor>::New();
  finActor->SetMapper(finMap);
  finActor->GetProperty()->SetColor(colors->GetColor3d("Silver").GetData());
//
// regular streamlines
//
  vtkSmartPointer<vtkLineSource> line1 =
    vtkSmartPointer<vtkLineSource>::New();
  line1->SetResolution(25);
  line1->SetPoint1(-6.36, 0.25, 0.06);
  line1->SetPoint2(-6.36, 0.25, 5.37);

  vtkSmartPointer<vtkPolyDataMapper> rakeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  rakeMapper->SetInputConnection(line1->GetOutputPort());

  vtkSmartPointer<vtkActor> rake1 =
    vtkSmartPointer<vtkActor>::New();
  rake1->SetMapper(rakeMapper);
  rake1->GetProperty()->SetColor(0.0,0.0,0.0);
  rake1->GetProperty()->SetLineWidth(5);

  vtkSmartPointer<vtkStreamTracer> streamers =
    vtkSmartPointer<vtkStreamTracer>::New();
  //  streamers->DebugOn();
  streamers->SetInputConnection(reader->GetOutputPort());
  streamers->SetSourceConnection(line1->GetOutputPort());
  streamers->SetMaximumPropagation(maxTime);
  streamers->SetInitialIntegrationStep(.2);
  streamers->SetMinimumIntegrationStep(.01);
  streamers->SetIntegratorType(2);
  streamers->Update();

  vtkSmartPointer<vtkPolyDataMapper> streamersMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  streamersMapper->SetInputConnection(streamers->GetOutputPort());
  streamersMapper->SetScalarRange(range);

  vtkSmartPointer<vtkActor> lines =
    vtkSmartPointer<vtkActor>::New();
  lines->SetMapper(streamersMapper);

  aren->AddActor(outline);
  aren->AddActor(wallActor);
  aren->AddActor(finActor);
  aren->AddActor(rake1);
  aren->AddActor(lines);
  aren->SetBackground(0.5,0.5,0.5);

  aren->ResetCamera();
  aren->GetActiveCamera()->Elevation(30.0);
  aren->GetActiveCamera()->Azimuth(30.0);
  aren->GetActiveCamera()->Dolly(1.2);
  aren->ResetCameraClippingRange();

  renWin->SetSize(640, 480);
  renWin->Render();

  // interact with data
  iren->Start();

  // Clean up

  return EXIT_SUCCESS;
}
