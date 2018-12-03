#include <vtkPolyData.h>
#include<vtkSLCReader.h>
#include <vtkStructuredGridGeometryFilter.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkContourFilter.h>
#include<vtkProperty.h>
#include <vtkExtractVOI.h>
#include<vtkOutlineFilter.h>


 //Author: Bharatesh Chakravarthi 
//Affiliation: Virtual Environment Lab, Chung-Ang University, Seoul, South Korea

 int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		//Pass the filename (<filename>.slc) as parameter to read .slc file 
		cout << "Required parameters: Filename" << endl;
		return EXIT_FAILURE;
	}
	
  std::string inputFilename = argv[1];
 	
  //Using vtkSLCReader to read Volumetric file format(<filename.slc>) 
	vtkSmartPointer<vtkSLCReader> reader = vtkSmartPointer<vtkSLCReader>::New();
	reader->SetFileName(inputFilename.c_str());
	reader->Update();
 	
  //Implementing Marching Cubes Algorithm to create the surface using vtkContourFilter object 
	vtkSmartPointer<vtkContourFilter> cFilter = vtkSmartPointer<vtkContourFilter>::New();
	cFilter->SetInputConnection(reader->GetOutputPort());
	
  //Change the range(2nd and 3rd Paramater) based on your requirement. recomended value for 1st parameter is above 1 
	cFilter->GenerateValues(5, 80.0, 100.0);
	cFilter->Update();
 	
  //Adding the outliner using vtkOutlineFilter object
	vtkSmartPointer<vtkOutlineFilter> outliner = vtkSmartPointer<vtkOutlineFilter>::New();
	outliner->SetInputConnection(reader->GetOutputPort());
	outliner->Update();
 	
  // Visualize
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(cFilter->GetOutputPort());
	mapper->SetScalarVisibility(0);
 	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetColor(0.89, 0.85, 0.78);
 	
  //extractVOI is used to fix the problem of subsampling of data and reduce slow interaction and increase loading speed
	vtkSmartPointer<vtkExtractVOI> extractVOI = vtkSmartPointer<vtkExtractVOI>::New();
	extractVOI->SetInputConnection(reader->GetOutputPort());
	extractVOI->SetSampleRate(2, 2, 2);
	extractVOI->Update();
 	
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
 	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
 	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);
 	
  renderer->AddActor(actor);
	renderer->SetBackground(1, 1, 1); // Background color green
 	renderWindow->Render();
	renderWindowInteractor->Start();
 	return EXIT_SUCCESS;
}
