// Demonstrates how to make and use VTK's MultiBlock type data

#include <vtkActor.h>
#include <vtkCompositeDataGeometryFilter.h>
#include <vtkExtractEdges.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

int main (int, char *[])
{
  // PART 1 Make some Data
  // make a tree
  vtkSmartPointer<vtkMultiBlockDataSet> root =
    vtkSmartPointer<vtkMultiBlockDataSet>::New();

  vtkSmartPointer<vtkMultiBlockDataSet> branch =
    vtkSmartPointer<vtkMultiBlockDataSet>::New();
  root->SetBlock(0, branch);

  // make some leaves
  vtkSmartPointer<vtkSphereSource> leaf1 =
    vtkSmartPointer<vtkSphereSource>::New();
  leaf1->SetCenter(0,0,0);
  leaf1->Update();
  branch->SetBlock(0, leaf1->GetOutput());

  vtkSmartPointer<vtkSphereSource> leaf2 =
    vtkSmartPointer<vtkSphereSource>::New();
  leaf2->SetCenter(1.75,2.5,0);
  leaf2->SetRadius(1.5);
  leaf2->Update();
  branch->SetBlock(1, leaf2->GetOutput());

  vtkSmartPointer<vtkSphereSource> leaf3 =
    vtkSmartPointer<vtkSphereSource>::New();
  leaf3->SetCenter(4,0,0);
  leaf3->SetRadius(2);
  leaf3->Update();
  root->SetBlock(1, leaf3->GetOutput());

  // uncomment to inspect
  //std::cerr << root->GetClassName() << std::endl;
  //root->PrintSelf(std::cerr, vtkIndent(0));

  // PART 2 Do something with the data
  // a non composite aware filter, the pipeline will iterate
  vtkSmartPointer<vtkExtractEdges> edges =
    vtkSmartPointer<vtkExtractEdges>::New();
  edges->SetInputData(root);

  // uncomment to inspect
  //edges->Update();
  //cerr << edges->GetOutputDataObject(0)->GetClassName() << endl;
  //edges->GetOutputDataObject(0)->PrintSelf(std::cerr, vtkIndent(0));

  // PART 3 Show the data
  // also demonstrate a composite aware filter
  // this filter aggregates all blocks into one polydata
  // this is handy for display, although fairly limited
  // see vtkCompositePolyDataMapper2 for something better
  vtkSmartPointer<vtkCompositeDataGeometryFilter> polydata =
    vtkSmartPointer<vtkCompositeDataGeometryFilter>::New();
  polydata->SetInputConnection(edges->GetOutputPort());

  // uncomment to inspect
  //polydata->Update();
  //std::cerr << polydata->GetOutput()->GetClassName() << std::endl;
  //polydata->GetOutput()->PrintSelf(std::cerr, vtkIndent(0));

  // display the data
  vtkSmartPointer<vtkRenderer> aren = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin  =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(aren);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(0, polydata->GetOutputPort(0));

  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  aren->AddActor(actor);

  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
