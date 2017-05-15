package require vtk

if { $argc != 2 } {
  puts "The command requires 2 arguments."
  puts "Please try again."
  exit
}

set folder [lindex $argv 0]
set outputFile [lindex $argv 1]

# Read all the DICOM files in the specified directory.
vtkDICOMImageReader reader
reader SetDirectoryName $folder
reader Update

set imagedata [reader GetOutput]

vtkXMLImageDataWriter writer
writer SetInput [reader GetOutput]
writer SetFileName $outputFile
writer Update

puts "Output file ( $outputFile ) has been correctly saved."
