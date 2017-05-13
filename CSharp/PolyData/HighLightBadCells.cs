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
            HighLightBadCells();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void HighLightBadCells() { 
         vtkSphereSource sphereSource = vtkSphereSource.New();
         sphereSource.Update();

         vtkTriangleFilter triangleFilter = vtkTriangleFilter.New();
         triangleFilter.SetInputConnection(sphereSource.GetOutputPort());
         triangleFilter.Update();

         //Create a mapper and actor
         vtkDataSetMapper sphereMapper = vtkDataSetMapper.New();
         sphereMapper.SetInputConnection(triangleFilter.GetOutputPort());
         vtkActor sphereActor = vtkActor.New();
         sphereActor.SetMapper(sphereMapper);

         vtkPolyData mesh = triangleFilter.GetOutput();
         Debug.WriteLine("There are " + mesh.GetNumberOfCells() + " cells.");

         vtkMeshQuality qualityFilter = vtkMeshQuality.New();
#if VTK_MAJOR_VERSION_5
         qualityFilter.SetInput(mesh);
#else
         qualityFilter.SetInputData(mesh);
#endif
         qualityFilter.SetTriangleQualityMeasureToArea();
         qualityFilter.Update();

         vtkDataSet qualityMesh = qualityFilter.GetOutput();
         vtkDoubleArray qualityArray = vtkDoubleArray.SafeDownCast(qualityMesh.GetCellData().GetArray("Quality"));
         Debug.WriteLine("There are " + qualityArray.GetNumberOfTuples() + " values.");

         for(int i = 0; i < qualityArray.GetNumberOfTuples(); i++) {
            double val = qualityArray.GetValue(i);
            Debug.WriteLine("value " +  i + ": " + val);
         }

         vtkThreshold selectCells = vtkThreshold.New();
         selectCells.ThresholdByLower(.02);
         selectCells.SetInputArrayToProcess( 
            0, 
            0, 
            0,
            1, // POINTS = 0, CELLS = 1, NONE = 2, POINTS_THEN_CELLS = 3, VERTICES = 4, EDGES = 5, ROWS = 6
            0  // SCALARS = 0, VECTORS = 1, NORMALS = 2, TCOORDS = 3, TENSORS = 4, GLOBALIDS = 5, PEDIGREEIDS = 6, EDGEFLAG = 7
            );

#if VTK_MAJOR_VERSION_5
         selectCells.SetInput(qualityMesh);
#else
         selectCells.SetInputData(qualityMesh);
#endif
         selectCells.Update();
         vtkUnstructuredGrid ug = selectCells.GetOutput();

         // Create a mapper and actor
         vtkDataSetMapper mapper = vtkDataSetMapper.New();
#if VTK_MAJOR_VERSION_5
         mapper.SetInput(ug);
#else
         mapper.SetInputData(ug);
#endif
         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);
         actor.GetProperty().SetColor(1.0, 0.0, 0.0);
         actor.GetProperty().SetRepresentationToWireframe();
         actor.GetProperty().SetLineWidth(5);
         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(1.0, 1.0, 1.0);
         // add our actors to the renderer
         renderer.AddActor(actor);
         renderer.AddActor(sphereActor);
      }
   }
}
