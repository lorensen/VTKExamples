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
            ColoredElevationMap();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void ColoredElevationMap() {
         // Create a grid of points (height/terrian map)
         vtkPoints points = vtkPoints.New();

         uint GridSize = 20;
         double xx, yy, zz;
         for(uint x = 0; x < GridSize; x++) {
            for(uint y = 0; y < GridSize; y++) {
               xx = x + vtkMath.Random(-.2, .2);
               yy = y + vtkMath.Random(-.2, .2);
               zz = vtkMath.Random(-.5, .5);
               points.InsertNextPoint(xx, yy, zz);
            }
         }

         // Add the grid points to a polydata object
         vtkPolyData inputPolyData = vtkPolyData.New();
         inputPolyData.SetPoints(points);

         // Triangulate the grid points
         vtkDelaunay2D delaunay = vtkDelaunay2D.New();
#if VTK_MAJOR_VERSION_5
         delaunay.SetInput(inputPolyData);
#else
         delaunay.SetInputData(inputPolyData);
#endif
         delaunay.Update();
         vtkPolyData outputPolyData = delaunay.GetOutput();

         double[] bounds = outputPolyData.GetBounds();

         // Find min and max z
         double minz = bounds[4];
         double maxz = bounds[5];

         Debug.WriteLine("minz: " + minz);
         Debug.WriteLine("maxz: " + maxz);

         // Create the color map
         vtkLookupTable colorLookupTable = vtkLookupTable.New();
         colorLookupTable.SetTableRange(minz, maxz);
         colorLookupTable.Build();

         // Generate the colors for each point based on the color map
         vtkUnsignedCharArray colors = vtkUnsignedCharArray.New();
         colors.SetNumberOfComponents(3);
         colors.SetName("Colors");

         Debug.WriteLine("There are " + outputPolyData.GetNumberOfPoints()
                   + " points.");


#if UNSAFE // fastest way to fill color array
         colors.SetNumberOfTuples(outputPolyData.GetNumberOfPoints());
         unsafe {
            byte* pColor = (byte*)colors.GetPointer(0).ToPointer();

            for(int i = 0; i < outputPolyData.GetNumberOfPoints(); i++) {
               double[] p = outputPolyData.GetPoint(i);

               double[] dcolor = colorLookupTable.GetColor(p[2]);
               Debug.WriteLine("dcolor: "
                         + dcolor[0] + " "
                         + dcolor[1] + " "
                         + dcolor[2]);

               byte[] color = new byte[3];
               for(uint j = 0; j < 3; j++) {
                  color[j] = (byte)( 255 * dcolor[j] );
               }
               Debug.WriteLine("color: "
                         + color[0] + " "
                         + color[1] + " "
                         + color[2]);

               *( pColor + 3 * i ) = color[0];
               *( pColor + 3 * i + 1 ) = color[1];
               *( pColor + 3 * i + 2 ) = color[2];
            }
         }
#else
         for(int i = 0; i < outputPolyData.GetNumberOfPoints(); i++) {
            double[] p = outputPolyData.GetPoint(i);

            double[] dcolor = colorLookupTable.GetColor(p[2]);
            Debug.WriteLine("dcolor: "
                      + dcolor[0] + " "
                      + dcolor[1] + " "
                      + dcolor[2]);

            byte[] color = new byte[3];
            for(uint j = 0; j < 3; j++) {
               color[j] = (byte)( 255 * dcolor[j] );
            }
            Debug.WriteLine("color: "
                      + color[0] + " "
                      + color[1] + " "
                      + color[2]);
            colors.InsertNextTuple3(color[0], color[1], color[2] );
            //IntPtr pColor = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(byte)) * 3);
            //Marshal.Copy(color, 0, pColor, 3);
            //colors.InsertNextTupleValue(pColor);
            //Marshal.FreeHGlobal(pColor);
         }
#endif

         outputPolyData.GetPointData().SetScalars(colors);

         // Create a mapper and actor
         vtkPolyDataMapper mapper = vtkPolyDataMapper.New();
#if VTK_MAJOR_VERSION_5
         mapper.SetInputConnection(outputPolyData.GetProducerPort());
#else
         mapper.SetInputData(outputPolyData);
#endif

         vtkActor actor = vtkActor.New();
         actor.SetMapper(mapper);

         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(0.2, 0.3, 0.4);
         // add our actor to the renderer
         renderer.AddActor(actor);
      }
   }
}
