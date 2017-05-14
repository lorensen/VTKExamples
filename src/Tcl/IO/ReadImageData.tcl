package require vtk

if { $argc != 1 } {
	puts "The command requires 1 argument: InputFileName"
	puts "Please try again."
	exit
}
 
set inputFile [lindex $argv 0]
 
# Read the iamge data from a VTI file
vtkXMLImageDataReader reader
reader SetFileName $inputFile
reader Update
 
# Check for number of points
set imagedata [reader GetOutput]
set numPoints [$imagedata GetNumberOfPoints]
 
if { $numPoints == 0 } {
	puts "Input Image has zero points."
	exit
} else {
	puts "Input Image has $numPoints points"
}
