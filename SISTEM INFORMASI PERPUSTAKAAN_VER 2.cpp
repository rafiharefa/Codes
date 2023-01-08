#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <queue>

#define _WIN32_WINNT 0x0500

#include <windows.h>

using namespace std;

struct Node{
  string label;
  int id, stock;
  Node *FChild, *PNode, *NSibling;
  //FC : First Child - NS : Next Sibling - PS : Previous Node
};

Node *newNode, *root;

HWND WINAPI GetConsoleWindowNT(void)
{
    //declare function pointer type
    typedef HWND WINAPI(*GetConsoleWindowT)(void);
    //declare one such function pointer
    GetConsoleWindowT GetConsoleWindow;
    //get a handle on kernel32.dll
    HMODULE hk32Lib = GetModuleHandle(TEXT("KERNEL32.DLL"));
    //assign procedure address to function pointer
    GetConsoleWindow = (GetConsoleWindowT)GetProcAddress(hk32Lib
    ,TEXT("GetConsoleWindow"));
    //check if the function pointer is valid
    //since the function is undocumented
    if(GetConsoleWindow == NULL){
        return NULL;
    }
    //call the undocumented function
    return GetConsoleWindow();
}

COORD get_console_dimensions(void);
COORD get_console_cursor_pos(void);
void gotoxy(short x, short y);
void centered(char const *str);
void createNewTree( string label );
Node *InsertFChild( string label, Node *node );
Node *InsertNSibling( string label, Node *node );

vector<Node *>genre;
vector<Node *>title;
vector<int>borrow_duration;
vector<int>borrow_amount;
vector<string>borrow_title;
vector<int>borrow_temp;
vector<int>borrow_id;

queue<int>queue_duration;
queue<int>queue_duration2;
queue<int>queue_amount;
queue<int>queue_id;
queue<string>queue_title;
queue<int>queue_fee;

queue<int>temp_duration;
queue<int>temp_duration2;
queue<int>temp_amount;
queue<int>temp_id;
queue<string>temp_title;
queue<int>temp_fee;

void DeclareV();
bool genre_checking();
bool title_checking();
bool borrow_checking();
int Sub2();
int TotalBook();
int TotalStock();
void InsertGenre(int n);
void InsertTitle(int n);
void DeleteTitle(int n);
void DeleteGenre(int n);
void BorrowBook(int n);
void ReturnBook();


void iterativePreorder(Node * root, int child = 0){
    int num = 1;
    int num2 = 0;
	if (root == NULL)
        return;
 
    stack<Node*> nodeStack;
    nodeStack.push(root);
 
 	centered("=========================================================");
 	centered("|  NO.  | ID |            NAME            |    STOCK    |");
 	
    while (nodeStack.empty() == false){
        // Pop the top item from stack and print it
        struct Node* node = nodeStack.top();
        
        int a,b;
        a = node->label.length();
        b = node -> stock;
        int c = 0;
        
        while(b != 0){
        	b = b/10;
        	++c;
		}
        
        if(node -> label != ""){
		
		if(num >= 10){
			if(node -> id >= 10){
				centered("---------------------------------------------------------");
				cout << setw(14) << "|  " << num << setw(5) << "| " << node -> id << " | " << node -> label << setw(34 - a) << "|      ";
			}else{
				centered("---------------------------------------------------------");
			cout << setw(14) << "|  " << num << setw(5) << "| " << node -> id << "  | " << node -> label << setw(34 - a) << "|      ";
			}
		}else if(node -> id >= 10){
			centered("---------------------------------------------------------");
			cout << setw(15) << "|   " << num << setw(5) << "| " << node -> id << " | " << node -> label << setw(34 - a) << "|      ";
		}else{
			centered("---------------------------------------------------------");
			cout << setw(15) << "|   " << num << setw(5) << "| " << node -> id << "  | " << node -> label << setw(34 - a) << "|      ";
		}

		if(node -> stock != 0){
			cout << node -> stock << setw(8 - c) << "|" << endl;
			num2++;
		}else{
			cout << "-" << "      |";
			cout << endl;
		}
			num++;
			
		}
		
        nodeStack.pop();
        // Push NSibling and FChild children of the popped node to stack
        switch(child){
        	case 0 : {
        		if (node->NSibling)
           		nodeStack.push(node->NSibling);
        		if (node->FChild)
           		 nodeStack.push(node->FChild);
				break;
			}
			case 1 : {
				if (node->FChild)
           		nodeStack.push(node->FChild);
           		if (node->NSibling)
				break;
			}
			case 2 : {
				if (node->NSibling)
				nodeStack.push(node->NSibling);
				if (node->FChild)
				break;
			}
		
		}
        
    }
    		int total_book  = TotalBook();
			int total_stok = TotalStock();
			
			int d = total_stok;
			int e = 0;
    
    centered("=========================================================");

	if(total_stok >= 10 && total_stok < 100){
			cout << setw(27) <<"| TOTAL BOOKS : " << total_book << " | TOTAL STOCK : " << total_stok << " |                  |" << endl;
	}else if(total_stok >= 100 && total_stok <1000){
			cout << setw(27) <<"| TOTAL BOOKS : " << total_book << " | TOTAL STOCK : " << total_stok << " |                 |" << endl;
	}else if(total_stok >= 1000){
			cout << setw(27) <<"| TOTAL BOOKS : " << total_book << " | TOTAL STOCK : " << total_stok << " |                |" << endl;
	}
	else{
			cout << setw(27) <<"| TOTAL BOOKS : " << total_book << " | TOTAL STOCK : " << total_stok << " |                   |" << endl;
	}
    centered("=========================================================");
}

void History(){
	
	
	system("cls");
	centered(" ===============================================================================");
	centered(" |                                   HISTORY                                   |");
	centered(" ===============================================================================");
	centered(" |   TYPE   | ID |       TITLE       | DURATION[B] | DURATION[R] |  LATE FEES  |");
	
	temp_amount = queue_amount;
	temp_duration = queue_duration;
	temp_duration2 = queue_duration2;
	temp_id = queue_id;
	temp_title = queue_title;
	temp_fee=queue_fee;
	
	while(!queue_id.empty()){
		
		string a = queue_title.front();
		int b = a.length();
		int c[3];
		
		if(queue_duration.front() == 0){
			
			if(queue_id.front() >= 10){
				
				if(queue_duration.front() >= 10){
					
					if(queue_duration2.front() >= 10){
						
						if(queue_fee.front() >= 10){
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  RETURN  | " << queue_id.front() << " | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(7) << "|   " << queue_duration2.front() << " DAYS" << setw(10) << "|  RP. "  <<queue_fee.front() << ".000 |" << endl;
							
						}else{
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  RETURN  | " << queue_id.front() << " | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(7) << "|   " << queue_duration2.front() << " DAYS" << setw(10) << "|  RP. "  <<queue_fee.front() << ".000  |" << endl;
							
						}
						
					}else{
						
						if(queue_fee.front() >= 10){
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  RETURN  | " << queue_id.front() << " | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(7) << "|   " << queue_duration2.front() << " DAYS" << setw(11) << "|  RP. "  <<queue_fee.front() << ".000 |" << endl;
							
						}else{
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  RETURN  | " << queue_id.front() << " | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(7) << "|   " << queue_duration2.front() << " DAYS" << setw(11) << "|  RP. "  <<queue_fee.front() << ".000  |" << endl;
							
						}	
						
					}
					
				}else{
					
					if(queue_duration2.front() >= 10){
						
						if(queue_fee.front() >= 10){
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  RETURN  | " << queue_id.front() << " | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(8) << "|   " << queue_duration2.front() << " DAYS" << setw(10) << "|  RP. "  <<queue_fee.front() << ".000 |" << endl;
							
						}else{
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  RETURN  | " << queue_id.front() << " | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(8) << "|   " << queue_duration2.front() << " DAYS" << setw(10) << "|  RP. "  <<queue_fee.front() << ".000  |" << endl;
							
						}	
						
					}else{
						
						if(queue_fee.front() >= 10){
						
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  RETURN  | " << queue_id.front() << " | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(8) << "|   " << queue_duration2.front() << " DAYS" << setw(11) << "|  RP. "  <<queue_fee.front() << ".000 |" << endl;
						
						}else{
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  RETURN  | " << queue_id.front() << " | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(8) << "|   " << queue_duration2.front() << " DAYS" << setw(11) << "|  RP. "  <<queue_fee.front() << ".000  |" << endl;
							
						}
						
					}
				
				}
				
				
			}else{
				
				if(queue_duration.front() >= 10){
					
					if(queue_duration2.front() >= 10){
						
						if(queue_fee.front() >= 10){
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  RETURN  | " << queue_id.front() << "  | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(7) << "|   " << queue_duration2.front() << " DAYS" << setw(10) << "|  RP. "  <<queue_fee.front() << ".000 |" << endl;
							
						}else{
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  RETURN  | " << queue_id.front() << "  | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(7) << "|   " << queue_duration2.front() << " DAYS" << setw(10) << "|  RP. "  <<queue_fee.front() << ".000  |" << endl;
							
						}
						
					}else{
						
						if(queue_fee.front() >= 10){
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  RETURN  | " << queue_id.front() << "  | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(7) << "|   " << queue_duration2.front() << " DAYS" << setw(11) << "|  RP. "  <<queue_fee.front() << ".000 |" << endl;
							
						}else{
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  RETURN  | " << queue_id.front() << "  | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(7) << "|   " << queue_duration2.front() << " DAYS" << setw(11) << "|  RP. "  <<queue_fee.front() << ".000  |" << endl;
							
						}
						
					}
				
			
				}else{
					
					if(queue_duration2.front() >= 10){
						
						if(queue_fee.front() >= 10){
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  RETURN  | " << queue_id.front() << "  | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(8) << "|   " << queue_duration2.front() << " DAYS" << setw(10) << "|  RP. "  <<queue_fee.front() << ".000 |" << endl;
							
						}else{
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  RETURN  | " << queue_id.front() << "  | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(8) << "|   " << queue_duration2.front() << " DAYS" << setw(10) << "|  RP. "  <<queue_fee.front() << ".000  |" << endl;
							
						}
							
					}else{
						
						if(queue_fee.front() >= 10){
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  RETURN  | " << queue_id.front() << "  | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(8) << "|   " << queue_duration2.front() << " DAYS" << setw(11) << "|  RP. "  <<queue_fee.front() << ".000 |" << endl;
							
						}else{
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  RETURN  | " << queue_id.front() << "  | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(8) << "|   " << queue_duration2.front() << " DAYS" << setw(11) << "|  RP. "  <<queue_fee.front() << ".000  |" << endl;
							
						}
						
					}
					
				}
				
			}
			
		}else{
			
			if(queue_id.front() >= 10){
				
				if(queue_duration.front() >= 10){
					
					if(queue_duration2.front() >= 10){
						
						if(queue_fee.front() >= 10){
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  BORROW  | " << queue_id.front() << " | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(7) << "|   " << queue_duration2.front() << " DAYS" << setw(10) << "|  RP. "  <<queue_fee.front() << ".000 |" << endl;
							
						}else{
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  BORROW  | " << queue_id.front() << " | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(7) << "|   " << queue_duration2.front() << " DAYS" << setw(10) << "|  RP. "  <<queue_fee.front() << ".000  |" << endl;
							
						}
						
					}else{
						
						if(queue_fee.front() >= 10){
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  BORROW  | " << queue_id.front() << " | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(7) << "|   " << queue_duration2.front() << " DAYS" << setw(11) << "|  RP. "  <<queue_fee.front() << ".000 |" << endl;
							
						}else{
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  BORROW  | " << queue_id.front() << " | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(7) << "|   " << queue_duration2.front() << " DAYS" << setw(11) << "|  RP. "  <<queue_fee.front() << ".000  |" << endl;
							
						}	
						
					}
					
				}else{
					
					if(queue_duration2.front() >= 10){
						
						if(queue_fee.front() >= 10){
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  BORROW  | " << queue_id.front() << " | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(8) << "|   " << queue_duration2.front() << " DAYS" << setw(10) << "|  RP. "  <<queue_fee.front() << ".000 |" << endl;
							
						}else{
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  BORROW  | " << queue_id.front() << " | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(8) << "|   " << queue_duration2.front() << " DAYS" << setw(10) << "|  RP. "  <<queue_fee.front() << ".000  |" << endl;
							
						}	
						
					}else{
						
						if(queue_fee.front() >= 10){
						
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  BORROW  | " << queue_id.front() << " | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(8) << "|   " << queue_duration2.front() << " DAYS" << setw(11) << "|  RP. "  <<queue_fee.front() << ".000 |" << endl;
						
						}else{
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  BORROW  | " << queue_id.front() << " | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(8) << "|   " << queue_duration2.front() << " DAYS" << setw(11) << "|  RP. "  <<queue_fee.front() << ".000  |" << endl;
							
						}
						
					}
				
				}
				
				
			}else{
				
				if(queue_duration.front() >= 10){
					
					if(queue_duration2.front() >= 10){
						
						if(queue_fee.front() >= 10){
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  BORROW  | " << queue_id.front() << "  | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(7) << "|   " << queue_duration2.front() << " DAYS" << setw(10) << "|  RP. "  <<queue_fee.front() << ".000 |" << endl;
							
						}else{
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  BORROW  | " << queue_id.front() << "  | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(7) << "|   " << queue_duration2.front() << " DAYS" << setw(10) << "|  RP. "  <<queue_fee.front() << ".000  |" << endl;
							
						}
						
					}else{
						
						if(queue_fee.front() >= 10){
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  BORROW  | " << queue_id.front() << "  | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(7) << "|   " << queue_duration2.front() << " DAYS" << setw(11) << "|  RP. "  <<queue_fee.front() << ".000 |" << endl;
							
						}else{
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  BORROW  | " << queue_id.front() << "  | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(7) << "|   " << queue_duration2.front() << " DAYS" << setw(11) << "|  RP. "  <<queue_fee.front() << ".000  |" << endl;
							
						}
						
					}
				
			
				}else{
					
					if(queue_duration2.front() >= 10){
						
						if(queue_fee.front() >= 10){
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  BORROW  | " << queue_id.front() << "  | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(8) << "|   " << queue_duration2.front() << " DAYS" << setw(10) << "|  RP. "  <<queue_fee.front() << ".000 |" << endl;
							
						}else{
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  BORROW  | " << queue_id.front() << "  | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(8) << "|   " << queue_duration2.front() << " DAYS" << setw(10) << "|  RP. "  <<queue_fee.front() << ".000  |" << endl;
							
						}
							
					}else{
						
						if(queue_fee.front() >= 10){
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  BORROW  | " << queue_id.front() << "  | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(8) << "|   " << queue_duration2.front() << " DAYS" << setw(11) << "|  RP. "  <<queue_fee.front() << ".000 |" << endl;
							
						}else{
							
						centered(" |-----------------------------------------------------------------------------|");
						cout << " |  BORROW  | " << queue_id.front() << "  | "  << queue_title.front() << setw(22 - b) << "|   " << queue_duration.front() << " DAYS";
						cout << setw(8) << "|   " << queue_duration2.front() << " DAYS" << setw(11) << "|  RP. "  <<queue_fee.front() << ".000  |" << endl;
							
						}
						
					}
					
				}
				
			}
		
		}
		
		queue_id.pop();
		queue_amount.pop();
		queue_duration.pop();
		queue_duration2.pop();
		queue_fee.pop();
		queue_title.pop();
		
	}
	
 queue_amount=temp_amount;
 queue_duration=temp_duration;
 queue_duration2=temp_duration2;
 queue_fee=temp_fee;
 queue_id=temp_id;
 queue_title=temp_title;
	
	centered(" ===============================================================================");
	
}

int main(){
	HWND hWnd=GetConsoleWindowNT();
    MoveWindow(hWnd,0,0,680,540,TRUE);
	
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	
	DeclareV();
	createNewTree("root");
	
	system("color F");
	
	
	int vgenre = 0;
	int vtitle = 0;
	int vborrow = 0;
	int MenuOption;
	do{
		
	int num = 1;
	
	main_menu:	
	system("cls");
	cout << "\n" << endl;
	centered("=========================================================");
	centered("|                                                       |");
	centered("|         WELCOME TO LIBRARY INFORMATION SYSTEM         |");
	centered("|                                                       |");
	centered("=========================================================");
	centered("|                        MAIN MENU                      |");
	centered("=========================================================");
	centered("|                                                       |");
	centered("|                  ESC -> EXIT                          |");
	centered("|                  1   -> DISPLAY BOOKS                 |");
	centered("|                  2   -> MANAGE  BOOKS                 |");
	centered("|                  3   -> BORROWS BOOKS                 |");
	centered("|                  4   -> RETURN  BOOKS                 |");
	centered("|                  5   -> HISTORY                       |");
	centered("|                                                       |");
	centered("---------------------------------------------------------");
	cout << "\n\n";
	centered("TYPE KEY!");
	centered("---------");
	MenuOption = getch();
	if(cin.fail()){
		cout << endl;
		centered("INPUT NUMBER!");
		cout << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getch();
		goto main_menu;
	}
	
	int input;
	
	switch(MenuOption){
		case 27 : {
			cout << endl;
			centered("PROGRAM FINISHED!");
			return 0;
			break;
		}
		case 49 : {
			
			system("cls");
			cout << "\n\n";
			centered("=========================================================");
			centered("|                                                       |");
			centered("|               LIBRARY SYSTEM INFORMATION              |");
			centered("|                  GENRE AND BOOKS LIST                 |");
			centered("|                                                       |");
			if(genre_checking()){
				centered("=========================================================");
				centered("|                                                       |");
				centered("|                     LIST IS EMPTY                     |");
				centered("|                                                       |");
				centered("=========================================================");
			}else{
			iterativePreorder(genre[0], 0);
			}
			cout << "\n" << endl;
			centered("CLICK ENTER TO GO BACK TO MAIN MENU");
			break;
		}
		case 50 : {
		
		sub2:
			int sub = Sub2();
			
				if(sub == 1){
					InsertGenre(vgenre);
					InsertTitle(vtitle);
					vgenre++;
					vtitle++;
				}
				else if(sub == 2){
					if(root -> FChild == NULL){
						InsertGenre(vgenre);
						InsertTitle(vtitle);
						vgenre++;
						vtitle++;
					}else if(genre_checking()){
						InsertGenre(vgenre);
						InsertTitle(vtitle);
						vgenre++;
						vtitle++;
					}else{
					InsertTitle(vtitle);
					vtitle++;	
					}
					
				}else if(sub == 3){
					if(title.size() == 0){
					cout << endl;
					centered(" INSERT BOOK FIRST!");
					getch();
					goto sub2;
					}else{
						if(title_checking()){
							cout << endl;
							centered(" INSERT BOOK FIRST!");
							getch();
							goto sub2;
						}else{
							DeleteTitle(vtitle);
						}
					}
				}else if(sub == 4){
					if(genre.size() == 0){
					cout << endl;
					centered("INSERT GENRE FIRST!");
					getch();
					goto sub2;
					}else{
						if(genre_checking()){
							cout << endl;
							centered("INSERT GENRE FIRST!");
							getch();
							goto sub2;		
						}else{
							DeleteGenre(vgenre);
						}
					}
					
				}else if(sub == 0){
					goto main_menu;
				}
				else{
					cout << "\n\n";
					centered("INVALID CHOICE!");
					getch();
					goto sub2;
				}
			break;
		}
		case 51 : {
			if(title_checking()){
			cout << "\n";
			centered("INSERT BOOK FIRST!");
			getch();
			goto main_menu;
			}else{
			BorrowBook(vborrow);
			vborrow++;
			}
			break;
		}
		case 52 : {
			if(vborrow == 0){
				cout << "\n";
				centered("NOTHING TO BE RETURNED!");
				getch();
			goto main_menu;
			}else if(borrow_checking()){
				cout << "\n";
				centered("NOTHING TO BE RETURNED!");
				getch();
			goto main_menu;
			}else if(title_checking()){
				cout << "\n";
				centered("NOTHING TO BE RETURNED!");
				getch();
			}
			else{
				ReturnBook();
				}
			break;
		}
		case 53 : {
			if(queue_id.empty()){
				cout << "\n";
				centered("HISTORY IS EMPTY!");
			}else{
			History();
			}
			break;
		}
		default : {
			cout << endl;
			centered("INVALID CHOICE!");
			break;
		}
	}
	
		getch();
		
}while(MenuOption != 27);
	return 0;
}

void InsertGenre(int n){
	
	string input;
	
	InsertGenre :
	system("cls");
	cout << "\n" << endl;
	centered("=========================================================");
	centered("|               INSERT BOOK - INSERT GENRE              |");
	centered("=========================================================");
	centered("|                      GENRES LIST                      |");
	
	if(root -> FChild  == NULL){
		centered("---------------------------------------------------------");
		centered("|                                                       |");
		centered("|                  GENRE LIST IS EMPTY                  |");
		centered("|                                                       |");
		centered("---------------------------------------------------------");
	}else if(genre_checking()){
		centered("---------------------------------------------------------");
		centered("|                                                       |");
		centered("|                  GENRE LIST IS EMPTY                  |");
		centered("|                                                       |");
		centered("---------------------------------------------------------");
	}else{
	iterativePreorder(genre[0], 2);
	}
	
	cout << "\n" << endl;
	centered("INSERT NEW GENRE");
	centered("----------------");
	cout << "\t\t\t\t  ";
	cin.ignore();
	getline(cin, input);
	
	if(root -> FChild == NULL){
		genre.insert(genre.begin(), InsertFChild(input, root));
		genre[n] -> id = n;
	}else{
		genre.insert(genre.begin() + n, InsertNSibling(input, genre[n-1]));
		genre[n] -> id = n;
	}
	
	cout << endl;
	cout << endl;
	centered("GENRE SUCCESSFULLY INSERTED TO THE LIST!");
	getch();
	

	
}

void InsertTitle(int n){
	
	string input;
	int input_stok;
	int choose;
	int num= 1;
	
	InsertTitle:
	system("cls");
	cout << "\n" << endl;
	centered("=========================================================");
	centered("|               INSERT BOOK - CHOOSE GENRE              |");
	centered("=========================================================");
	centered("|                      GENRES LIST                      |");
	
	
	if(root -> FChild  == NULL){
		centered("---------------------------------------------------------");
		centered("|                                                       |");
		centered("|                  GENRE LIST IS EMPTY                  |");
		centered("|                                                       |");
		centered("---------------------------------------------------------");
	
	}else if(genre_checking()){
		centered("---------------------------------------------------------");
		centered("|                                                       |");
		centered("|                  GENRE LIST IS EMPTY                  |");
		centered("|                                                       |");
		centered("---------------------------------------------------------");
	}
	
	else{
	iterativePreorder(genre[0], 2);
	}

	cout << "\n" << endl;
	centered("CHOOSE GENRE ID");
	centered("---------------");
	cout << setw(39) << " ";cin >> choose;
	
	if(cin.fail()){
		cout << endl;
		centered("INPUT NUMBER!");
		cout << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getch();
		goto InsertTitle;
	}
	
	if(choose >= genre.size()){
		cout << "\n\n";
		centered("INVALID CHOICE!");
		getch();
		goto InsertTitle;	
	}else{
		
	InsertTitle2 :
	system("cls");
	cout << "\n" << endl;
	centered("=========================================================");
	centered("|               INSERT BOOK - INSERT TITLE              |");
	centered("=========================================================");
	centered("|                       BOOK LIST                       |");
	
	
	if(genre[choose] -> FChild == NULL){
		centered("---------------------------------------------------------");
		centered("|                                                       |");
		centered("|                  BOOKS LIST IS EMPTY                  |");
		centered("|                                                       |");
		centered("---------------------------------------------------------");
	}else if(title_checking()){
		centered("---------------------------------------------------------");
		centered("|                                                       |");
		centered("|                  BOOKS LIST IS EMPTY                  |");
		centered("|                                                       |");
		centered("---------------------------------------------------------");
	}else{
	iterativePreorder(genre[choose] -> FChild, 2);
	cout << endl;
	}
	
	
	cout << "\n" << endl;
	centered("INPUT BOOK TITLE");
	centered("----------------");
	cout << "\t\t\t\t  ";
	cin.ignore();
	getline(cin, input);
	cout << endl;
	
	if(input == genre[choose] -> label){
		cout << "\n\n";
		centered("BOOK TITLE MUST BE DIFFERENT WITH GENRE NAME");
		getch();
		goto InsertTitle2;
	}
	
	book_stock :
	
	system("cls");
	cout << "\n" << endl;
	centered("=========================================================");
	centered("|               INSERT BOOK - INSERT STOCK              |");
	centered("=========================================================");
	centered("|                       BOOK LIST                       |");
	
	
	if(genre[choose] -> FChild == NULL){
		centered("---------------------------------------------------------");
		centered("|                                                       |");
		centered("|                  BOOKS LIST IS EMPTY                  |");
		centered("|                                                       |");
		centered("---------------------------------------------------------");
	}else if(title_checking()){
		centered("---------------------------------------------------------");
		centered("|                                                       |");
		centered("|                  BOOKS LIST IS EMPTY                  |");
		centered("|                                                       |");
		centered("---------------------------------------------------------");
	}else{
	iterativePreorder(genre[choose] -> FChild, 2);
	cout << endl;
	}
	
	cout << "\n" << endl;
	centered("INPUT BOOK STOCK");
	centered("----------------");
	cout << setw(38) << " ";cin >> input_stok;
	
	if(cin.fail()){
		cout << endl;
		centered("INPUT NUMBER!");
		cout << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getch();
		goto book_stock;
	}
	
	if(input_stok <= 0){
		cout << "\n\n";
		centered("BOOK STOCK MUST BE GREATER THAN 0!");
		getch();
		goto book_stock;
	}
	
	if(genre[choose] -> FChild == NULL){
		title.push_back(InsertFChild(input, genre[choose]));
		title[n] -> id = n;
		title[n] -> stock = input_stok;
		
		cout << "\n\n";
		centered("BOOK SUCCESSFULLY INSERTED TO THE LIST");
		

	}else{
		int temp;
		for(int i = 0;i < title.size();i++){
			if(title[i] == genre[choose] -> FChild){
				temp = i;
			}
		}
		
		if(title[temp] -> NSibling != NULL){
		for(int i = 0;i < title.size();i++){
			if(title[i] == title[temp] -> NSibling){
				temp = i;
				}
			}
		
			title.push_back( InsertNSibling(input, title[temp]));
			title[n] -> id = n;
			title[n] -> stock = input_stok;
			
			cout << "\n\n";
			centered("BOOK SUCCESSFULLY INSERTED TO THE LIST");
		
		}
		
		else{
			
			title.push_back(InsertNSibling(input, title[temp]));
			title[n] -> id = n;	
			title[n] -> stock = input_stok;
			
			cout << "\n\n";
			centered("BOOK SUCCESSFULLY INSERTED TO THE LIST");
			
	}
	
				
	}

}

}

void BorrowBook(int n){
	
	int choose, choose2;
	
	BorrowBook:
	system("cls");
	cout << "\n" << endl;
	centered("=========================================================");
	centered("|               BORROW BOOK - CHOOSE GENRE              |");
	centered("=========================================================");
	centered("|                      GENRES LIST                      |");
	
	
	if(root -> FChild  == NULL){
		centered("---------------------------------------------------------");
		centered("|                                                       |");
		centered("|                  GENRE LIST IS EMPTY                  |");
		centered("|                                                       |");
		centered("---------------------------------------------------------");
	
	}else if(genre_checking()){
		centered("---------------------------------------------------------");
		centered("|                                                       |");
		centered("|                  GENRE LIST IS EMPTY                  |");
		centered("|                                                       |");
		centered("---------------------------------------------------------");
	}
	
	else{
	iterativePreorder(genre[0], 2);
	}

	cout << "\n" << endl;
	centered("CHOOSE GENRE ID");
	centered("---------------");
	cout << setw(39) << " ";cin >> choose;
	
	if(cin.fail()){
		cout << endl;
		centered("INPUT NUMBER!");
		cout << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getch();
		goto BorrowBook;
	}
	
	if(genre[choose] == NULL){
		cout << "\n\n";
		centered("INVALID CHOICE!");
		getch();
		goto BorrowBook;	
	}
//	else if(genre[choose] -> FChild -> label == ""){
//		cout << "\n\n";
//		centered("THIS GENRE HAS NO BOOKS!");
//		getch();
//		goto BorrowBook;
//	}
	else{
		
	BorrowBook2 :
	system("cls");
	cout << "\n" << endl;
	centered("=========================================================");
	centered("|               BORROW BOOK - CHOOSE BOOKS              |");
	centered("=========================================================");
	centered("|                       BOOK LIST                       |");
	
	
	if(genre[choose] -> FChild == NULL){
		centered("---------------------------------------------------------");
		centered("|                                                       |");
		centered("|                  BOOKS LIST IS EMPTY                  |");
		centered("|                                                       |");
		centered("---------------------------------------------------------");
	}else if(title_checking()){
		centered("---------------------------------------------------------");
		centered("|                                                       |");
		centered("|                  BOOKS LIST IS EMPTY                  |");
		centered("|                                                       |");
		centered("---------------------------------------------------------");
	}else{
	iterativePreorder(genre[choose] -> FChild, 2);
	cout << endl;
	}
	
	cout << "\n";
	centered("CHOOSE BOOK ID");
	centered("--------------");
	cout << setw(39) << " ";cin >> choose2;
	
	if(cin.fail()){
		cout << endl;
		centered("INPUT NUMBER!");
		cout << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getch();
		goto BorrowBook2;
	}
	
	if(title[choose2] == NULL){
		cout << "\n\n";
		centered("INVALID CHOICE!");
		getch();
		goto BorrowBook2;
	}else{
	
	if(title[choose2] -> stock <= 0){
		cout << "\n\n";
		centered("BOOK YOU SELECTED IS OUT OF STOCK");
		getch();
		goto BorrowBook2;
	}
		
	int amount;
	
	BorrowBook3 :
	system("cls");
	cout << "\n" << endl;
	centered("=========================================================");
	centered("|               BORROW BOOK - INSERT AMOUNT             |");
	centered("=========================================================");
	centered("|                       BOOK LIST                       |");
	
	
	if(genre[choose] -> FChild == NULL){
		centered("---------------------------------------------------------");
		centered("|                                                       |");
		centered("|                  BOOKS LIST IS EMPTY                  |");
		centered("|                                                       |");
		centered("---------------------------------------------------------");
	}else if(title_checking()){
		centered("---------------------------------------------------------");
		centered("|                                                       |");
		centered("|                  BOOKS LIST IS EMPTY                  |");
		centered("|                                                       |");
		centered("---------------------------------------------------------");
	}else{
	iterativePreorder(genre[choose] -> FChild, 2);
	cout << endl;
	}	
	
	cout << "\n";
	centered("AMOUNT OF BOOKS YOU TO BORROW");
	centered("-----------------------------");
	cout << setw(39) << " ";cin >> amount;
	
	if(cin.fail()){
		cout << endl;
		centered("INPUT NUMBER!");
		cout << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getch();
		goto BorrowBook3;
	}
	
	if(amount >= title[choose2] -> stock){
		cout << "\n\n";
		centered("AMOUNT OF BOOK MUST BE LESS THAN STOCK!");
		getch();
		goto BorrowBook3;
	}else if(amount < 0){
		cout << "\n\n";
		centered("AMOUNT OF BOOK MUST BE GREATER THAN 0!");
		getch();
		goto BorrowBook3;
	}
	
	int duration;
	
	BorrowBook4 :
	system("cls");
	cout << "\n" << endl;
	centered("=========================================================");
	centered("|              BORROW BOOK - INSERT DURATION            |");
	centered("=========================================================");
	centered("|                       BOOK LIST                       |");
	
	
	if(genre[choose] -> FChild == NULL){
		centered("---------------------------------------------------------");
		centered("|                                                       |");
		centered("|                  BOOKS LIST IS EMPTY                  |");
		centered("|                                                       |");
		centered("---------------------------------------------------------");
	}else if(title_checking()){
		centered("---------------------------------------------------------");
		centered("|                                                       |");
		centered("|                  BOOKS LIST IS EMPTY                  |");
		centered("|                                                       |");
		centered("---------------------------------------------------------");
	}else{
	iterativePreorder(genre[choose] -> FChild, 2);
	cout << endl;
	}
	
	cout << "\n"; 
	centered("BORROWING DURATION [DAYS] - MAXIMUM DURATION IS 30 DAYS");
	centered("-------------------------------------------------------");
	cout << setw(39) << " ";cin >> duration;
	
	if(cin.fail()){
		cout << endl;
		centered("INPUT NUMBER!");
		cout << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getch();
		goto BorrowBook4;
	}else if(duration > 30){
		cout << endl;
		centered("MAXIMUM DURATION IS 30 DAYS");
		getch();
		goto BorrowBook4;
	}else if(duration <= 0){
		cout << endl;
		centered("DURATION MUST BE GREATER THAN 0");
		getch();
		goto BorrowBook4;
	}
	
	title[choose2] -> stock = title[choose2] -> stock - amount;
	borrow_duration.insert(borrow_duration.begin() + n, duration);
	borrow_amount.insert(borrow_amount.begin() + n, amount);
	borrow_title.insert(borrow_title.begin() + n, title[choose2] -> label);
	borrow_temp.insert(borrow_temp.begin() + n, choose2);
	borrow_id.insert(borrow_id.begin() + n, n);
	
	queue_duration.push(duration);
	queue_duration2.push(0);
	queue_fee.push(0);
	queue_title.push(title[choose2] -> label);
	queue_id.push(n);
	
	cout << "\n\n";
	centered("BOOK SUCCESSFULLY BORROWED");
	cout << endl;
	cout << "\t\t\t       " << "BORROWING ID : " << borrow_id[n] << endl;
	cout << "\t\t\t       " << "----------------" << endl;	
		}
	
	}

}

void ReturnBook(){
	
	ReturnBook :
	system("cls");
	cout << "\n" << endl;
	centered("=========================================================");
	centered("|               RETURN BOOK - CHOOSE BORROW             |");
	centered("=========================================================");
	centered("|                      BORROW LIST                      |");
	centered("---------------------------------------------------------");
	cout << "\n\n";
	
	int num = 1;
	
	for(int i = 0;i < borrow_amount.size();i++){
		if(borrow_amount[i] != 0){
		cout << setw(32) << num << ". BORROW ID : " << borrow_id[i] << endl;
		centered("----------------");
		num++;
		}
	}
	
	cout << "\n\n";
	
	int choose;
	
	centered("CHOOSE BORROW ID");
	centered("----------------");
	cout << setw(39) << " ";cin >> choose;
	if(cin.fail()){
		cout << endl;
		centered("INPUT NUMBER!");
		cout << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getch();
		goto ReturnBook;
	}else if(choose >= borrow_amount.size()){
		cout << endl;
		centered("INVALID CHOICE!");
		getch();
		goto ReturnBook;
	}else if(borrow_id[choose] == -1){
		cout << endl;
		centered("INVALID CHOICE!");
		getch();
		goto ReturnBook;
	}
	
	int duration;
	ReturnBook2 :
	system("cls");
	cout << "\n" << endl;
	centered("=========================================================");
	centered("|               RETURN BOOK - CHOOSE BORROW             |");
	centered("=========================================================");
	centered("|                      BORROW INFO                      |");
	centered("---------------------------------------------------------");
	cout << "\n\n";
	cout << "\t\t\t  BORROW ID       : " << borrow_id[choose] << endl;
	cout << "\t\t\t  BOOK   TITLE    : " << borrow_title[choose] << endl;
	cout << "\t\t\t  BORROW AMOUNT   : " << borrow_amount[choose] << endl;
	cout << "\t\t\t  BORROW DURATION : " << borrow_duration[choose] << " DAYS" << endl;
	cout << "\n\n";
	centered("BOOK RETURN DURATION [DAYS]");
	centered("---------------------------");
	cout << setw(38) << " ";cin >> duration;
	
	if(cin.fail()){
		cout << endl;
		centered("INPUT NUMBER!");
		cout << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getch();
		goto ReturnBook2;
	}else if(duration < 0){
		cout << endl;
		centered("INPUT DURATION CORRECTLY!");
		getch();
		goto ReturnBook2;
	}
	
	int fee = 0;
	
	if(duration > borrow_duration[choose]){
		fee = duration - borrow_duration[choose];
		cout << endl;
		cout << "\t\t\t     LATE FEES : RP." << fee << ".000 "<< endl;
		centered("---------------------");
	}
	cout << endl;
	centered("BOOK SUCCESSFULLY RETURNED");
	
	int a = borrow_temp[choose];
	int b = borrow_amount[choose];
	title[a] -> stock = title[a] -> stock + b;
	
	queue_duration.push(0);
	queue_duration2.push(duration);
	queue_fee.push(fee);
	queue_title.push(borrow_title[choose]);
	queue_id.push(borrow_id[choose]);
	
	borrow_amount[choose] = 0;
	borrow_duration[choose] = 0;
	borrow_temp[choose] = 0;
	borrow_title[choose] = "";
	borrow_id[choose] = -1;
	
}

int TotalStock(){
	int total_stok;
	for(int i = 0;i < title.size();i++){
		if(title[i] -> stock != 0){
			total_stok += title[i] -> stock - 1;
		}
	}
	return total_stok;
}

int TotalBook(){
	int total = 0;
	for(int i = 0;i < title.size();i++ ){
		
		if(title[i] -> label != ""){
			total++;
		}

	}
	return total;
	
}

void DeleteTitle(int n){
	
	int option;
	
	delete_sub:
	system("cls");
	cout << "\n" << endl;
	centered("=========================================================");
	centered("|               DELETE BOOK - CHOOSE GENRE              |");
	centered("=========================================================");
	centered("|                      GENRES LIST                      |");
	
	
	if(root -> FChild  == NULL){
		centered("---------------------------------------------------------");
		centered("|                                                       |");
		centered("|                  GENRE LIST IS EMPTY                  |");
		centered("|                                                       |");
		centered("---------------------------------------------------------");
	
	}else if(genre_checking()){
		centered("---------------------------------------------------------");
		centered("|                                                       |");
		centered("|                  GENRE LIST IS EMPTY                  |");
		centered("|                                                       |");
		centered("---------------------------------------------------------");
	}
	
	else{
	iterativePreorder(genre[0], 2);
	}
	
	int choose;
	cout << "\n" << endl;
	centered("CHOOSE GENRE ID");
	centered("---------------");
	cout << setw(39) << " ";cin >> choose;
	
	if(cin.fail()){
		cout << endl;
		centered("INPUT NUMBER!");
		cout << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getch();
		goto delete_sub;
	}
	
	if(choose >= genre.size()){
		cout << endl;
		centered("INVALID CHOICE!");
		getch();
		goto delete_sub;
	}else{
		
	delete_sub2:
	system("cls");
	cout << "\n" << endl;
	centered("=========================================================");
	centered("|               DELETE BOOK - CHOOSE BOOKS              |");
	centered("=========================================================");
	centered("|                      GENRES LIST                      |");
	
	
	if(root -> FChild  == NULL){
		centered("---------------------------------------------------------");
		centered("|                                                       |");
		centered("|                  BOOKS LIST IS EMPTY                  |");
		centered("|                                                       |");
		centered("---------------------------------------------------------");
	
	}else if(genre_checking()){
		centered("---------------------------------------------------------");
		centered("|                                                       |");
		centered("|                  BOOKS LIST IS EMPTY                  |");
		centered("|                                                       |");
		centered("---------------------------------------------------------");
	}
	
	else{
	iterativePreorder(genre[choose] -> FChild, 2);
	}
	
	cout << "\n" << endl;
	centered("CHOOSE BOOK ID");
	centered("--------------");
	cout << setw(38) << " ";cin >> option;
	
	if(cin.fail()){
		cout << endl;
		centered("INPUT NUMBER!");
		cout << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getch();
		goto delete_sub2;
	}
	
	if(title[option] == NULL){
		cout << endl;
		centered("INVALID CHOICE!");
		getch();
		goto delete_sub2;
	}else if(option >= n){
		cout << endl;
		centered("INVALID CHOICE!");
		getch();
		goto delete_sub2;	
	}else if(title[option] -> label == ""){
		cout << endl;
		centered("INVALID CHOICE!");
		getch();
		goto delete_sub2;
	}
	else{
	title[option] -> label = "";
	title[option] -> stock = 0;
	
	for(int i = 0;i < borrow_temp.size();i++){
		if(borrow_temp[i] == option){
		borrow_amount[i] = 0;
		borrow_duration[i] = 0;
		borrow_temp[i] = 0;
		borrow_title[i] = "";
		borrow_id[i] = -1;
			}
		}
	}


	cout << "\n" << endl;
	
	
	centered("BOOK SUCCESSFULLY DELETED");

	}
}

void DeleteGenre(int n){

	int option;
	
	delete_sub:
	system("cls");
	cout << "\n" << endl;
	centered("=========================================================");
	centered("|               DELETE BOOK - CHOOSE GENRE              |");
	centered("=========================================================");
	centered("|                      GENRES LIST                      |");
	
	
	if(root -> FChild  == NULL){
		centered("---------------------------------------------------------");
		centered("|                                                       |");
		centered("|                  GENRE LIST IS EMPTY                  |");
		centered("|                                                       |");
		centered("---------------------------------------------------------");
	
	}else if(genre_checking()){
		centered("---------------------------------------------------------");
		centered("|                                                       |");
		centered("|                  GENRE LIST IS EMPTY                  |");
		centered("|                                                       |");
		centered("---------------------------------------------------------");
	}
	
	else{
	iterativePreorder(genre[0], 2);
	}
	
	cout << "\n" << endl;
	centered("CHOOSE GENRE ID");
	centered("---------------");
	cout << setw(38) << " ";cin >> option;
	
	if(cin.fail()){
		cout << endl;
		centered("INPUT NUMBER!");
		cout << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getch();
		goto delete_sub;
	}
		
	
	if(genre[option] == NULL){
		cout << endl;
		centered("INVALID CHOICE!");
		getch();
		goto delete_sub;
	}else if(option >= n){
		cout << endl;
		centered("INVALID CHOICE!");
		getch();
		goto delete_sub;	
	}else if(genre[option] -> label == ""){
		cout << endl;
		centered("INVALID CHOICE!");
		getch();
		goto delete_sub;
	}
	else{
	genre[option] -> label = "";
	}
	
	if(genre[option] != NULL){
		
		for(int i = 0;i < title.size();i++){
			if(title[i] -> PNode == genre[option]){
				title[i] -> label = "";
				title[i] -> stock = 0;
//				stock[i] = 0;

				for(int j = 0;j < borrow_temp.size();j++){
					if(borrow_temp[j] == i){
				borrow_amount[i] = 0;
				borrow_duration[i] = 0;
				borrow_temp[i] = 0;
				borrow_title[i] = "";
				borrow_id[i] = -1;
					}
				}
	
				
				
			}else if(title[i] -> PNode == genre[option] -> FChild){
				title[i] -> label = "";
				title[i] -> stock = 0;
//				stock[i] = 0;

for(int j = 0;j < borrow_temp.size();j++){
					if(borrow_temp[j] == i){
				borrow_amount[i] = 0;
				borrow_duration[i] = 0;
				borrow_temp[i] = 0;
				borrow_title[i] = "";
				borrow_id[i] = -1;
					}
				}

			}else if(title[i] -> PNode == genre[option] -> FChild -> NSibling){
				title[i] -> label = "";
				title[i] -> stock = 0;
//				stock[i] = 0;		

for(int j = 0;j < borrow_temp.size();j++){
					if(borrow_temp[j] == i){
				borrow_amount[i] = 0;
				borrow_duration[i] = 0;
				borrow_temp[i] = 0;
				borrow_title[i] = "";
				borrow_id[i] = -1;
					}
				}

			}
			else{
			
			}
		}
		
	}


	cout << "\n" << endl;
	
	
	centered("GENRE SUCCESSFULLY DELETED");

}

void DeclareV(){
	
	genre.reserve(100);
	title.reserve(100);
//	stock.reserve(10);	
	for(int i = 0;i < genre.capacity();i++){
		genre[i] = NULL;
		title[i] = NULL;
//		stock[i] = 0;
	}
}

bool borrow_checking(){
		
	int a = 0;
		for(int i = 0;i < borrow_id.size();i++){
			if(borrow_id[i] == -1){
				a++;
			}
		}
		
		if(a == borrow_id.size()){
		return true;
		}else{
		return false;
		}
		
}

bool genre_checking(){
	
		int a = 0;
		for(int i = 0;i < genre.size();i++){
			if(genre[i] -> label == ""){
				a++;
			}
		}
		
		if(a == genre.size()){
		return true;
		}else{
		return false;
		}
	
}

bool title_checking(){
	
		int a = 0;
		for(int i = 0;i < title.size();i++){
		if(title[i] -> label == ""){
		a++;
			}
		}
		if(a == title.size()){
		return true;
		}else{
		return false;
		}
	
}

void createNewTree( string label ){
    root = new Node();
    root -> label = label;
    root -> FChild = NULL;
    root -> NSibling = NULL;
    root -> PNode = NULL;
}

Node *InsertFChild( string label, Node *node ){
    newNode = new Node();
    newNode -> label = label;
    newNode -> FChild = NULL;
    newNode -> NSibling = NULL;
    newNode -> PNode = node;
    node -> FChild = newNode;
    return newNode;
}

Node *InsertNSibling( string label, Node *node ){
    newNode = new Node();
    newNode -> label = label;
    newNode -> FChild = NULL;
    newNode -> NSibling = NULL;
    newNode -> PNode = node;
    node -> NSibling = newNode;
    return newNode;
}

int Sub2(){
	
	sub:
	system("cls");
	cout << "\n" << endl;
	
	centered("=========================================================");
	centered("|                  MANAGE BOOK - SUBMENU                |");
	centered("=========================================================");
	centered("|                                                       |");
	centered("|                  0   -> EXIT                          |");
	centered("|                  1   -> INSERT  GENRE                 |");
	centered("|                  2   -> INSERT  BOOKS                 |");
	centered("|                  3   -> DELETE  BOOKS                 |");
	centered("|                  4   -> DELETE  GENRE                 |");
	centered("|                                                       |");
	centered("---------------------------------------------------------");
	cout << "\n\n";
	centered("TYPE KEY!");
	centered("---------");
	int sub2;
	cout << setw(39) << " ";cin >> sub2;
	
	if(cin.fail()){
		cout << endl;
		centered("INPUT NUMBER!");
		cout << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getch();
		goto sub;
	}
	
	
	return sub2;
	
}

COORD get_console_dimensions(void){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    COORD dimensions = { csbi.srWindow.Right - csbi.srWindow.Left,
                         csbi.srWindow.Bottom - csbi.srWindow.Top };
    return dimensions;
}

COORD get_console_cursor_pos(void){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition;
}

void gotoxy(short x, short y){
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void centered(char const *str){
    size_t length = strlen(str);
    short x = (short)(get_console_dimensions().X - length) / 2;
    gotoxy(x, get_console_cursor_pos().Y);
    puts(str);
}
