/**********************************************************************
Program cs2123p5.c by Timothy Hennessy
Purpose:	
    This file  corresponds to cs2123p5Driver.c and contains
    additional functions to help with building and using an unordered
    binary tree. 
Command Parameters:
    N/A
Input:
    The functions in this file are called from main in cs2123p5Driver.c.
Results/Returns:
    NodeT *searchT(NodeT *p, char szId[]) 
    void prettyPrintT(NodeT *p, int iIndent, TextList textList)
    char * help(NodeT *p, char szAnswers[], int iAns, TextList textList)
    void freeT(NodeT *p)
    NodeT *allocateNodeT(Element elem)
    NodeT * insertT(NodeT **pp, Element value, char cYN)
    NodeT * findParent(NodeT *p, char szId[], char *cLR)
    void delete(NodeT *p, char szId[], char cLR)
Notes:
    This program is designed to work with cs2123p5Driver.c
**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "cs2123p5.h"

// functions to write
/******************** searchT **************************************
NodeT *searchT(NodeT *p, char szId[])
Purpose:
    Search for an ID in the tree and return a pointer to the NODE
    or NULL if not found
Parameters:
    I   NodeT *p                A pointer to the binary tree to be
                                searched.
    I   char szId[]             ID used to search through tree
Returns:
    A pointer to the node in the binary tree matching the argument
    szId.
    If the a node does not exist matching the ID, NULL is returned.
Notes:
    1. Since the diagnosis tree is an unordered structure, it is 
    potentially necessary to traverse the entire binary tree until
    no more nodes exist which means NULL is returned and the 
    node being searched for does not exist in the tree.
    2. If the node being searched for exists, a pointer to it is
    returned.
**************************************************************************/
NodeT * searchT(NodeT *p, char szId[])
{
	NodeT *pFind;
	if (p == NULL)
		return p;
	// node is found
	if (strcmp(p->element.szId, szId) == 0)
		return p;
	pFind = searchT(p->pLeft, szId);
	// not found
	if (pFind != NULL)
		return pFind;
	else
		return searchT(p->pRight, szId);	
}
/********************* prettyPrintT **************************************
void prettyPrintT(NodeT *p, int iIndent, TextList textList)
Purpose:
    Prints the contents of the tree in a pretty print style.  Prints the
    ID and corresponding display text.
Parameters:
    I   NodeT *p                A pointer to the binary tree to be
                                searched.
    I   int iIndent             Sets the initial amount of indention
                                to ensure pretty print is pretty.
    I   TextList textList       A pointer to a structure of arrays
                                containing entries correspoding to the
                                diagnosis tree.                                
Returns:
    N/A
Notes:
    Starts at the root of the tree and recursively prints out
    each entry in the textList->arrayM 
**************************************************************************/
void prettyPrintT(NodeT *p, int iIndent, TextList textList)
{
    int i;
    if (p == NULL)
        return;
	prettyPrintT(p->pRight, iIndent + 1, textList);
    printf("\n   ");
    for (i = 0; i < iIndent; i++)
    {
        printf("   ");
    }
    printf("%s %s", p->element.szId, getText(textList, p->element.szId));
	prettyPrintT(p->pLeft, iIndent + 1, textList);    
}
/************************** help **************************************
char * help(NodeT *p, char szAnswers[], int iAns, TextList textList)
Purpose:
    Returns the diagnosis based on the Y or N answers to the questions.
    If it doesn't have one, it returns NULL.
Parameters:
    I   NodeT *p                A pointer to the binary tree to be
                                searched.
    I   int iIndent             Sets the initial amount of indention
                                to ensure pretty print is pretty.
    I   char szAnswers[]        Array of chars consisting of either
                                Y or N used to traverse diagnosis tree
    I   int iAns                Integer corresponding to the subscript of
                                szAnswers
    I   TextList textList       Pointer to an array of structures containing
                                text values corresponding to the diagnosis tree
Returns:
    -char *szId                 If a diagnosis is reached, the p->element.szId
                                is returned corresponding to it
    -NULL                       No diagnosis was reached
Notes:
    Special conditions:
    1.) List is empty or no diagnosis was reached - NULL is returned
    2.) A nodeT is reached with a cNodeType of 'D', return the szId
    3.) Traverse tree based on Y or N values, if N go p->pLeft else
    must be Y and function goes p->pRight
**************************************************************************/
char * help(NodeT *p, char szAnswers[], int iAns, TextList textList)
{
	// using the answers given return diagnosis
	// if it doesn't have diganosis return NULL
	char c = szAnswers[iAns];
	if (p == NULL)
		return NULL;
	// if a diagnosis node is reached the command was successful
	if (p->element.cNodeType == 'D')
		return p->element.szId;
	// go left for N and right for Y
	if (c == 'N')
	{
        printf("\t%s: %s %c\n"
			 , p->element.szId
             , getText(textList, p->element.szId)
			 , 'N');
		return help(p->pLeft, szAnswers, iAns + 1, textList);
	}
	else
	{   // prints out Y 
        printf("\t%s: %s %c\n"
			 , p->element.szId
             , getText(textList, p->element.szId)
			 , 'Y');
		return help(p->pRight, szAnswers, iAns + 1, textList);
	}
}
/******************** freeT **************************************
void freeT(NodeT *p)
Purpose:
    Frees all nodes in a given tree.  
Parameters:
    I   NodeT *p                A pointer to the binary tree to be
                                searched.
Returns:
    N/A
Notes:
    If p->pLeft and p->pRight are both null 
    then the current node is a leaf.  When this function finds a 
    leaf, it frees the leaf and continues this process until null.
**************************************************************************/
void freeT(NodeT *p)
{
    if (p->pLeft != NULL)
		freeT(p->pLeft);
	if(p->pRight != NULL)
		freeT(p->pRight);
    free(p);
}
/******************** allocateNodeT **************************************
NodeT *allocateNodeT(Element elem)
Purpose:
    Dynamically allocates memory for a new NodeT and returns a pointer
    to that new NodeT.  
Parameters:
    I   Element elem            Contains element data to be added to newly
                                allocated NodeT.
Returns:
    A pointer to NodeT.
Notes:
    If malloc fails the program aborts.
**************************************************************************/
NodeT * allocateNodeT(Element elem)
{
	NodeT *pNew = (NodeT *) malloc(sizeof(NodeT));
	if (pNew == NULL)
		ErrExit(ERR_ALGORITHM, "No memory left for allocating a NodeT");
	pNew->element = elem;
	pNew->pLeft = NULL;
	pNew->pRight = NULL;
	return pNew;
}
/************************ insertNodeT ************************************
NodeT * insertT(NodeT **pp, Element value, char szParentId[], char cYN)
Purpose:
    Takes the address of the parent node and uses the value of cYN 
    to determine where to insert node.
Parameters:
    I  NodeT **pp                A double pointer to a NodeT structure
    I  Element value             Element structure containing data to
                                 be added by allocateNodeT
    I  char szParentId[]         Array containing the szId of the 
                                 parent node
    I char cYN                   Y refers to the right
                                 R refers to the left
Returns:
    NULL    - if no node was added
    NodeT * - if a node was successfully inserted
Notes:
    1.) Function makes the assumption that the parent node exists and 
    that the node itself does not already exist.  It determines this 
    from the driver file, which should have ensured that the parent 
    exists and that the node does not already exist.
    2.) The address passed in via the pp argument is the node of the
    parent which will receive a new child.
    3.) If the value of cYN == 'N' then the child goes to the left.
        If the value of cYN == 'Y' then the child goes to the right.
        (i.e., If 'N' (*pp)->pLeft = allocatedNodeT(value)
               else (*pp)->pRight = allocateNodeT(value))
**************************************************************************/
NodeT * insertT(NodeT **pp, Element value, char szParentId[], char cYN)
{
	NodeT *pFind;
	if (*pp == NULL)
		return NULL;
	if (strcmp((*pp)->element.szId, szParentId) == 0)
	{
		if (cYN == 'N')
		{
			(*pp)->pLeft = allocateNodeT(value);
			return *pp;
		}
		else
		{
			(*pp)->pRight = allocateNodeT(value);
			return *pp;
		}
	}
    pFind = insertT(&((*pp)->pLeft), value, szParentId, cYN);
	if (pFind != NULL)
		return pFind;
	else
		return insertT(&((*pp)->pRight), value, szParentId, cYN);
}
/************************ findParent ************************************
NodeT * findParent(NodeT *p, char szId[], char *cLR)
Purpose:
    Recursively traverses tree to find the parent node corresponding to
    a given child (szId). 
Parameters:
    I  NodeT *p              pointer to the current tree node
    I  char szId[]           Id of child to be found
    O  char *cLR             Stores a char (L or R)
Returns:
    NodeT * -  to the parent or NULL.
    L or R  -  is returned via parameter corresponding to what side  of 
               the parent the child is on.
Notes:
    Takes as an argument a pointer to a nodeT from our tree.  It looks
    at both the p->pLeft and the p->pRight to determine if the corresponding 
    child (szId) has been found.  If one of the pointers belongs to the 
    child we are searching for we return the address of the parent.  If no
    match is found, NULL is returned.
**************************************************************************/
NodeT * findParent(NodeT *p, char szId[], char *cLR)
{
	NodeT *pParentNodeLeft = p->pLeft;               // stores address of node to the left
	NodeT *pParentNodeRight = p->pRight;             // stores address of node to the right
	NodeT *pFind;
	if (p == NULL)
		return p;
	if (strcmp(pParentNodeLeft->element.szId, szId) == 0)
	{
		*cLR = 'L';
		return p;
	}
	if (strcmp(pParentNodeRight->element.szId, szId) == 0)
	{
		*cLR = 'R';
		return p;
	}
	pFind = findParent(p->pLeft, szId, cLR);
	if (pFind != NULL)
		return pFind;
	else
		return findParent(p->pRight, szId, cLR);
}
/**************************** delete *************************************
void delete(NodeT *p, char szId[], char cLR)
Purpose:
    Takes the id of a parent node, disassociates the respective child node
    and then passes the address of the child node to freeT(). 
Parameters:
    I  NodeT *p              pointer to the current tree node
    I  char szId[]           Id of child to be found
    I  char cLR              Side of parent child is on
Returns:
    N/A
Notes:
    Takes as an argument a pointer to a nodeT from our tree.  It looks
    at both the p->pLeft and the p->pRight to determine if the corresponding 
    child (szId) has been found.  If one of the pointers belongs to the 
    child we are searching for we return the address of the parent.  If no
    match is found, NULL is returned.  Function makes assumption that the
    address of the node passed in is the parent node.
**************************************************************************/
void delete(NodeT *p, char szId[], char cLR)
{   // p is assumed to be the parent node
	NodeT *pRemove;
	// exit function if called improperly with a NULL address
	if (p == NULL)
		return;
	// disassociate child from parent then send child 
	// and its tree to freeT
	if (cLR == 'L')
	{
		pRemove = p->pLeft;
		p->pLeft = NULL;
		freeT(pRemove);
	}
	else
	{ // child is on the right of the parent
		pRemove = p->pRight;
		p->pRight = NULL;
		freeT(pRemove);
	}
}

