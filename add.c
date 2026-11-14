#include "apc.h"

/*----------------------------------------------------------
 * Perform addition of two large numbers represented as
 * doubly linked lists.
 *
 * Traversal starts from the least significant digit
 * (tail) towards the most significant digit (head).
 *
 * The result is built by inserting each computed digit
 * at the front of the result list.
 *----------------------------------------------------------*/
void addition(node *tail1, node *tail2, node **headR, node **tailR)
{
    int carry = 0;

    /* Continue until both operands are completely processed */
    while (tail1 != NULL || tail2 != NULL)
    {
        int digit1 = 0;
        int digit2 = 0;

        /* Read digit from operand 1 */
        if (tail1 != NULL)
        {
            digit1 = tail1->data;
            tail1 = tail1->prev;
        }

        /* Read digit from operand 2 */
        if (tail2 != NULL)
        {
            digit2 = tail2->data;
            tail2 = tail2->prev;
        }

        /* Add digits along with previous carry */
        int sum = digit1 + digit2 + carry;

        /* Calculate new carry and current result digit */
        carry = sum / 10;
        int digit = sum % 10;

        /* Insert result digit at the beginning */
        insert_first(headR, tailR, digit);
    }

    /* Insert any remaining carry */
    if (carry)
    {
        insert_first(headR, tailR, carry);
    }
}