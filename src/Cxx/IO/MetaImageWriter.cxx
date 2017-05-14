// some standard vtk headers
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

// headers needed for this example
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageCast.h>
#include <vtkMetaImageWriter.h>
#include <vtkMetaImageReader.h>
#include <vtkImageMandelbrotSource.h>
#include <vtkImageActor.h>

int main(int, char *[])
{
   // adapt path !
   std::string filePath = "julia_mha.mhd";
   std::string filePathRaw = "julia_mha.raw";
   // Create an image
   vtkSmartPointer<vtkImageMandelbrotSource> source =
      vtkSmartPointer<vtkImageMandelbrotSource>::New();

   vtkSmartPointer<vtkImageCast> castFilter = 
      vtkSmartPointer<vtkImageCast>::New();
   castFilter->SetOutputScalarTypeToUnsignedChar();
   castFilter->SetInputConnection(source->GetOutputPort());
   castFilter->Update();

   vtkSmartPointer<vtkMetaImageWriter> writer =
      vtkSmartPointer<vtkMetaImageWriter>::New();
   writer->SetInputConnection(castFilter->GetOutputPort());
   writer->SetFileName(filePath.c_str());
   writer->SetRAWFileName(filePathRaw.c_str());
   writer->Write();

   // Read and display file for verification that it was written correctly
   vtkSmartPointer<vtkMetaImageReader> reader = 
      vtkSmartPointer<vtkMetaImageReader>::New();
   reader->SetFileName(filePath.c_str());
   reader->Update();

   vtkSmartPointer<vtkImageActor> actor =
      vtkSmartPointer<vtkImageActor>::New();
   actor->GetMapper()->SetInputConnection(reader->GetOutputPort());

   vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
   vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
   renderWindow->AddRenderer(renderer);
   vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
   renderWindowInteractor->SetRenderWindow(renderWindow);

   renderer->AddActor(actor);
   renderer->SetBackground(.2, .3, .4);

   renderWindow->Render();
   renderWindowInteractor->Start();

   return EXIT_SUCCESS;
}
