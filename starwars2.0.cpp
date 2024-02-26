#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <chrono>
#include <thread>
#include <ctime>
#include <vector>

using namespace std;

struct data {
	
	int friendly_hp;
	int friendly_x;
	int friendly_y;
	
	string enemy_name;
    int enemy_size;
    int enemy_hp;
    int enemy_x;
    int enemy_y;
    
    int map_size;
};

struct bullet {
	int x;
	int y;
};

void run();

void  display(int display_code);													//a function which gets a code, and displays what needs to be displayed based on that code

int MainMenu_input();																//gets the input from main menu (mainly the map size)

void render (data& info, int** map);												//renders the map

int** initialize_game (data& info);													//initializes the game

void run1 (data& info, int** map, vector<bullet>& bulletArray);			//a recursive version of the run function

void move_ship (data& info, int** map);												//moves the friendly ship

void spawn_enemy (data& info, int** map);											//spawns an enemy

void enemy_ship (data& info, int** map);											//does the needed functions on enemy ship, such as moving them, destroying them and etc.

void destroy_enemy (data& info, int** map);											//destroys the enemy

void add_bullet (data& info, int** map, vector<bullet>& bulletArray);

void remove_bullet (data& info, int** map, vector<bullet>& bulletArray);

void move_bullet (data& info, int** map, vector<bullet>& bulletArray);

int main() {
	
	srand (time (0));
	
	run();
	
	return 0;
}

void run() {
	
	data info;
	
	vector <bullet> bulletArray;

	/*the 2d array 'map' that has been allocated dynamically, is an array that store one of the 4 values
	{0, 1, 2, 3} for each coordiantion in the map. 0 indicates that the location is empty, 1 is for friendly 
	ship, 2 is for enemy ship and 3 indicates that there is a bullet in the location. */ 
	int** map = initialize_game (info);

    run1(info, map, bulletArray);
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
			
			cout << "\nWrong input!(Press the Enter key to continue . . .)";
			
			cin.ignore();
			
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
						    
								display (4);
						    
							    return map_size + 1;	
						    	
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


void render (data& info, int** map){

	system ("cls");
			
 	int rows = 2 * info.map_size + 1;
    int cols = 4 * info.map_size + 1;
    
    cout << endl << "Hit points: " << info.friendly_hp;
	
	
	for (int i = 0; i < cols - 32; i++)
		cout << ' ';
	
	cout << "Enemy hit points: " << info.enemy_hp << endl; 
    
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
                    if (map[(j-2)/4][(i-1)/2]==0)
						cout << ' ';
					else if (map[(j-2)/4][(i-1)/2]==1)
						cout << '#';
					else if (map[(j-2)/4][(i-1)/2]==2)
						cout << '*';
					else
						cout << '^';		
                }
            }  
        
            if (j == cols - 1)
                cout << endl;
        }			
			
}


int** initialize_game (data& info) {

    display(0);
	
	info.map_size = MainMenu_input();
	
	int** map = new int*[info.map_size];		//dynamically allocating memory for all the rows of the map combined.
	
	for (int i = 0; i < info.map_size; i++)		//dynamically allocating memory for every single row of the map.
		map[i] = new int[info.map_size];
	
	for (int i = 0; i < info.map_size; i++)		//setting all the values to 0, meaning that in the start of the game, we have a completely empty map.
		for ( int j = 0; j < info.map_size; j++)
			map[i][j] = 0;
			
	map [info.map_size/2][info.map_size-1] = 1;	//changing the value in bottom middle of the map to 1, indicating the friendly ship.
	info.friendly_x = info.map_size / 2;
	info.friendly_y = info.map_size - 1;
	
	info.friendly_hp = 3;

	info.enemy_hp = 0;            	            //making the enemy's hitpoints 0 in the start of the game so the run1 function spawns an enemy using the spawn_enemy function
	
	return map;
}
	
	

void run1 (data& info, int** map, vector<bullet>& bulletArray){
	
	if (info.enemy_hp == 0)
	    spawn_enemy(info, map);
	
	render (info, map);
	
	move_ship (info, map);
	
	move_bullet (info, map, bulletArray);
	
	add_bullet (info, map, bulletArray);
	
	enemy_ship (info, map);
	
	run1(info, map, bulletArray);
	
}


void move_ship (data& info, int** map) {
	
	int input; 
	
	input = getch(); 
		
	if (input == 224) {
		
		input = getch();
		
		switch (input){
			
			case 72: {
				
				display(5);
				
				break;
			}
			
			case 80: {              //if user presses the down arrow key
				break;
			}
			
			case 75: {              //if user presses the left arrow key
			
				if (map[0][info.map_size - 1] == 1)
				    break;
			
				map[info.friendly_x][info.friendly_y] = 0;
			    info.friendly_x --;
			    map[info.friendly_x][info.friendly_y] = 1;
			    
				break;
			}
		
			case 77: {              //if user presses the right arrow key 
				
				if (map[info.map_size - 1][info.map_size - 1] == 1)
				    break;
			
				map[info.friendly_x][info.friendly_y] = 0;
			    info.friendly_x ++;
			    map[info.friendly_x][info.friendly_y] = 1;
			    
				break;
			}
	    }
	}
	
	else if (input == 27){		   //if the esc key gets pressed
	    cout << "esc";
	    cin.ignore();}
	else 
	    display(5);
	
}


void spawn_enemy (data& info, int** map) {
	
	info.enemy_size = rand() % 4 + 1;
	
	switch (info.enemy_size) {
		
		case 1: {
			
			info.enemy_name = "Dart";
			
			info.enemy_hp = 1;
			info.enemy_size = 1;
			
			info.enemy_x = rand() % info.map_size;					//these x and y variables belong to the top left block of the enemy, as previously metioned.
			info.enemy_y = 0;			
			
			map[info.enemy_x][info.enemy_y] = 2;
			
			break;
		}
		
		case 2: {
			
			info.enemy_name = "Striker";
			
			info.enemy_hp = 2;
			info.enemy_size = 2;
			
			info.enemy_x = rand() % (info.map_size - 1);			//because the size of the ship is 2*2, the left most blocks of the ship need to be off the right edge of the map by at least 1 unit.
			info.enemy_y = 0;
			
			for (int i = info.enemy_x; i < info.enemy_size + info.enemy_x; i++ )
				for (int j = info.enemy_y; j < info.enemy_size + info.enemy_y; j++)
				    map[i][j] = 2;
			
			break;
		}
		
		case 3: {
			
			info.enemy_name = "Wraith";
			
			info.enemy_hp = 4;
			info.enemy_size = 3;
			
			info.enemy_x = rand() % (info.map_size - 2);
			info.enemy_y = 0;
			
			for (int i = info.enemy_x; i < info.enemy_size + info.enemy_x; i++ )
				for (int j = info.enemy_y; j < info.enemy_size + info.enemy_y; j++)
				    map[i][j] = 2;
			
			break;
		}
		
		case 4: {
			
			info.enemy_name = "Banshee";
			
			info.enemy_hp = 6;
			info.enemy_size = 4;
			
			info.enemy_x = rand() % (info.map_size - 3);
			info.enemy_y = 0;
			
			for (int i = info.enemy_x; i < info.enemy_size + info.enemy_x; i++ )
				for (int j = info.enemy_y; j < info.enemy_size + info.enemy_y; j++)
				    map[i][j] = 2;
			
			break;
		}
	}
}

void enemy_ship (data& info, int** map) {

	if (map [info.friendly_x][info.friendly_y - 1] == 2)
		destroy_enemy (info, map);
		
	else if (info.enemy_y + info.enemy_size == info.map_size)					//checks if the enemy ship has exited the map and destroys it if it has
			destroy_enemy (info, map);

	else {
			
	for (int i = info.enemy_x; i < info.enemy_x + info.enemy_size; i++)		//if none of the conditions mentioned above have happened, moves the enemy ship down by one unit	
		for (int j = info.enemy_y; j < info.enemy_y + info.enemy_size; j++)
			map[i][j] = 0;

	info.enemy_y ++;
	
	for (int i = info.enemy_x; i < info.enemy_x + info.enemy_size; i++)		//if none of the conditions mentioned above have happened, moves the enemy ship down by one unit	
		for (int j = info.enemy_y; j < info.enemy_y + info.enemy_size; j++)
			map[i][j] = 2;
	}
}

void destroy_enemy (data& info, int** map) {
	
	for (int i = 0; i < info.map_size; i++)
		for (int j = 0; j < info.map_size; j++)
			if (map[i][j] == 2)
				map[i][j] = 0;
	
	info.enemy_hp = 0;		
}

void add_bullet(data& info, int** map, vector<bullet>& bulletArray) {

    bullet newBullet;

    newBullet.x = info.friendly_x;

    newBullet.y = info.friendly_y - 1;

    bulletArray.push_back(newBullet);

    map[newBullet.x][newBullet.y] = 3;
}



void remove_bullet (data& info, int** map, bullet* bulletArray) {
	
	
	
	
	
	
}

	
void move_bullet(data& info, int** map, vector<bullet>& bulletArray) {

    for (int i = 0; i < bulletArray.size(); i++)
        map[bulletArray[i].x][bulletArray[i].y] = 0;

    for (int i = 0; i < bulletArray.size(); i++)
        bulletArray[i].y--;

    for (int i = 0; i < bulletArray.size(); i++)
        map[bulletArray[i].x][bulletArray[i].y] = 3;
}

