import vtk.vtkNativeLibrary;
import vtk.vtkTimerLog;

public class TimerLog 
{
  //-----------------------------------------------------------------
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
  //-----------------------------------------------------------------
		
  public static void main(String s[]) 
  {
    vtkTimerLog TimerLog = new vtkTimerLog();

    System.out.println("Current Time:" + TimerLog.GetUniversalTime());
    TimerLog.MarkEvent("File Opened");
    TimerLog.MarkEvent("Did Somthing");
    System.out.println("Timer Log:" + TimerLog);	     
  }
}
