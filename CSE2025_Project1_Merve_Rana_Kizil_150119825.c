// CSE2025 Data Structures - Project #1
// Merve Rana Kızıl - 150119825


#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;


Node* createNode(int data);
Node* addElement(Node* head, int data);
//void printLinkedList(Node* head);
Node* initializeLinkedList(int length);
int getLinkedListLength(Node* head);
Node* multiply(Node* multiplicand, Node* multiplier);
void freeLinkedList(Node* head);
Node* reverseLinkedList(Node* head);
void writeLinkedList(Node *multiplicand, Node* multiplier, Node* result);


/*void printLinkedList(Node* head){
    while(head != NULL){
        printf("%d", head->data);
        head = head->next;
        printf("\n");
    }
}*/

Node* createNode(int data){
    Node* newNode = malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->data = data;
    return newNode;
}

Node* addElement(Node* head, int data){
    Node* newNode = createNode(data);
    newNode->next = head;
    head = newNode;
    return head;
}


Node* initializeLinkedList(int length){

    Node* head = createNode(0);
    Node* temp = head;

    int i;
    for(i = 0; i<length-1; i++ ){
        head->next = createNode(0);
        head = head->next;
    }

    return temp;
}

int getLinkedListLength(Node* head){

    int counter = 0;

    while(head != NULL){
        head = head->next;
        counter++;
    }

    return counter;
}


Node* multiply(Node* multiplicand, Node* multiplier){

    Node* result = initializeLinkedList(getLinkedListLength(multiplicand)+ getLinkedListLength(multiplier) + 1); // max length
    Node* intermediate_result = result; // temp head for the result
    int currentResult;

    int step = 0;
    while(multiplier != NULL){

        int carry = 0;
        intermediate_result = result;

        int i;
        for(i=step;i>0;i--)
            intermediate_result = intermediate_result->next; // move one digit after each step

        while(multiplicand != NULL){

            currentResult = multiplicand->data * multiplier->data;
            carry = currentResult/10;
            intermediate_result->data = intermediate_result->data + currentResult%10;

            // find the carry and store it
            if(intermediate_result->data >= 10){
                carry += intermediate_result->data/10;
                intermediate_result->data = intermediate_result->data%10;
            }

            if(intermediate_result->next != NULL){
                intermediate_result = intermediate_result->next;
                // add the carry to the next digit
                intermediate_result->data = intermediate_result->data + carry;
            }

            // traverse multiplicand
            multiplicand = multiplicand->next;

        }

        // traverse multiplier
        multiplier = multiplier->next;
        step++;

    }

    return result;

}


void freeLinkedList(Node* head){
   Node* temp;

   while (head != NULL){
       temp = head;
       head = head->next;
       free(temp);
    }

}

Node* reverseLinkedList(Node* head) {
    Node* previous = NULL;
    Node* current = head;

    // traverse the linked list
    while (current != NULL){
        Node* next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }

    head = previous;

    return head;

}


// prints multiplicand, multiplier and result to file
void writeLinkedList(Node *multiplicand, Node* multiplier, Node* result){

    multiplicand = reverseLinkedList(multiplicand);
    multiplier = reverseLinkedList(multiplier);
    result = reverseLinkedList(result);

    FILE *fptr = fopen("output.txt", "w");

    fprintf(fptr, "multiplicand: ");

    while(multiplicand != NULL){
        fprintf(fptr, "%d", multiplicand->data);

        multiplicand = multiplicand->next;
    }

    fprintf(fptr, "\n");
    fprintf(fptr, "multiplier: ");


     while(multiplier != NULL){
        fprintf(fptr, "%d", multiplier->data);

        multiplier = multiplier->next;
    }

    fprintf(fptr, "\n");
    fprintf(fptr, "result: ");

    int flag = 0;

    while(result != NULL){
        while(result->data == 0 && flag == 0){
            result = result->next;
            flag = 1;
        }

        fprintf(fptr, "%d", result->data);
        result = result->next;
    }
}



int main() {

    Node* multiplicand = NULL;
    Node* multiplier = NULL;

    FILE *fptr = fopen ( "input.txt", "r");
    char ch = getc(fptr);

    int new_line = 0;


    // get the digits one by one
    while (ch != EOF) {
        if (ch == '\n'){
            new_line = 1;
        }else{
            if(new_line != 1){
                multiplicand = addElement(multiplicand, ch - '0');
            }
            else{
                multiplier = addElement(multiplier, ch - '0');
            }
        }
        ch = getc (fptr);
    }

    fclose (fptr);

    Node* result = multiply(multiplicand, multiplier);

    writeLinkedList(multiplicand, multiplier, result);

    //printLinkedList(result);

    freeLinkedList(multiplicand);
    freeLinkedList(multiplier);

    return 0;
}
