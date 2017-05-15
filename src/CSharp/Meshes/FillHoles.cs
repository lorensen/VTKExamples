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
            FillHoles(null);
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void FillHoles(string filePath) {
         vtkPolyData input = vtkPolyData.New();
         if(filePath == null) {
            GenerateData(ref input);
         }
         else {
         vtkXMLPolyDataReader reader = vtkXMLPolyDataReader.New();
         reader.SetFileName(filePath);
         reader.Update();

         input.ShallowCopy(reader.GetOutput());
         }

         vtkFillHolesFilter fillHolesFilter = vtkFillHolesFilter.New();
#if VTK_MAJOR_VERSION_5
         fillHolesFilter.SetInputConnection(input.GetProducerPort());
#else
         fillHolesFilter.SetInputData(input);
#endif

         fillHolesFilter.Update();

         // Create a mapper and actor
         vtkPolyDataMapper originalMapper = vtkPolyDataMapper.New();
#if VTK_MAJOR_VERSION_5
         originalMapper.SetInputConnection(input.GetProducerPort());
#else
         originalMapper.SetInputData(input);
#endif

         vtkActor originalActor = vtkActor.New();
         originalActor.SetMapper(originalMapper);

         vtkPolyDataMapper filledMapper = vtkPolyDataMapper.New();
         filledMapper.SetInputConnection(fillHolesFilter.GetOutputPort());

         vtkActor filledActor = vtkActor.New();
         filledActor.SetMapper(filledMapper);

         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         this.Size = new System.Drawing.Size(612, 352);

         // Define viewport ranges
         // (xmin, ymin, xmax, ymax)
         double[] leftViewport = new double[] { 0.0, 0.0, 0.5, 1.0 };
         double[] rightViewport = new double[] { 0.5, 0.0, 1.0, 1.0 };

         // Setup both renderers
         vtkRenderer leftRenderer = vtkRenderer.New();
         renderWindow.AddRenderer(leftRenderer);
         leftRenderer.SetViewport(leftViewport[0], leftViewport[1], leftViewport[2], leftViewport[3]);
         leftRenderer.SetBackground(.6, .5, .4);

         vtkRenderer rightRenderer = vtkRenderer.New();
         renderWindow.AddRenderer(rightRenderer);
         rightRenderer.SetViewport(rightViewport[0], rightViewport[1], rightViewport[2], rightViewport[3]);
         rightRenderer.SetBackground(.4, .5, .6);

         // Add the sphere to the left and the cube to the right
         leftRenderer.AddActor(originalActor);
         rightRenderer.AddActor(filledActor);
         leftRenderer.ResetCamera();
         rightRenderer.ResetCamera();
         renderWindow.Render();
      }


      void GenerateData(ref vtkPolyData input)
      {
        // Create a sphere
        vtkSphereSource sphereSource = vtkSphereSource.New();
        sphereSource.Update();

        // Remove some cells
        vtkIdTypeArray ids = vtkIdTypeArray.New();
        ids.SetNumberOfComponents(1);

        // Set values
        ids.InsertNextValue(2);
        ids.InsertNextValue(10);

        vtkSelectionNode selectionNode = vtkSelectionNode.New();

        selectionNode.SetFieldType((int)vtkSelectionNode.SelectionField.CELL);
        selectionNode.SetContentType((int)vtkSelectionNode.SelectionContent.INDICES);
        selectionNode.SetSelectionList(ids);
        selectionNode.GetProperties().Set(vtkSelectionNode.INVERSE(), 1); //invert the selection

        vtkSelection selection = vtkSelection.New();
        selection.AddNode(selectionNode);

        vtkExtractSelection extractSelection = vtkExtractSelection.New();
        extractSelection.SetInputConnection(0, sphereSource.GetOutputPort());
#if VTK_MAJOR_VERSION_5
        extractSelection.SetInput(1, selection);
#else
        extractSelection.SetInputData(1, selection);
#endif
        extractSelection.Update();

        // In selection
        vtkDataSetSurfaceFilter surfaceFilter = vtkDataSetSurfaceFilter.New();
        surfaceFilter.SetInputConnection(extractSelection.GetOutputPort());
        surfaceFilter.Update();

        input.ShallowCopy(surfaceFilter.GetOutput());
      }
   }
}
