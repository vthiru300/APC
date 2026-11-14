  #include "apc.h"

/*----------------------------------------------------------
 * Perform subtraction of two large numbers represented as
 * doubly linked lists.
 *
 * Assumption:
 *   Operand1 >= Operand2 (absolute values).
 *
 * Traversal begins from the least significant digit (tail)
 * and proceeds towards the most significant digit (head).
 * Borrow is handled whenever a digit in the minuend is
 * smaller than the corresponding digit in the subtrahend.
 *----------------------------------------------------------*/
void subtraction(node *tail1, node *tail2, node **headR, node **tailR)
{
    int borrow = 0;

    /* Continue until all digits are processed */
    while (tail1 || tail2)
    {
        int digit1 = 0;
        int digit2 = 0;

        /* Read next digit from operand1 */
        if (tail1)
        {
            digit1 = tail1->data;
            tail1 = tail1->prev;
        }

        /* Read next digit from operand2 */
        if (tail2)
        {
            digit2 = tail2->data;
            tail2 = tail2->prev;
        }

        /* Apply borrow from the previous digit */
        digit1 = digit1 - borrow;

        /* Borrow from the next higher digit if required */
        if (digit1 < digit2)
        {
            digit1 += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        /* Store the current result digit */
        insert_first(headR, tailR, digit1 - digit2);
    }

    /* Remove unnecessary leading zeros */
    remove_prezeros(headR);
}
