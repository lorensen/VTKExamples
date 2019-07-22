//
// Create bar charts of frequency of letters. 
//
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkLinearExtrusionFilter.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkVectorText.h>

#include <vector>

int main( int argc, char *argv[] ) 
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  std::vector<vtkSmartPointer<vtkVectorText> > letters;
  std::vector<vtkSmartPointer<vtkLinearExtrusionFilter> > extrude;
  std::vector<vtkSmartPointer<vtkPolyDataMapper> > mappers;
  std::vector<vtkSmartPointer<vtkActor> > actors;

  char filename[512];
  char text[2];
  static char alphabet[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int i, j, freq[26], maxFreq;
  float x, y;
  FILE *fPtr;
  int c;

//
// count the letters
//
  if ( (argc == 1) || ((argc == 2) && !(strcmp("-S", argv[1]))) )
    {
    cerr << "Please provide filename: " << argv[0] << " filename\n";
    strcpy( filename, "./Makefile" );
    cerr << "Using the file " << filename << " as input\n";
    }
  else
    {
    strcpy( filename, argv[1] );
    }

  if ( (fPtr = fopen (filename, "r")) == NULL )
    {
    cerr << "Cannot open file: " <<  filename << "\n";
    exit(1);
    }

  for (i=0; i<26; i++) freq[i] = 0;
  while ( (c=fgetc(fPtr)) != EOF )
    {
    if ( isalpha(c) )
      {
      c = tolower(c);
      freq[c-97]++;
      }
    }

  for (maxFreq=0, i=0; i<26; i++)
    if ( freq[i] > maxFreq ) 
      maxFreq = freq[i];
//
// graphics stuff
//
  vtkSmartPointer<vtkRenderer> ren =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renWin);
//
// Setup letters
//
  text[1] = '\0';
  for (i=0; i<26; i++)
    {
    text[0] = alphabet[i];
    letters.push_back(vtkSmartPointer<vtkVectorText>::New());
    letters[i]->SetText(text);

    extrude.push_back(vtkSmartPointer<vtkLinearExtrusionFilter>::New());
    extrude[i]->SetInputConnection(letters[i]->GetOutputPort());
    extrude[i]->SetExtrusionType(VTK_VECTOR_EXTRUSION);
    extrude[i]->SetVector(0,0,1.0);
    extrude[i]->SetScaleFactor((double)freq[i] / maxFreq * 2.50);

    mappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
    mappers[i]->SetInputConnection(extrude[i]->GetOutputPort());
    mappers[i]->ScalarVisibilityOff();

    actors.push_back(vtkSmartPointer<vtkActor>::New());
    actors[i]->SetMapper(mappers[i]);
    actors[i]->GetProperty()->SetColor(colors->GetColor3d("Peacock").GetData());
    if ( freq[i] <= 0 )
    {
      actors[i]->VisibilityOff();
    }
    ren->AddActor(actors[i]);
    }
//
// Position actors
//
  for (y=0.0, j=0; j<2; j++, y+=(-3.0))
  {
    for (x=0.0, i=0; i<13; i++, x+=1.5)
    {
      actors[j*13 + i]->SetPosition(x, y, 0.0);
    }
  }

  ren->ResetCamera();
  ren->SetBackground(colors->GetColor3d("Silver").GetData());
  ren->GetActiveCamera()->Elevation(30.0);
  ren->GetActiveCamera()->Azimuth(-30.0);
  ren->GetActiveCamera()->Dolly(1.25);
  ren->ResetCameraClippingRange();

  renWin->SetSize(640, 480);

  // interact with data
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
