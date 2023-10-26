# SillyQL
A relational database language created entirely from scratch, coded in C++.

This project provides a set of functions that mimic some of the basic operations of SQL. These are ideal for those looking to understand the underlying mechanics of database operations without diving deep into a full-fledged SQL environment.

Functions  
1. CREATE  
Description: Initializes a new table with specified columns.  
Usage: CREATE(table_name, [column1, column2, ...])  
2. INSERT  
Description: Adds a new row of data to a specified table.  
Usage: INSERT(table_name, {column1: value1, column2: value2, ...})  
3. JOIN  
Description: Combines rows from two tables based on a related column.  
Usage: JOIN(table1_name, table2_name, shared_column_name)  
4. REMOVE  
Description: Deletes rows from a table based on specified conditions.  
Usage: REMOVE(table_name, {column1: condition1, ...})  
5. PRINT  
Description: Displays the content of a specified table.  
Usage: PRINT(table_name)  
6. GENERATE INDEX  
Description: Creates an index on a specified column to speed up search operations.  
Usage: GENERATE_INDEX(table_name, column_name)  
Getting Started  
To use these functions, simply import the required module and call the desired function as demonstrated in the usage instructions.  

⚠️ WARNING ⚠️

This project is from the EECS 281 course at the University of Michigan and is uploaded for educational and presentation purposes only.

University of Michigan students: Do not copy or use any part of this project for your own EECS 281 assignments or any other coursework. The University of Michigan has strict academic integrity guidelines, and any violation can lead to severe consequences.

For others, while you're welcome to reference or learn from the code, please do not directly copy or plagiarize the content. Always give credit where it's due and respect the effort that went into creating this project.

Thank you for your understanding!
