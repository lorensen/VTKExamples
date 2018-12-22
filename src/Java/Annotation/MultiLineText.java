import vtk.vtkNativeLibrary;
import vtk.vtkTextProperty;
import vtk.vtkTextMapper;
import vtk.vtkActor2D;
import vtk.vtkPoints;
import vtk.vtkCellArray;
import vtk.vtkNamedColors;
import vtk.vtkCoordinate;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper2D;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;


public class MultiLineText  
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
		   vtkNamedColors Color = new vtkNamedColors(); 
		   //For singleLineTextB Actor Color
		   double singleLineTextActorBColor[] = new double[4];
		   //For singleLineTextActorC Color
		   double singleLineTextActorCColor[] = new double[4];
		   //For singleLineTextActorT Color
		   double singleLineTextActorTColor[] = new double[4];
		   //For textMapperLColor
		   double textMapperLColor[] = new double[4];
		   //For textMapperCColor
		   double textMapperCColor[] = new double[4];
		   //For textMapperRColor
		   double textMapperRColor[] = new double[4];
		   //For gridActor
		   double Grid_Actor[] = new double[4];
		   
		   //For Renderer Background Color
		   double BgColor[] = new double[4];
		   
		   
		   //Change Color Name to Use your own Color to singleLineTextActorB Color
		   Color.GetColor("IndianRed",singleLineTextActorBColor);
		   //Change Color Name to Use your own Color to singleLineTextActorC  Color
		   Color.GetColor("DarkBlue",singleLineTextActorCColor);
		   //Change Color Name to Use your own Color to singleLineTextActorT  Color
		   Color.GetColor("Maroon",singleLineTextActorTColor);
		   //Change Color Name to Use your own Color to textMapperLColor
		   Color.GetColor("Crimson",textMapperLColor);
		   //Change Color Name to Use your own Color to textMapperCColor
		   Color.GetColor("Black",textMapperCColor);
		   //Change Color Name to Use your own Color to textMapperRColor
		   Color.GetColor("Navy",textMapperRColor);
		   //Change Color Name to Use your own Color to textMapperRColor
		   Color.GetColor("DimGray",Grid_Actor);
		   //Change Color Name to Use your own Color for Renderer Background
		   Color.GetColor("BlanchedAlmond",BgColor);


		  vtkTextProperty singleLineTextProp = new vtkTextProperty();
		  singleLineTextProp.SetFontSize(24);
		  singleLineTextProp.SetFontFamilyToArial();
		  singleLineTextProp.BoldOff();
		  singleLineTextProp.ItalicOff();
		  singleLineTextProp.ShadowOff();
		  
		  vtkTextProperty multiLineTextProp = new vtkTextProperty();
		  multiLineTextProp.ShallowCopy(singleLineTextProp);
		  multiLineTextProp.BoldOn();
		  multiLineTextProp.ItalicOn();
		  multiLineTextProp.ShadowOn();
		  multiLineTextProp.SetLineSpacing(0.8);
		  
		  vtkTextMapper singleLineTextB = new vtkTextMapper();
		  singleLineTextB .SetInput("Single Line(Bottom)");
		  singleLineTextB.GetTextProperty().ShallowCopy(singleLineTextProp);
		  singleLineTextB.GetTextProperty().SetVerticalJustificationToBottom();
		  singleLineTextB .GetTextProperty().SetColor(singleLineTextActorBColor);
		  
		  vtkActor2D singleLineTextActorB = new vtkActor2D();
		  singleLineTextActorB.SetMapper(singleLineTextB);
		  singleLineTextActorB.GetPositionCoordinate().SetCoordinateSystemToNormalizedDisplay();
		  singleLineTextActorB.GetPositionCoordinate().SetValue(0.05, 0.85);
		  
		  		  
		  vtkTextMapper singleLineTextC = new vtkTextMapper();
		  singleLineTextC .SetInput("Single Line(centered)");
		  singleLineTextC.GetTextProperty().ShallowCopy(singleLineTextProp);
		  singleLineTextC.GetTextProperty().SetVerticalJustificationToCentered();
		  singleLineTextC .GetTextProperty().SetColor(singleLineTextActorCColor);
				  
		  vtkActor2D singleLineTextActorC = new vtkActor2D();
		  singleLineTextActorC.SetMapper(singleLineTextC);
		  singleLineTextActorC.GetPositionCoordinate().SetCoordinateSystemToNormalizedDisplay();
		  singleLineTextActorC.GetPositionCoordinate().SetValue(0.05, 0.75);
		  
		  vtkTextMapper singleLineTextT = new vtkTextMapper();
		  singleLineTextT .SetInput("Single Line(Top)");
		  singleLineTextT.GetTextProperty().ShallowCopy(singleLineTextProp);
		  singleLineTextT.GetTextProperty().SetVerticalJustificationToTop();
		  singleLineTextT .GetTextProperty().SetColor(singleLineTextActorTColor);
						  
		  vtkActor2D singleLineTextActorT = new vtkActor2D();
		  singleLineTextActorT.SetMapper(singleLineTextT);
		  singleLineTextActorT.GetPositionCoordinate().SetCoordinateSystemToNormalizedDisplay();
		  singleLineTextActorT.GetPositionCoordinate().SetValue(0.05, 0.65);	

		  vtkTextMapper textMapperL = new vtkTextMapper();
		  textMapperL .SetInput("This is\nmulti-line\ntext output\n(left-top)");
		  textMapperL.GetTextProperty().ShallowCopy(multiLineTextProp);
		  textMapperL.GetTextProperty().SetJustificationToLeft();
		  textMapperL.GetTextProperty().SetVerticalJustificationToTop();
		  textMapperL .GetTextProperty().SetColor(textMapperLColor);
								  
		  vtkActor2D textActorL = new vtkActor2D();
		  textActorL.SetMapper(textMapperL);
		  textActorL.GetPositionCoordinate().SetCoordinateSystemToNormalizedDisplay();
		  textActorL.GetPositionCoordinate().SetValue(0.05, 0.5);
		    
		  vtkTextMapper textMapperC = new vtkTextMapper();
		  textMapperC .SetInput("This is\nmulti-line\ntext output\n(centered)");
		  textMapperC.GetTextProperty().ShallowCopy(multiLineTextProp);
		  textMapperC.GetTextProperty().SetJustificationToCentered();
		  textMapperC.GetTextProperty().SetVerticalJustificationToCentered();
		  textMapperC .GetTextProperty().SetColor(textMapperCColor);
								  
		  vtkActor2D textActorC = new vtkActor2D();
		  textActorC.SetMapper(textMapperC);
		  textActorC.GetPositionCoordinate().SetCoordinateSystemToNormalizedDisplay();
		  textActorC.GetPositionCoordinate().SetValue(0.5, 0.5);
		  
		  vtkTextMapper textMapperR = new vtkTextMapper();
		  textMapperR .SetInput("This is\nmulti-line\ntext output\n(right-bottom)");
		  textMapperR.GetTextProperty().ShallowCopy(multiLineTextProp);
		  textMapperR.GetTextProperty().SetJustificationToRight();
		  textMapperR.GetTextProperty().SetVerticalJustificationToBottom();
		  textMapperR .GetTextProperty().SetColor(textMapperRColor);
								  
		  vtkActor2D textActorR = new vtkActor2D();
		  textActorR.SetMapper(textMapperR);
		  textActorR.GetPositionCoordinate().SetCoordinateSystemToNormalizedDisplay();
		  textActorR.GetPositionCoordinate().SetValue(0.95, 0.5);
		  
		  vtkPoints Pts = new vtkPoints();
		  Pts.InsertNextPoint(0.05, 0.0, 0.0);
		  Pts.InsertNextPoint(0.05, 1.0, 0.0);
		  Pts.InsertNextPoint(0.5, 0.0, 0.0);
		  Pts.InsertNextPoint(0.5, 1.0, 0.0);
		  Pts.InsertNextPoint(0.95, 0.0, 0.0);
		  Pts.InsertNextPoint(0.95, 1.0, 0.0);
		  Pts.InsertNextPoint(0.0, 0.5, 0.0);
		  Pts.InsertNextPoint(1.0, 0.5, 0.0);
		  Pts.InsertNextPoint(0.00, 0.85, 0.0);
		  Pts.InsertNextPoint(0.50, 0.85, 0.0);
		  Pts.InsertNextPoint(0.00, 0.75, 0.0);
		  Pts.InsertNextPoint(0.50, 0.75, 0.0);
		  Pts.InsertNextPoint(0.00, 0.65, 0.0);
		  Pts.InsertNextPoint(0.50, 0.65, 0.0);
		  
		  vtkCellArray Lines = new vtkCellArray();
		  Lines.InsertNextCell(2);
		  Lines.InsertNextCell(0);
		  Lines.InsertNextCell(1);
		  Lines.InsertNextCell(2);
		  Lines.InsertNextCell(2);
		  Lines.InsertNextCell(3);
		  Lines.InsertNextCell(2);
		  Lines.InsertNextCell(4);
		  Lines.InsertNextCell(5);
		  Lines.InsertNextCell(2);
		  Lines.InsertNextCell(6);
		  Lines.InsertNextCell(7);
		  Lines.InsertNextCell(2);
		  Lines.InsertNextCell(8);
		  Lines.InsertNextCell(9);
		  Lines.InsertNextCell(2);
		  Lines.InsertNextCell(10);
		  Lines.InsertNextCell(11);
		  Lines.InsertNextCell(2);
		  Lines.InsertNextCell(12);
		  Lines.InsertNextCell(13);
		  
		  vtkPolyData Grid = new vtkPolyData();
		  Grid.SetPoints(Pts);
		  Grid.SetLines(Lines);
		  
		  vtkCoordinate normCoords = new vtkCoordinate();
		  normCoords.SetCoordinateSystemToNormalizedViewport();
		  
		  vtkPolyDataMapper2D Mapper = new vtkPolyDataMapper2D();
		  Mapper.SetInputData(Grid);
		  Mapper.SetTransformCoordinate(normCoords);
		  
		  vtkActor2D GridActor = new vtkActor2D();
		  GridActor.SetMapper(Mapper);
	          GridActor.GetProperty().SetColor(Grid_Actor);
		  
		  
		  // Create the renderer, render window and interactor.
		  vtkRenderer ren = new vtkRenderer();
		  vtkRenderWindow renWin = new vtkRenderWindow();
		  renWin.AddRenderer(ren);
		  vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
		  iren.SetRenderWindow(renWin);
	      
		   // Visualise the arrow
		   ren.AddActor2D(textActorL);
		   ren.AddActor2D(textActorC);
		   ren.AddActor2D(textActorR);
		   ren.AddActor2D(singleLineTextActorB);
		   ren.AddActor2D(singleLineTextActorC);
		   ren.AddActor2D(singleLineTextActorT);
		   ren.AddActor2D(GridActor);
		   ren.SetBackground(BgColor);
	      
	           renWin.SetSize(500,500);
	           renWin.Render();

	           iren.Initialize();
	           iren.Start();

	  }
} 
