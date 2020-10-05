<!DOCTYPE html>
<html lang="en">

A very simple C code that generates ASCII tables in console mode.
The following example demonstrates the output of this API.
Note, the code is using heap (malloc) to generate a linked list of 
columns behind the scenes.
 
<pre>
+----------------------------------------+
|col a     |col b           |col c       |
+----------------------------------------+
|1         |string a        |10          |
|2         |string b        |20          |
|3         |string c        |30          |
+----------------------------------------+ 
</pre>

Usage Example:
<pre>
    int main()
    {
        con_table tbl;        
        contable_init(&tbl); // Initializes the table object.

        contable_add_column(&tbl, "col a", contable_decimal,   10); // Add decimal column, width  10 characters
        contable_add_column(&tbl, "col b", contable_string,    16); // Add string column
        contable_add_column(&tbl, "col c", contable_decimal,   12); // Add decimal column

        contable_print(&tbl, "%d%s%d", 1, "string a", 10);
        contable_print(&tbl, "%d%s%d", 2, "string b", 20);
        contable_print(&tbl, "%d%s%d", 3, "string c", 30);

        contable_destroy(&tbl,true); // Release the memory that was allocated.

        return 0;
    }

</pre>

Copyright (c) 2020, Eitan Michaelson
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

</html>
