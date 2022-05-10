#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define null 0

/*

  Disclaimer : This is not my underlying code it is just my fixed and improved version of the code provided by the stack overflow user.
  
 */

// Defines a structure for node
struct RadixNode
{
    // To store data
    int number, postNumber, radix;
    // Pointer to next node and
    struct RadixNode *nextNode, *radNode;
}; // End of structure
typedef struct RadixNode *List;

// Prototype of functions
void showList(List);
List getHead();
void createNode(List);
void insertNode(List, int, List);
int getBiggest(List);
void sortList(List, int);
void repositionNode(List, List, int);
void deleteNode(List);
void resetList(List);
int main();

// Function to create and return head node
List getHead()
{
    List headNode;
    headNode = malloc(sizeof(struct RadixNode));
    headNode->number = -1;
    headNode->postNumber = -1;
    headNode->radix = 0;
    headNode->nextNode = null;
    headNode->radNode = null;
    return headNode;

}

// Function to create a list with 10 nodes
void createNode(List headNode)
{
    int counter;
    List currentNode = headNode;
    for (counter = 0; counter < 10; counter++)
    {
        List newNode;
        newNode = malloc(sizeof(struct RadixNode));
        newNode->nextNode = null;
        newNode->radNode = null;
        newNode->number = 0;
        newNode->radix = 0;
        newNode->postNumber = counter;
        currentNode->nextNode = newNode;
        currentNode = newNode;

    }
}

// Function to insert a number to list
void insertNode(List list, int number, List temporaryList)
{
    int remainder = number % 10;
    for (list = list->nextNode; list->postNumber != remainder; list = list->nextNode)
        ;

    while (list->radNode != null)
        list = list->radNode;

    temporaryList->number = number;
    temporaryList->radix = 0;
    temporaryList->postNumber = list->postNumber;
    temporaryList->radNode = null;
    temporaryList->nextNode = null;
    list->radNode = temporaryList;
}
// Function to return number of digits in the biggest number in the list
int getBiggest(List list)
{
    int biggestNumber = 0, countDigits;
    List temporaryList = list, currentList;
    for (temporaryList = temporaryList->nextNode; temporaryList != null; temporaryList = temporaryList->nextNode)
    {
        for (currentList = temporaryList; currentList != null; currentList = currentList->radNode)
        {
            if (biggestNumber < currentList->number)
                biggestNumber = currentList->number;
        }
    }
    countDigits = 0;
    while (biggestNumber > 0)
    {
        countDigits++;
        biggestNumber /= 10;
    }
    return countDigits;
}

// Function to reset the list
void resetList(List list)
{
    List temporaryList;
    for (list = list->nextNode; list != null; list = list->nextNode)
        for (temporaryList = list->radNode; temporaryList != null; temporaryList = temporaryList->radNode)
            temporaryList->radix = 0;
}

// Function to perform radix sort
void sortList(List list, int biggestNum)
{
    List temporaryListOne, temporaryListTwo, temporaryListThree;
    int base = 10, number, passNumber, position;

    for (passNumber = 0; passNumber < biggestNum - 1; passNumber++, base = base * 10)
    {
        temporaryListTwo = list;
        for (temporaryListTwo = temporaryListTwo->nextNode; temporaryListTwo != null; temporaryListTwo = temporaryListTwo->nextNode)
        {
            temporaryListThree = temporaryListTwo;
            temporaryListOne = temporaryListTwo;
            for (temporaryListThree = temporaryListThree->radNode; temporaryListThree != null; temporaryListThree = temporaryListThree->radNode)
            {
                number = temporaryListThree->number;
                position = number / base;
                position = position % 10;
                if (temporaryListThree->radix == 0)
                {
                    deleteNode(temporaryListOne);
                    repositionNode(list, temporaryListThree, position);
                    temporaryListThree = temporaryListOne;
                }
                else
                    temporaryListOne = temporaryListOne->radNode;
            }
        }
        printf("\n\nPass %d\n\n", passNumber + 2);
        showList(list);
        resetList(list);
    }
}
// Function to reposition the node belongs to its right place
void repositionNode(List list, List listPosition, int position)
{
    List currentList = list, temporaryList = listPosition;
    for (currentList = currentList->nextNode; currentList->postNumber != position; currentList = currentList->nextNode)
        ;
    while (currentList->radNode != null)
        currentList = currentList->radNode;
    temporaryList->postNumber = position;
    temporaryList->radix = 1;
    temporaryList->radNode = null;
    temporaryList->nextNode = null;
    currentList->radNode = temporaryList;
}

// Function to delete the node before moving it to its right position
void deleteNode(List list)
{
    List currentList = list;
    currentList->radNode = currentList->radNode->radNode;
}

// Function to display the list
void showList(List list)
{
    List currentList, temporaryList = list;
    for (temporaryList = temporaryList->nextNode; temporaryList != null; temporaryList = temporaryList->nextNode)
    {
        for (currentList = temporaryList->radNode; currentList != null; currentList = currentList->radNode)
            printf("\t%d", currentList->number);
    }
}

// main function definition
int main()
{
    int len, counter, biggestNum;
    List list;
    int numbers[] = {9, 11, 32, 87, 100, 108, 122, 265, 554, 626, 963};
    len = sizeof(numbers) / sizeof(numbers[0]);
    list = getHead();
    createNode(list);
    List temporaryList[len];

    for (int i = 0; i < len; ++i)
        temporaryList[i] = malloc(sizeof(struct RadixNode));

    for (counter = 0; counter < len; counter++)
        insertNode(list, numbers[counter], temporaryList[counter]);

    printf("\nPass 1:\n\n");
    showList(list);
    biggestNum = getBiggest(list);
    sortList(list, biggestNum);
    printf("\n\nAfter radix sort\n\n");
    showList(list);
    printf("\n");
    
    free(list);

    // free temporary list that was causing memory leak
    for (int i = 0; i < len; ++i) free(temporaryList[i]);

    /*free(headNode);
    free(newNode);
    free(temporaryList);*/
    return 0;
}
