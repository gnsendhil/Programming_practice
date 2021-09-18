/* Given a text file as an argument, your program will read the file, and output the 20
most frequently used words in the file in order, along with their frequency. */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SUCCESS 0
#define FAILURE 1
#define HASH_MAP_SIZE	1000
#define STRING_SIZE     100

#define NO_FREQ_WORDS   20

typedef struct tagHashNode{
	char *pString;
	int count;
	struct tagHashNode * next;
}HashNode_t;

char word[STRING_SIZE];

HashNode_t *LL_Head = NULL;
int LL_count = 0;

/* Hash table to store the string and corresponding count */
HashNode_t *hash_map[HASH_MAP_SIZE];
/* Array to store the valid hash index */
int hash_index_arr[HASH_MAP_SIZE], hash_index_cnt;

unsigned int ComputeHashKey(char *pString);
int InsertHashNodeToDescendingLL(HashNode_t *Node);
int Insert_String_toHashTable(char *pString);
int my_strlen(char *pString);
char * my_strcpy(char *dest, char *src);
int my_strcmp(char *s1, char *s2);




/* Parses the strings from text file and inserts into Hash table */
void ParseTextFile(FILE *fd){
    char ch;
    int index =0;
    while((ch = fgetc(fd)) != EOF)
    {
        /* add the characters in the below condition to ignore it */
        if((ch == ' ') || (ch == '\n') || (ch == '(') || (ch == ')') || (ch == '.') || (ch == ',') || (ch == ';') || (ch == '[') || (ch == ']')\
            || (ch == '{') || (ch == '}') || (ch == ':') || (ch == '"'))
        {
            word[index] = '\0';
            /* Send only the valid words. ignore empty spaces and empty lines */
            if( index != 0)
            {
                //printf("%s\n", word);
                Insert_String_toHashTable(word);
            }
            index = 0;
        }
        else
        {
            word[index] = ch;
            index++;
        }
    }
    if(index != 0)
    {
        word[index] = '\0';
        //printf("%s", word);
        Insert_String_toHashTable(word);
    }
}

/* Inserts the String to hash table */
int Insert_String_toHashTable(char *pString){
    HashNode_t  *temp_node, *prev_node;

    if(pString == NULL)
    {
        printf("LINE %d Invalid String\n", __LINE__);
        return FAILURE;
    }
    //printf("%s size %lu\n", pString, strlen(pString));
    
    unsigned int hash = ComputeHashKey( pString );
    int hash_index = hash % HASH_MAP_SIZE;
    
    /* No element present in the hash index */
    if(hash_map[hash_index] == NULL)
    {
        temp_node = (HashNode_t *)malloc(sizeof(HashNode_t));
        temp_node->count = 1;
        temp_node->next = NULL;
        temp_node->pString = (char *)malloc(my_strlen(pString) + 1);
        my_strcpy(temp_node->pString, pString);
        hash_map[hash_index] = temp_node;
        hash_index_arr[hash_index_cnt++] = hash_index;
        //printf("Inserted %s @ index %d\n", temp_node->pString, hash_index);
    }
    else
    {
        temp_node = hash_map[hash_index];
        while(temp_node != NULL)
        {
            if(my_strcmp(temp_node->pString, pString) == 0)
            {
                /* found a string already existing in hash, so increment the count */
                temp_node->count++;
                //printf("Incremented count for %s @ index %d and count is %d \n", temp_node->pString, hash_index, temp_node->count);
                break;
            }
            prev_node = temp_node;
            temp_node = temp_node->next;
        }
        /* No existing node matches with the string, add a new node */
        if(temp_node == NULL){
            temp_node = (HashNode_t *)malloc(sizeof(HashNode_t));
            temp_node->count = 1;
            temp_node->next = NULL;
            temp_node->pString = (char *)malloc(my_strlen(pString) + 1);
            my_strcpy(temp_node->pString, pString);
            prev_node->next = temp_node;
            //printf("Inserted %s @ index %d at the end of list \n", temp_node->pString, hash_index);
        }
    }
    return SUCCESS;
}

/* Compute Hash Key for incoming string */
unsigned int ComputeHashKey(char *pString){
	/* initialise with some prime number */
	unsigned int hash =4999;
	if(pString == NULL){
		printf("Incoming string is not valid\n");
		return FAILURE; 
	}
	while(*pString){
		hash += (hash << 5) + hash + *pString++;
	}
	
	return hash;
}

/* Removes the nodes from hash table and inserts into Linked list */
void ConsumeHashTableNodes(void)
{
    HashNode_t * temp_node;
    int hash_index;
    printf("hash index cnt %d\n", hash_index_cnt);
    for(int i=0; i<hash_index_cnt; i++)
    {
        hash_index = hash_index_arr[i];
        //printf("hash index %d i %d \n", hash_index, i);
        while(hash_map[hash_index]!= NULL)
        {
            temp_node = hash_map[hash_index];
            //printf("called InsertHashNodeToDescendingLL for the string %s and cnt %d\n", temp_node->pString, temp_node->count);
            hash_map[hash_index] = temp_node->next;
            InsertHashNodeToDescendingLL(temp_node);
        }
    }
}

/* The incoming node will be inserted into Linked List in descending order. The List will have NO_FREQ_WORDS nodes max at a time */
int InsertHashNodeToDescendingLL(HashNode_t *Node){
    /* First Element */
    if(LL_Head == NULL)
    {
        Node->next = NULL;
        LL_Head = Node;
        LL_count = 1;
    }
    else
    {
        HashNode_t *temp_node = LL_Head;
        HashNode_t *prev_node;
        while(temp_node != NULL)
        {
            if(temp_node->count >= Node->count)
            {
                prev_node = temp_node;
                temp_node = temp_node->next;
            }
            else
            {
                /* Insert at the begining of the list */
                if(temp_node == LL_Head)
                {
                    Node->next = LL_Head;
                    LL_Head = Node;
                    LL_count++;
                }
                else
                {
                    Node->next = temp_node;
                    prev_node->next = Node;
                    LL_count++;
                }
                break;
            }
        }

        /* Insert at the end of the list */
        if(temp_node == NULL)
        {
            Node->next = NULL;
            prev_node->next = Node;
            LL_count++;
        }
        /* Optimization */
        /* retain only 20 words at a time */
        if(LL_count > NO_FREQ_WORDS)
        {
            HashNode_t * temp = LL_Head;
            for(int i=1; i<NO_FREQ_WORDS; i++)
            {
                temp = temp->next;
            }
            free(temp->next->pString);
            free(temp->next);
            temp->next = NULL;
            LL_count = NO_FREQ_WORDS;
        }
    }
    return SUCCESS;
}

/* Prints the most occuring words */
void PrintStringOccurences(void)
{
    int count=0;
    HashNode_t * temp = LL_Head;
    while(temp != NULL)
    {
        printf("%d \t %s \n", temp->count, temp->pString);
        count++;
        temp = temp->next;
        if(count == 20)
            break;
    }
}

/* Not Implemented. Useful for debugging */
void ProfileHashMap(void)
{
}

/* Test API */
void TestComputeHashKey(void){
	char *p = "hello";
	printf("Hashvalue of %s is %u \n",p, ComputeHashKey(p));
    p = NULL;
    ComputeHashKey(p);
}

/* Test suite API */
void TestAPI(){
	TestComputeHashKey();
}

/* Entry to the program */
int main(int argc, char *argv[])
{
	//TestAPI();
    FILE *fd;
    char *p = argv[1];
    //printf("filename %s\n", p);

    fd = fopen(p,"rb");

    if(fd == NULL)
    {
        printf("File doesnt exists\n");
    }

    ParseTextFile(fd);
    //printf("ConsumeHashTableNodes called\n");
    ConsumeHashTableNodes();
    //printf("PrintStringOccurences called\n");
    PrintStringOccurences();
}

/* Util function */
int my_strlen(char *pString)
{
    int count = 0;

    while(*pString++)
        count++;

    return count;
}

/* Util function */
char * my_strcpy(char *dest, char *src)
{
    char *temp;
    if((dest == NULL) || (src == NULL))
        return NULL;

    temp = dest;
    while((*dest++ = *src++)){}
    return temp;
}

/* Util functions */
int my_strcmp(char *s1, char *s2)
{
    while(*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}
