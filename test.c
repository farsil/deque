/* See LICENSE for license details. */

#include <stdio.h>
#include "deque.h"

#define ASSERT_STRUCTURE(deque, first, last, size) do   \
{                                                       \
    assert(DEQUE_FIRST((deque)) == (first));            \
    assert(DEQUE_LAST((deque)) == (last));              \
    assert(DEQUE_SIZE((deque)) == (size));              \
} while (0)


#define ASSERT_DATA(deque, head, tail, size) do         \
{                                                       \
    assert(NODE_DATA(DEQUE_FIRST((deque))) == (head));  \
    assert(NODE_DATA(DEQUE_LAST((deque))) == (tail));   \
    assert(DEQUE_SIZE((deque)) == (size));              \
} while (0)

typedef STRUCT_NODE(int) t_node;
typedef STRUCT_DEQUE(int) t_deque;

void test_nodes(t_deque* deque)
{
    t_node n1, n2, n3;

    NODE_DATA(&n1) = 1;
    NODE_DATA(&n2) = 2;
    NODE_DATA(&n3) = 3;

    ASSERT_STRUCTURE(deque, NULL, NULL, 0);

    DEQUE_PUSH_NODE(deque, &n1);
    ASSERT_STRUCTURE(deque, &n1, &n1, 1);
    ASSERT_DATA(deque, 1, 1, 1);

    DEQUE_PUSH_NODE(deque, &n2);
    ASSERT_STRUCTURE(deque, &n2, &n1, 2);
    ASSERT_DATA(deque, 2, 1, 2);

    DEQUE_PUSH_NODE(deque, &n3);
    ASSERT_STRUCTURE(deque, &n3, &n1, 3);
    ASSERT_DATA(deque, 3, 1, 3);

    DEQUE_CLEAR(deque);
    ASSERT_STRUCTURE(deque, NULL, NULL, 0);

    DEQUE_APPEND_NODE(deque, &n1);
    ASSERT_STRUCTURE(deque, &n1, &n1, 1);
    ASSERT_DATA(deque, 1, 1, 1);

    DEQUE_APPEND_NODE(deque, &n2);
    ASSERT_STRUCTURE(deque, &n1, &n2, 2);
    ASSERT_DATA(deque, 1, 2, 2);

    DEQUE_APPEND_NODE(deque, &n3);
    ASSERT_STRUCTURE(deque, &n1, &n3, 3);
    ASSERT_DATA(deque, 1, 3, 3);

    DEQUE_CLEAR(deque);
    ASSERT_STRUCTURE(deque, NULL, NULL, 0);

    DEQUE_APPEND_NODE(deque, &n1);
    ASSERT_STRUCTURE(deque, &n1, &n1, 1);
    ASSERT_DATA(deque, 1, 1, 1);

    DEQUE_PUSH_NODE(deque, &n2);
    ASSERT_STRUCTURE(deque, &n2, &n1, 2);
    ASSERT_DATA(deque, 2, 1, 2);

    DEQUE_APPEND_NODE(deque, &n3);
    ASSERT_STRUCTURE(deque, &n2, &n3, 3);
    ASSERT_DATA(deque, 2, 3, 3);

    DEQUE_CLEAR(deque);
    ASSERT_STRUCTURE(deque, NULL, NULL, 0);

    DEQUE_PUSH_NODE(deque, &n1);
    ASSERT_STRUCTURE(deque, &n1, &n1, 1);
    ASSERT_DATA(deque, 1, 1, 1);

    DEQUE_APPEND_NODE(deque, &n2);
    ASSERT_STRUCTURE(deque, &n1, &n2, 2);
    ASSERT_DATA(deque, 1, 2, 2);

    DEQUE_PUSH_NODE(deque, &n3);
    ASSERT_STRUCTURE(deque, &n3, &n2, 3);
    ASSERT_DATA(deque, 3, 2, 3);

    DEQUE_POP_NODE(deque);
    ASSERT_STRUCTURE(deque, &n1, &n2, 2);
    ASSERT_DATA(deque, 1, 2, 2);

    DEQUE_POP_NODE(deque);
    ASSERT_STRUCTURE(deque, &n2, &n2, 1);
    ASSERT_DATA(deque, 2, 2, 1);

    DEQUE_POP_NODE(deque);
    ASSERT_STRUCTURE(deque, NULL, NULL, 0);
}

void test_data(t_deque* deque)
{
    t_node *first, *last, *aux;

    ASSERT_STRUCTURE(deque, NULL, NULL, 0);

    DEQUE_PUSH(deque, int, 1);
    ASSERT_DATA(deque, 1, 1, 1);

    DEQUE_APPEND(deque, int, 2);
    ASSERT_DATA(deque, 1, 2, 2);

    DEQUE_POP(deque, int);
    ASSERT_DATA(deque, 2, 2, 1);

    DEQUE_PUSH(deque, int, 3);
    ASSERT_DATA(deque, 3, 2, 2);

    DEQUE_FREE(deque, int);
    ASSERT_STRUCTURE(deque, NULL, NULL, 0);

    DEQUE_APPEND(deque, int, 4);
    ASSERT_DATA(deque, 4, 4, 1);

    DEQUE_APPEND(deque, int, 5);
    ASSERT_DATA(deque, 4, 5, 2);

    DEQUE_PUSH(deque, int, 6);
    ASSERT_DATA(deque, 6, 5, 3);

    // Voluntarilly creates a memory leak
    first = DEQUE_FIRST(deque);
    last = DEQUE_LAST(deque);
    DEQUE_CLEAR(deque);
    ASSERT_STRUCTURE(deque, NULL, NULL, 0);

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
    ASSERT_STRUCTURE(&deque, NULL, NULL, 0);

    test_nodes(&deque);
    test_data(&deque);

    printf("All tests passed.\n");
    return 0;
}
