#include <vtkSmartPointer.h>
#include <vtkProcrustesAlignmentFilter.h>

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

#include <vtkMultiBlockDataSet.h>
#include <vtkMultiBlockDataGroupFilter.h>
#include <vtkNamedColors.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  //create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = 
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetPhiResolution(31);
  sphereSource->SetThetaResolution(31);

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
  Actor1a->GetProperty()->SetDiffuseColor(colors->GetColor3d("Tomato").GetData());
 
  vtkSmartPointer<vtkPolyDataMapper> map1b = 
    vtkSmartPointer<vtkPolyDataMapper> ::New();
  map1b->SetInputConnection(transformer1->GetOutputPort());
 
  vtkSmartPointer<vtkActor> Actor1b = 
    vtkSmartPointer<vtkActor> ::New();
  Actor1b->SetMapper(map1b);
  Actor1b->GetProperty()->SetDiffuseColor(colors->GetColor3d("Banana").GetData());
 
  vtkSmartPointer<vtkPolyDataMapper> map1c = 
      vtkSmartPointer<vtkPolyDataMapper>::New();
  map1c->SetInputConnection(transformer2->GetOutputPort());
  vtkSmartPointer<vtkActor> Actor1c = 
      vtkSmartPointer<vtkActor>::New();
  Actor1c->SetMapper(map1c);
  Actor1c->GetProperty()->SetDiffuseColor(colors->GetColor3d("Peacock").GetData());
 
  // align the shapes using Procrustes (using SetModeToRigidBody) 
  vtkSmartPointer<vtkProcrustesAlignmentFilter> procrustes1 = 
          vtkSmartPointer<vtkProcrustesAlignmentFilter>::New();
  vtkSmartPointer<vtkMultiBlockDataGroupFilter> group =
    vtkSmartPointer<vtkMultiBlockDataGroupFilter>::New();
  group->AddInputConnection(sphereSource->GetOutputPort());
  group->AddInputConnection(transformer1->GetOutputPort());
  group->AddInputConnection(transformer2->GetOutputPort());
  procrustes1->SetInputConnection(group->GetOutputPort());
  procrustes1->GetLandmarkTransform()->SetModeToRigidBody();
 
  // map the aligned shapes into the second renderer
  vtkSmartPointer<vtkDataSetMapper> map2a = 
      vtkSmartPointer<vtkDataSetMapper>::New();
 
  procrustes1->Update();
  map2a->SetInputData(dynamic_cast<vtkDataSet*>(procrustes1->GetOutput()->GetBlock(0)));

  vtkSmartPointer<vtkActor> Actor2a = 
      vtkSmartPointer<vtkActor>::New();
  Actor2a->SetMapper(map2a);
  Actor2a->GetProperty()->SetDiffuseColor(colors->GetColor3d("Tomato").GetData());
 
  vtkSmartPointer<vtkDataSetMapper> map2b =
      vtkSmartPointer<vtkDataSetMapper>::New();
  procrustes1->Update();
  map2b->SetInputData(dynamic_cast<vtkDataSet*>(procrustes1->GetOutput()->GetBlock(1)));

  vtkSmartPointer<vtkActor> Actor2b =
    vtkSmartPointer<vtkActor>::New();
  Actor2b->SetMapper(map2b);
  Actor2b->GetProperty()->SetDiffuseColor(colors->GetColor3d("Banana").GetData());
 
  vtkSmartPointer<vtkDataSetMapper> map2c =
      vtkSmartPointer<vtkDataSetMapper>::New();
  procrustes1->Update();
  map2c->SetInputData(dynamic_cast<vtkDataSet*>(procrustes1->GetOutput()->GetBlock(2)));

  vtkSmartPointer<vtkActor> Actor2c = 
      vtkSmartPointer<vtkActor>::New();
  Actor2c->SetMapper(map2c);
  Actor2c->GetProperty()->SetDiffuseColor(colors->GetColor3d("Peacock").GetData());
 
  //align the shapes using Procrustes (using SetModeToSimilarity (default))
  vtkSmartPointer<vtkProcrustesAlignmentFilter> procrustes2 =
      vtkSmartPointer<vtkProcrustesAlignmentFilter>::New();
  procrustes2->SetInputConnection(group->GetOutputPort());
 
  // map the aligned shapes into the third renderer
  vtkSmartPointer<vtkDataSetMapper> map3a =
      vtkSmartPointer<vtkDataSetMapper>::New();
  procrustes2->Update();
  map3a->SetInputData(dynamic_cast<vtkDataSet*>(procrustes2->GetOutput()->GetBlock(0)));

  vtkSmartPointer<vtkActor> Actor3a =
      vtkSmartPointer<vtkActor>::New();
  Actor3a->SetMapper(map3a);
  Actor3a->GetProperty()->SetDiffuseColor(colors->GetColor3d("Tomato").GetData());
 
  vtkSmartPointer<vtkDataSetMapper> map3b =
      vtkSmartPointer<vtkDataSetMapper>::New();
  procrustes2->Update();
  map3b->SetInputData(dynamic_cast<vtkDataSet*>(procrustes2->GetOutput()->GetBlock(1)));

  vtkSmartPointer<vtkActor> Actor3b =
      vtkSmartPointer<vtkActor>::New();
  Actor3b->SetMapper(map3b);
  Actor3b->GetProperty()->SetDiffuseColor(colors->GetColor3d("Banana").GetData());
 
  vtkSmartPointer<vtkDataSetMapper> map3c =
      vtkSmartPointer<vtkDataSetMapper>::New();
  procrustes2->Update();
  map3c->SetInputData(dynamic_cast<vtkDataSet*>(procrustes2->GetOutput()->GetBlock(2)));

  vtkSmartPointer<vtkActor> Actor3c =
      vtkSmartPointer<vtkActor>::New();
  Actor3c->SetMapper(map3c);
  Actor3c->GetProperty()->SetDiffuseColor(colors->GetColor3d("Peacock").GetData());
 
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
  renWin->SetSize(600, 300);
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
 
  ren1->SetBackground(colors->GetColor3d("Bisque").GetData());
  ren1->SetViewport(0.0, 0.0, 0.33, 1.0);
  ren1->GetActiveCamera()->SetPosition(1, -1, 0);
  ren1->ResetCamera();
 
  ren2->SetBackground(colors->GetColor3d("Cornsilk").GetData());
  ren2->SetViewport(0.33, 0.0, 0.66, 1.0);
  ren2->ResetCamera();
  ren2->GetActiveCamera()->SetPosition(1, -1, 0);
  ren2->ResetCamera();

  ren3->SetBackground(colors->GetColor3d("Eggshell").GetData());
  ren3->SetViewport(0.66, 0.0, 1.0, 1.0);
  ren3->ResetCamera();
  ren3->GetActiveCamera()->SetPosition(1, -1, 0);
  ren3->ResetCamera();
 
  renWin->Render();
  interactor->Start();
 
  return EXIT_SUCCESS;
}
