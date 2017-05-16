If you want to use [VTK Examples](https://gitlab.kitware.com/lorensen/VTKExamples/wikis/home) you have several options. If you are a Wiki Example Developer, [go here](../Instructions/ForDevelopers) or a Wiki Example Administrator [go here](../Instructions/ForAdministrators).

## Build an example

At the bottom of each example page, there are instructions on how to build the example.

## Build all of the examples

If you are really getting excited about learning VTK and are tried of
downloading individual examples you can build them all.

1. As a VTK Remote module
   When you configure your VTK build, set Module_WikiExamples:BOOL=ON and rebuild VTK.

2. Download a [zip](https://gitlab.kitware.com/lorensen/VTKExamples/repository/archive.zip?ref=master)
or [tar](https://gitlab.kitware.com/lorensen/VTKExamples/repository/archive.tar.gz?ref=master) file containing the source

3. Clone the VTK examples repository

   `   git clone https://lorensen@gitlab.kitware.com/lorensen/VTKExamples.git
   `

### Update the examples repository

If you cloned the examples repository, you can get the latest updates:

`
cd VTKWikiExamples
git pull https://github.com/lorensen/VTKWikiExamples.git
cd ../VTKWikiExamples-build
cmake ../VTKWikiExamples
make
`

###Run all of the examples

`
ctest
`
