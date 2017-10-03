// This example demonstrates how hierarchical box (uniform rectilinear)
// AMR datasets can be processed using the new vtkHierarchicalBoxDataSet class.
//

#include <vtkSmartPointer.h>
#include <vtkCamera.h>
#include <vtkCellDataToPointData.h>
#include <vtkCompositeDataPipeline.h>
#include <vtkContourFilter.h>
#include <vtkExtractLevel.h>
#include <vtkHierarchicalDataSetGeometryFilter.h>
#include <vtkOutlineCornerFilter.h>
#include <vtkHierarchicalPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkShrinkPolyData.h>
#include <vtkXMLHierarchicalBoxDataReader.h>

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " file.vtm" << std::endl;
    return EXIT_FAILURE;
  }
  // Standard rendering classes
  vtkSmartPointer<vtkRenderer> ren =
    vtkSmartPointer<vtkRenderer>::New();

  vtkCamera* cam = ren->GetActiveCamera();
  cam->SetPosition(-5.1828, 5.89733, 8.97969);
  cam->SetFocalPoint(14.6491, -2.08677, -8.92362);
  cam->SetViewUp(0.210794, 0.95813, -0.193784);

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  vtkSmartPointer<vtkXMLHierarchicalBoxDataReader> reader =
    vtkSmartPointer<vtkXMLHierarchicalBoxDataReader>::New();
  reader->SetFileName(argv[1]);

  // geometry filter
  vtkSmartPointer<vtkHierarchicalDataSetGeometryFilter> geom =
    vtkSmartPointer<vtkHierarchicalDataSetGeometryFilter>::New();
  geom->SetInputConnection(0, reader->GetOutputPort(0));

  vtkSmartPointer<vtkShrinkPolyData> shrink =
    vtkSmartPointer<vtkShrinkPolyData>::New();
  shrink->SetShrinkFactor(0.5);
  shrink->SetInputConnection(0, geom->GetOutputPort(0));

  // // Rendering objects
   vtkSmartPointer<vtkHierarchicalPolyDataMapper> shMapper =
     vtkSmartPointer<vtkHierarchicalPolyDataMapper>::New();
   shMapper->SetInputConnection(0, shrink->GetOutputPort(0));
   vtkSmartPointer<vtkActor> shActor =
     vtkSmartPointer<vtkActor>::New();
   shActor->SetMapper(shMapper);
   shActor->GetProperty()->SetColor(0, 0, 1);
   ren->AddActor(shActor);

  // corner outline
   vtkSmartPointer<vtkOutlineCornerFilter> ocf =
     vtkSmartPointer<vtkOutlineCornerFilter>::New();
   vtkSmartPointer<vtkCompositeDataPipeline> pipeline =
     vtkSmartPointer<vtkCompositeDataPipeline>::New();
   ocf->SetExecutive(pipeline);
   ocf->SetInputConnection(0, reader->GetOutputPort(0));

  // // Rendering objects
  // // This one is actually just a vtkPolyData so it doesn't need a hierarchical
  // // mapper, but we use this one to test hierarchical mapper with polydata input
   vtkSmartPointer<vtkHierarchicalPolyDataMapper> ocMapper =
     vtkSmartPointer<vtkHierarchicalPolyDataMapper>::New();
   ocMapper->SetInputConnection(0, ocf->GetOutputPort(0));

   vtkSmartPointer<vtkActor> ocActor =
     vtkSmartPointer<vtkActor>::New();
   ocActor->SetMapper(ocMapper);
   ocActor->GetProperty()->SetColor(1, 0, 0);
   ren->AddActor(ocActor);

   // cell 2 point and contour
   vtkSmartPointer<vtkExtractLevel> el =
     vtkSmartPointer<vtkExtractLevel>::New();
   el->SetInputConnection(0, reader->GetOutputPort(0));
   el->AddLevel(2);

   vtkSmartPointer<vtkCellDataToPointData> c2p =
     vtkSmartPointer<vtkCellDataToPointData>::New();
   pipeline = vtkCompositeDataPipeline::New();
   c2p->SetExecutive(pipeline);
   c2p->SetInputConnection(0, el->GetOutputPort(0));

   vtkSmartPointer<vtkContourFilter> contour =
     vtkSmartPointer<vtkContourFilter>::New();

   pipeline = vtkCompositeDataPipeline::New();
   contour->SetExecutive(pipeline);
   contour->SetInputConnection(0, c2p->GetOutputPort(0));
   contour->SetValue(0, -0.013);
   contour->SetInputArrayToProcess(
     0,0,0,vtkDataObject::FIELD_ASSOCIATION_POINTS,"phi");

   // Rendering
   vtkSmartPointer<vtkHierarchicalPolyDataMapper> contMapper =
     vtkSmartPointer<vtkHierarchicalPolyDataMapper>::New();
   contMapper->SetInputConnection(0, contour->GetOutputPort(0));
   vtkSmartPointer<vtkActor> contActor =
     vtkSmartPointer<vtkActor>::New();

   contActor->SetMapper(contMapper);
   contActor->GetProperty()->SetColor(1, 0, 0);
   ren->AddActor(contActor);

   ren->SetBackground(1,1,1);
   renWin->SetSize(300,300);
   ren->ResetCamera();
   iren->Start();

   return EXIT_SUCCESS;
}
