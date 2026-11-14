#include "apc.h"
#include <stdlib.h>

/*----------------------------------------------------------
 * Perform division of two large numbers represented as
 * doubly linked lists.
 *
 * Uses the long division algorithm:
 *  1. Bring down one digit from the dividend.
 *  2. Compare the current remainder with the divisor.
 *  3. Repeatedly subtract the divisor until the remainder
 *     becomes smaller.
 *  4. The number of successful subtractions forms one
 *     quotient digit.
 *----------------------------------------------------------*/
void division(node *head1, node *tail1,
              node *head2, node *tail2,
              node **headR, node **tailR)
{
    /* Initialize quotient list */
    *headR = NULL;
    *tailR = NULL;

    /* Initialize remainder list */
    node *remHead = NULL;
    node *remTail = NULL;

    /* Traverse the dividend from MSB to LSB */
    node *ptr1 = head1;

    while (ptr1 != NULL)
    {
        /*--------------------------------------------------
         * Bring down the next digit into the remainder.
         * Digits are appended to preserve MSB → LSB order.
         *--------------------------------------------------*/
        insert_last(&remHead, &remTail, ptr1->data);

        /* Remove unnecessary leading zeros */
        remove_prezeros(&remHead);

        int count = 0;

        /*--------------------------------------------------
         * Count how many times the divisor fits into the
         * current remainder.
         *--------------------------------------------------*/
        if (remHead != NULL)
        {
            while (compare_lists(remHead, head2) >= 0)
            {
                node *tempHead = NULL;
                node *tempTail = NULL;

                /* remainder = remainder - divisor */
                subtraction(remTail, tail2, &tempHead, &tempTail);

                /* Update remainder with subtraction result */
                remHead = tempHead;
                remTail = tempTail;

                count++;

                /* Prevent infinite looping in case of error */
                if (remHead == NULL)
                    break;
            }
        }

        /*--------------------------------------------------
         * Append the quotient digit to the result list.
         *--------------------------------------------------*/
        node *newNode = (node *)malloc(sizeof(node));

        if (newNode == NULL)
            return;

        newNode->data = count;
        newNode->next = NULL;
        newNode->prev = *tailR;

        if (*tailR != NULL)
        {
            (*tailR)->next = newNode;
        }
        else
        {
            *headR = newNode;
        }

        *tailR = newNode;

        /* Move to the next dividend digit */
        ptr1 = ptr1->next;
    }

    /* Remove leading zeros from the quotient */
    remove_prezeros(headR);

    /* If quotient is empty, represent the result as 0 */
    if (*headR == NULL)
    {
        insert_last(headR, tailR, 0);
    }
}