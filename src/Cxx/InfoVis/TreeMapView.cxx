#include <vtkDataRepresentation.h>
#include <vtkRenderWindow.h>
#include <vtkRegressionTestImage.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTestUtilities.h>
#include <vtkTreeMapView.h>
#include <vtkViewTheme.h>
#include <vtkXMLTreeReader.h>
#include <vtkSmartPointer.h>
#include <vtkTesting.h>

int main(int argc, char* argv[])
{
  vtkSmartPointer<vtkTesting> testHelper =
    vtkSmartPointer<vtkTesting>::New();
  testHelper->AddArguments(argc,const_cast<const char **>(argv));
  std::string dataRoot = testHelper->GetDataRoot();
  std::string treeFileName = dataRoot + "/Data/Infovis/XML/vtkclasses.xml";
  std::string graphFileName = dataRoot + "/Data/Infovis/XML/vtklibrary.xml";

  if (argc > 2)
  {
    treeFileName = argv[1];  // vtkclasses.xml
    graphFileName = argv[2]; // vtklibrary.xml
  }

  // We need to put the graph and tree edges in different domains.
  vtkSmartPointer<vtkXMLTreeReader> reader1 =
    vtkSmartPointer<vtkXMLTreeReader>::New();
  reader1->SetFileName(treeFileName.c_str());
  reader1->SetEdgePedigreeIdArrayName("tree edge");
  reader1->GenerateVertexPedigreeIdsOff();
  reader1->SetVertexPedigreeIdArrayName("id");

  vtkSmartPointer<vtkXMLTreeReader> reader2 =
    vtkSmartPointer<vtkXMLTreeReader>::New();
  reader2->SetFileName(graphFileName.c_str());
  reader2->SetEdgePedigreeIdArrayName("graph edge");
  reader2->GenerateVertexPedigreeIdsOff();
  reader2->SetVertexPedigreeIdArrayName("id");

  reader1->Update();
  reader2->Update();

  vtkSmartPointer<vtkTreeMapView> view =
    vtkSmartPointer<vtkTreeMapView>::New();
  view->DisplayHoverTextOff();
  view->SetTreeFromInputConnection(reader2->GetOutputPort());
  view->SetGraphFromInputConnection(reader1->GetOutputPort());

  view->SetAreaColorArrayName("level");
  view->SetEdgeColorToSplineFraction();
  view->SetColorEdges(true);
  view->SetAreaLabelArrayName("id");
  view->SetAreaHoverArrayName("id");
  view->SetAreaLabelVisibility(true);
  view->SetAreaSizeArrayName("VertexDegree");

  // Apply a theme to the views
  vtkViewTheme* const theme = vtkViewTheme::CreateMellowTheme();
  view->ApplyViewTheme(theme);
  theme->Delete();

  view->GetRenderWindow()->SetMultiSamples(0);
  view->GetRenderWindow()->SetAlphaBitPlanes(1);
  view->Update();
  view->ResetCamera();

  view->GetRenderWindow()->Render();
  view->GetInteractor()->Initialize();
  view->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
