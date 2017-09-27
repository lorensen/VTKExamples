#include <vtkMultiBlockDataSet.h>
#include <vtkSphereSource.h>
#include <vtkNew.h>
#include <vtkCompositePolyDataMapper2.h>
#include <vtkCompositeDataDisplayAttributes.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

int main( int /* argc */, char * /* argv */ [] )
{
  vtkNew<vtkSphereSource> sphere1;
  sphere1->SetRadius(3);
  sphere1->SetCenter(0,0,0);
  sphere1->Update();
  vtkNew<vtkSphereSource> sphere2;
  sphere2->SetRadius(2);
  sphere2->SetCenter(2,0,0);
  sphere2->Update();

  vtkNew<vtkMultiBlockDataSet> mbds;
  mbds->SetNumberOfBlocks(3);
  mbds->SetBlock(0, sphere1->GetOutput());
  // Leave block 1 NULL.  NULL blocks are valid and should be handled by
  // algorithms that process multiblock datasets.  Especially when
  // running in parallel where the blocks owned by other processes are
  // NULL in this process.
  mbds->SetBlock(2, sphere2->GetOutput());

  vtkNew<vtkCompositePolyDataMapper2> mapper;
  mapper->SetInputDataObject(mbds.GetPointer());
  vtkNew<vtkCompositeDataDisplayAttributes> cdsa;
  mapper->SetCompositeDataDisplayAttributes(cdsa.Get());

  // You can use the vtkCompositeDataDisplayAttributes to set the color,
  // opacity and visibiliy of individual blocks of the multiblock dataset.
  // Attributes are mapped by block pointers (vtkDataObject*), so these can
  // be queried by their flat index through a convenience function in the
  // attribute class (vtkCompositeDataDisplayAttributes::DataObjectFromIndex).
  // Alternatively, one can set attributes directly through the mapper using
  // flat indices.
  //
  // This sets the block at flat index 3 red
  // Note that the index is the flat index in the tree, so the whole multiblock
  // is index 0 and the blocks are flat indexes 1, 2 and 3.  This affects
  // the block returned by mbds->GetBlock(2).
  double color[] = {1, 0, 0};
  mapper->SetBlockColor(3, color);

  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper.Get());

  vtkNew<vtkRenderer> renderer;
  vtkNew<vtkRenderWindow> renderWindow;
  renderWindow->AddRenderer(renderer.Get());
  vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
  renderWindowInteractor->SetRenderWindow(renderWindow.Get());

  renderer->AddActor(actor.Get());

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
