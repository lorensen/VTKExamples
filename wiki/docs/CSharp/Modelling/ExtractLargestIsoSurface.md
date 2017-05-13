[VTKExamples](/home/)/[CSharp](/CSharp)/Modelling/ExtractLargestIsoSurface

### Description
* Contributed by: Jinyoung Hwang

This example reads a structured points dataset stored in a .vtk file and constructs a 3D model using vtkMarchingCubes.
vtkPolyDataConnectivityFilter is used to extract the largest isosurface.

Data is available at:
 1. test.vtk: http://web.kaist.ac.kr/~hjy/test.vtk
 2. brainweb.img: http://web.kaist.ac.kr/~hjy/brainweb.img
 3. brainweb.hdr: http://web.kaist.ac.kr/~hjy/brainweb.hdr
Second and third datasets can be downloaded from BrainWeb (http://www.bic.mni.mcgill.ca/brainweb/), which is free of charge in use for a research.
"test.vtk" was converted from "brainweb.img" using a program by Erik Vidholm (http://www.cb.uu.se/~erik/vtk/rawToVTK.cpp).

The examples expects 2 or 3 argments:

 ExtractLargestIsosurface InputFilename Threshold [](ExtractLargest)
  if ExtractLargest is omitted or 1, the largest isosurface is extracted
  if ExtractLargest is 0, all of the isosurfaces are extracted

Try
 ExtractLargestIsosurface test.vtk 50 1
and compare the results to
 ExtractLargestIsosurface test.vtk 50 0

A tutorial on how to setup a Windows Forms Application utilizing ActiViz.NET can be found here: [Setup a Windows Forms Application to use ActiViz.NET](http://www.vtk.org/Wiki/VTK/CSharp/ActiViz.NET)<br />
Note: As long as ActiViz.NET is not build with VTK version 6.0 or higher you must define the preprocessor directive VTK_MAJOR_VERSION_5.

**ExtractLargestIsoSurface.cs**
```csharp
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
            // don't forget to adapt the file path
            ExtractLargestIsoSurface("test.vtk", 50, true);
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void ExtractLargestIsoSurface(string filePath, double threshold, bool extractLargest) { 
         // Load data
         vtkStructuredPointsReader reader = vtkStructuredPointsReader.New();
         reader.SetFileName(filePath);

         // Create a 3D model using marching cubes
         vtkMarchingCubes mc = vtkMarchingCubes.New();
         mc.SetInputConnection(reader.GetOutputPort());
         mc.ComputeNormalsOn();
         mc.ComputeGradientsOn();
         mc.SetValue(0, threshold);  // second value acts as threshold

         // To remain largest region
         vtkPolyDataConnectivityFilter confilter = vtkPolyDataConnectivityFilter.New();
         confilter.SetInputConnection(mc.GetOutputPort());
         confilter.SetExtractionModeToLargestRegion();

         // Create a mapper
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         if(extractLargest) {
            mapper.SetInputConnection(confilter.GetOutputPort());
         }
         else {
            mapper.SetInputConnection(mc.GetOutputPort());
         }

         mapper.ScalarVisibilityOff();    // utilize actor's property I set

         // Visualize
         vtkActor actor = vtkActor.New();
         actor.GetProperty().SetColor(1, 1, 1);
         actor.SetMapper(mapper);

         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // add our actor to the renderer
         renderer.AddActor(actor);
      }
   }
}
```
