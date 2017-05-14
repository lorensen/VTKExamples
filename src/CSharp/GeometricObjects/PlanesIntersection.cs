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
            PlanesIntersection();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void PlanesIntersection() {
         vtkSphereSource sphereSource = vtkSphereSource.New();
         sphereSource.Update();

         double[] bounds = new double[6];
         bounds = sphereSource.GetOutput().GetBounds();

         vtkPoints box = vtkPoints.New();

         box.SetNumberOfPoints(8);

         double xMin, xMax, yMin, yMax, zMin, zMax;
         xMin = bounds[0]; xMax = bounds[1];
         yMin = bounds[2]; yMax = bounds[3];
         zMin = bounds[4]; zMax = bounds[5];

         box.SetPoint(0, xMax, yMin, zMax);
         box.SetPoint(1, xMax, yMin, zMin);
         box.SetPoint(2, xMax, yMax, zMin);
         box.SetPoint(3, xMax, yMax, zMax);
         box.SetPoint(4, xMin, yMin, zMax);
         box.SetPoint(5, xMin, yMin, zMin);
         box.SetPoint(6, xMin, yMax, zMin);
         box.SetPoint(7, xMin, yMax, zMax);

         vtkPlanesIntersection planesIntersection = vtkPlanesIntersection.New();
         planesIntersection.SetBounds(bounds[0], bounds[1], bounds[2], bounds[3], bounds[4], bounds[5]);
         int intersects = planesIntersection.IntersectsRegion(box);
         Debug.WriteLine("Intersects? " + ( ( intersects == 1 ) ? true : false ).ToString());
         // nothing to visualize
      }
   }
}
