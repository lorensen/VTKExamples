using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

using Kitware.VTK;

namespace ActiViz.Examples {
   public partial class Form1 : Form {
      public Form1() {
         InitializeComponent();
      }


      private void renderWindowControl1_Load(object sender, EventArgs e) {
         try {
            ReadPDB();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void ReadPDB() {
         // Path to vtk data must be set as an environment variable
         // VTK_DATA_ROOT = "C:\VTK\vtkdata-5.8.0"
         vtkTesting test = vtkTesting.New();
         string root = test.GetDataRoot();
         string filePath = System.IO.Path.Combine(root, @"Data\caffeine.pdb");

         vtkPDBReader pdb = vtkPDBReader.New();
         pdb.SetFileName(filePath);
         pdb.SetHBScale(1.0);
         pdb.SetBScale(1.0);
         pdb.Update();
         Debug.WriteLine("# of atoms is: " + pdb.GetNumberOfAtoms());
         // if molecule contains a lot of atoms, reduce the resolution of the sphere (represents an atom) for faster rendering
         int resolution = (int)Math.Floor(Math.Sqrt(300000.0 / pdb.GetNumberOfAtoms())); // 300000.0 is an empriric value
         if(resolution > 20)
            resolution = 20;
         else if(resolution < 4)
            resolution = 4;

         Debug.WriteLine("Resolution is: " + resolution);
         vtkSphereSource sphere = vtkSphereSource.New();
         sphere.SetCenter(0, 0, 0);
         sphere.SetRadius(1);
         sphere.SetThetaResolution(resolution);
         sphere.SetPhiResolution(resolution);

         vtkGlyph3D glyph = vtkGlyph3D.New();
         glyph.SetInputConnection(pdb.GetOutputPort());
         glyph.SetOrient(1);
         glyph.SetColorMode(1);
         // glyph.ScalingOn();
         glyph.SetScaleMode(2);
         glyph.SetScaleFactor(.25);
         glyph.SetSourceConnection(sphere.GetOutputPort());

         vtkPolyDataMapper atomMapper = vtkPolyDataMapper.New();
         atomMapper.SetInputConnection(glyph.GetOutputPort());
         atomMapper.ImmediateModeRenderingOn();
         atomMapper.UseLookupTableScalarRangeOff();
         atomMapper.ScalarVisibilityOn();
         atomMapper.SetScalarModeToDefault();

         vtkLODActor atom = vtkLODActor.New();
         atom.SetMapper(atomMapper);
         atom.GetProperty().SetRepresentationToSurface();
         atom.GetProperty().SetInterpolationToGouraud();
         atom.GetProperty().SetAmbient(0.15);
         atom.GetProperty().SetDiffuse(0.85);
         atom.GetProperty().SetSpecular(0.1);
         atom.GetProperty().SetSpecularPower(30);
         atom.GetProperty().SetSpecularColor(1, 1, 1);
         atom.SetNumberOfCloudPoints(30000);


         vtkTubeFilter tube = vtkTubeFilter.New();
         tube.SetInputConnection(pdb.GetOutputPort());
         tube.SetNumberOfSides(resolution);
         tube.CappingOff();
         tube.SetRadius(0.2);
         // turn off variation of tube radius with scalar values
         tube.SetVaryRadius(0);
         tube.SetRadiusFactor(10);

         vtkPolyDataMapper bondMapper = vtkPolyDataMapper.New();
         bondMapper.SetInputConnection(tube.GetOutputPort());
         bondMapper.ImmediateModeRenderingOn();
         bondMapper.UseLookupTableScalarRangeOff();
         bondMapper.ScalarVisibilityOff();
         bondMapper.SetScalarModeToDefault();

         vtkLODActor bond = vtkLODActor.New();
         bond.SetMapper(bondMapper);
         bond.GetProperty().SetRepresentationToSurface();
         bond.GetProperty().SetInterpolationToGouraud();
         bond.GetProperty().SetAmbient(0.15);
         bond.GetProperty().SetDiffuse(0.85);
         bond.GetProperty().SetSpecular(0.1);
         bond.GetProperty().SetSpecularPower(30);
         bond.GetProperty().SetSpecularColor(1, 1, 1);
         bond.GetProperty().SetDiffuseColor(1.0000, 0.8941, 0.70981);


         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(0.2, 0.3, 0.4);
         // add our actor to the renderer
         renderer.AddActor(atom);
         renderer.AddActor(bond);
      }
   }
}
