
#include "contable.h"

int main(void)
{
    con_table tbl;
    contable_init(&tbl);

    contable_add_column(&tbl, "col a", contable_decimal, 10); // Add decimal column
    contable_add_column(&tbl, "col b", contable_string, 16);  // Add string column
    contable_add_column(&tbl, "col c", contable_decimal, 12); // Add decimal column

    contable_print(&tbl, "%d%s%d", 1, "string a", 10);
    contable_print(&tbl, "%d%s%d", 2, "string b", 20);
    contable_print(&tbl, "%d%s%d", 3, "string c", 30);

    contable_destroy(&tbl, true);

    return 0;
}
