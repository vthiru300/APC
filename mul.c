#include "apc.h"

/*----------------------------------------------------------
 * Perform multiplication of two large numbers represented
 * as doubly linked lists.
 *
 * Uses the grade-school multiplication algorithm:
 *  1. Multiply each digit of the second operand with every
 *     digit of the first operand.
 *  2. Generate a partial product.
 *  3. Append the required number of trailing zeros.
 *  4. Add the partial product to the accumulated result.
 *----------------------------------------------------------*/
void multiplication(node *tail1, node *tail2, node **headR, node **tailR)
{
    node *ptr2 = tail2;
    int shift = 0;

    /* Process each digit of the multiplier */
    while (ptr2)
    {
        node *tempHead = NULL;
        node *tempTail = NULL;
        int carry = 0;

        node *ptr1 = tail1;

        /* Multiply one digit with the entire multiplicand */
        while (ptr1)
        {
            int prod = ptr1->data * ptr2->data + carry;

            carry = prod / 10;

            insert_first(&tempHead, &tempTail, prod % 10);

            ptr1 = ptr1->prev;
        }

        /* Insert any remaining carry */
        if (carry)
        {
            insert_first(&tempHead, &tempTail, carry);
        }

        /*--------------------------------------------------
         * Append trailing zeros according to the current
         * digit position (place value).
         *--------------------------------------------------*/
        for (int i = 0; i < shift; i++)
        {
            node *new = malloc(sizeof(node));

            new->data = 0;
            new->next = NULL;
            new->prev = tempTail;

            if (tempTail)
            {
                tempTail->next = new;
            }
            else
            {
                tempHead = new;
            }

            tempTail = new;
        }

        /*--------------------------------------------------
         * Add the current partial product to the accumulated
         * result.
         *--------------------------------------------------*/
        node *newHead = NULL;
        node *newTail = NULL;

        addition(*tailR, tempTail, &newHead, &newTail);

        *headR = newHead;
        *tailR = newTail;

        /* Move to the next multiplier digit */
        ptr2 = ptr2->prev;
        shift++;
    }

    /* Remove leading zeros from the final product */
    remove_prezeros(headR);
}