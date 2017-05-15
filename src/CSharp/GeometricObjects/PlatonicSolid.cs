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
            PlatonicSolid();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void PlatonicSolid() {
         vtkPlatonicSolidSource platonicSolidSource = vtkPlatonicSolidSource.New();
         platonicSolidSource.SetSolidTypeToOctahedron();

         // Each face has a different cell scalar
         vtkLookupTable lut = vtkLookupTable.New();
         lut.SetNumberOfTableValues(8);
         lut.SetTableRange(0.0, 7.0);
         lut.Build();
         lut.SetTableValue(0, 0, 0, 0, 1);
         lut.SetTableValue(1, 0, 0, 1, 1);
         lut.SetTableValue(2, 0, 1, 0, 1);
         lut.SetTableValue(3, 0, 1, 1, 1);
         lut.SetTableValue(4, 1, 0, 0, 1);
         lut.SetTableValue(5, 1, 0, 1, 1);
         lut.SetTableValue(6, 1, 1, 0, 1);
         lut.SetTableValue(7, 1, 1, 1, 1);

         // Visualize
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         mapper.SetInputConnection(platonicSolidSource.GetOutputPort());
         mapper.SetLookupTable(lut);
         mapper.SetScalarRange(0, 7);

         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         renderer.SetBackground(0.2, 0.3, 0.4);
         renderer.AddActor(actor);
      }
   }
}
