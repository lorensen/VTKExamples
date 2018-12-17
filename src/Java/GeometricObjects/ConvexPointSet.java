import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkConvexPointSet;
import vtk.vtkPoints;
import vtk.vtkUnstructuredGrid;
import vtk.vtkDataSetMapper;
import vtk.vtkSphereSource;
import vtk.vtkNativeLibrary;
import vtk.vtkPanel;
import vtk.vtkPolyData;
import vtk.vtkGlyph3DMapper;

 
public class ConvexPointSet extends JPanel implements ActionListener 
{
	  private static final long serialVersionUID = 1L;
	  private vtkPanel renWin;
	  private JButton exitButton;

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
  
  
	  public ConvexPointSet() 
	  {
		    super(new BorderLayout());
	    
		    vtkNamedColors Color = new vtkNamedColors();
	  
		    //For Actor Color
		    double ActorColor[] = new double[4];
		    //For Point Actor Color
		    double PointActorColor[] = new double[4];
		    //Renderer Background Color
		    double BgColor[] = new double[4];
		  
			   
		    //Change Color Name to Use your own Color for Change Actor Color
		    Color.GetColor("Cyan",ActorColor);
		    //Change Color Name to Use your own Color for Change Point Actor Color
		    Color.GetColor("OrangeRed",PointActorColor);
		    //Change Color Name to Use your own Color for Renderer Background
		    Color.GetColor("DarkOrange",BgColor);

		    vtkConvexPointSet CPS = new vtkConvexPointSet();
		    vtkPoints Points = new vtkPoints();
		    Points.InsertNextPoint(0, 0, 0);
		    Points.InsertNextPoint(1, 0, 0);
		    Points.InsertNextPoint(1, 1, 0);
		    Points.InsertNextPoint(0, 1, 0);
		    Points.InsertNextPoint(0, 0, 1);
		    Points.InsertNextPoint(1, 0, 1);
		    Points.InsertNextPoint(1, 1, 1);
		    Points.InsertNextPoint(0, 1, 1);
		    Points.InsertNextPoint(0.5, 0, 0);
		    Points.InsertNextPoint(1, 0.5, 0);
		    Points.InsertNextPoint(0.5, 1, 0);
		    Points.InsertNextPoint(0, 0.5, 0);
		    Points.InsertNextPoint(0.5, 0.5, 0);
		    
		    for (int i = 0; i < 13; ++i)
		    {
		      CPS.GetPointIds().InsertId(i, i);
		    }
		    
		    vtkUnstructuredGrid UG = new vtkUnstructuredGrid();
		    UG.Allocate(1, 1);
		    UG.InsertNextCell(CPS.GetCellType(), CPS.GetPointIds());
		    UG.SetPoints(Points);
		    
		    
		    vtkDataSetMapper Mapper = new vtkDataSetMapper();
		    Mapper.SetInputData(UG);   
		    
		    vtkActor Actor = new vtkActor();
		    Actor.SetMapper(Mapper);
		    Actor.GetProperty().SetColor(ActorColor);
		    Actor.GetProperty().SetLineWidth(3.0);
		    Actor.GetProperty().EdgeVisibilityOn();
		    
		    // Glyph the points
		    vtkSphereSource Sphere = new vtkSphereSource();
		    Sphere.SetRadius(0.03);
		    Sphere.SetPhiResolution(21);
		    Sphere.SetThetaResolution(21);
		    

		    vtkPolyData PolyData = new vtkPolyData();
		    PolyData.SetPoints(Points);
		    
		    vtkGlyph3DMapper PointMapper = new vtkGlyph3DMapper();
		    PointMapper.SetInputData(PolyData);
		    PointMapper.SetSourceConnection(Sphere.GetOutputPort());

		    vtkActor PointActor = new vtkActor();
		    PointActor.SetMapper(PointMapper);
		    PointActor.GetProperty().SetColor(PointActorColor);

		    renWin = new vtkPanel();
		    renWin.GetRenderer().AddActor(Actor);
		    renWin.GetRenderer().AddActor(PointActor);
		    renWin.GetRenderer().SetBackground(BgColor);
		    renWin.resetCamera();
		    renWin.GetRenderer().GetActiveCamera().Azimuth(210);
		    renWin.GetRenderer().GetActiveCamera().Elevation(30);
		    renWin.resetCameraClippingRange();
		    renWin.setSize(640, 480);
		  
		    // Add Java UI components
		    exitButton = new JButton("Exit");
		    exitButton.addActionListener(this);

		    add(renWin, BorderLayout.CENTER);
		    add(exitButton, BorderLayout.SOUTH);
	  }

	  /** An ActionListener that listens to the button. */
	  public void actionPerformed(ActionEvent e)
	  {
		  if (e.getSource().equals(exitButton)) 
		  {
			  	System.exit(0);
		  }
	  }

	  public static void main(String s[]) 
	  {
		  SwingUtilities.invokeLater(new Runnable() 
		  {
			  public void run() 
			  {
		        JFrame frame = new JFrame("Convex Point Set");
		        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		        frame.getContentPane().setLayout(new BorderLayout());
		        frame.getContentPane().add(new ConvexPointSet(), BorderLayout.CENTER);
		        frame.setSize(400, 400);
		        frame.setLocationRelativeTo(null);
		        frame.setVisible(true);
			  }
		  });
	  }
}
