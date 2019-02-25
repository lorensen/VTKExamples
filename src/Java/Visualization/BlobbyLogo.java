import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkPolyDataMapper;
import vtk.vtkPolyDataReader;
import vtk.vtkTransform;
import vtk.vtkTransformPolyDataFilter;
import vtk.vtkPolyDataNormals;
import vtk.vtkAppendPolyData;
import vtk.vtkImplicitModeller;
import vtk.vtkContourFilter;
import vtk.vtkProperty;

public class BlobbyLogo 
{
  // -----------------------------------------------------------------
  // Load VTK library and print which library was not properly loaded
  static 
  {
    if (!vtkNativeLibrary.LoadAllNativeLibraries()) 
    {
      for (vtkNativeLibrary lib : vtkNativeLibrary.values()) 
      {
        if (!lib.IsLoaded()) 
        {
          System.out.println(lib.GetLibraryName() + " not loaded");
        }
      }
    }
    vtkNativeLibrary.DisableOutputWindow(null);
  }
  // -----------------------------------------------------------------

  public static void main(String args[]) 
  {
    //parse command line arguments
    if (args.length != 3) 
    {
      System.err.println("Usage: java -classpath ... Filename(.vtk) Filename(.vtk) Filename(.vtk) e.g v.vtk t.vtk k.vtk");
      return;
    }
    
    vtkRenderer aRenderer = new vtkRenderer();
    vtkRenderWindow aRenderWindow = new vtkRenderWindow();
    aRenderWindow.AddRenderer(aRenderer);
    vtkRenderWindowInteractor anInteractor = new vtkRenderWindowInteractor();
    anInteractor.SetRenderWindow(aRenderWindow);
    aRenderWindow.SetSize( 300, 300 );
    
    //read the geometry file containing the letter v
    vtkPolyDataReader letterV = new vtkPolyDataReader();
    letterV.SetFileName (args[0]);

    //read the geometry file containing the letter t
    vtkPolyDataReader letterT = new vtkPolyDataReader();
    letterT.SetFileName (args[1]);

    //read the geometry file containing the letter k
    vtkPolyDataReader letterK = new vtkPolyDataReader();
    letterK.SetFileName (args[2]);
    
    //create a transform and transform filter for each letter
    vtkTransform VTransform = new vtkTransform();
    vtkTransformPolyDataFilter VTransformFilter = new vtkTransformPolyDataFilter();
    VTransformFilter.SetInputConnection(letterV.GetOutputPort());
    VTransformFilter.SetTransform (VTransform);

    vtkTransform TTransform = new vtkTransform();
    vtkTransformPolyDataFilter TTransformFilter = new vtkTransformPolyDataFilter();
    TTransformFilter.SetInputConnection (letterT.GetOutputPort());
    TTransformFilter.SetTransform (TTransform);

    vtkTransform KTransform = new vtkTransform();
    vtkTransformPolyDataFilter KTransformFilter = new vtkTransformPolyDataFilter();
    KTransformFilter.SetInputConnection(letterK.GetOutputPort());
    KTransformFilter.SetTransform (KTransform);
  
    //now append them all
    vtkAppendPolyData appendAll = new vtkAppendPolyData();
    appendAll.AddInputConnection (VTransformFilter.GetOutputPort());
    appendAll.AddInputConnection (TTransformFilter.GetOutputPort());
    appendAll.AddInputConnection (KTransformFilter.GetOutputPort());

    //create normals
    vtkPolyDataNormals logoNormals = new vtkPolyDataNormals();
    logoNormals.SetInputConnection (appendAll.GetOutputPort());
    logoNormals.SetFeatureAngle (60);

    //map to rendering primitives
    vtkPolyDataMapper logoMapper = new vtkPolyDataMapper();
    logoMapper.SetInputConnection (logoNormals.GetOutputPort());

    //now an actor
    vtkActor logo = new vtkActor();
    logo.SetMapper (logoMapper);
    
    //now create an implicit model of the same letter
    vtkImplicitModeller blobbyLogoImp = new vtkImplicitModeller();
    blobbyLogoImp.SetInputConnection(appendAll.GetOutputPort());
    blobbyLogoImp.SetMaximumDistance (.075);
    blobbyLogoImp.SetSampleDimensions (64,64,64); 
    blobbyLogoImp.SetAdjustDistance (0.05);

    //extract an iso surface
    vtkContourFilter blobbyLogoIso = new vtkContourFilter();
    blobbyLogoIso.SetInputConnection(blobbyLogoImp.GetOutputPort());
    blobbyLogoIso.SetValue (1, 1.5);

    //map to rendering primitives
    vtkPolyDataMapper blobbyLogoMapper = new vtkPolyDataMapper();
    blobbyLogoMapper.SetInputConnection(blobbyLogoIso.GetOutputPort());
    blobbyLogoMapper.ScalarVisibilityOff ();
     
    vtkNamedColors Color = new vtkNamedColors(); 

    double tomatoColor[] = new double[4];
    double bananaColor[] = new double[4];
    double BgColor[] = new double[4];

    Color.GetColor("tomato",tomatoColor);
    Color.GetColor("banana",bananaColor);
    Color.GetColor("SlateGray",BgColor);
    
    vtkProperty tomato = new vtkProperty();
    tomato.SetDiffuseColor(tomatoColor);
    tomato.SetSpecular(.3);
    tomato.SetSpecularPower(20);

    vtkProperty banana = new vtkProperty();
    banana.SetDiffuseColor(bananaColor);
    banana.SetDiffuse (.7);
    banana.SetSpecular(.4);
    banana.SetSpecularPower(20);
    
    //An actor
    vtkActor blobbyLogo = new vtkActor();
    blobbyLogo.SetMapper (blobbyLogoMapper);
    blobbyLogo.SetProperty (banana);

    // position the letters

    VTransform.Translate (-16.0,0.0,12.5);
    VTransform.RotateY (40);

    KTransform.Translate (14.0, 0.0, 0.0);
    KTransform.RotateY (-40);

    // move the polygonal letters to the front
    logo.SetProperty (tomato);
    logo.SetPosition(0,0,6);

    aRenderer.AddActor(logo);
    aRenderer.AddActor(blobbyLogo);

    aRenderer.SetBackground(BgColor);

    aRenderWindow.Render();

    // interact with data
    anInteractor.Start();

  }
}
