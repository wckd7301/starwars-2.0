#include <iostream>
#include <cstdlib>
#include <conio.h>
using namespace std;

void run();

void  display(int display_code);    //a function which gets a code, and displays what needs to be displayed based on that code

int MainMenu_input();

void grid (int map_size);

int main() {
	
	run();
	
	return 0;
}

void run() {
	
	display(0);
	
	int map_size = MainMenu_input();
	
	grid (map_size);
	
	
	
	
	
	
	
	
}

void display (int display_code) {
	
	switch(display_code){
		
		case 0: {                          //this display code is used for displaying the main menu.
			
			system ("cls");
			
			cout << "---------------------------------\n|           Main Menu           |\n";
			cout << "|                               |\n|          1. New Game          |\n";
			cout << "|          2. Continue          |\n|         3. High Score         |\n";
			cout << "|            4. Exit            |\n|                               |\n";
			cout << "---------------------------------";
			
			break;
		}
		
		case 1: {                         //this display code is used for displaying the "map size selection" part.
			
			system("cls");
			
			cout << "---------------------------------\n|      Select the map size:     |\n";
			cout << "|                               |\n|          1. 15 * 15           |\n";
			cout << "|          2. 20 * 20           |\n|          3. 25 * 25           |\n";
			cout << "|     4. Enter the map size     |\n";
			cout << "|                               |\n---------------------------------";
			
			break;
		}
		
		case 2: {
			
			system("cls");
			
			cout << "Enter the map size: ";
			
			break;
		}
		
		case 3:{
			
			system("cls");
			
			cout << "Map size cannot be less than 15! (Press any key to continue . . .)";
			
			_getch();
			
			break;
		}
		
	}

}


int MainMenu_input() {
	
	while(true){
		
	    char menu_input;
	    menu_input = getch(); 
	
	    switch (menu_input){
		
		    case '1': {
			
			    display  (1);
			    
			    char map_size_input;
			    map_size_input = getch();
			    
			    switch (map_size_input){
			    	
			    	case '1': {
						return 15;
					}
			    	
			    	case '2': {
						return 20;
					}
			    	
			    	case '3': {
						return 25;
					}
					
					case '4': {
						
						while (true){
						
						    display (2);
						
						    int map_size;
						    cin >> map_size;
						    
						    if (map_size < 15)
						        display (3);
						    
							else
							    return map_size;
					    }
					}
				}
			
			    break;
		    }
		
		    case '2': {
			    break;
		    }
		
		    case '3': {
			    break;
		    }
		
		    case '4': {
			    exit(0);
		    }
		
		    default: {
			    break;
		    }
		
	    } 
	
    }
	
	
}
void grid (int map_size){
	int k = map_size*2 + 1;
	int h = map_size*4 + 1;
	int i,j;
	char grid1[k][h]; 
    for (int i = 0; i < k;i++){
    	for (int j = 0;j < h;j++){
    			if (i%2!=0){	
			if (j%4==0){
			grid1[i][j]='|';		
			}
			else
			grid1[i][j]=' ';
	}
	else {
		if (j%4==0)
		grid1[i][j]=' ';
		else 
		grid1[i][j]='-';
	}

		}
	}
	system("cls");
    for (int i = 0; i < k;i++){
    	for (int j = 0;j < h;j++){
			cout << grid1[i][j];
			if (j == h - 1)
			cout << endl;
	}
			}


	}
