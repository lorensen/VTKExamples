#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkConeSource.h>
#include <vtkGlyph3D.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

#include <array>

int main(int, char* [])
{

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  // 8.1.0+
  vtkNew<vtkNamedColors> colors;
#else
  vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
#endif
  // Set the background color.
  std::array<unsigned char , 4> bkg{{26, 51, 102, 255}};
    colors->SetColor("Bkg", bkg.data());

  // Create the rendering objects.
#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkRenderer> ren1;
  vtkNew<vtkRenderWindow> renWin;
  vtkNew<vtkRenderWindowInteractor> iren;
#else
  vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
  vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
#endif
  renWin->AddRenderer(ren1);
  iren->SetRenderWindow(renWin);

  // Create the pipeline, ball and spikes.
#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkSphereSource> sphere;
#else
  vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
#endif
  sphere->SetPhiResolution(7);
  sphere->SetThetaResolution(7);

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkPolyDataMapper> sphereMapper;
#else
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
#endif
  sphereMapper->SetInputConnection(sphere->GetOutputPort());

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkActor> sphereActor;
#else
  vtkSmartPointer<vtkActor> sphereActor = vtkSmartPointer<vtkActor>::New();
#endif
  sphereActor->SetMapper(sphereMapper);

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkActor> sphereActor2;
#else
  vtkSmartPointer<vtkActor> sphereActor2 = vtkSmartPointer<vtkActor>::New();
#endif
  sphereActor2->SetMapper(sphereMapper);

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkConeSource> cone;
#else
  vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();
#endif
  cone->SetResolution(5);

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkGlyph3D> glyph;
#else
  vtkSmartPointer<vtkGlyph3D> glyph = vtkSmartPointer<vtkGlyph3D>::New();
#endif
  glyph->SetInputConnection(sphere->GetOutputPort());
  glyph->SetSourceConnection(cone->GetOutputPort());
  glyph->SetVectorModeToUseNormal();
  glyph->SetScaleModeToScaleByVector();
  glyph->SetScaleFactor(0.25);

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkPolyDataMapper> spikeMapper;
#else
  vtkSmartPointer<vtkPolyDataMapper> spikeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
#endif
  spikeMapper->SetInputConnection(glyph->GetOutputPort());

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkActor> spikeActor;
#else
  vtkSmartPointer<vtkActor> spikeActor = vtkSmartPointer<vtkActor>::New();
#endif
  spikeActor->SetMapper(spikeMapper);

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkActor> spikeActor2;
#else
  vtkSmartPointer<vtkActor> spikeActor2 = vtkSmartPointer<vtkActor>::New();
#endif
  spikeActor2->SetMapper(spikeMapper);
  spikeActor->SetPosition(0, 0.7, 0);
  sphereActor->SetPosition(0, 0.7, 0);
  spikeActor2->SetPosition(0, -1.0, -10);
  sphereActor2->SetPosition(0, -1.0, -10);
  spikeActor2->SetScale(1.5, 1.5, 1.5);
  sphereActor2->SetScale(1.5, 1.5, 1.5);

  ren1->AddActor(sphereActor);
  ren1->AddActor(spikeActor);
  ren1->AddActor(sphereActor2);
  ren1->AddActor(spikeActor2);
  ren1->SetBackground(colors->GetColor3d("Bkg").GetData());
  renWin->SetSize(300, 300);
  //   renWin->DoubleBufferOff();

  // Do the first render and then zoom in a little.
  renWin->Render();
  ren1->GetActiveCamera()->SetFocalPoint(0, 0, 0.0);
  ren1->GetActiveCamera()->Zoom(1.8);
  ren1->GetActiveCamera()->SetFocalDisk(0.05);

  renWin->Render();

  iren->Start();

  return EXIT_SUCCESS;
}
