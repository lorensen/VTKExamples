 import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import vtk.vtkActor;
import vtk.vtkNativeLibrary;
import vtk.vtkPanel;
import vtk.vtkPolyDataMapper;
import vtk.vtkLine;
import vtk.vtkCellArray;
import vtk.vtkPoints;
import vtk.vtkPolyData;


//Author: Bharatesh Chakravarthi
//Affiliation: VE Lab, Chung Ang University, Seoul, South Korea. 


public class LongLine extends JPanel implements ActionListener 
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
	  
	  
	  public LongLine() 
	  {
	    super(new BorderLayout());
	    
	    double origin[] = new double[] {0.0,0.0,0.0};
	    double p0[] = new double[] {1.0,0.0,0.0};
	    double p1[] = new double[] {0.0,1.0,0.0};
	    double p2[] = new double[] {0.0,1.0,2.0};
	    double p3[] = new double[] {1.0,2.0,3.0};
	    
    
		//Create a vtkPoints object and store the points in it
		   vtkPoints Points = new vtkPoints();
		   Points.InsertNextPoint(origin);
		   Points.InsertNextPoint(p0);
		   Points.InsertNextPoint(p1);
		   Points.InsertNextPoint(p2);
		   Points.InsertNextPoint(p3);
		   
	    
	    
		// Create a cell array to store the lines in and add the lines to it
	
		vtkCellArray Lines = new vtkCellArray();
		for(int i = 0; i < 3; i++)
		 {
			vtkLine Line = new vtkLine();
			Line.GetPointIds().SetId(0, i);
			Line.GetPointIds().SetId(1, i+1);
			Lines.InsertNextCell(Line);
		 }
	   
		//// Create a polydata
		vtkPolyData LinesPolyData = new vtkPolyData();
		LinesPolyData.SetPoints(Points);
		LinesPolyData.SetLines(Lines);

	  
		 //Create a Mapper and Actor
		 vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
		 Mapper.SetInputData(LinesPolyData);

		 vtkActor Actor = new vtkActor();
		 Actor.SetMapper(Mapper);
		 Actor.GetProperty().SetColor(1.0, 0.5, 0.5); 
		 Actor.GetProperty().SetLineWidth(5);
	   
		  renWin = new vtkPanel();
		  renWin.GetRenderer().AddActor(Actor);
		  renWin.GetRenderer().SetBackground(0.1, 0.5, 0.1);
		  renWin.resetCamera();
		  renWin.resetCameraClippingRange();

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
	        JFrame frame = new JFrame("Long Line");
	        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	        frame.getContentPane().setLayout(new BorderLayout());
	        frame.getContentPane().add(new LongLine(), BorderLayout.CENTER);
	        frame.setSize(400, 400);
	        frame.setLocationRelativeTo(null);
	        frame.setVisible(true);
	      }
	    });
	  }
	}  
