using System;

using Kitware.VTK;

namespace ActiViz.Examples {
   class Program {
      static void Main(string[] args) {
         FindAllArrayNames(null);
         Console.WriteLine("\nPress any key to continue...");
         Console.ReadKey();
      }


     private static void FindAllArrayNames(string filePath) {
         vtkPolyData polydata = vtkPolyData.New();

         if(filePath == null) {
            vtkSphereSource sphereSource = vtkSphereSource.New();
            sphereSource.Update();
            vtkXMLPolyDataWriter writer = vtkXMLPolyDataWriter.New();
            writer.SetFileName(@"c:\vtk\vtkdata-5.8.0\Data\testFindAllArrayNames.vtp");
            writer.SetInputConnection(sphereSource.GetOutputPort());
            writer.Write();
            polydata = sphereSource.GetOutput();
         }
         else {
            vtkXMLPolyDataReader reader = vtkXMLPolyDataReader.New();
            reader.SetFileName(filePath);
            reader.Update();
            polydata = reader.GetOutput();
         }
         FindAllData(ref polydata);
      }


      private static void FindAllData(ref vtkPolyData polydata) {
         Console.WriteLine("Normals: " + polydata.GetPointData().GetNormals());

         int numberOfPointArrays = polydata.GetPointData().GetNumberOfArrays();
         Console.WriteLine("Number of PointData arrays: " + numberOfPointArrays);

         int numberOfCellArrays = polydata.GetCellData().GetNumberOfArrays();
         Console.WriteLine("Number of CellData arrays: " + numberOfCellArrays);

         Console.WriteLine(
            Environment.NewLine + 
            "Type table/key: " + 
            Environment.NewLine + 
            "-------------------------");
         //more values can be found in <VTK_DIR>/Common/vtkSetGet.h

         Console.WriteLine(3 + " unsigned char");
         Console.WriteLine(7 + " unsigned int");
         Console.WriteLine(10 + " float");
         Console.WriteLine(11 + " double" + Environment.NewLine);

         for(int i = 0; i < numberOfPointArrays; i++) {
            // The following two lines are equivalent
            //arrayNames.push_back(polydata.GetPointData().GetArray(i).GetName());
            //arrayNames.push_back(polydata.GetPointData().GetArrayName(i));
            int dataTypeID = polydata.GetPointData().GetArray(i).GetDataType();
            string dataTypeAsString = polydata.GetPointData().GetArray(i).GetDataTypeAsString();
            Console.WriteLine("Array " + i + ": " 
               + polydata.GetPointData().GetArrayName(i)
               + " (type: " + dataTypeID + ")"
               + " (type as string: " + dataTypeAsString + ")" + Environment.NewLine);
         }

         for(int i = 0; i < numberOfCellArrays; i++) {
            // The following two lines are equivalent
            //polydata.GetPointData().GetArray(i).GetName();
            //polydata.GetPointData().GetArrayName(i);
            int dataTypeID = polydata.GetCellData().GetArray(i).GetDataType();
            string dataTypeAsString = polydata.GetPointData().GetArray(i).GetDataTypeAsString();
            Console.WriteLine("Array " + i + ": "
               + polydata.GetCellData().GetArrayName(i)
               + " (type: " + dataTypeID + ")"
               + " (type as string: " + dataTypeAsString + ")");
         }
      }
    }
}
