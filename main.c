#include "apc.h"

int main(int argc, char *argv[])
{
    node *head1 = NULL, *tail1 = NULL;
    node *head2 = NULL, *tail2 = NULL;
    node *headR = NULL, *tailR = NULL;

    /*----------------------------------------------------------
     * Validate command line arguments
     * Usage: ./a.out <operand1> <operator> <operand2>
     *----------------------------------------------------------*/
    if (argc != 4)
    {
        printf("ERROR: Argument count must be 4 only\n");
        return 0;
    }

    if (validate(argv[1]) == -1)
        return 0;

    if (validate(argv[3]) == -1)
        return 0;

    /*----------------------------------------------------------
     * Determine the sign of both operands
     *----------------------------------------------------------*/
    int sign1 = (argv[1][0] == '-') ? -1 : +1;
    int sign2 = (argv[3][0] == '-') ? -1 : +1;

    /*----------------------------------------------------------
     * Create linked lists using only the absolute values.
     * Skip '+' or '-' before creating the list.
     *----------------------------------------------------------*/
    create_list((argv[1][0] == '+' || argv[1][0] == '-') ? argv[1] + 1 : argv[1],
                &head1, &tail1);

    create_list((argv[3][0] == '+' || argv[3][0] == '-') ? argv[3] + 1 : argv[3],
                &head2, &tail2);

    print_list(head1);
    print_list(head2);

    /*----------------------------------------------------------
     * Validate the operator
     *----------------------------------------------------------*/
    char oper = argv[2][0];

    if (argv[2][1] != '\0' ||
        (oper != '+' && oper != '-' &&
         oper != 'x' && oper != 'X' &&
         oper != '/'))
    {
        printf("ERROR: Invalid operator\n");
        return 0;
    }

    /*----------------------------------------------------------
     * Perform the required arithmetic operation
     *----------------------------------------------------------*/
    switch (oper)
    {
        /*======================== ADDITION ========================*/
        case '+':
        {
            /* Compare magnitudes of operands */
            int cmp = compare_lists(head1, head2);

            printf("Result : ");

            /* Same sign -> perform addition */
            if (sign1 == sign2)
            {
                addition(tail1, tail2, &headR, &tailR);

                if (sign1 == -1)
                    printf("-");
            }
            else
            {
                /* Different signs -> perform subtraction */

                if (cmp == 0)
                {
                    /* Numbers are equal */
                    insert_first(&headR, &tailR, 0);
                }
                else if (cmp > 0)
                {
                    /* Operand1 has greater magnitude */
                    subtraction(tail1, tail2, &headR, &tailR);

                    if (sign1 == -1)
                        printf("-");
                }
                else
                {
                    /* Operand2 has greater magnitude */
                    subtraction(tail2, tail1, &headR, &tailR);

                    if (sign2 == -1)
                        printf("-");
                }
            }

            print_list(headR);
            break;
        }

        /*======================= SUBTRACTION =======================*/
        case '-':
        {
            /* Equivalent to operand1 + (-operand2) */
            int cmp = compare_lists(head1, head2);

            printf("Result : ");

            /* Different signs -> addition */
            if (sign1 != sign2)
            {
                addition(tail1, tail2, &headR, &tailR);

                if (sign1 == -1)
                    printf("-");
            }
            else
            {
                /* Same signs -> subtraction */

                if (cmp == 0)
                {
                    insert_first(&headR, &tailR, 0);
                }
                else if (cmp > 0)
                {
                    subtraction(tail1, tail2, &headR, &tailR);

                    if (sign1 == -1)
                        printf("-");
                }
                else
                {
                    subtraction(tail2, tail1, &headR, &tailR);

                    if (sign2 == +1)
                        printf("-");
                    else
                        printf("+");      // Optional
                }
            }

            print_list(headR);
            break;
        }

        /*===================== MULTIPLICATION ======================*/
        case 'x':
        case 'X':
        {
            multiplication(tail1, tail2, &headR, &tailR);

            printf("Result : ");

            /* Negative only if signs differ */
            if (sign1 * sign2 == -1)
                printf("-");

            print_list(headR);
            break;
        }

        /*======================== DIVISION =========================*/
        case '/':
        {
            /* Check for NULL divisor */
            if (head2 == NULL)
            {
                printf("Division by zero not allowed");
                return 0;
            }

            /* Check if divisor consists entirely of zeros */
            node *temp = head2;
            int allZero = 1;

            while (temp != NULL)
            {
                if (temp->data != 0)
                {
                    allZero = 0;
                    break;
                }

                temp = temp->next;
            }

            if (allZero)
            {
                printf("ERROR: Division by zero not allowed\n");
                return 0;
            }

            division(head1, tail1, head2, tail2, &headR, &tailR);

            printf("Result : ");

            /* Negative only if signs differ */
            if (sign1 * sign2 == -1)
                printf("-");

            print_list(headR);
            break;
        }

        /*==================== INVALID OPERATOR ====================*/
        default:
            printf("Invalid operator\n");
    }

    return 0;
}