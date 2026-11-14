#include "apc.h"

/*----------------------------------------------------------
 * Validate whether the input operand contains only digits.
 * A leading '+' or '-' sign is allowed.
 *----------------------------------------------------------*/
int validate(char *s)
{
    int i = 0;

    /* Skip optional sign */
    if (s[i] == '+' || s[i] == '-')
    {
        i++;
    }

    /* Check remaining characters are digits */
    while (s[i] != '\0')
    {
        if (s[i] < '0' || s[i] > '9')
        {
            printf("ERROR: Entered argument are not digits\n");
            return -1;
        }
        i++;
    }

    printf("SUCCESS: Argument validated\n");
    return 1;
}

/*----------------------------------------------------------
 * Create a doubly linked list from the given operand string.
 * Each digit is stored in one node.
 *----------------------------------------------------------*/
void create_list(char *opr, node **head, node **tail)
{
    int i = 0;

    while (opr[i] != '\0')
    {
        int data = opr[i] - '0';

        node *new = malloc(sizeof(node));

        if (new == NULL)
        {
            printf("Memory allocation failed\n");
            return;
        }

        new->data = data;
        new->prev = NULL;
        new->next = NULL;

        /* Insert first node */
        if (*head == NULL)
        {
            *head = *tail = new;
        }
        /* Insert at the end */
        else
        {
            new->prev = *tail;
            (*tail)->next = new;
            *tail = new;
        }

        i++;

        /* Remove unnecessary leading zeros */
        remove_prezeros(head);
    }
}

/*----------------------------------------------------------
 * Insert a node at the beginning of the list.
 *----------------------------------------------------------*/
int insert_first(node **head, node **tail, int data)
{
    node *new = malloc(sizeof(node));

    if (new == NULL)
        return 0;

    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    /* Empty list */
    if (*head == NULL)
    {
        *head = *tail = new;
        return 1;
    }

    /* Insert before current head */
    new->next = *head;
    (*head)->prev = new;
    *head = new;

    return 1;
}

/*----------------------------------------------------------
 * Insert a node at the end of the list.
 *----------------------------------------------------------*/
void insert_last(node **head, node **tail, int data)
{
    node *newNode = (node *)malloc(sizeof(node));

    if (newNode == NULL)
        return;

    newNode->data = data;
    newNode->next = NULL;

    /* Empty list */
    if (*tail == NULL)
    {
        newNode->prev = NULL;
        *head = *tail = newNode;
    }
    /* Append after current tail */
    else
    {
        newNode->prev = *tail;
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

/*----------------------------------------------------------
 * Display the contents of the linked list.
 *----------------------------------------------------------*/
void print_list(node *head)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    while (head)
    {
        printf("%d", head->data);
        head = head->next;
    }

    printf("\n");
}

/*----------------------------------------------------------
 * Count the number of nodes in the linked list.
 *----------------------------------------------------------*/
int count_nodes(node *head)
{
    int count = 0;

    while (head)
    {
        count++;
        head = head->next;
    }

    return count;
}

/*----------------------------------------------------------
 * Compare the magnitudes of two numbers represented
 * as linked lists.
 *
 * Returns:
 *   1  -> list1 > list2
 *  -1  -> list1 < list2
 *   0  -> equal
 *----------------------------------------------------------*/
int compare_lists(node *head1, node *head2)
{
    int len1 = count_nodes(head1);
    int len2 = count_nodes(head2);

    /* Compare lengths first */
    if (len1 > len2)
        return 1;

    if (len1 < len2)
        return -1;

    /* Lengths equal, compare digit by digit */
    while (head1 && head2)
    {
        if (head1->data > head2->data)
            return 1;

        if (head1->data < head2->data)
            return -1;

        head1 = head1->next;
        head2 = head2->next;
    }

    return 0;
}

/*----------------------------------------------------------
 * Remove unnecessary leading zeros.
 * Example:
 *   000123 -> 123
 *   0000   -> 0
 *----------------------------------------------------------*/
void remove_prezeros(node **head)
{
    node *temp;

    while (*head != NULL &&
           (*head)->data == 0 &&
           (*head)->next != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;

        free(temp);
    }
}

/*----------------------------------------------------------
 * Extract the sign of the operand.
 *
 * Returns:
 *  -1 -> negative
 *  +1 -> positive
 *----------------------------------------------------------*/
int get_sign(const char *numStr)
{
    if (numStr[0] == '-')
        return -1;

    return +1;
}

/*----------------------------------------------------------
 * Determine the sign of an addition/subtraction result.
 *
 * sign1      -> sign of operand1
 * sign2      -> sign of operand2
 * cmpResult  -> comparison of absolute values
 *----------------------------------------------------------*/
int resolve_add_sub_sign(int sign1, int sign2, int cmpResult)
{
    /* Same sign -> addition */
    if (sign1 == sign2)
    {
        return sign1;
    }

    /* Different signs -> larger magnitude decides sign */
    return (cmpResult >= 0) ? sign1 : sign2;
}

/*----------------------------------------------------------
 * Determine the sign of multiplication.
 *----------------------------------------------------------*/
int resolve_mul_sign(int sign1, int sign2)
{
    return sign1 * sign2;
}

/*----------------------------------------------------------
 * Determine the signs of quotient and remainder.
 *
 * Quotient sign  = dividend × divisor
 * Remainder sign = dividend
 *----------------------------------------------------------*/
void resolve_div_signs(int sign1, int sign2, int *signQ, int *signR)
{
    *signQ = sign1 * sign2;
    *signR = sign1;
}