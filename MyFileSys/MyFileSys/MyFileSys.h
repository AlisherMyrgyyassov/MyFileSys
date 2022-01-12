class myFileSys
{
private:
    char fileName[2][100][100];
    char folderName[2][100];
    int numFileFolder[2];
# define NO_OF_CHARS 256
    void badCharHeuristic(char* name, int ln, int badchar[NO_OF_CHARS]);
public:
    void update();
    void display();
    bool ifWord(int folder_number, char* word);
    void enter_menu();
    void saveall();
    void main_menu();
    bool search(char* textline, char* pattern);
    void search_menu();
};