#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Linked list structure
struct LinkedList {

    int lineNumber;
    LinkedList* next;

    LinkedList(int info) {

        this->lineNumber = info;
        this->next = NULL;
    }
};

// Doubly linked list
struct ListNode {

    string value; 
    LinkedList* head, *tail;
    ListNode* left, *right;

    ListNode(string text, int info) {

        this->value = text;
        this->head = new LinkedList(info);
        this->tail = this->head;
        this->left = this->right = NULL;
    }
};

// Checks if the head of the node is null
bool emptyHead(ListNode* head) {

    if (head == NULL) {
        
        return true;
    }

    else {

        return false;
    }
}

// Linear insertertion sorts the words in ascending order
void linearInsertion(ListNode*& head, string text, int info) {

    if (head->value == text) {

        LinkedList* temporaryValue = new LinkedList(info);
        (head->tail)->next = temporaryValue;
        head->tail = temporaryValue;

        return;
    }

    // Moves to the left if head->value is greater than the text value
    else if (head->value > text) {

        if (head->left != NULL) {

            linearInsertion(head->left, text, info);
        }

        else {

            head->left = new ListNode(text, info);
        }
    }

    // Moveas to the right if head->value is less than the text value
    else {

        if (head->right != NULL) {

            linearInsertion(head->right, text, info);
        }

        else {

            head->right = new ListNode(text, info);
        }
    }
}

// Creates an empty node and fills it using linear insertion
void insertNode(ListNode*& head, string text, int info) {

    // Creates a new head pointer if the emptyHead() function is true
    if (emptyHead(head)) {

        head = new ListNode(text, info);

        return;
    }
    
    linearInsertion(head, text, info);
}

// Displays the list
void outputSorting(ListNode*& node, int& counter) {

    if (emptyHead(node)) {

        return;
    }

    if (node->value == "") {

        outputSorting(node->left, counter);
    }

    else {

        outputSorting(node->left, counter);
        cout << (node->value) << " --> ";

        // Increments counter value per each new unique word
        counter++;
    }
    
    LinkedList* temporaryValue = node->head;

    while (temporaryValue != NULL) {

        if (node->value == "") {

            temporaryValue = temporaryValue->next;
        }

        else {

            cout << temporaryValue->lineNumber << " ";
            temporaryValue = temporaryValue->next;
        }
    }

    cout << endl;
    
    outputSorting(node->right, counter);
}

// Formats the words in order to print
string formatWords(string singleWord) {

    // Transforms the words to lowercase
    transform(singleWord.begin(), singleWord.end(), singleWord.begin(), ::tolower);

    int wordLength = singleWord.length();

    // Ensures the words are lowercase
    int i = 0;
    int j = wordLength - 1;

    for (; i < wordLength; ++i) {

        if (singleWord[i] >= 97 && singleWord[i] <= 122) {
            
            break;
        }
    }

    for (; j > -1; --j) {

        if (singleWord[j] >= 97 && singleWord[j] <= 122) {

            break;
        }
    }

    return singleWord.substr(i, j - i + 1);
}

// Deletes the list for the next file
void emptyList(ListNode** del) {

    ListNode* current = *del;
    ListNode* next;

    while (current != NULL) {

        next = current->right;
        free(current);
        current = next;
    }

    *del = NULL;
}

// Driver function
int main() {
    
    string userInput;

    // Counts the number of unique words in the file
    int counter = 0;

    while (true) {

        // Prompts the user for an input
        cout << "Enter a file name (Enter '*' to quit): ";
        cin >> userInput;

        ifstream inputFile;

        // Enter * to quit the program
        if (userInput == "*") {

            exit(EXIT_FAILURE);
        }

        // Opens the input file
        inputFile.open(userInput);

        // Prints an error if the file can't be opened
        if (!inputFile) {

            cout << "File doesn't exist! Try again" << endl;
            cout << endl;

            continue;
        }

        else {

            // Holds an entire line
            string oneLine;
            // Holds a single word
            string singleWord;

            int lineNumber = 1;
            string spaceSeparation = " ";

            // Creates a new list node
            ListNode* head = new ListNode(singleWord, lineNumber);

            // Loops until the end of the file is reached
            while (!inputFile.eof()) {

                getline(inputFile, oneLine);

                int beginning = 0;
                int ending = oneLine.find(spaceSeparation);

                while (ending != std::string::npos) {

                    singleWord = oneLine.substr(beginning, ending - beginning);
                    singleWord = formatWords(singleWord);
                    insertNode(head, singleWord, lineNumber);

                    beginning = ending + 1;
                    ending = oneLine.find(spaceSeparation, beginning);
                }

                singleWord = oneLine.substr(beginning, ending - beginning);
                singleWord = formatWords(singleWord);
                insertNode(head, singleWord, lineNumber);

                // Increments the line number to reach the next line
                lineNumber++;
            }

            // Displays the list
            outputSorting(head, counter);

            // Prints the number of unique words in the file
            cout << "Number of unique words: " << counter << endl;

            // Deletes the list
            emptyList(&head);

            cout << endl;
        }
    }
  
    return 0;
}
