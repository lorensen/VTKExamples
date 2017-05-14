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
            VectorFieldNonZeroExtraction();
         }
         catch(Exception ex) {
            MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK);
         }
      }


      private void VectorFieldNonZeroExtraction() { 
         // Create an image
         vtkImageData image = vtkImageData.New();
         CreateVectorField(ref image);

         // This filter produces a vtkImageData with an array named "Magnitude"
         vtkImageMagnitude magnitudeFilter = vtkImageMagnitude.New();
         magnitudeFilter.SetInputConnection(image.GetProducerPort());
         magnitudeFilter.Update(); 

         image.GetPointData().AddArray(magnitudeFilter.GetOutput().GetPointData().GetScalars());
         image.GetPointData().SetActiveScalars("Magnitude");

         vtkThresholdPoints thresholdVector = vtkThresholdPoints.New();
         thresholdVector.SetInput(image);
         thresholdVector.SetInputArrayToProcess(
            0, 
            0, 
            (int)vtkDataObject.FieldAssociations.FIELD_ASSOCIATION_POINTS, 
            (int)vtkDataSetAttributes.AttributeTypes.SCALARS,
            "Magnitude");
         thresholdVector.ThresholdByUpper(0.00001);
         thresholdVector.Update();

         // in case you want to save imageData
         //vtkXMLPolyDataWriter writer = vtkXMLPolyDataWriter.New();
         //writer.SetFileName("output.vtp");
         //writer.SetInputConnection(thresholdPoints.GetOutputPort());
         //writer.Write();

         // repesents the pixels
         vtkCubeSource cubeSource = vtkCubeSource.New();
         cubeSource.SetXLength(2.0);
         cubeSource.SetYLength(2.0);
         cubeSource.SetZLength(2.0);
         vtkGlyph3D glyph = vtkGlyph3D.New();
         glyph.SetInput(image);
         glyph.SetSourceConnection(cubeSource.GetOutputPort());
         // don't scale glyphs according to any scalar data
         glyph.SetScaleModeToDataScalingOff();

         vtkPolyDataMapper glyphMapper = vtkPolyDataMapper.New();
         glyphMapper.SetInputConnection(glyph.GetOutputPort());
         // don't color glyphs according to scalar data
         glyphMapper.ScalarVisibilityOff();
         glyphMapper.SetScalarModeToDefault();

         vtkActor actor = vtkActor.New();
         actor.SetMapper(glyphMapper);

         // represent vector field
         vtkGlyph3D vectorGlyph = vtkGlyph3D.New();
         vtkArrowSource arrowSource = vtkArrowSource.New();
         vtkPolyDataMapper vectorGlyphMapper = vtkPolyDataMapper.New();

         int n = image.GetPointData().GetNumberOfArrays();
         for(int i = 0; i < n; i++) {
            Debug.WriteLine("name of array["+ i + "]: " + image.GetPointData().GetArrayName(i));
         }

         vtkPolyData tmp = thresholdVector.GetOutput();
         Debug.WriteLine("number of thresholded points: " + tmp.GetNumberOfPoints());
         vectorGlyph.SetInputConnection(thresholdVector.GetOutputPort());

         // in case you want the point glyphs to be oriented according to 
         // scalar values in array "ImageScalars" uncomment the following line
         image.GetPointData().SetActiveVectors("ImageScalars");

         vectorGlyph.SetSourceConnection(arrowSource.GetOutputPort());
         vectorGlyph.SetScaleModeToScaleByVector();
         vectorGlyph.SetVectorModeToUseVector();
         vectorGlyph.ScalingOn();
         vectorGlyph.OrientOn();
         vectorGlyph.SetInputArrayToProcess(
            1,
            0,
            (int)vtkDataObject.FieldAssociations.FIELD_ASSOCIATION_POINTS,
            (int)vtkDataSetAttributes.AttributeTypes.SCALARS,
            "ImageScalars");

         vectorGlyph.Update();

         vectorGlyphMapper.SetInputConnection(vectorGlyph.GetOutputPort());
         vectorGlyphMapper.Update();

         vtkActor vectorActor = vtkActor.New();
         vectorActor.SetMapper(vectorGlyphMapper);


         // get a reference to the renderwindow of our renderWindowControl1
         vtkRenderWindow renderWindow = renderWindowControl1.RenderWindow;
         // renderer
         vtkRenderer renderer = renderWindow.GetRenderers().GetFirstRenderer();
         // set background color
         renderer.SetBackground(.2, .6, .3);
         //Add the actors to the renderer, set the background and size 
         renderer.AddActor(actor);
         renderer.AddActor(vectorActor);
      }


      void CreateVectorField(ref vtkImageData image) {
         // Specify the size of the image data
         image.SetDimensions(3, 3, 3);
         image.SetNumberOfScalarComponents(3);
         image.SetScalarTypeToFloat();
         image.AllocateScalars();
         image.SetSpacing(10.0, 10.0, 10.0);
         int[]  dims = image.GetDimensions();

         float[] pixel = new float[] {0.0f, 0.0f, 0.0f};
         IntPtr pPixel;
         
         // Zero the vectors
         for(int z = 0; z < dims[2]; z++) {
            for(int y = 0; y < dims[1]; y++) {
               for(int x = 0; x < dims[0]; x++) {
                  pPixel = image.GetScalarPointer(x, y, 0);
                  Marshal.Copy(pixel, 0, pPixel, 3);
               }
            }
         }

         // Set two of the pixels to non zero values
         pixel[0] = 8.0f;
         pixel[1] = 8.0f;
         pixel[2] = -8.0f;
         pPixel = image.GetScalarPointer(0, 2, 0);
         Marshal.Copy(pixel, 0, pPixel, 3);

         pixel[0] = 8.0f;
         pixel[1] = -8.0f;
         pixel[2] = 8.0f;
         pPixel = image.GetScalarPointer(2, 0, 2);
         Marshal.Copy(pixel, 0, pPixel, 3);
      }
   }
}
