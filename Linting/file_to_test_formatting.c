/**
 * @file file_to_test_formatting.h
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This file is to test the linter formatting. Manipulated it as you'd
 * like, it's not part of the project build.
 * @version 0.1
 * @date 2020-04-28
 *
 * @copyright Copyright (c) 2020
 *
 */

void foo(void)
{
    int a = 5;
    switch (a)
    {
        case 1:
        {
        }
        break;
        case 2:
        {
        }
        break;
        case 3:
        {
        }
        break;
        case 4:

            break;

        case 5:
        case 6:
        {
        }
        break;

        case 7:
        {
        }
        break;
        case 8:

            break;
    }

    int *p1;
    int *p2;
    int *p3;
    int *p4;

    int a = 5;
    int b = 4;
    int c, d;

    if (1)
    {
        // do some stuff if true
    }
    else
    {
        // do some stuff
    }

    if (1)
    {
    }
    else
    {
        // unindented else block
    }

    if (1)
    {
        do
        {
        } while (1);

        while (1)
        {
        }
    }

    if (1)
    {
        do
        {

        } while (1);
    }

    if (1)
    {
        do
        {

        } while (1);
    }
}