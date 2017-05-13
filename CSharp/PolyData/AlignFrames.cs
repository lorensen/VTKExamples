using System;
using System.Runtime.InteropServices;
using Kitware.VTK;

namespace ActiViz.Examples {
   class Program {

      struct Frame {
         private float[] origin;
         private float[] xDirection;
         private float[] yDirection;
         private float[] zDirection;

         internal float[] Origin {
            get { return origin; }
         }

         internal float[] XDirection {
            get { return xDirection; }
         }

         internal float[] YDirection {
            get { return yDirection; }
         }

         internal float[] ZDirection {
            get { return zDirection; }
         }

         internal Frame(float[] origin, float[] xDirection, float[] yDirection, float[] zDirection) {
            this.origin = new float[3];
            this.xDirection = new float[3];
            this.yDirection = new float[3];
            this.zDirection = new float[3];
            origin.CopyTo(this.origin, 0);
            xDirection.CopyTo(this.xDirection, 0);
            yDirection.CopyTo(this.yDirection, 0);
            zDirection.CopyTo(this.zDirection, 0);

            Normalize(ref xDirection);
            Normalize(ref yDirection);
            Normalize(ref zDirection);

            Console.WriteLine("Origin: " + 
               this.origin[0] + " " + 
               this.origin[1] + " " + 
               this.origin[2]);
            Console.WriteLine("xDirection: " + 
               this.xDirection[0] + " " + 
               this.xDirection[1] + " " + 
               this.xDirection[2]);
            Console.WriteLine("yDirection: " + 
               this.yDirection[0] + " " + 
               this.yDirection[1] + " " + 
               this.yDirection[2]);
            Console.WriteLine("zDirection: " + 
               this.zDirection[0] + " " + 
               this.zDirection[1] + " " + 
               this.zDirection[2]);
         }


         private void Normalize(ref float[] vector) {
            IntPtr pDirection = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(float)) * 3);
            Marshal.Copy(vector, 0, pDirection, 3);
            vtkMath.Normalize(pDirection);
            Marshal.FreeHGlobal(pDirection);
         }


         internal void ApplyTransform(ref vtkTransform transform, string filename) {
            vtkPolyData polydata = vtkPolyData.New();
            CreatePolydata(ref polydata);

            vtkTransformFilter transformFilter = vtkTransformFilter.New();
#if VTK_MAJOR_VERSION_5
            transformFilter.SetInputConnection(polydata.GetProducerPort());
#else
            transformFilter.SetInputData(polydata);
#endif
            transformFilter.SetTransform(transform);
            transformFilter.Update();

            vtkXMLPolyDataWriter writer = vtkXMLPolyDataWriter.New();
            writer.SetFileName(filename);
#if VTK_MAJOR_VERSION_5
            writer.SetInputConnection(transformFilter.GetOutputPort());
#else
            writer.SetInputData(transformFilter);
#endif
            writer.Write();
         }


         internal void CreatePolydata(ref vtkPolyData polydata) {
            vtkPoints points = vtkPoints.New();

            points.InsertNextPoint(this.origin[0], this.origin[1], this.origin[2]);

            float[] x = new float[3];
            float[] y = new float[3];
            float[] z = new float[3];
            
            Add(this.origin, this.xDirection, ref x);
            Add(this.origin, this.yDirection, ref y);
            Add(this.origin, this.zDirection, ref z);

            points.InsertNextPoint(x[0], x[1], x[2]);
            points.InsertNextPoint(y[0], y[1], y[2]);
            points.InsertNextPoint(z[0], z[1], z[2]);

            polydata.SetPoints(points);

            vtkVertexGlyphFilter vertexGlyphFilter = vtkVertexGlyphFilter.New();
#if VTK_MAJOR_VERSION_5
            vertexGlyphFilter.AddInput(polydata);
#else
            vertexGlyphFilter.AddInputData(polydata);
#endif
            vertexGlyphFilter.Update();
            polydata.ShallowCopy(vertexGlyphFilter.GetOutput());
         }


         internal void Write(string filename) {
            vtkPolyData polydata = vtkPolyData.New();
            CreatePolydata(ref polydata);

            vtkXMLPolyDataWriter writer = vtkXMLPolyDataWriter.New();
            writer.SetFileName(filename);
#if VTK_MAJOR_VERSION_5
            writer.SetInputConnection(polydata.GetProducerPort());
#else
            writer.SetInputData(polydata);
#endif
            writer.Write();
         }
      }


      static void Main(string[] args) {
         float[] frame1origin = new float[] { 0, 0, 0 };
         float[] frame1XDirection = new float[] { 1, 0, 0 };
         float[] frame1YDirection = new float[] { 0, 1, 0 };
         Console.WriteLine(frame1YDirection[0] + " " + frame1YDirection[1] + " " + frame1YDirection[2]);
         float[] frame1ZDirection = new float[] { 0, 0, 1 };
         Frame frame1 = new Frame(frame1origin, frame1XDirection, frame1YDirection, frame1ZDirection);
         Console.WriteLine("\nWriting frame1.vtp...");
         // adjust path
         frame1.Write(@"c:\vtk\vtkdata-5.8.0\Data\frame1.vtp");

         float[] frame2origin = new float[] { 0, 0, 0 };
         float[] frame2XDirection = new float[] { .707f, .707f, 0 };
         float[] frame2YDirection = new float[] { -.707f, .707f, 0 };
         float[] frame2ZDirection = new float[] { 0, 0, 1 };
         Frame frame2 = new Frame(frame2origin, frame2XDirection, frame2YDirection, frame2ZDirection);
         Console.WriteLine("\nWriting frame2.vtp...");
         // adjust path
         frame2.Write(@"c:\vtk\vtkdata-5.8.0\Data\frame2.vtp");

         vtkTransform transform = vtkTransform.New();
         AlignFrames(frame2, frame1, ref transform); // Brings frame2 to frame1

         Console.WriteLine("\nWriting transformed.vtp...");
         // adjust path
         frame2.ApplyTransform(ref transform, @"c:\vtk\vtkdata-5.8.0\Data\transformed.vtp");

         Console.WriteLine("\nPress any key to continue...");
         Console.ReadKey();
      }


      static void AlignFrames(Frame sourceFrame, Frame targetFrame, ref vtkTransform transform) {
         // This function takes two frames and finds the matrix M between them.
         vtkLandmarkTransform landmarkTransform = vtkLandmarkTransform.New();

         // Setup source points
         vtkPoints sourcePoints = vtkPoints.New();

         sourcePoints.InsertNextPoint(
            sourceFrame.Origin[0], 
            sourceFrame.Origin[1], 
            sourceFrame.Origin[2]);

         float[] sourceX = new float[3];
         float[] sourceY = new float[3];
         float[] sourceZ = new float[3];
         
         Add(sourceFrame.Origin, sourceFrame.XDirection, ref sourceX);
         Add(sourceFrame.Origin, sourceFrame.YDirection, ref sourceY);
         Add(sourceFrame.Origin, sourceFrame.ZDirection, ref sourceZ);

         sourcePoints.InsertNextPoint(sourceX[0], sourceX[1], sourceX[2]);
         sourcePoints.InsertNextPoint(sourceY[0], sourceY[1], sourceY[2]);
         sourcePoints.InsertNextPoint(sourceZ[0], sourceZ[1], sourceZ[2]);

         // Setup target points
         vtkPoints targetPoints = vtkPoints.New();
         targetPoints.InsertNextPoint(targetFrame.Origin[0], targetFrame.Origin[1], targetFrame.Origin[2]);

         float[] targetX = new float[3];
         float[] targetY = new float[3];
         float[] targetZ = new float[3];

         Add(targetFrame.Origin, targetFrame.XDirection, ref targetX);
         Add(targetFrame.Origin, targetFrame.YDirection, ref targetY);
         Add(targetFrame.Origin, targetFrame.ZDirection, ref targetZ);

         targetPoints.InsertNextPoint(targetX[0], targetX[1], targetX[2]);
         targetPoints.InsertNextPoint(targetY[0], targetY[1], targetY[2]);
         targetPoints.InsertNextPoint(targetZ[0], targetZ[1], targetZ[2]);

         landmarkTransform.SetSourceLandmarks(sourcePoints);
         landmarkTransform.SetTargetLandmarks(targetPoints);
         landmarkTransform.SetModeToRigidBody();
         landmarkTransform.Update();

         vtkMatrix4x4 M = landmarkTransform.GetMatrix();
         transform.SetMatrix(M);
      }

      // helper function
      static void Add(float[] vec1, float[] vec2, ref float[] vec) {
         vec[0] = vec1[0] + vec2[0];
         vec[1] = vec1[1] + vec2[1];
         vec[2] = vec1[2] + vec2[2];
      }
   }
}
