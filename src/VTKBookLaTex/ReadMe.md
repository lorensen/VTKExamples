# VTK TextBook

These LaTex files generate the VTK textbook as a PDF. **lualatex** and **biber** are used to generate the PDF.

The master document is **VTKTextBook.tex**.

The process is:

```
lualatex VTKTextBook
biber VTKTextBook
lualatex VTKTextBook
lualatex VTKTextBook
```

## Texmaker

- In **Options|Commands**:

    - Set **Bib(la)tex** to `biber %`

- In **Options|Quick Build**

    - Select **User** and enter the following line:

      ```
      lualatex -interaction=nonstopmode %.tex|biber %|lualatex -interaction=nonstopmode %.tex|lualatex -interaction=nonstopmode %.tex
      ```