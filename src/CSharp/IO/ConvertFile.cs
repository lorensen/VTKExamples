using System;
using System.Diagnostics;
using Kitware.VTK;

void ConvertFile() {
   string inputFileName = "test.vtu";
   string outputFileName = "test.ply";

   vtkXMLPolyDataReader reader = vtkXMLPolyDataReader.New();
   reader.SetFileName(inputFileName);
   reader.Update();

   vtkPLYWriter writer = vtkPLYWriter.New();
   writer.SetFileName(outputFileName);
   writer.SetInputConnection(reader.GetOutputPort());
   writer.Update();
}
