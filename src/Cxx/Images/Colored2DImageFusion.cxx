#include <vtkSmartPointer.h>

#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>
#include <vtkActor.h>
#include <vtkDataSet.h>
#include <vtkDataSetMapper.h>
#include <vtkImageBlend.h>
#include <vtkImageData.h>
#include <vtkImageMapToColors.h>
#include <vtkLookupTable.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int argc, char *argv[])
{
  // Parse input arguments
  if ( argc < 3 )
  {
    std::cerr << "Usage: " << argv[0]
              << " Input1Filename Input2Filename" << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkLookupTable> imgFirstColorMap =
    vtkSmartPointer<vtkLookupTable>::New(); // hot color map
  imgFirstColorMap->SetRange( 0.0, 255.0 );
  imgFirstColorMap->SetHueRange( 0.0, 0.1 );
  imgFirstColorMap->SetValueRange( 0.4, 0.8 );
  imgFirstColorMap->Build();

  vtkSmartPointer<vtkLookupTable> imgSecondColorMap =
      vtkSmartPointer<vtkLookupTable>::New(); // cold color map
  imgSecondColorMap->SetRange( 0.0, 255.0 );
  imgSecondColorMap->SetHueRange( 0.67, 0.68 );
  imgSecondColorMap->SetValueRange( 0.4, 0.8 );
  imgSecondColorMap->Build();

  vtkSmartPointer<vtkImageReader2Factory> readerFactory =
    vtkSmartPointer<vtkImageReader2Factory>::New();
  vtkSmartPointer<vtkImageReader2> imgReader;
  imgReader.TakeReference(
    readerFactory->CreateImageReader2(argv[1]));
  imgReader->SetFileName(argv[1]);

  vtkSmartPointer<vtkImageReader2> imgReaderMoving;
  imgReaderMoving.TakeReference(
    readerFactory->CreateImageReader2(argv[2]));
  imgReaderMoving->SetFileName(argv[2]);

  vtkSmartPointer<vtkImageMapToColors> firstColorMapper =
      vtkSmartPointer<vtkImageMapToColors>::New();
  firstColorMapper->SetInputConnection( imgReader->GetOutputPort() );
  firstColorMapper->SetLookupTable( imgFirstColorMap );

  vtkSmartPointer<vtkImageMapToColors> secondColorMapper =
      vtkSmartPointer<vtkImageMapToColors>::New();
  secondColorMapper->SetInputConnection( imgReaderMoving->GetOutputPort() );
  secondColorMapper->SetLookupTable( imgSecondColorMap );

  vtkSmartPointer<vtkImageBlend> imgBlender =
      vtkSmartPointer<vtkImageBlend>::New();
  imgBlender->SetOpacity( 0, 0.5 );
  imgBlender->SetOpacity( 1, 0.5 );
  imgBlender->AddInputConnection( firstColorMapper->GetOutputPort() );
  imgBlender->AddInputConnection( secondColorMapper->GetOutputPort() );

  vtkSmartPointer<vtkDataSetMapper> imgDataSetMapper =
      vtkSmartPointer<vtkDataSetMapper>::New();
  imgDataSetMapper->SetInputConnection(imgBlender->GetOutputPort());

  vtkSmartPointer<vtkActor> imgActor =
      vtkSmartPointer<vtkActor>::New();
  imgActor->SetMapper( imgDataSetMapper );

  vtkSmartPointer<vtkRenderer> imgRenderer =
      vtkSmartPointer<vtkRenderer>::New();
  imgRenderer->AddActor( imgActor );

  vtkSmartPointer<vtkRenderWindow> imgRenderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
  imgRenderWindow->AddRenderer( imgRenderer );

  vtkSmartPointer<vtkRenderWindowInteractor> imgInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  imgInteractor->SetRenderWindow( imgRenderWindow );
  imgRenderWindow->Render();
  imgInteractor->Initialize();
  imgInteractor->Start();

  return EXIT_SUCCESS;
}
