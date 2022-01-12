#define _CRT_SECURE_NO_WARNINGS //disabling warnings caused by using "unsafe" functions

#include <iostream>
#include <fstream>
#include <string>
#include "MyFileSys.h"
using namespace std;

void myFileSys::badCharHeuristic(char* name, int ln, int badchar[NO_OF_CHARS]) // Preprocessing before using Boyer Moore's bad character heuristic 
{
    int i;
    for (i = 0; i < NO_OF_CHARS; i++) // At the beginning, all occurances are -1 
        badchar[i] = -1;
    for (i = 0; i < ln; i++)// Adding the actual index of when the character occured last time
        badchar[(int)name[i]] = i;
}
void myFileSys::update()
{
    ifstream windows_fd;
    ifstream ios_fd;
    windows_fd.open("WINDOWS.txt"); //you can modify the path and build a solution again to change the path
    ios_fd.open("IOS.txt");
    int i = 0; int j = 0;
    while (!windows_fd.eof()) //updating for the first folder
    {
        windows_fd >> fileName[0][i];
        i++;
    }
    while (!ios_fd.eof()) //updating for the second folder
    {
        ios_fd >> fileName[1][j];
        j++;
    }
    numFileFolder[0] = i;
    numFileFolder[1] = j;
    windows_fd.close();
    ios_fd.close();
}

void myFileSys::display() //Printing file and folder names
{
    cout << "========================" << endl << "Folder 0: Windows" << endl;
    for (int i = 0; i < numFileFolder[0]; i++) {
        cout << fileName[0][i] << endl;
    }
    cout << "###Number of files: " << numFileFolder[0] << endl << "========================" << endl << "Folder 1: IOS" << endl;
    for (int i = 0; i < numFileFolder[1]; i++) {
        cout << fileName[1][i] << endl;
    }
    cout << "###Number of files: " << numFileFolder[1] << endl << "========================" << endl;

}

bool myFileSys::ifWord(int folder_number, char* word)
{
    bool thereissuchword = false; //this variable is false by default. If the program cannot find this word, it remains as false
    for (int i = 0; i < numFileFolder[folder_number]; i++) //checking if the file exists in the folder with this number
    {
        if (strcmp(fileName[folder_number][i], word) == 0)
        {
            thereissuchword = true; //if the word found, the variable becomes "true"
        }
    }
    return thereissuchword; //returning the obtained value. If the word found, then it's true, else false.
}
void myFileSys::enter_menu()
{
    char answer[100];
    char stop[100] = "-1";
    while (true) //Making a loop for allowing user having multiple inputs
    {
        int folder_number;
        cout << "Please input your folder number (-1 to exit to main menu):" << endl;
        cin >> folder_number;
        if (folder_number == -1) { break; } //First condition to exit the program. If the user inputs "-1", then the program ends.
        cout << "Please input your file name(-1 to exit to main menu): " << endl;
        cin >> answer;
        if (strcmp(answer, stop) == 0) { break; } //Another condition to exit the program. If the user inputs "-1", then the program ends
        if (ifWord(folder_number, answer) == false)
        {
            strcpy(fileName[folder_number][numFileFolder[folder_number]], answer);
            cout << "#You added a new file called " << answer << "#" << endl;
            numFileFolder[folder_number]++;
        }
        else
        {
            cout << "This file already exists. Input another filename." << endl;
        }
    }
}
void myFileSys::saveall()
{
    ofstream windows_fd;
    ofstream ios_fd;
    windows_fd.open("WINDOWS.txt"); //IMPORTANT!!! Please change the following addresses to make the program work
    ios_fd.open("IOS.txt");
    for (int i = 0; i < numFileFolder[0]; i++) //updating for the first folder
    {
        windows_fd << fileName[0][i] << endl;
    }
    for (int i = 0; i < numFileFolder[1]; i++)  //updating for the first folder
    {
        ios_fd << fileName[1][i] << endl;
    }
    cout << "All files are saved\n";
    windows_fd.close();
    ios_fd.close();
}
void myFileSys::main_menu()
{
    while (true) //Making a loop for allowing user having multiple inputs
    {
        cout << "======Main Menu======\n" //display the user interface
            << "(0) - Display data\n"
            << "(1) - Enter your filename\n"
            << "(2) - Search an element\n"
            << "(3) - Save all changes\n"
            << "(-1) - Exit\n"
            << "====================\n"
            << "Please input your number:\n";
        int choice;
        cin >> choice; //depending on the user's choice, other functions will be called
        if (choice == 0) { display(); }
        if (choice == 1) { enter_menu(); }
        if (choice == 2) { search_menu(); }
        if (choice == 3) { saveall(); }
        if (choice == -1) { break; }
    }
}

/* A pattern searching Boyer Moore Algorithm */
bool myFileSys::search(char* textline, char* pattern) //textline is the text we are searching for the pattern
{ //The function returns did the pattern appear inside the text line
    int pattern_len = strlen(pattern);
    int text_len = strlen(textline);
    int badchar[NO_OF_CHARS];
    int numAppeared = 0;
    badCharHeuristic(pattern, pattern_len, badchar); //calling the private function doing preprocessing for the algorithm
    int shft = 0; //shft is the shift of the pattern given above with respect to the text line 
    while (shft <= (text_len - pattern_len))
    {
        int j = pattern_len - 1;
        while (j >= 0 && pattern[j] == textline[shft + j])
            j--;
        if (j < 0)
        {
            numAppeared++;
            shft += (shft + pattern_len < text_len) ? pattern_len - badchar[textline[shft + pattern_len]] : 1;
        }

        else
            shft += max(1, j - badchar[textline[shft + j]]);
    }
    if (numAppeared == 0) //if no appearances, then nothing found
        return false;
    else
        return true;
}
void myFileSys::search_menu() //menu function allowing the user to interact with the actual search function
{
    cout << "Enter your word you want to find:\n";
    char word[100];
    cin >> word;
    int totalOccurances = 0;
    for (int i = 0; i < numFileFolder[0]; i++) //Searching for the element in the 0th folder
    {
        if (search(fileName[0][i], word) == 1) //if the pattern occured, then it counts in total occurances
        {
            cout << "Found element " << fileName[0][i] << " with index " << i << " in folder 0\n";
            totalOccurances++;
        }
    }
    for (int i = 0; i < numFileFolder[1]; i++) //Searching for the element in the 1st folder
    {
        if (search(fileName[1][i], word) == 1)
        {
            cout << "Found element " << fileName[1][i] << " with index " << i << " in folder 1\n";
            totalOccurances++;
        }
    }
    if (totalOccurances == 0)
        cout << "Nothing found\n";
}

