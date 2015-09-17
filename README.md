# Binomial-Heap-and-Leftist-Tree

implementation of Left tree and Binomial Heap 

Leftist Tree :
-Struct node lnode : contains the node structure for leftist tree .
Functions :
-Linsert : Inserts element into the leftist tree
-Lremovemin : removes the minimum element, if tree is empty it returns null.
-Lmeld : takes two leftist node as inputs and meld them together following through
the right child of the node having smallest value.
-Lmerge : recursively calls lmeld till both nodes are melded together.
-Height : Finds the height of the leftist tree.
-Levelp : Used for level printing. it gets the height from height function and then for
each level calls the function level to print elements in the same level.
-Level : recursively call itself to print all elements in a given level.


Binomial Heap :
-Struct node bnode : contains the node structure for Binomial Heap.
-Sturct node qnode : used for bulding queue for level printing.
Functions :
-Binsert : Inserts element into the binomial heap.
-Bremovemin : removes min element from the heap, returns null if heap is empty.
-Bmerge : take two binomial heaps as inputs and then merges them into one.
-Bpaircombine : combines two tree with same degree to form a single tree with
higher degree.
-Bprintlevel : used for level order printing of binomial heap , start from the root and
goes through every node in its circular list and if the node has child, then that child
will be pushed into queue, it is used to print all elements its circular list.
-Benqueue : an element is pushed into the queue.
-Bdequeue : an element is dequeued from the queue
-Bqempty : check whether queue is empty or not.
