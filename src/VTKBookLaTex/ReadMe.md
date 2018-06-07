# VTK TextBook

## Introduction

These LaTex files generate the VTK textbook as a PDF. **lualatex** and **biber** are used to generate the PDF.

The master document is  `VTKTextBook.tex`.

The process is documented in these scripts:

- `MakeDocument.bash` and `MakeDocument.cmd`.
- `Clean.bash` and `Clean.cmd`.

Running `MakeDocument` will generate the PDF.

## Editors used

[TexStudio](https://www.texstudio.org/) is used to edit/build the document.

if setting up TexStudio, remember to go to  **Configure TeXstudio|Build** and change the **Default Compiler** to `LuaLaTex` and the **Default Bibliography Tool** to `Biber`.

[JabRef](http://www.jabref.org/) is used to maintain the bibliography.

## Procedure for adding/editing chapters

1. When starting a chapter, copy the relevant figures across from `src/VTKBook/Figures` into `src/VTKLaTex/Figures`. After that just add figures into `src/VTKLaTex/Figures`.

2. Do the bibliography at the end of the chapter using JabRef (load the existing `Bibliography.bib` first) and then do the Bibliographic Notes section to confirm all references are correct.

3. Where examples exist in https://lorensen.github.io/VTKExamples/site/VTKBookFigures/ these are added to  `src/VTKLaTex/Figures` and  `src/VTKLaTex/Figures/ReadMe.md` is updated with the figure name and the path to the testing image. The intent is to create a script to ensure the figures are in sync with the testing images.

4. If there is no drawing or figure available th scrape it from the original pdf and place it in  `src/VTKLaTex/Figures/Scraped`. When better images become available they are placed into  `src/VTKLaTex/Figures` and the corresponding image in  `src/VTKLaTex/Figures/Scraped` is removed.

5. For equations use Bernard's excellent work in `Equations.txt` with one minor change, instead of `\vec{v}` use `\overrightarrow{v\ }` to improve appearances. At the end of each equation you need to add the following line:

    ```
    \myequations{Description of the Equation}
    ```
    This means the equation listings will have a short description for each equation.

6. For code listings add a short description. See Chapter 12 for examples.

7. In doing the chapter you will find references to pages and sections in other chapters. As these occur, add the relevant labels into the other chapters. 

## Indexing
When indexing make sure all sections/subsections/subsubsections when indexed use a page range.

```
\section{some section}
\index{some section|(}
    ... lots of text ...
\index{some section|)}
```

## ToDo

Here we list tasks that need to be done.

### General

 1. Create a script to copy and rename the VTKExamples test files into the Figures dub directory. See `src/VTKLaTex/Figures/ReadMe.md` for a list of files chapter by chapter. This script wil need to be callable from `Admin/ScrapeRepo` in the section **# Copy VTKBookLaTex files**.

 2. Better versions of the files in `Figures/Scraped` will be needed for publication quality. When a new version is made it should go into `Figures` and the correspond one in `Fiugures/Scraped` removed.

 3. Figures will need adjustment.

 4. Figures in `Figures` will need to be reviewed and better versions provided.

 5. Improve layout.
