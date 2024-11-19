/************************************************************************************************
Name:	    CoachLDEW
Date:	    11.18.2024
Purpose:    This program demonstrates a highlighted menu that cycles through the menu options using
            the arrow keys to move through the options            
*************************************************************************************************/
#include <iostream>			//This library contains standard input and output processes
#include <Windows.h>		//This library contains the function to control the cursor position
#include <conio.h>          //Provides basic console input/output functions
#include <chrono>           //This library provides a collection of types and functions to work with time
#include <thread>           //This library provides functions that access the current thread of execution


using namespace std;

void Cls();
void NoResize();
void HideCursor();
void GoToXY(double x, double y);
void SetConsoleColor(int textColor, int bgColor);
void DrawBorders(int xPos, int yPos, int width, int height);
void ConstructConsole(int width, int height, int fontW, int fontH, string fontName, string titleName);


//If the position of the highlighted item matches it's position in the list, then the color will be red, else it will be white
void SetColor(int a, int b)
{
    if (a == b)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
}


int main()
{
    bool gameOver = false;

    ConstructConsole(40, 20, 8, 16, "Consolas", "HIGHLIGHTED MENU");
    HideCursor();
    NoResize();

    int option = 1;         //Current menu option
    int min = 1;            //Minimum number of options in menu
    int max = 6;            //Maximum number of options in menu


    while (!gameOver)
    {
        DrawBorders(0, 0, 40, 20);
        //Menu Items
        GoToXY(17, 2);
        SetColor(option, 1);
        cout << "Item 1" << endl;

        GoToXY(17, 3);
        SetColor(option, 2);
        cout << "Item 2" << endl;

        GoToXY(17, 4);
        SetColor(option, 3);
        cout << "Item 3" << endl;

        GoToXY(17, 5);
        SetColor(option, 4);
        cout << "Item 4" << endl;


        GoToXY(17, 6);
        SetColor(option, 5);
        cout << "Item 5" << endl;

        GoToXY(17, 7);
        SetColor(option, 6);
        cout << "EXIT" << endl;

        while (true)
        {
            if (GetAsyncKeyState(VK_UP))
            {
                if (option > min)
                {
                    option--;
                    break;
                }
            }
            if (GetAsyncKeyState(VK_DOWN))
            {
                if (option < max)
                {
                    option++;
                    break;
                }
            }
            if (GetAsyncKeyState(VK_RETURN))
            {
                goto next;
            }
        }

        this_thread::sleep_for(chrono::milliseconds(100));
        Cls();

        if (false)
        {
            next:
            if (option == 1)
            {
                GoToXY(8, 10);
                cout << "Item 1 has been selected";
            }
            if (option == 2)
            {
                GoToXY(8, 10);
                cout << "Item 2 has been selected";
            }
            if (option == 3)
            {
                GoToXY(8, 10);
                cout << "Item 3 has been selected";
            }
            if (option == 4)
            {
                GoToXY(8, 10);
                cout << "Item 4 has been selected";
            }
            if (option == 5)
            {
                GoToXY(8, 10);
                cout << "Item 5 has been selected";
            }
            if (option == 6)
            {
                GoToXY(8, 10);
                cout << "Exiting the program...";
                this_thread::sleep_for(chrono::seconds(3));
                GoToXY(1, 11);
            }
            break;
        }
    }

	return 0;
}



void ConstructConsole(int width, int height, int fontW, int fontH, string fontName, string titleName)
{
    int screenWidth = 0;
    int screenHeight = 0;

    string title;

    //Initializing an object of wstring
    wstring tempTitle = wstring(titleName.begin(), titleName.end());

    //Applying c_str() method on temp
    LPCWSTR wideStringTitleName = tempTitle.c_str();

    //Places a title in the Title Bar;
    //SetConsoleTitle(L"Constuct Console");
    SetConsoleTitle(wideStringTitleName);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

    if (hOut == INVALID_HANDLE_VALUE)
        cout << "Bad Handle" << endl;

    screenWidth = width;
    screenHeight = height;

    // Change console visual size to a minimum so ScreenBuffer can shrink below the actual visual size
    SMALL_RECT sRECTWindow = { 0, 0, 1, 1 };
    SetConsoleWindowInfo(hOut, TRUE, &sRECTWindow);

    // Set the size of the screen buffer
    COORD coord = { (short)screenWidth, (short)screenHeight };
    if (!SetConsoleScreenBufferSize(hOut, coord))
        cout << "SetConsoleScreenBufferSize" << endl;

    // Assign screen buffer to the console
    if (!SetConsoleActiveScreenBuffer(hOut))
        cout << "SetConsoleActiveScreenBuffer" << endl;

    string font;

    //Initializing an object of wstring
    wstring temp = wstring(fontName.begin(), fontName.end());

    //Applying c_str() method on temp
    LPCWSTR wideStringFontName = temp.c_str();

    // Set the font size now that the screen buffer has been assigned to the console
    CONSOLE_FONT_INFOEX cfi;
    //Change the font
    lstrcpyW(cfi.FaceName, wideStringFontName);
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = fontW;
    cfi.dwFontSize.Y = fontH;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;

    if (!SetCurrentConsoleFontEx(hOut, false, &cfi))
        cout << "SetCurrentConsoleFontEx" << endl;

    //Get screen buffer info and check the maximum allowed window size. Return error if exceeded, so user knows their dimensions/fontsize 
    //are too large
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hOut, &csbi))
        cout << "GetConsoleScreenBufferInfo" << endl;
    if (screenHeight > csbi.dwMaximumWindowSize.Y)
        cout << "Screen Height / Font Height Too Big" << endl;
    if (screenWidth > csbi.dwMaximumWindowSize.X)
        cout << "Screen Width / Font Width Too Big" << endl;

    //Set Physical Console Window Size
    sRECTWindow = { 0, 0, (short)(screenWidth - 1), (short)(screenHeight - 1) };
    if (!SetConsoleWindowInfo(hOut, TRUE, &sRECTWindow))
        cout << "SetConsoleWindowInfo" << endl;

    //Set flags to allow mouse input		
    if (!SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
        cout << "SetConsoleMode" << endl;

    //Allocate memory for screen buffer
    CHAR_INFO* screenBuffer = new CHAR_INFO[screenWidth * screenHeight];
    memset(screenBuffer, 0, sizeof(CHAR_INFO) * screenWidth * screenHeight);
}//End ConstructConsole()

void GoToXY(double x, double y)
{
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);		//Get the ID of the console window

    COORD coord;								//Variable of type COORD that holds the X and Y position
    coord.X = x;
    coord.Y = y;

    //Takes two parameters.  The ID of the console window and Structure of the type COORD which are the coordinates where
    //we want to position the cursor.	
    SetConsoleCursorPosition(hOut, coord);
}//End GoToXY

void HideCursor()
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);		//Get the ID of the console window
    //Data Structure that controls the apearance of the cursor.  It has two attributes dwSize and bVisible
    CONSOLE_CURSOR_INFO cursor;
    //This attribute changes the size of the cursor. Here it is set at 100%
    cursor.dwSize = 100;
    //This Boolean attribute sets the cursor to visible or invisible.  False is invisible
    cursor.bVisible = false;

    //Manipulates the characteristics it takes two parameters.  The ID of the console window and a data structure that
    //handles the appearance of the cursor
    //You have to pass the cursor variable by reference so that it can make changes to the actual object
    SetConsoleCursorInfo(hCon, &cursor);
}//End HideCursor()

void SetConsoleColor(int textColor, int bgColor) {
    /************************************************************************************************
             0 - BLACK			6 - YELLOW			12 - LIGHTRED
             1 - BLUE			7 - WHITE			13 - LIGHTPURPLE
             2 - GREEN			8 - GREY			14 - LIGHTYELLOW
             3 - AQUA			9 - LIGHTBLUE		15 - BRIGHT WHITE
             4 - RED			10 - LIGHTGREEN
             5 - PURPLE			11 - LIGHTAQUA
************************************************************************************************/
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
}//End SetConsoleColor()


void DrawBorders(int xPos, int yPos, int width, int height)
{
    int tAndB = 205;			//Character code for top and bottom borders
    int lAndR = 186;			//Character code for left and right borders
    int topLeft = 201;			//Character code for top left corner
    int botLeft = 200;			//Character code for bottom left corner
    int topRight = 187;			//Character code for top right corner
    int botRight = 188;			//Character code for bottom right corner

    //Top & Bottom Borders
    for (int i = xPos; i < (xPos + (width - 1)); i++)
    {
        //Top horizontal border
        GoToXY(i, yPos);
        cout << (char)tAndB;

        //Bottom horizontal border
        GoToXY(i, ((yPos + 1) + (height - 2)));
        cout << (char)tAndB;
    }

    //Left & Right Borders
    for (int j = (yPos + 1); j < ((yPos + 1) + (height - 2)); j++)
    {
        //Left vertical border
        GoToXY(xPos, j);
        cout << (char)lAndR;

        //Right vertical border
        GoToXY((xPos + (width - 1)), j);
        cout << (char)lAndR;
    }

    //Corners
    //Top Left
    GoToXY(xPos, yPos);
    cout << (char)topLeft;

    //Bottom Left
    GoToXY(xPos, ((yPos + 1) + (height - 2)));
    cout << (char)botLeft;

    //Top Right
    GoToXY((xPos + (width - 1)), yPos);
    cout << (char)topRight;

    //Bottom Right
    GoToXY((xPos + (width - 1)), ((yPos + 1) + (height - 2)));
    cout << (char)botRight;
}//End DrawBorders()

void NoResize()
{
    //Create a HANDLE to the console window
    HWND console = GetConsoleWindow();
    if (console != NULL)
    {
        //Get the current window style
        LONG style = GetWindowLong(console, GWL_STYLE);

        //Remove the resizable style
        style &= ~WS_MAXIMIZEBOX;
        style &= ~WS_THICKFRAME;

        //Set the new style
        SetWindowLong(console, GWL_STYLE, style);
    }
}

void Cls()
{
    // Get the Win32 handle representing standard output.
    // This generally only has to be done once, so we make it static.
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD topLeft = { 0, 0 };

    // std::cout uses a buffer to batch writes to the underlying console.
    // We need to flush that to the console because we're circumventing
    // std::cout entirely; after we clear the console, we don't want
    // stale buffered text to randomly be written out.
    std::cout.flush();

    // Figure out the current width and height of the console window
    if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
        // TODO: Handle failure!
        abort();
    }
    DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

    DWORD written;

    // Flood-fill the console with spaces to clear it
    FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

    // Reset the attributes of every character to the default.
    // This clears all background colour formatting, if any.
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

    // Move the cursor back to the top left for the next sequence of writes
    SetConsoleCursorPosition(hOut, topLeft);
}