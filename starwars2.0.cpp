#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <chrono>
#include <thread>

using namespace std;

struct data {
  
    int friendly_x;
    int friendly_y;
  
    int enemy_x;
    int enemy_y;
    string enemy_name;
    
    int map_size;
};

void run();

void  display(int display_code);    //a function which gets a code, and displays what needs to be displayed based on that code

int MainMenu_input();

void render (data& map);

void initialize_game (data& map);

void run1 (data& map);

void move_ship (data& map);

int main() {
	
	run();
	
	return 0;
}

void run() {
	
	data map;
	
	initialize_game (map);
	
    run1(map);
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
	
		case 5: {
			
			cout << "\nWrong input!(Press any key to continue . . .)";
			
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


void render (data& map){

	system ("cls");
			
 	int rows = 2 * map.map_size + 1;
    int cols = 4 * map.map_size + 1;
    
    for (int i = 0; i < rows; i++)	
        for (int j = 0; j < cols; j++){
            if (i % 2 == 0){
                if (j % 4 == 0)
                    cout << ' ';
                else 
                    cout << '-';	
            }
            else {
                if (j % 4 == 0)
                    cout << '|';
                else if (j % 4 == 1 || j % 4 == 3)
                    cout << ' ';
                else {
                    if (((j + 2) / 4) - 1 == map.friendly_x && (i + 1) / 2 == map.friendly_y)
                        cout << '#';
                    else 
                        cout << ' ';			
                }
            }  
        
            if (j == cols - 1)
                cout << endl;
        }			
			
}


void initialize_game (data& map) {

    display(0);
	
	map.map_size = MainMenu_input();
	
	map.friendly_x = map.map_size / 2;
	map.friendly_y = map.map_size;
	
}

void run1 (data& map){
	
	render (map);
	
	move_ship (map);
	
	
	
	
	run1(map);
	
}


void move_ship (data& map) {
	
	int input; 
	
	input = getch(); 
		
	if (input == 224) {
		
		input = getch();
		
		switch (input){
			
			case 72: {
				
				display(5);
				
				break;
			}
			
			case 80: {               //if user presses the down arrow key
				break;
			}
			
			case 75: {              //if user presses the left arrow key
			
				map.friendly_x --;
			    
				break;
			}
		
			case 77: {              //if user presses the right arrow key 
				
				map.friendly_x ++;
				
				break;
			}
	    }
	}
	
	else if (input == 27)		//if the esc key gets pressed
	    cout << "esc";
	    
	else 
	    display(5);
	
}