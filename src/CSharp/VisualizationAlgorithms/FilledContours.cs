using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Windows.Forms;
using System.Diagnostics;

using Kitware.VTK;

namespace ActiViz.Examples {
   public partial class Form1 : Form {
      public Form1() {
         InitializeComponent();
      }


      private void renderWindowControl1_Load(object sender, EventArgs e) {
         try {
            FilledContours(@"c:\vtk\vtkdata-5.8.0\Data\filledContours.vtp", 10);
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void FilledContours(string filePath, int numberOfContours) {
         // Read the file
         vtkXMLPolyDataReader reader = vtkXMLPolyDataReader.New();

         reader.SetFileName(filePath);
         reader.Update(); // Update so that we can get the scalar range

         double[] scalarRange = reader.GetOutput().GetPointData().GetScalars().GetRange();

         vtkAppendPolyData appendFilledContours = vtkAppendPolyData.New();

         double delta = ( scalarRange[1] - scalarRange[0] ) / ( numberOfContours - 1 );

         // Keep the clippers alive
         List<vtkClipPolyData>  clippersLo = new List<vtkClipPolyData>();
         List<vtkClipPolyData>  clippersHi = new List<vtkClipPolyData>();

         for(int i = 0; i < numberOfContours; i++) {
            double valueLo = scalarRange[0] + i * delta;
            double valueHi = scalarRange[0] + ( i + 1 ) * delta;

            clippersLo.Add(vtkClipPolyData.New());
            clippersLo[i].SetValue(valueLo);
            if(i == 0) {
               clippersLo[i].SetInputConnection(reader.GetOutputPort());
            }
            else {
               clippersLo[i].SetInputConnection(clippersHi[i - 1].GetOutputPort(1));
            }
            clippersLo[i].InsideOutOff();
            clippersLo[i].Update();

            clippersHi.Add(vtkClipPolyData.New());
            clippersHi[i].SetValue(valueHi);
            clippersHi[i].SetInputConnection(clippersLo[i].GetOutputPort());
            clippersHi[i].GenerateClippedOutputOn();
            clippersHi[i].InsideOutOn();
            clippersHi[i].Update();
            if(clippersHi[i].GetOutput().GetNumberOfCells() == 0) {
               continue;
            }

            vtkFloatArray cd = vtkFloatArray.New();
            cd.SetNumberOfComponents(1);
            cd.SetNumberOfTuples(clippersHi[i].GetOutput().GetNumberOfCells());
            cd.FillComponent(0, valueLo);

            clippersHi[i].GetOutput().GetCellData().SetScalars(cd);
            appendFilledContours.AddInputConnection(clippersHi[i].GetOutputPort());
         }

         vtkCleanPolyData filledContours = vtkCleanPolyData.New();
         filledContours.SetInputConnection(appendFilledContours.GetOutputPort());

         vtkLookupTable lut = vtkLookupTable.New();
         lut.SetNumberOfTableValues(numberOfContours + 1);
         lut.Build();
         vtkPolyDataMapper contourMapper = vtkPolyDataMapper.New();
         contourMapper.SetInputConnection(filledContours.GetOutputPort());
         contourMapper.SetScalarRange(scalarRange[0], scalarRange[1]);
         contourMapper.SetScalarModeToUseCellData();
         contourMapper.SetLookupTable(lut);

         vtkActor contourActor = vtkActor.New();
         contourActor.SetMapper(contourMapper);
         contourActor.GetProperty().SetInterpolationToFlat();

         vtkContourFilter contours = vtkContourFilter.New();
         contours.SetInputConnection(filledContours.GetOutputPort());
         contours.GenerateValues(numberOfContours, scalarRange[0], scalarRange[1]);

         vtkPolyDataMapper contourLineMapperer = vtkPolyDataMapper.New();
         contourLineMapperer.SetInputConnection(contours.GetOutputPort());
         contourLineMapperer.SetScalarRange(scalarRange[0], scalarRange[1]);
         contourLineMapperer.ScalarVisibilityOff();

         vtkActor contourLineActor = vtkActor.New();
         contourLineActor.SetMapper(contourLineMapperer);
         contourLineActor.GetProperty().SetLineWidth(2);

         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(.2, .3, .4);
         // add our actor to the renderer
         renderer.AddActor(contourActor);
         renderer.AddActor(contourLineActor);
      }
   }
}
