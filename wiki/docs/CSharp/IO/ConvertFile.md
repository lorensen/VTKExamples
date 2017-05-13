[VTKExamples](Home)/[CSharp](CSharp)/IO/ConvertFile

### Description
This example demonstrates how to read a file and then write it to a different type of file. In this example, we read a vtp file and write a ply file, but simply by changing the reader/writer classes instantiated, different behavior can be achieved. 

**ConvertFile.cs**
```csharp
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
```
