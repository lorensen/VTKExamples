import vtk.vtkRTAnalyticSource;
import vtk.vtkImplicitDataSet;
import vtk.vtkNativeLibrary;

class ImplicitDataSet{  
	
	static {
	    if (!vtkNativeLibrary.LoadAllNativeLibraries()) {
	      for (vtkNativeLibrary lib : vtkNativeLibrary.values()) {
	        if (!lib.IsLoaded()) {
	          System.out.println(lib.GetLibraryName() + " not loaded");
	        }
	      }
	    }
	    vtkNativeLibrary.DisableOutputWindow(null);
	  }
	
	
    public static void main(String args[]){  
    	
    		  vtkRTAnalyticSource waveletSource = new vtkRTAnalyticSource();
    		  waveletSource.Update();
    		  
    		  vtkImplicitDataSet implicitWavelet = new vtkImplicitDataSet();
    		  implicitWavelet.SetDataSet(waveletSource.GetOutput());

    		  double x[] = new double[] {0.5,0,0};
    		  // Value should roughly be 258.658.

    		 
		  System.out.print("x: " + implicitWavelet.EvaluateFunction(x));
		  
    }   
}   
