#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <chrono>
#include <thread>
#include <ctime>
#include <vector>
#include <iomanip>

using namespace std;

struct data {	
	int friendly_hp;
	int friendly_x;
	int friendly_previous_x;
	int friendly_y;
	
	string enemy_name;
    int enemy_size;
    int enemy_hp;
    int enemy_x;
    int enemy_y;
    
    int score;
    int winningScore;
    
    int map_size;
};

struct bullet {
	int x;
	int y;
};

void run ();
void run1 (data& info, int** map, vector<bullet>& bulletVector);
void infiniteContinue (data& info, int** map, vector<bullet>& bulletVector);
void display (int display_code);
void setWinningScore (data& info);
void render (data& info, int** map);
int** initializeGame (data& info);
void moveFriendlyShip (data& info, int** map);
void moveEnemyShip (data& info, int** map);
void spawnEnemy (data& info, int** map, vector<bullet>& bulletVector);
void destroyEnemy (data& info, int** map);
void addBullet (data& info, int** map, vector<bullet>& bulletVector);
void moveBullets (data& info, int** map, vector<bullet>& bulletVector);
void removeOutOfTheMapBullets (data& info, int** map, vector<bullet>& bulletVector);
void shipColision (data& info, int** map);
void bulletColision (data& info, int** map, vector<bullet>& bulletVector);
void win (data& info, int** map, vector<bullet>& bulletVector);
void lose (data& info);

int main () {
	
	srand (time (0));
	
	run();
}

void run () {
	
	data info;
	
	vector<bullet> bulletVector;
	
	/*the 2d array 'map' that has been allocated dynamically, is an array that store one of the 4 values
	{0, 1, 2, 3} for each coordiantion in the map. 0 indicates that the location is empty, 1 is for friendly 
	ship, 2 is for enemy ship and 3 indicates that there is a bullet in the location. */ 
	int** map = initializeGame (info);
	
	setWinningScore (info);
	
	run1 (info, map, bulletVector);
}

void run1 (data& info, int** map, vector<bullet>& bulletVector) {
	
	moveBullets (info, map, bulletVector);
		
	bulletColision (info, map, bulletVector);
		
	if (info.enemy_hp == 0)
		render (info, map);
	
	if (info.enemy_hp == 0)
	    spawnEnemy(info, map, bulletVector);
	
	render (info, map);
		
	moveFriendlyShip (info, map);
		
	shipColision (info, map);
		
	if (info.enemy_hp == 0)
		render (info, map);
		
	addBullet (info, map, bulletVector);
		
	bulletColision (info, map, bulletVector);
		
	moveEnemyShip (info, map);
		
	if (info.enemy_hp > 0)
		render (info, map);
		
	bulletColision (info, map, bulletVector);
		
	shipColision (info, map);
		
	if (info.enemy_hp != 0)
		bulletColision (info, map, bulletVector);
		
	removeOutOfTheMapBullets (info, map, bulletVector);	
		
	if (info.score >= info.winningScore)	
		win (info, map, bulletVector);
		
	if (info.friendly_hp <= 0 ) 
		lose (info);
			
	run1 (info, map, bulletVector);
}

void infiniteContinue (data& info, int** map, vector<bullet>& bulletVector) {

	moveBullets (info, map, bulletVector);
		
	bulletColision (info, map, bulletVector);
		
	if (info.enemy_hp == 0)
		render (info, map);
	
	if (info.enemy_hp == 0)
	    spawnEnemy(info, map, bulletVector);
	
	render (info, map);
		
	moveFriendlyShip (info, map);
		
	shipColision (info, map);
		
	if (info.enemy_hp == 0)
		render (info, map);
		
	addBullet (info, map, bulletVector);
		
	bulletColision (info, map, bulletVector);
		
	moveEnemyShip (info, map);
		
	if (info.enemy_hp > 0)
		render (info, map);
		
	bulletColision (info, map, bulletVector);
		
	shipColision (info, map);
		
	if (info.enemy_hp != 0)
		bulletColision (info, map, bulletVector);
		
	removeOutOfTheMapBullets (info, map, bulletVector);	
		
	if (info.friendly_hp <= 0 ) 
		lose (info);	
		
	infiniteContinue (info, map, bulletVector);
}

int** initializeGame (data& info) {
	
	while(true){
		
		display (0);
		
	    char menu_input;
	    menu_input = getch(); 
	
	    switch (menu_input){
		
		    case '1': {
			
			    display  (1);
			    
			    char map_size_input;
			    map_size_input = getch();
			    
			    switch (map_size_input){
			    	
			    	case '1': {
						info.map_size = 15;
						break;
					}
			    	
			    	case '2': {
						info.map_size = 17;
						break;
					}
			    	
			    	case '3': {
						info.map_size = 19;
						break;
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
						    
							    info.map_size = map_size + 1;	
						    	
							}
							else
							    info.map_size = map_size;
								break;
					
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
			   
			   display (5);
			   
			    break;
		    }
			
	    } 
		break;
    }
	
	int** map = new int*[info.map_size];		//dynamically allocating memory for all the rows of the map combined.
	
	for (int i = 0; i < info.map_size; i++)		//dynamically allocating memory for every single row of the map.
		map[i] = new int[info.map_size];
	
	for (int i = 0; i < info.map_size; i++)		//setting all the values to 0, meaning that in the start of the game, we have a completely empty map.
		for ( int j = 0; j < info.map_size; j++)
			map[i][j] = 0;
			
	map [info.map_size/2][info.map_size-1] = 1;	//changing the value in bottom middle of the map to 1, indicating the friendly ship.
	info.friendly_x = info.map_size / 2;
	info.friendly_y = info.map_size - 1;
	
	info.score = 0;
	info.friendly_hp = 3;

	info.enemy_hp = 0;            	            //making the enemy's hitpoints 0 in the start of the game so the run1 function spawns an enemy using the spawn_enemy function
	
	return map;
}


void display (int display_code) {
	
	switch(display_code){
		
		case 0: {                          //this display code is used for displaying the main menu.
			
			system ("cls");
			
			cout << "---------------------------------\n|           Main Menu           |\n";
			cout << "|                               |\n|          1. New Game          |\n";
			cout << "|          2. Continue          |\n|        3. Instructions        |\n";
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
		
		
		case 6: {
			
			system ("cls");
			
			cout << "Enter the target score for winnig: ";
			
			break;
		}
	
		case 7: {
			
			cout << "Can't clip through the edge of the universe, can we!(Press the Enter key to continue . . .)";
			cin.ignore();
			
			break;
		}
	
		case 8: {
			
			
			
			
			
			
			break;
		}	
	
	
	}

}

void setWinningScore (data& info) {
	
	display (6);	
	
	cin >> info.winningScore;
}


void spawnEnemy (data& info, int** map, vector<bullet>& bulletVector) {

while (info.enemy_hp <= 0){
	
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
	
	for (int i = info.enemy_x; i < info.enemy_size + info.enemy_x; i++ )
		for (int j = info.enemy_y; j < info.enemy_size + info.enemy_y; j++)
			for (int p = 0; p < bulletVector.size(); p++)
				if (bulletVector[p].x == i && bulletVector[p].y == j){
					
					bullet temp;
            
        		    temp = bulletVector[p];
            
            		bulletVector[p] = bulletVector [bulletVector.size() - 1];
            
            		bulletVector [bulletVector.size() - 1] = temp;
            
            		bulletVector.pop_back();
					
					info.enemy_hp --;
				}
				
	if (info.enemy_hp <= 0)
		destroyEnemy (info, map);			

}
}

void render (data& info, int** map) {
	
	system ("cls");
			
 	int rows = 2 * info.map_size + 1;
    int cols = 4 * info.map_size + 1;
    
    cout << endl << "Hit points: " << info.friendly_hp;
	
	
	for (int i = 0; i < (cols - 45) / 2; i++)
		cout << ' ';
	
	
	cout << "Score: " << setw(7) << setfill('0') << info.score;
	
	for (int i = 0; i< (cols - 45) / 2 - 1; i++)
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


void moveFriendlyShip (data& info, int** map) {
bool flag = false;
	
	info.friendly_previous_x = info.friendly_x;
	
	while (flag == false){
	
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
				flag = true;
				break;
			}
			
			case 75: {              //if user presses the left arrow key
			
				if (map[0][info.map_size - 1] == 1){
				
					display (7);
					render (info, map);
					break;
				}
				    
				map[info.friendly_x][info.friendly_y] = 0;
			    info.friendly_x --;
			    map[info.friendly_x][info.friendly_y] = 1;
			    
			    flag = true;
			    
				break;
			}
		
			case 77: {              //if user presses the right arrow key 
				
				if (map[info.map_size - 1][info.map_size - 1] == 1){
				    display (7);
					render (info, map);
					break;
				}
			
				map[info.friendly_x][info.friendly_y] = 0;
			    info.friendly_x ++;
			    map[info.friendly_x][info.friendly_y] = 1;
			    
			    flag = true;
			    
				break;
			}
	    }
	}
	
	else if (input == 27){		   //if the esc key gets pressed
	    cout << "esc";
	    cin.ignore();
	    flag = true;
	}
	else 
	    display(5);
	}
	
}

void shipColision (data& info, int** map) {
	
	if (map[info.friendly_x][info.friendly_y - 1] == 2){
		destroyEnemy (info, map);
		info.friendly_hp --;
	}
	
}

void destroyEnemy (data& info, int** map) {
	
	for (int i = 0; i < info.map_size; i++)
		for (int j =0; j < info.map_size; j++)
			if (map[i][j] == 2)
				map[i][j] = 0;
				
	info.enemy_hp = 0;			
}

void addBullet(data& info, int** map, vector<bullet>& bulletVector) {

    bullet newBullet;

    newBullet.x = info.friendly_previous_x;

    newBullet.y = info.friendly_y - 1;

    bulletVector.push_back(newBullet);

    map[newBullet.x][newBullet.y] = 3;
}

void bulletColision (data& info, int** map, vector<bullet>& bulletVector) {

	for (int i = 0; i < bulletVector.size(); i++)
		if (map[bulletVector[i].x][bulletVector[i].y-1] == 2){
		
			map[bulletVector[i].x][bulletVector[i].y] = 0;
		
			bullet temp;
            
            temp = bulletVector[i];
            
            bulletVector[i] = bulletVector [bulletVector.size() - 1];
            
            bulletVector [bulletVector.size() - 1] = temp;
            
            bulletVector.pop_back();
			
			info.enemy_hp --;
			
			if (info.enemy_hp < 1) {
				info.score += info.enemy_size * info.enemy_size * 2;
				destroyEnemy (info, map);	
				render (info, map);
			}
			
			
		}
}



	
void moveEnemyShip(data& info, int** map) {
    if (info.enemy_y + info.enemy_size == info.map_size) {
        // Enemy ship has exited the map
        info.enemy_hp = 0;
        info.friendly_hp--;
        destroyEnemy(info, map);
        render(info, map);
    } else {
        // Remove the enemy ship from its current position
        for (int i = info.enemy_x; i < info.enemy_x + info.enemy_size; i++)
            for (int j = info.enemy_y; j < info.enemy_y + info.enemy_size; j++)
                if (i >= 0 && i < info.map_size && j >= 0 && j < info.map_size)
                    map[i][j] = 0;

        // Move the enemy ship down by one unit
        info.enemy_y++;

        // Place the enemy ship in its new position
        for (int i = info.enemy_x; i < info.enemy_x + info.enemy_size; i++)
            for (int j = info.enemy_y; j < info.enemy_y + info.enemy_size; j++)
                if (i >= 0 && i < info.map_size && j >= 0 && j < info.map_size)
                    map[i][j] = 2;
    }
}

	


void moveBullets (data& info, int** map, vector<bullet>& bulletVector) {

	for (int i = 0; i < bulletVector.size(); i++)
        map[bulletVector[i].x][bulletVector[i].y] = 0;

    for (int i = 0; i < bulletVector.size(); i++)
        bulletVector[i].y--;

    for (int i = 0; i < bulletVector.size(); i++)
        map[bulletVector[i].x][bulletVector[i].y] = 3;
}

void removeOutOfTheMapBullets (data& info, int** map, vector<bullet>& bulletVector) {

	for (int i = 0; i < bulletVector.size(); i++) {				//checks if a bullet has exited the map, swaps it with the last bullet in the vector and removes it using the pop_back function
        if (bulletVector[i].y < 0) {
            map[bulletVector[i].x][bulletVector[i].y] = 0;

            bullet temp;
            
            temp = bulletVector[i];
            
            bulletVector[i] = bulletVector [bulletVector.size() - 1];
            
            bulletVector [bulletVector.size() - 1] = temp;
            
            bulletVector.pop_back();

            break;
        }
    }
}


void win (data& info, int** map, vector<bullet>& bulletVector) {
	
	cout << "win";
	
	cout << "continue ? y/n";
	
	char input;
	
	input = getch();
	
	switch (input) {
		
		case 'y' :{
			
			infiniteContinue (info, map, bulletVector);
			
			break;
		}
		
		
		case 'n' :{
			
			exit (0);
			
			
			
			break;
		}	
		
		
		default : {
			display (5);
			break;
		}		
		
		
		
		
		
		
		
	}

}

void lose (data& info) {
	
	cout << "lose";
	
	_getch ();
	
	exit (0);
	
}