#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <chrono>
#include <thread>

using namespace std;

void run();

void  display(int display_code);    //a function which gets a code, and displays what needs to be displayed based on that code

int MainMenu_input();

char** map (int map_size);

void render_map (char** pointer_to_map, int map_size);

int main() {
	
	run();
	
	return 0;
}

void run() {
	
	display(0);
	
	int map_size = MainMenu_input();
	
	char** pointer_to_map = map (map_size);
	
	render_map (pointer_to_map, map_size);
	
	
	
	
	
	
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
			cout << "|          2. 17 * 17           |\n|          3. 19 * 19           |\n";
			cout << "|     4. Enter the map size     |\n";
			cout << "|                               |\n---------------------------------";
			
			break;
		}
		
		case 2: {
			
			system("cls");
			
			cout << "Enter the map size: ";
			
			break;
		}
		
		case 3: {
			
			system("cls");
			
			cout << "Map size cannot be less than 15! (Press any key to continue . . .)";
			
			_getch();
			
			break;
		}
		
		case 4: {
			
			system ("cls");
			
			cout << "It would be better if the map size was an odd number, so the map size that has been entered will be plus 1.";
			
			this_thread::sleep_for(chrono::seconds(3));
			
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
						return 17;
					}
			    	
			    	case '3': {
						return 19;
					}
					
					case '4': {
						
						while (true){
						
						    display (2);
						
						    int map_size;
						    cin >> map_size;
						    
						    if (map_size < 15)
						        display (3);
						    else if (map_size % 2 == 0){
						    	
						    	
						    	
							}
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


char** map (int map_size){
	
	int rows = map_size * 2 + 1;
	
    int cols = map_size * 4 + 1;
	
	char** grid = new char*[rows];                   //allocating memory for the grid, dynamicaly.
    
    
    for (int i = 0; i < rows; ++i) {                 //alocating memory to each row, dynamicaly.
        grid[i] = new char[cols];
    }
    
	for (int i = 0; i < rows; i++){                  //creating an empty map.
    
		for (int j = 0;j < cols; j++){
    		
			if (i%2 != 0){	
			    
				if (j%4 == 0)
			        grid[i][j] = '|';		
			
			    else
			        grid[i][j] = ' ';
	        }
	
	        else {
	
		        if (j%4 == 0)
		            grid[i][j] = ' ';
	
		        else 
		            grid[i][j] = '-';
	        }

		}
	}
	
	grid [map_size * 2 - 1][map_size * 2] = '#';                          //adding the ship to the map.
    

	return grid;
}

void render_map (char** grid, int map_size){

    system("cls");
	
	for (int i = 0; i < map_size * 2 + 1; i++)
	    for (int j = 0; j < map_size * 4 + 1; j++){
	    	
	    	cout << grid [i][j];
	    	
	    	if (j == 4 * map_size )
	    	    cout << endl;
		}
	
	
	
}