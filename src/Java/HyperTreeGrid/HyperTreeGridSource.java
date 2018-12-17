import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;


import vtk.vtkNativeLibrary;
import vtk.vtkPanel;
import vtk.vtkActor;
import vtk.vtkHyperTreeGridSource;
import vtk.vtkShrinkFilter;
import vtk.vtkDataSetMapper;
import vtk.vtkNamedColors;


public class HyperTreeGridSource extends JPanel implements ActionListener {
	  private static final long serialVersionUID = 1L;
	  private vtkPanel renWin;
	  private JButton exitButton;

	  // -----------------------------------------------------------------
	  // Load VTK library and print which library was not properly loaded
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
	  // -----------------------------------------------------------------
	  
	  
	   public HyperTreeGridSource() {
	    super(new BorderLayout());
	   
	    
	   vtkNamedColors Color = new vtkNamedColors(); 
	   //For Actor Color
	   double ActorColor[] = new double[4];
	   //For Renderer Background Color
	   double BgColor[] = new double[4];
	   
	   
	   //Change Color Name to Use your own Color for Change Actor Color
	   Color.GetColor("Burlywood",ActorColor);
	   //Change Color Name to Use your own Color for Renderer Background
	   Color.GetColor("Teal",BgColor);
	
	   
	   // Create hyper tree grid source
	   vtkHyperTreeGridSource Source = new vtkHyperTreeGridSource();
	   Source.SetMaximumLevel(6);
	   Source.SetGridSize(3, 3, 2);
	   Source.SetGridScale(1.5, 1.0, 0.7);
	   Source.SetDimension(3);
	   Source.SetBranchFactor(4);
	   Source.SetDescriptor("RRR .R. .RR ..R ..R .R.|R.......................... ........................... ........................... .............R............. ....RR.RR........R......... .....RRRR.....R.RR......... ........................... ........................... ...........................|........................... ........................... ........................... ...RR.RR.......RR.......... ........................... RR......................... ........................... ........................... ........................... ........................... ........................... ........................... ........................... ............RRR............|........................... ........................... .......RR.................. ........................... ........................... ........................... ........................... ........................... ........................... ........................... ...........................|........................... ..........................." );
	   Source.Update();

	   vtkShrinkFilter Shrink = new vtkShrinkFilter();
	   Shrink.SetInputConnection(Source.GetOutputPort());
	   Shrink.SetShrinkFactor(0.8);
	   
	   vtkDataSetMapper Mapper = new vtkDataSetMapper();
	   Mapper.SetInputConnection(Shrink.GetOutputPort());
	   Mapper.ScalarVisibilityOff();
	   
	   
	   vtkActor Actor = new vtkActor();
	   Actor.SetMapper(Mapper);
	   Actor.GetProperty().SetDiffuseColor(ActorColor);

	  renWin = new vtkPanel();
	  renWin.GetRenderer().AddActor(Actor);
	  renWin.resetCamera();
	  renWin.GetRenderer().SetBackground(BgColor);
	  renWin.GetRenderer().ResetCamera();
	  renWin.GetRenderer().GetActiveCamera().Azimuth(150);
	  renWin.GetRenderer().GetActiveCamera().Elevation(30);
	  renWin.GetRenderer().ResetCameraClippingRange();
	  
 
	  // Add Java UI components
	  exitButton = new JButton("Exit");
	  exitButton.addActionListener(this);

	  add(renWin, BorderLayout.CENTER);
	  add(exitButton, BorderLayout.SOUTH);
	  }

	  /** An ActionListener that listens to the button. */
	  public void actionPerformed(ActionEvent e) {
	    if (e.getSource().equals(exitButton)) {
	      System.exit(0);
	    }
	  }

	  public static void main(String s[]) {
	    SwingUtilities.invokeLater(new Runnable() {
	      public void run() {
	        JFrame frame = new JFrame("HyperTreeGrid Source");
	        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	        frame.getContentPane().setLayout(new BorderLayout());
	        frame.getContentPane().add(new HyperTreeGridSource(), BorderLayout.CENTER);
	        frame.setSize(400, 400);
	        frame.setLocationRelativeTo(null);
	        frame.setVisible(true);
	      }
	    });
	  }
	} 
