If you want to use [VTK Examples](https://github.com/lorensen/VTKExamples) you have several options. If you are a Wiki Example Developer, [go here](../Instructions/ForDevelopers) or a Wiki Example Administrator [go here](../Instructions/ForAdministrators).

## Build an example

At the bottom of each example page, there are instructions on how to build the example.

## Build all of the examples

If you are really getting excited about learning VTK and are tried of
downloading individual examples you can build them all.

1. As a VTK Remote module
   When you configure your VTK build, set Module_WikiExamples:BOOL=ON and rebuild VTK.

2. Download a [zip](https://github.com/lorensen/VTKExamples/archive/master.zip) containing the source.

3. Clone the VTK examples repository

   `   git clone https://github.com/lorensen/VTKExamples.git
   `

### Update the examples repository

If you cloned the examples repository, you can get the latest updates:

`
cd VTKExamples
git pull
cd ../VTKExamples-build
cmake ../VTKExamples
make
`

###Run all of the examples

`
ctest
`
