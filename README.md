# SillyQL
A relational database language created entirely from scratch, coded in C++.

This project provides a set of functions that mimic some of the basic operations of SQL. These are ideal for those looking to understand the underlying mechanics of database operations without diving deep into a full-fledged SQL environment. Use of this project is to be done through the command line.

## **Functions**  
Database commands:
1. CREATE  
Description: Creates a new table with N columns (where N > 0). Each column contains data of type <coltype> and is accessed with the name <colname>. Table names and column names are guaranteed to be space-free. No two columns in the same table will have the same name (you do not need to check). Valid data types for coltype are {double, int, bool, string}. This table is initially empty.  
Syntax: ```CREATE <tablename> <N> <coltype1> <coltype2> ... <coltypeN> <colname1> <colname2> ... <colnameN>```  
2. QUIT  
Description: Clears up allocated memory.  
3. REMOVE  
Description: Remove existing table from the database, deleting all data in the table and its definition.  
Syntax: ```REMOVE <tablename>```  

Table commands:
1. INSERT  
Description: Adds a new row of data to a specified table.   
Syntax:  
```
INSERT INTO <tablename> <N> ROWS  
<value11> <value12> ... <value1M>  
<value21> <value22> ... <value2M>  
...  
<valueN1> <valueN2> ... <valueNM>
```  
3. PRINT  
Description: Displays the content of a specified table. Can choose to print specified rows using WHERE or the entire table using ALL  
Syntax: ```PRINT FROM <tablename> <N> <print_colname1> <print_colname2> ... <print_colnameN> {WHERE <colname> <OP> <value> | ALL}```  
4. DELETE
Description: Delete selected rows from the specified table.  
Syntax: ```DELETE FROM <tablename> WHERE <colname> <OP> <value>```  
5. JOIN  
Description: Join two tables where values in selected columns match, and print results.  
Syntax: ```JOIN <tablename1> AND <tablename2> WHERE <colname1> = <colname2> AND PRINT <N> <print_colname1> <1|2> <print_colname2> <1|2> ... <print_colnameN> <1|2>```  
9. GENERATE  
Description: Directs the program to create an index of the type <indextype> on the column <colname> in the table <tablename>, where <indextype> is strictly limited to the set {hash, bst}, denoting a hash table index and a binary search tree index respectively. 
Syntax: ```GENERATE FOR <tablename> <indextype> INDEX ON <colname>```   

Getting Started  
To use these functions, navigate to the directory where the files are contained. To generate an executable, run ```make silly```. Then to run it type ```./silly.exe```  

⚠️ WARNING ⚠️

This project is from the EECS 281 course at the University of Michigan and is uploaded for educational and presentation purposes only.

University of Michigan students: Do not copy or use any part of this project for your own EECS 281 assignments or any other coursework. The University of Michigan has strict academic integrity guidelines, and any violation can lead to severe consequences.

For others, while you're welcome to reference or learn from the code, please do not directly copy or plagiarize the content. Always give credit where it's due and respect the effort that went into creating this project.

Thank you for your understanding!
