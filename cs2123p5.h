/**********************************************************************
cs2123p5.h
Purpose:
    Defines constants:
        max constants
        boolean constants
        error constants
        deletion constants
        insertT Error constants

    Defines typedef for
        Token
        For Diagnosis Tree:
            Element
            NodeT
        For TextList:
            TextEntry
            TextListImp
            TextList
 Protypes 
        TextList functions
        Diagnosis Tree functions
        Utility functions provided by Larry
Notes:

**********************************************************************/

/***  Constants ***/

// Maximum sizes

#define MAX_TOKEN_SIZE      50   // Maximum number of actual characters for a token
#define MAX_LINE_SIZE       100  // Maximum number of characters per input line
#define MAX_TEXT_LIST_SIZE  100  // Maximum size of Text List array
#define MAX_TEXT_SIZE       70   // Text Size for display text associated with Q or D
#define MAX_ID_SIZE         12   // Maximum size of an ID
#define MAX_NUMBER_ANSWERS  30   // When traversing tree, this is the maximum number 
                                 // answers to reach a leaf.
// Boolean Constants
#define TRUE 1
#define FALSE 0

// Error Constants
#define ERR_ALGORITHM       903
#define ERR_COMMAND_LINE    900    // invalid command line argument
#define ERR_DATA            905    // Bad input data

// exitUsage control 
#define USAGE_ONLY          0      // user only requested usage information
#define USAGE_ERR           -1     // usage error, show message and usage information

// Deletion Constants
#define DEL_NOT_FOUND 0
#define DEL_FOUND     2
#define DEL_DONE      3

// insertT Error Constants
#define ERR_NO_PARENT            800
#define ERR_NODE_ALREADY_EXISTS  801

/*** typedefs ***/

typedef char Token[MAX_TOKEN_SIZE + 1];     // token type to help with parsing

// Diagnosis Tree typedefs
typedef struct
{
    char cNodeType;                         // Q - Question, D - Diagnosis
    char szId[MAX_ID_SIZE + 1];             // id for the question or diagnosis
} Element;

typedef struct NodeT
{
    Element element;
    struct NodeT *pLeft;
    struct NodeT *pRight;
} NodeT;

// Text List typedefs  - used to equate an ID to a display string
typedef struct TextEntry
{
    char cType;                             // Q - Question, D - Diagnosis
    char szId[MAX_ID_SIZE + 1];             // id for the question or diagnosis
    char szText[MAX_TEXT_SIZE + 1];         // display text
} TextEntry;

typedef struct TextListImp
{
    int iNumEntry;                          // Number of entries in the Text array
    TextEntry arrayM[MAX_TEXT_LIST_SIZE];   // Contains the Text data for each Q or D
} TextListImp;
typedef TextListImp *TextList;

/*** Function Prototypes ***/

// TextList functions - already provided
void addTextEntry(TextList textList, TextEntry text);
char * getText(TextList textList, char *pszId);
int findText(TextList textList, char *pszId);
TextList newTextList();

// Diagnosis Tree functions
// Note:  Larry didn't include one for inserting into the tree since 
//        student's insertion function may be different.
char * help(NodeT *p, char szAnswers[], int iAns, TextList textList);
void prettyPrintT(NodeT *p, int iIndent, TextList textList);
void freeT(NodeT *p);
NodeT * searchT(NodeT *p, char szId[]);
NodeT * allocateNodeT(Element elem);
NodeT * insertT(NodeT **pp, Element value, char pszParentId[], char cYN);
NodeT * findParent(NodeT *p, char szId[], char *cLR);
void delete(NodeT *p, char szId[], char cLR);


// functions in most programs, but require modifications
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo);

// Utility routines provided by Larry (copy from program #2)
void ErrExit(int iexitRC, char szFmt[], ...);
char * getToken(char *pszInputTxt, char szToken[], int iTokenSize);


