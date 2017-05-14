### Description
This example creates a 3x3 table. The columns MUST be added first - if you attempt to call AddRow type functions, they will not do anything (or produce errors) because the table still has 0 columns until you tell it otherwise. This example adds 3 empty columns to the table, then goes back and fills them in. 

Warning: the table does not copy the data, so if you add the SAME column to the table each time, i.e.
<source lang="cpp">
vtkSmartPointer<vtkVariantArray> col = vtkSmartPointer<vtkVariantArray>::New();

col->InsertNextValue(vtkVariant(0.0));
col->InsertNextValue(vtkVariant(0.0));
col->InsertNextValue(vtkVariant(0.0));
table->AddColumn(Col);
table->AddColumn(Col);
table->AddColumn(Col);
</source>

If you modify one of the entries in the table with  Table->SetValue ( r,c, vtkVariant ( counter ) ); after they have all been set to the same column, the rth entry in EVERY column will be changed.
