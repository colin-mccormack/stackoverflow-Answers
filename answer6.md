# Question : Memory leak using free() when creating a linked list with radix sort in C #

## Answer : ##

You are freeing the nodes as you allocate them. To fix your code simply comment out line 78.

// free(temporaryList); 

### Explanation:

Your underlying code is good, but the error is in the application of dynamic memory application. In the insertNode function you are creating a list and then dynamically allocating it as a memory block the size of a radixNode. As you set the data for this node you are now allocating the information in the block of memory you just allocated. When you free it right after this line (list->radNode = temporaryList;) becomes useless and now points to garbage which is what was causing your memory issues.

### Fixing Memory Leak (EDIT):

Although the simple solution shown above works it still results in memory not being freed. In order to properly allocate and free the memory my solution is to allocate it as an array in main and then free it in a loop also in main.
