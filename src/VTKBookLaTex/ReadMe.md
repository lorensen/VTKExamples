# VTK TextBook

## Introduction

These LaTex files generate the VTK textbook as a PDF. **lualatex** and **biber** are used to generate the PDF.

The master document is  `VTKTextBook.tex`.

The process is documented in these scripts:

- `MakeDocument.bash` and `MakeDocument.cmd`.
- `Clean.bash` and `Clean.cmd`.

Running `MakeDocument` will generate the PDF. 

## [TexStudio](https://www.texstudio.org/)

This LaTex editor/builder seems to work quite well.

### Setup

In **Configure TeXstudio|Build** change the **Default Compiler** to `LuaLaTex` and the **Default Bibliography Tool** to `Biber`.

## [LaTexDraw](http://latexdraw.sourceforge.net/)

Maybe useful for producing the drawings.

## ToDo

### Introduction

Here we list tasks that need to be done.

### General

 1. Create a script to copy and rename the VTKExamples test files into the Figures dub directory. See ReadMe.md in this directory for a list of files chapter by chapter. This script wil need to be callable from `Admin/ScrapeRepo` in the section **# Copy VTKBookLaTex files**.

 2. Better versions of the files in `Figures/Scraped` will be needed for publication quality. When a new version is made it should go into `Figures` and the correspond one in `Fugures/Scraped` removed.

 3. Bibliographic links - need to work out hou to get the BibTexKey instead of a number displayed in the text. e.g. instead of `[1]` we need `[Nielson90]`.

 Following is a chapter by chapter list of tasks.

### Chapter 03

- Fig 3.28 needs adjustment.

- Fig 3-30: Code needs to be written to generate these figures. I suggest `RotateCow.cxx` and `RotateCow.py` based on `https://lorensen.github.io/VTKExamples/site/Cxx/Rendering/Rotations/`, alternatively `Rotations.cxx` and `Rotations.py` could be modified. I would like the colours to match those in Fig 3-31 and Fig-3-32.

### Chapter 06

- Figure 6.3: Code needs to be written to generate the four plates here. `Rainbow.cxx`and `Rainbow.py`already exist.

- Figure 6.6: Modify `MarchingCasesA` so that the last two cases are centered and the black backgrounds are changed to match the other backgrounds.

- Figure 6-10: Modify `MarchingCasesB` so that the last two cases are centered and the black backgrounds are changed to match the other backgrounds.

- Figure 6.25: Need the alternate view here.