/**
  ******************************************************************************
  * @file    contable.c
  * @author  SolarEdge Infrastructure Team.
 *  @brief   Console tables API.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 SolarEdge.
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */

#include "llist.h"
#include "contable.h"
#include <malloc.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

  /**************************************************************************/ /**
   * @brief
   *  Print the same character multiple times.
   * @return void.
   *
   *****************************************************************************/

static void contable_print_multiple(char c, int count)
{
    int i;
    for (i = 0; i < count; i++)
        putchar(c);
}

/**************************************************************************/ /**
 * @brief
 *  Add a column to the table.
 * @return bool.
 *
 *****************************************************************************/

bool contable_add_column(con_table* tbl, char* name, con_col_type type, int width)
{

    con_col* elm = NULL;

    if (!tbl || tbl->columnsAdded == true)
        return false;

    // Allocate a pointer for the request
    elm = (con_col*)malloc(sizeof(con_col));
    if (elm)
    {
        memset(elm, 0, (sizeof(con_col)));
        strncpy(elm->name, name, sizeof((con_col*)0)->name);
        elm->type = type;
        elm->width = width;

        if (elm->type == contable_hex)
            elm->width -= 2; // Accommodate for the addition of '0x'

        LL_APPEND(tbl->columns, elm); // Add to the list

        tbl->totalWidh += (1 + width);

        return true;
    }

    return false;
}

/**************************************************************************/ /**
 * @brief
 *  Print a table raw separator.
 * @return void.
 *
 *****************************************************************************/

void contable_print_separator(con_table* tbl)
{
    // Print the header
    if (tbl)
    {
        printf("+");
        contable_print_multiple('-', tbl->totalWidh - 2);
        printf("+\r\n");
    }
}

/**************************************************************************/ /**
 * @brief
 *  Print a table blank line.
 * @return void.
 *
 *****************************************************************************/

void contable_print_blank(con_table* tbl)
{
    con_col* elm = NULL;

    // Print the header
    if (tbl)
    {

        LL_FOREACH(tbl->columns, elm)
        {
            printf("|");
            contable_print_multiple(' ', elm->width);
        }

        printf("|\r\n");
    }
}

/**************************************************************************/ /**
 * @brief
 *  Print table raw.
 * @return void.
 *
 *****************************************************************************/

int contable_print(con_table* tbl, const char* _format, ...)
{
    va_list  argptr;
    con_col* elm = NULL;
    int      n, w, len = 0;
    char* s = NULL;

    if (!tbl)
        return -1; // Invalid pointer

    if (tbl->columnsAdded == false)
    {

        // Print the header
        contable_print_separator(tbl);

        LL_FOREACH(tbl->columns, elm)
        {
            printf("|");
            w = elm->width;

            if (elm->type == contable_hex)
                w += 2; // Accommodate for the addition of '0x'

            printf("%-*s", w, elm->name);
        }

        printf("|\r\n+");
        contable_print_multiple('-', tbl->totalWidh - 2);
        printf("+\r\n");

        tbl->columnsAdded = true; // Column are not allowed to be added from now on.
    }
    va_start(argptr, _format);

    LL_FOREACH(tbl->columns, elm)
    {
        printf("|");
        if (elm->type == contable_decimal)
        {
            n = va_arg(argptr, int);
            printf("%-*d", elm->width, n);
        }
        else if (elm->type == contable_string)
        {
            s = va_arg(argptr, char*);
            printf("%-*s", elm->width, s);
        }
        else if (elm->type == contable_hex)
        {
            n = va_arg(argptr, int);
            printf("0x%-*x", elm->width, n);
        }
    }

    printf("|\r\n");
    va_end(argptr);
    return len;
}

/**************************************************************************/ /**
 * @brief
 *  Destroy a table object and free it's internal columns list.
 * @return void.
 *
 *****************************************************************************/

void contable_destroy(con_table* tbl, bool separator)
{

    con_col* elm = NULL, * tmp;

    if (tbl)
    {
        if (separator == true)
            contable_print_separator(tbl);

        // Purge the previously allocated list
        LL_FOREACH_SAFE(tbl->columns, elm, tmp)
        {
            LL_DELETE(tbl->columns, elm);
            free(elm);
        }

        tbl->columns = NULL;
        tbl->totalWidh = 1;
        tbl->columnsAdded = false;
    }
}

/**************************************************************************/ /**
 * @brief
 *  Initializes a table object.
 * @return void.
 *
 *****************************************************************************/

void contable_init(con_table* tbl)
{
    if (tbl)
    {
        tbl->columns = NULL;
        tbl->totalWidh = 1;
        tbl->columnsAdded = false;
    }
}
