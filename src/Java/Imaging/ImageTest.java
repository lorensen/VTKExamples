import java.awt.FileDialog;
import java.awt.Frame;
import vtk.*;

public class ImageTest  {

	/**
	 * ImageTest provides a means to test the ImageReader2Factory
	 * Image files understood by vtk are displayed, 
	 * all others are reported with a message. 
	 */
	vtkRenderWindow renWin;
	vtkRenderWindowInteractor iren;
	vtkRenderer ren1;
	vtkImageReader2Factory imageReaderFactory;
	vtkImageReader2 imageReader;
	vtkImageActor ImageActor;
	vtkInteractorObserver imageStyle;

	// Loading Native Libraries.
  	// Now it works in eclipse without any issues.
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

	public static void main(String[] args) {
		
		ImageTest me = new ImageTest();
		me.doit();
		
	}


	public void doit() {
		/*
		 * Use a file dialog to allow selection of any file for 
		 * test of the imagereaderfactory.
		 * only does one file per exection.
		 */
		System.out.println("init in ImageTest");
		ren1 = new vtkRenderer();
		renWin = new vtkRenderWindow();
		iren = new vtkRenderWindowInteractor();
		imageStyle = new vtkInteractorStyleImage();

		FileDialog fd = new FileDialog( new Frame(),"File name to load",
				FileDialog.LOAD);
		fd.setFile("*.*");
		fd.setVisible(true);
		String selected = fd.getFile();
		fd.setVisible(false);
		if (selected != null) {
			String outname = fd.getDirectory() + selected;

			imageReaderFactory = new vtkImageReader2Factory();
			imageReader = imageReaderFactory.CreateImageReader2(outname);
			if (imageReader != null) {
				imageReader.SetFileName(outname);
				imageReader.SetDataOrigin(0, 0, 0);
				imageReader.Update();

				ImageActor = new vtkImageActor();
				ImageActor.SetInput(imageReader.GetOutput());
				renWin.AddRenderer(ren1);
				iren.SetRenderWindow(renWin);
				
				iren.SetInteractorStyle(imageStyle);

				ren1.AddActor(ImageActor);
				renWin.AddRenderer(ren1);

				iren.Initialize();
				iren.Start();
				System.out.println("Return from interactor");
				renWin.Finalize();
			} else {
				System.out.println("No reader found for " + outname);
			}

		} else {
			System.out.println("No file name selected");
		}

	}
}
