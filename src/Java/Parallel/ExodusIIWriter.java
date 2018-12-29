import vtk.vtkNativeLibrary;
import vtk.vtkExodusIIWriter;
import vtk.vtkTimeSourceExample;

public class ExodusIIWriter 
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
	  // Provide default values.
		String fileName = "Output.exii";
		for(int i = 0; i < args.length; ++i)
		{
		  switch (i) 
		  {
		    case 0:
		        	fileName = args[i];
		        	break;

		  }
		}
		vtkTimeSourceExample TimeSource = new vtkTimeSourceExample();
		vtkExodusIIWriter ExodusWriter = new vtkExodusIIWriter();
		ExodusWriter.SetFileName(fileName);
		ExodusWriter.SetInputConnection(TimeSource.GetOutputPort());
		ExodusWriter.WriteAllTimeStepsOn();
		ExodusWriter.Write();
	}		  
}
