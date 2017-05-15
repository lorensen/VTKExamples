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
            OrientedArrow();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void OrientedArrow() {
         //Create an arrow.
         vtkArrowSource arrowSource = vtkArrowSource.New();

         // Generate a random start and end point
         vtkMath.RandomSeed(8775070);
         double[] startPoint = new double[]{
            vtkMath.Random(-10,10),
            vtkMath.Random(-10,10),
            vtkMath.Random(-10,10)
         };

         double[] endPoint = new double[]{
            vtkMath.Random(-10,10),
            vtkMath.Random(-10,10),
            vtkMath.Random(-10,10)
         };

         // Compute a basis
         double[] normalizedX = new double[3];
         double[] normalizedY = new double[3];
         double[] normalizedZ = new double[3];

         // The X axis is a vector from start to end
         myMath.Subtract(endPoint, startPoint, ref normalizedX);
         double length = myMath.Norm(normalizedX);
         myMath.Normalize(ref normalizedX);

         // The Z axis is an arbitrary vector cross X
         double[] arbitrary = new double[]{
            vtkMath.Random(-10,10),
            vtkMath.Random(-10,10),
            vtkMath.Random(-10,10)
         };
         myMath.Cross(normalizedX, arbitrary, ref normalizedZ);
         myMath.Normalize(ref normalizedZ);
         // The Y axis is Z cross X
         myMath.Cross(normalizedZ, normalizedX, ref normalizedY);
         vtkMatrix4x4 matrix = vtkMatrix4x4.New();

         // Create the direction cosine matrix
         matrix.Identity();
         for(int i = 0; i < 3; i++) {
            matrix.SetElement(i, 0, normalizedX[i]);
            matrix.SetElement(i, 1, normalizedY[i]);
            matrix.SetElement(i, 2, normalizedZ[i]);
         }

         // Apply the transforms
         vtkTransform transform = vtkTransform.New();
         transform.Translate(startPoint[0], startPoint[1], startPoint[2]);
         transform.Concatenate(matrix);
         transform.Scale(length, length, length);


         //Create a mapper and actor for the arrow
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
         vtkActor actor = vtkActor.New();
#if USER_MATRIX
         mapper.SetInputConnection(arrowSource.GetOutputPort());
         actor.SetUserMatrix(transform.GetMatrix());
#else
         // Transform the polydata
         vtkTransformPolyDataFilter transformPD = vtkTransformPolyDataFilter.New();
         transformPD.SetTransform(transform);
         transformPD.SetInputConnection(arrowSource.GetOutputPort());
         mapper.SetInputConnection(transformPD.GetOutputPort());
#endif
         actor.SetMapper(mapper);

         // Create spheres for start and end point
         vtkSphereSource sphereStartSource = vtkSphereSource.New();
         sphereStartSource.SetCenter(startPoint[0], startPoint[1], startPoint[2]);
         vtkPolyDataMapper sphereStartMapper = vtkPolyDataMapper.New();
         sphereStartMapper.SetInputConnection(sphereStartSource.GetOutputPort());
         vtkActor sphereStart = vtkActor.New();
         sphereStart.SetMapper(sphereStartMapper);
         sphereStart.GetProperty().SetColor(1.0, 1.0, .3);

         vtkSphereSource sphereEndSource = vtkSphereSource.New();
         sphereEndSource.SetCenter(endPoint[0], endPoint[1], endPoint[2]);
         vtkPolyDataMapper sphereEndMapper = vtkPolyDataMapper.New();
         sphereEndMapper.SetInputConnection(sphereEndSource.GetOutputPort());
         vtkActor sphereEnd = vtkActor.New();
         sphereEnd.SetMapper(sphereEndMapper);
         sphereEnd.GetProperty().SetColor(1.0, .3, .3);

         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         renderer.SetBackground(0.2, 0.3, 0.4);
         renderer.AddActor(actor);
         renderer.AddActor(sphereStart);
         renderer.AddActor(sphereEnd);
         renderer.ResetCamera();
      }
   }


   // I'm using my own math class
   // reason: due to the fact that ActiViz wraps native, unmanaged functions in class vtkMath
   // many of the arguments like double arrays (for vector definition) has to be passed by an IntPtr.
   //
   // But there do exist some managed open source math libraries of professional quality, that it
   // should be not a problem at all using another math library for vector algebra.
   //   
   // vtkmath could be used for vetor algebra, no doubt, but then functions which heavily relies on 
   // vector algebra like dot or cross product, etc. would be full of Marshaling code.

   public class myMath {
      public static void Subtract(double[] a, double[] b, ref double[] c) {
         c[0] = a[0] - b[0];
         c[1] = a[1] - b[1];
         c[2] = a[2] - b[2];
      }


      public static double Norm(double[] x) {
         return Math.Sqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);
      }


      public static void Normalize(ref double[] x) {
         double length = Norm(x);
         x[0] /= length;
         x[1] /= length;
         x[2] /= length;
      }

      public static void Cross(double[] x, double[] y, ref double[] z) {
         z[0] = ( x[1] * y[2] ) - ( x[2] * y[1] );
         z[1] = ( x[2] * y[0] ) - ( x[0] * y[2] );
         z[2] = ( x[0] * y[1] ) - ( x[1] * y[0] );
      }
   }

}
