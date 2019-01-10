import vtk.vtkNativeLibrary;
import vtk.vtkMinimalStandardRandomSequence;


public class RandomSequence 
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
	
  public static void main(String s[]) 
  {					  
    //Create a random sequence generator.
    vtkMinimalStandardRandomSequence Sequence = new vtkMinimalStandardRandomSequence();
    //initialize the sequence
    Sequence.SetSeed(1);

    //Get 3 random numbers.
    double x = Sequence.GetValue();
    Sequence.Next();
    double y = Sequence.GetValue();
    Sequence.Next();
    double z = Sequence.GetValue();
    Sequence.Next();

    // You can also use Sequence.GetRangeValue(-1.0, 1.0) to set a range on the random values.

    System.out.println("X:"+x + "\n" + "Y:" + y + "\n" + "Z:"+ z);
    
  }		  
}
