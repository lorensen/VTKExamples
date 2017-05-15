#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPointSet.h>
#include <vtkPolyData.h>
#include <vtkLandmarkTransform.h>
#include <vtkCamera.h>
#include <vtkSphereSource.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkProcrustesAlignmentFilter.h>
#if VTK_MAJOR_VERSION > 5
#include <vtkMultiBlockDataSet.h>
#include <vtkMultiBlockDataGroupFilter.h>
#endif 
int main(int, char *[])
{
  //create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = 
      vtkSmartPointer<vtkSphereSource>::New();
 
  // make two copies of the shape and distort them a little
  vtkSmartPointer<vtkTransform> transform1 = 
    vtkSmartPointer<vtkTransform>::New();
  transform1->Translate(0.2, 0.1, 0.3);
  transform1->Scale(1.3, 1.1, 0.8);
 
  vtkSmartPointer<vtkTransform> transform2 = 
    vtkSmartPointer<vtkTransform> ::New();
  transform2->Translate(0.3, 0.7, 0.1);
  transform2->Scale(1.0, 0.1, 1.8);
 
  vtkSmartPointer<vtkTransformPolyDataFilter> transformer1 = 
          vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transformer1->SetInputConnection(sphereSource->GetOutputPort());
  transformer1->SetTransform(transform1);
 
  vtkSmartPointer<vtkTransformPolyDataFilter> transformer2 = 
          vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transformer2->SetInputConnection(sphereSource->GetOutputPort());
  transformer2->SetTransform(transform2);
 
  // map these three shapes into the first renderer
  vtkSmartPointer<vtkPolyDataMapper> map1a = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  map1a->SetInputConnection(sphereSource->GetOutputPort());
 
  vtkSmartPointer<vtkActor> Actor1a = 
    vtkSmartPointer<vtkActor> ::New();
  Actor1a->SetMapper(map1a);
  Actor1a->GetProperty()->SetDiffuseColor(1.0000, 0.3882, 0.2784);
 
  vtkSmartPointer<vtkPolyDataMapper> map1b = 
    vtkSmartPointer<vtkPolyDataMapper> ::New();
  map1b->SetInputConnection(transformer1->GetOutputPort());
 
  vtkSmartPointer<vtkActor> Actor1b = 
    vtkSmartPointer<vtkActor> ::New();
  Actor1b->SetMapper(map1b);
  Actor1b->GetProperty()->SetDiffuseColor(0.3882, 1.0000, 0.2784);
 
  vtkSmartPointer<vtkPolyDataMapper> map1c = 
      vtkSmartPointer<vtkPolyDataMapper>::New();
  map1c->SetInputConnection(transformer2->GetOutputPort());
  vtkSmartPointer<vtkActor> Actor1c = 
      vtkSmartPointer<vtkActor>::New();
  Actor1c->SetMapper(map1c);
  Actor1c->GetProperty()->SetDiffuseColor(0.3882, 0.2784, 1.0000);
 
  // align the shapes using Procrustes (using SetModeToRigidBody) 
  vtkSmartPointer<vtkProcrustesAlignmentFilter> procrustes1 = 
          vtkSmartPointer<vtkProcrustesAlignmentFilter>::New();
#if VTK_MAJOR_VERSION <=5 
  procrustes1->SetNumberOfInputs(3);
  procrustes1->SetInputConnection(sphereSource->GetOutputPort());
  procrustes1->AddInputConnection(transformer1->GetOutputPort());
  procrustes1->AddInputConnection(transformer2->GetOutputPort());
#else
  vtkSmartPointer<vtkMultiBlockDataGroupFilter> group =
    vtkSmartPointer<vtkMultiBlockDataGroupFilter>::New();
  group->AddInputConnection(sphereSource->GetOutputPort());
  group->AddInputConnection(transformer1->GetOutputPort());
  group->AddInputConnection(transformer2->GetOutputPort());
  procrustes1->SetInputConnection(group->GetOutputPort());
#endif
  procrustes1->GetLandmarkTransform()->SetModeToRigidBody();
 
  // map the aligned shapes into the second renderer
  vtkSmartPointer<vtkDataSetMapper> map2a = 
      vtkSmartPointer<vtkDataSetMapper>::New();
 
#if VTK_MAJOR_VERSION <= 5
  map2a->SetInputConnection(procrustes1->GetOutputPort(0));
#else
  procrustes1->Update();
  map2a->SetInputData(vtkDataSet::SafeDownCast(procrustes1->GetOutput()->GetBlock(0)));
#endif
  vtkSmartPointer<vtkActor> Actor2a = 
      vtkSmartPointer<vtkActor>::New();
  Actor2a->SetMapper(map2a);
  Actor2a->GetProperty()->SetDiffuseColor(1.0000, 0.3882, 0.2784);
 
  vtkSmartPointer<vtkDataSetMapper> map2b =
      vtkSmartPointer<vtkDataSetMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  map2b->SetInputConnection(procrustes1->GetOutputPort(1));
#else
  procrustes1->Update();
  map2b->SetInputData(vtkDataSet::SafeDownCast(procrustes1->GetOutput()->GetBlock(1)));
#endif
  vtkSmartPointer<vtkActor> Actor2b =
    vtkSmartPointer<vtkActor>::New();
  Actor2b->SetMapper(map2b);
  Actor2b->GetProperty()->SetDiffuseColor(0.3882, 1.0000, 0.2784);
 
  vtkSmartPointer<vtkDataSetMapper> map2c =
      vtkSmartPointer<vtkDataSetMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  map2c->SetInputConnection(procrustes1->GetOutputPort(2));
#else
  procrustes1->Update();
  map2c->SetInputData(vtkDataSet::SafeDownCast(procrustes1->GetOutput()->GetBlock(2)));
#endif
  vtkSmartPointer<vtkActor> Actor2c = 
      vtkSmartPointer<vtkActor>::New();
  Actor2c->SetMapper(map2c);
  Actor2c->GetProperty()->SetDiffuseColor(0.3882, 0.2784, 1.0000);
 
  //align the shapes using Procrustes (using SetModeToSimilarity (default))
  vtkSmartPointer<vtkProcrustesAlignmentFilter> procrustes2 =
      vtkSmartPointer<vtkProcrustesAlignmentFilter>::New();
#if VTK_MAJOR_VERSION <=5 
  procrustes2->SetNumberOfInputs(3);
  procrustes2->SetInputConnection(sphereSource->GetOutputPort());
  procrustes2->AddInputConnection(transformer1->GetOutputPort());
  procrustes2->AddInputConnection(transformer2->GetOutputPort());
#else
  procrustes2->SetInputConnection(group->GetOutputPort());
#endif
 
  // map the aligned shapes into the third renderer
  vtkSmartPointer<vtkDataSetMapper> map3a =
      vtkSmartPointer<vtkDataSetMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  map3a->SetInputConnection(procrustes2->GetOutputPort(0));
#else
  procrustes2->Update();
  map3a->SetInputData(vtkDataSet::SafeDownCast(procrustes2->GetOutput()->GetBlock(0)));
#endif
  vtkSmartPointer<vtkActor> Actor3a =
      vtkSmartPointer<vtkActor>::New();
  Actor3a->SetMapper(map3a);
  Actor3a->GetProperty()->SetDiffuseColor(1.0000, 0.3882, 0.2784);
 
  vtkSmartPointer<vtkDataSetMapper> map3b =
      vtkSmartPointer<vtkDataSetMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  map3b->SetInputConnection(procrustes2->GetOutputPort(1));
#else
  procrustes2->Update();
  map3b->SetInputData(vtkDataSet::SafeDownCast(procrustes2->GetOutput()->GetBlock(1)));
#endif
  vtkSmartPointer<vtkActor> Actor3b =
      vtkSmartPointer<vtkActor>::New();
  Actor3b->SetMapper(map3b);
  Actor3b->GetProperty()->SetDiffuseColor(0.3882, 1.0000, 0.2784);
 
  vtkSmartPointer<vtkDataSetMapper> map3c =
      vtkSmartPointer<vtkDataSetMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  map3c->SetInputConnection(procrustes2->GetOutputPort(2));
#else
  procrustes2->Update();
  map3c->SetInputData(vtkDataSet::SafeDownCast(procrustes2->GetOutput()->GetBlock(2)));
#endif
  vtkSmartPointer<vtkActor> Actor3c =
      vtkSmartPointer<vtkActor>::New();
  Actor3c->SetMapper(map3c);
  Actor3c->GetProperty()->SetDiffuseColor(0.3882, 0.2784, 1.0000);
 
  // Create the RenderWindow and its three Renderers
  vtkSmartPointer<vtkRenderer> ren1 =
      vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderer> ren2 =
      vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderer> ren3 =
      vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
      vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);
  renWin->AddRenderer(ren2);
  renWin->AddRenderer(ren3);
  renWin->SetSize(300, 100);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renWin);
 
  // Add the actors to the renderer
  ren1->AddActor(Actor1a);
  ren1->AddActor(Actor1b);
  ren1->AddActor(Actor1c);
 
  ren2->AddActor(Actor2a);
  ren2->AddActor(Actor2b);
  ren2->AddActor(Actor2c);
 
  ren3->AddActor(Actor3a);
  ren3->AddActor(Actor3b);
  ren3->AddActor(Actor3c);
 
  // set the properties of the renderers
 
  ren1->SetBackground(1, 1, 1);
  ren1->SetViewport(0.0, 0.0, 0.33, 1.0);
  ren1->ResetCamera();
  ren1->GetActiveCamera()->SetPosition(1, -1, 0);
  ren1->ResetCamera();
 
  ren2->SetBackground(1, 1, 1);
  ren2->SetViewport(0.33, 0.0, 0.66, 1.0);
  ren2->ResetCamera();
  ren2->GetActiveCamera()->SetPosition(1, -1, 0);
  ren2->ResetCamera();
 
  ren3->SetBackground(1, 1, 1);
  ren3->SetViewport(0.66, 0.0, 1.0, 1.0);
  ren3->ResetCamera();
  ren3->GetActiveCamera()->SetPosition(1, -1, 0);
  ren3->ResetCamera();
 
  renWin->Render();
  interactor->Start();
 
  return EXIT_SUCCESS;
}
