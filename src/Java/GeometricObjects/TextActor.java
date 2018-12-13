import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;


import vtk.vtkNativeLibrary;
import vtk.vtkPanel;
import vtk.vtkTextActor;
import vtk.vtkNamedColors;


public class TextActor extends JPanel implements ActionListener {
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
	  
	  
	   public TextActor() {
	    super(new BorderLayout());
	   
	   
	   vtkNamedColors Color = new vtkNamedColors(); 
	   //For Actor Color
	   double ActorColor[] = new double[4];
	   //For Renderer Background Color
	   double BgColor[] = new double[4];
	   
	   
	   //Change Color Name to Use your own Color for Change Actor Color
	   Color.GetColor("Red",ActorColor);
	   //Change Color Name to Use your own Color for Renderer Background
	   Color.GetColor("Black",BgColor);

   
	  vtkTextActor Text = new vtkTextActor();
	  Text.SetInput("Hello World");
	  Text.SetDisplayPosition(20, 30);
	  Text.GetTextProperty().SetFontSize(40);
	  Text.GetTextProperty().SetFontFamilyToArial();
	  Text.GetTextProperty().BoldOn();
	  Text.GetTextProperty().ShadowOn();
	  Text.GetTextProperty().GetShadowOffset();
	  Text.GetTextProperty().SetColor(ActorColor);
	  
  
	  renWin = new vtkPanel();
	  renWin.GetRenderer().AddActor(Text);
	  renWin.resetCamera();
	  renWin.GetRenderer().SetBackground(BgColor);
	  
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
	        JFrame frame = new JFrame("Text Actor");
	        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	        frame.getContentPane().setLayout(new BorderLayout());
	        frame.getContentPane().add(new TextActor(), BorderLayout.CENTER);
	        frame.setSize(400, 400);
	        frame.setLocationRelativeTo(null);
	        frame.setVisible(true);
	      }
	    });
	  }
	} 
