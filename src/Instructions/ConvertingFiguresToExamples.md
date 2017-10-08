There is an ongoing effort to convert the examples in the [VTK Book](http://www.kitware.com/products/books/VTKTextbook.pdf) into VTKExamples.

# Process to Convert Figures to Examples

1. Follow the procedure [ForDevelopers](/Instructions/ForDevelopers) to contribute examples.
2. Download a copy of the [VTK Book](http://www.kitware.com/products/books/VTKTextbook.pdf).
3. Look at the [VTKBookFigures](/VTKBookFigures) page and look for examples that have not been converted. These examples will not have a link to source code.
4. Go to your VTK source checkout. Run the script [VTKExamples/src/Admin/getDeletedFile.sh](https://github.com/lorensen/VTKExamples/blob/master/src/Admin/getDeletedFile.sh) with the name of the source file (e.g. walkCow.tcl) in the figure example to be converted. This script will create a source file in the current directory and also report the URL for the original repo location of the example.
5. Pick a source directory to contain the new example. Look at the Chapter heading in the book to guide where to put the new example.
6. Convert the source tcl code or old C++ code to C++ code that will compile and run with the current VTK API. Follow the [guidelines for coding C++ examples](/Instructions/Guidelines).
7. If the figure example name is short, e.g. bluntStr we suggest giving it a more descriptive name e.g. BluntStreamlines. Notice the first letter is uppercase.
7. Edit the [VTKBookFigures page](/VTKBookFigures) as follows:
    1. In the first column of the table, add a link from the Figure to the source code.
    2. In the second column of the table, add the VTK classes that are illustrated by the example.
    3. In the third column, cut and paste the caption from the VTK Book.
    4. If there is a source file mentioned in the caption, make link to the original code URL printed by the *getDeletedFile.sh* script.
