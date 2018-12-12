import java.awt.BorderLayout;
import java.io.File;
import java.io.IOException;
import java.io.Serializable;
import java.util.concurrent.TimeUnit;
import javax.swing.JFrame;
import javax.swing.SwingUtilities;
import vtk.vtkActor;
import vtk.vtkArrowSource;
import vtk.vtkCubeSource;
import vtk.vtkGlyph3D;
import vtk.vtkObject;
import vtk.vtkPanel;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper;
import vtk.vtkThresholdPoints;
import vtk.vtkUnstructuredGrid;
import vtk.vtkXMLUnstructuredGridReader;


public class VectorFieldExample implements Serializable {

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
    private static final long serialVersionUID = 1L;

    public static vtkPanel showVectorField(
            File file,
            int elementInFile,
            double threshold,
            double scaleFactor) {

        vtkXMLUnstructuredGridReader reader = new vtkXMLUnstructuredGridReader();

        reader.SetFileName(file.getAbsolutePath());
        reader.Update();
        vtkUnstructuredGrid image = reader.GetOutput();
        image.GetPointData().SetVectors(image.GetPointData().GetArray(elementInFile));

        vtkThresholdPoints thresholdVector = new vtkThresholdPoints();
        thresholdVector.SetInputData(image);
        thresholdVector.SetInputArrayToProcess(
                elementInFile,
                image.GetInformation());

        thresholdVector.ThresholdByUpper(threshold);
        thresholdVector.Update();


        // represent vector field
        vtkGlyph3D vectorGlyph = new vtkGlyph3D();
        vtkArrowSource arrowSource = new vtkArrowSource();
        vtkPolyDataMapper vectorGlyphMapper = new vtkPolyDataMapper();

        int n = image.GetPointData().GetNumberOfArrays();
        for (int i = 0; i < n; i++) {
            System.out.println("name of array[" + i + "]: " + image.GetPointData().GetArrayName(i));
        }

        vtkPolyData tmp = thresholdVector.GetOutput();
        System.out.println("number of thresholded points: " + tmp.GetNumberOfPoints());

        vectorGlyph.SetInputData(image);
        vectorGlyph.SetSourceConnection(arrowSource.GetOutputPort());
        vectorGlyph.SetScaleModeToScaleByVector();
        vectorGlyph.SetVectorModeToUseVector();
        vectorGlyph.ScalingOn();
        vectorGlyph.OrientOn();
        vectorGlyph.SetInputArrayToProcess(
                elementInFile,
                image.GetInformation());

        vectorGlyph.SetScaleFactor(scaleFactor);

        vectorGlyph.Update();

        vectorGlyphMapper.SetInputConnection(vectorGlyph.GetOutputPort());
        vectorGlyphMapper.Update();

        vtkActor vectorActor = new vtkActor();
        vectorActor.SetMapper(vectorGlyphMapper);



        vtkPanel vis = new vtkPanel();
        vis.GetRenderer().AddActor(vectorActor);

        return vis;
    }

    public static void main(String s[]) throws IOException {


        SwingUtilities.invokeLater(new Runnable() {

            @Override
            public void run() {

                JFrame frame = new JFrame("VTKJPanel Demo");
                frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

                File file = new File("../src/Testing/Data/tetra.vtu"); // needs to be replaced

                vtkPanel panel = showVectorField(file, 2, 0.001, 0.05); // values need to be replaced

                frame.add(panel, BorderLayout.CENTER);
                frame.setSize(600, 600);
                frame.setLocationRelativeTo(null);
                frame.setVisible(true);

                panel.repaint();

            }
        });
    }
}
