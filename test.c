/* See LICENSE for license details. */

#include <stdio.h>
#include "deque.h"

typedef STRUCT_NODE(int) t_node;
typedef STRUCT_DEQUE(int) t_deque;

void validate_structure(t_deque* deque, t_node* first, t_node* last,
        size_t size)
{
    assert(DEQUE_FIRST(deque) == first);
    assert(DEQUE_LAST(deque) == last);
    assert(DEQUE_SIZE(deque) == size);
}

void validate_data(t_deque* deque, int head, int tail, size_t size)
{
    assert(NODE_DATA(DEQUE_FIRST(deque)) == head);
    assert(NODE_DATA(DEQUE_LAST(deque)) == tail);
    assert(DEQUE_SIZE(deque) == size);
}

void test_nodes(t_deque* deque)
{
    t_node n1, n2, n3;

    NODE_DATA(&n1) = 1;
    NODE_DATA(&n2) = 2;
    NODE_DATA(&n3) = 3;

    validate_structure(deque, NULL, NULL, 0);

    DEQUE_PUSH_NODE(deque, &n1);
    validate_structure(deque, &n1, &n1, 1);
    validate_data(deque, 1, 1, 1);

    DEQUE_PUSH_NODE(deque, &n2);
    validate_structure(deque, &n2, &n1, 2);
    validate_data(deque, 2, 1, 2);

    DEQUE_PUSH_NODE(deque, &n3);
    validate_structure(deque, &n3, &n1, 3);
    validate_data(deque, 3, 1, 3);

    DEQUE_CLEAR(deque);
    validate_structure(deque, NULL, NULL, 0);

    DEQUE_APPEND_NODE(deque, &n1);
    validate_structure(deque, &n1, &n1, 1);
    validate_data(deque, 1, 1, 1);

    DEQUE_APPEND_NODE(deque, &n2);
    validate_structure(deque, &n1, &n2, 2);
    validate_data(deque, 1, 2, 2);

    DEQUE_APPEND_NODE(deque, &n3);
    validate_structure(deque, &n1, &n3, 3);
    validate_data(deque, 1, 3, 3);

    DEQUE_CLEAR(deque);
    validate_structure(deque, NULL, NULL, 0);

    DEQUE_APPEND_NODE(deque, &n1);
    validate_structure(deque, &n1, &n1, 1);
    validate_data(deque, 1, 1, 1);

    DEQUE_PUSH_NODE(deque, &n2);
    validate_structure(deque, &n2, &n1, 2);
    validate_data(deque, 2, 1, 2);

    DEQUE_APPEND_NODE(deque, &n3);
    validate_structure(deque, &n2, &n3, 3);
    validate_data(deque, 2, 3, 3);

    DEQUE_CLEAR(deque);
    validate_structure(deque, NULL, NULL, 0);

    DEQUE_PUSH_NODE(deque, &n1);
    validate_structure(deque, &n1, &n1, 1);
    validate_data(deque, 1, 1, 1);

    DEQUE_APPEND_NODE(deque, &n2);
    validate_structure(deque, &n1, &n2, 2);
    validate_data(deque, 1, 2, 2);

    DEQUE_PUSH_NODE(deque, &n3);
    validate_structure(deque, &n3, &n2, 3);
    validate_data(deque, 3, 2, 3);

    DEQUE_POP_NODE(deque);
    validate_structure(deque, &n1, &n2, 2);
    validate_data(deque, 1, 2, 2);

    DEQUE_POP_NODE(deque);
    validate_structure(deque, &n2, &n2, 1);
    validate_data(deque, 2, 2, 1);

    DEQUE_POP_NODE(deque);
    validate_structure(deque, NULL, NULL, 0);
}

void test_data(t_deque* deque)
{
    t_node *first, *last, *aux;

    validate_structure(deque, NULL, NULL, 0);

    DEQUE_PUSH(deque, int, 1);
    validate_data(deque, 1, 1, 1);

    DEQUE_APPEND(deque, int, 2);
    validate_data(deque, 1, 2, 2);

    DEQUE_POP(deque, int);
    validate_data(deque, 2, 2, 1);

    DEQUE_PUSH(deque, int, 3);
    validate_data(deque, 3, 2, 2);

    DEQUE_FREE(deque, int);
    validate_structure(deque, NULL, NULL, 0);

    DEQUE_APPEND(deque, int, 4);
    validate_data(deque, 4, 4, 1);

    DEQUE_APPEND(deque, int, 5);
    validate_data(deque, 4, 5, 2);

    DEQUE_PUSH(deque, int, 6);
    validate_data(deque, 6, 5, 3);

    // Voluntarilly creates a memory leak
    first = DEQUE_FIRST(deque);
    last = DEQUE_LAST(deque);
    DEQUE_CLEAR(deque);
    validate_structure(deque, NULL, NULL, 0);

    // Check if the data of the first element is still there
    assert(NODE_DATA(first) == 6);

    // Traverse the structure and check if the rest of the data is still there
    aux = NODE_NEXT(first);
    assert(NODE_DATA(aux) == 4);

    aux = NODE_NEXT(aux);
    assert(NODE_DATA(aux) == 5);
    assert(last == aux);

    aux = NODE_NEXT(aux);
    assert(aux == NULL);

    // Fix the memory leak. Unnecessary, but I like doing things clean :)
    for (aux = first; aux != NULL; aux = NODE_NEXT(aux))
        NODE_FREE(aux);
}

int main(int argc, char* argv[])
{
    t_deque deque;

    DEQUE_INIT(&deque);
    validate_structure(&deque, NULL, NULL, 0);

    test_nodes(&deque);
    test_data(&deque);

    printf("All tests passed.\n");
    return 0;
}
