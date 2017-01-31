# deque.h
`deque.h` implements a type generic, single linked, double ended queue suitable
for both FIFO and LIFO operations. Its code is mostly inspired by the `STAILQ`
macros availabile in FreeBSD's `sys/queue.h` header, with a few differences:

* Does not make use of any non-standard #includes, so it has no dependencies to
  external files: just drop the `deque.h` file in your project and you're good
  to go.
* Allows obtaining the deque size in O(1) thanks to a specialized `size` field
  in the header.

The interface is well documented in the `deque.h` file itself, so it will not
be reported here. 

# Example
This example shows the basic operations (push, append, pop, iterate) you can
perform with the deque:

    #include <stdio.h>
    #include "deque.h"
    
    typedef int t_data;

    // The STRUCT_NODE and STRUCT_DEQUE macros expand to a struct definition
    // so they are necessary in order to use the deque.
    typedef STRUCT_NODE(t_data) t_node;
    typedef STRUCT_DEQUE(t_data) t_deque;

    int main(int argc, char* argv[])
    {
        t_deque deque;
        DEQUE_INIT(&deque);

        // There are also versions of PUSH/APPEND/POP that operate on node
        // structures, see the documentation in deque.h for more details.
        DEQUE_PUSH(&deque, t_data, 3);
        DEQUE_APPEND(&deque, t_data, 5);
        DEQUE_POP(&deque, t_data);
        DEQUE_PUSH(&deque, t_data, 4);
        DEQUE_APPEND(&deque, t_data, 8);

        // Should print 'Head: 4, Tail: 8, Size: 2'.
        printf("Head: %d, Tail: %d, Size: %lu\n\n", DEQUE_HEAD(&deque), 
                DEQUE_TAIL(&deque), DEQUE_SIZE(&deque));

        // Prints out the whole deque.
        for (t_node* node = DEQUE_FIRST(&deque); node != NULL; 
                node = NODE_NEXT(node))
        {
            printf("Address: %p, Next: %p, Value: %d\n", node, 
                NODE_NEXT(node), NODE_DATA(node));
        }

        // Destroys all dynamically allocated nodes (created by APPEND and 
        // PUSH) and resets the deque.
        DEQUE_FREE(&deque, t_data);

        return 0;
    }
