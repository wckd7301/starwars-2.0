#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <chrono>
#include <thread>
#include <ctime>
#include <vector>
#include <iomanip>
#include <fstream>

#define reset "\033[0m"                     //defining the ANSI color codes.
#define red "\033[31m"
#define green "\033[32m"
#define yellow "\033[33m"
#define blue "\033[34m"
#define magenta "\033[35m"
#define cyan "\033[36m"
#define white "\033[37m"
#define bright_red "\033[91m"
#define bright_green "\033[92m"
#define bright_yellow "\033[93m"
#define bright_blue "\033[94m"
#define bright_magenta "\033[95m"
#define bright_cyan "\033[96m"

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
int** initializeGame (data& info, vector<bullet>& bulletVector);
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
void secondaryMenu (data& info,int** map);
void saveGame (data& info, int** map, vector<bullet>& bulletVector);
void continueGame (data& info, vector<bullet>& bulletVector);

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
	int** map = initializeGame (info, bulletVector);
	
	setWinningScore (info);
	
	run1 (info, map, bulletVector);
}

void run1 (data& info, int** map, vector<bullet>& bulletVector) {
	
	saveGame (info, map, bulletVector);
	
	render (info, map);
	
	moveBullets (info, map, bulletVector);
		
	bulletColision (info, map, bulletVector);
		
	if (info.enemy_hp == 0)
		render (info, map);
	
	if (info.enemy_hp == 0)
	    spawnEnemy(info, map, bulletVector);
	
	if (info.score >= info.winningScore)	
		win (info, map, bulletVector);
		
	if (info.friendly_hp <= 0 ) 
		lose (info);	
		
	moveFriendlyShip (info, map);
		
	shipColision (info, map);
		
	if (info.enemy_hp == 0)
		render (info, map);
		
	addBullet (info, map, bulletVector);
	
	render (info, map);
	
	bulletColision (info, map, bulletVector);
		
	moveEnemyShip (info, map);
		
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

	saveGame (info, map, bulletVector);
render (info, map);
	moveBullets (info, map, bulletVector);
		
	bulletColision (info, map, bulletVector);
		
	if (info.enemy_hp == 0)
		render (info, map);
	
	if (info.enemy_hp == 0)
	    spawnEnemy(info, map, bulletVector);
			
	moveFriendlyShip (info, map);
		
	shipColision (info, map);
		
	if (info.enemy_hp == 0)
		render (info, map);
		
	addBullet (info, map, bulletVector);
		
	render (info, map);
		
	bulletColision (info, map, bulletVector);
		
	moveEnemyShip (info, map);
		
	bulletColision (info, map, bulletVector);
		
	shipColision (info, map);
		
	if (info.enemy_hp != 0)
		bulletColision (info, map, bulletVector);
		
	removeOutOfTheMapBullets (info, map, bulletVector);	
		
	if (info.friendly_hp <= 0 ) 
		lose (info);	
		
	infiniteContinue (info, map, bulletVector);
}

int** initializeGame (data& info, vector<bullet>& bulletVector) {
	
	bool flag = false;
	
	while(flag == false){
		
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
						flag = true;
						break;
					}
			    	
			    	case '2': {
						info.map_size = 17;
						flag = true;
						break;
					}
			    	
			    	case '3': {
						info.map_size = 19;
						flag = true;
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
						    	flag = true;
							}
							else
							    info.map_size = map_size;
								flag = true;
								break;
					
					    }
					}
				}
			
			    break;
		    }
		
		    case '2': {
			   
			   continueGame (info, bulletVector);
			   
			    break;
		    }
		
		    case '3': {
			   
			   display (10);
			   
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
			
			for (int i=0; i<20; i++){

				int randomColorCode = rand() %	13;

				switch (randomColorCode) {
	
					case 0  :{
					    system ("CLS");	
						cout << red << "Congratulations! You win!";
						this_thread::sleep_for(chrono::milliseconds(100));	
						break;
					}
	
					case 1  :{
						system ("CLS");	
						cout << green << "Congratulations! You win!";
						this_thread::sleep_for(chrono::milliseconds(100));	
						break;
					}
	
					case 2  :{
						system ("CLS");	
						cout << yellow << "Congratulations! You win!";
						this_thread::sleep_for(chrono::milliseconds(100));	
						break;
					}
	
					case 3  :{
						system ("CLS");	
						cout << blue << "Congratulations! You win!";
						this_thread::sleep_for(chrono::milliseconds(100));	
						break;
					}
	
					case 4  :{
						system ("CLS");	
						cout << magenta << "Congratulations! You win!";
						this_thread::sleep_for(chrono::milliseconds(100));	
						break;
					}
	
					case 5  :{
						system ("CLS");	
						cout << cyan << "Congratulations! You win!";
						this_thread::sleep_for(chrono::milliseconds(100));	
						break;
					}
	
					case 6  :{
						system ("CLS");	
						cout << bright_red << "Congratulations! You win!";
						this_thread::sleep_for(chrono::milliseconds(100));	
						break;
					}
	
					case 7  :{
						system ("CLS");	
						cout << white << "Congratulations! You win!";
						this_thread::sleep_for(chrono::milliseconds(100));	
						break;
					}
	
					case 8  :{
						system ("CLS");	
						cout << bright_blue << "Congratulations! You win!";
						this_thread::sleep_for(chrono::milliseconds(100));
						break;
					}
	
					case 9  :{
						system ("CLS");	
						cout << bright_yellow << "Congratulations! You win!";
						this_thread::sleep_for(chrono::milliseconds(100));	
						break;
					}
	
					case 10 :{
						system ("CLS");	
						cout << bright_green << "Congratulations! You win!";
						this_thread::sleep_for(chrono::milliseconds(100));	
						break;
					}
	
					case 11 :{
						system ("CLS");	
						cout << bright_cyan << "Congratulations! You win!";
						this_thread::sleep_for(chrono::milliseconds(100));	
						break;
					}
	
					case 12 :{
						system ("CLS");	
						cout << bright_magenta << "Congratulations! You win!";
						this_thread::sleep_for(chrono::milliseconds(100));	
						break;
					}
				}	
			}
	
			cout << reset << endl << "Do you wish to continue? (y/n)";
		
			break;
		}	
	
		case 9:{
			
			system("CLS");
	
			for (int i=0; i<5; i++){
				cout << red << "Game over!";
			    this_thread::sleep_for(chrono::milliseconds(500));
    		    system ("CLS");	
	    		this_thread::sleep_for(chrono::milliseconds(500));
        	
			}
	
			cout << red << "Game over!" << reset;
	
			break;
		}
	
		case 10 :{
			
			system ("cls");
			
			cout << "Hi there . . .";
			
			this_thread::sleep_for(chrono::milliseconds(2000));
			
			system ("cls");
			
			cout << "Welcome to Star Wars 2 . . .";
			
			this_thread::sleep_for(chrono::milliseconds(2000));
			
			system ("cls");
			
			cout << "You will be put in the bottom of a map.";
			
			this_thread::sleep_for(chrono::milliseconds(300));
			
			cout << "\nThe size of the map is yours to pick.";
			
			this_thread::sleep_for(chrono::milliseconds(300));
			
			cout << "\nFirst, you will need to set a winning score, a target or goal of you will ...";
			
			this_thread::sleep_for(chrono::milliseconds(300));
			
			cout << "\nThen, you have to reach to the target before losing all of your hit points.";
			
			this_thread::sleep_for(chrono::milliseconds(300));
			
			cout << "\nDiffrent enemies will spawn at the top of the map, and you need to eliminate them before they reach you or the bottom of the map.";
			
			this_thread::sleep_for(chrono::milliseconds(300));
			
			cout << "\nYou can use arrow keys to move, each move will trigger the guns to shoot a bullet, you can press the down arrow key to shoot while staying still.";
			
			this_thread::sleep_for(chrono::milliseconds(300));
			
			cout << "\nAt each stage of the game, the game will be automatically saved. You can comeback and continue your game any time!";
			
			this_thread::sleep_for(chrono::milliseconds(300));
			
			cout << "\n\nPress any key to return to the main menu . . .";
			
			_getch ();
			
			break;
		}
	
		case 11: {
			
			system ("cls");
			
			cout << "1. Resume\n2. Instructions\n3. Save and exit\n4. Exit without saving";
			
			break;
		}

		case 12: {
			
			system ("cls");
			
			this_thread::sleep_for(chrono::milliseconds(300));
			
			cout << "\nDiffrent enemies will spawn at the top of the map, and you need to eliminate them before they reach you or the bottom of the map.";
			
			this_thread::sleep_for(chrono::milliseconds(300));
			
			cout << "\nYou can use arrow keys to move, each move will trigger the guns to shoot a bullet, you can press the down arrow key to shoot while staying still.";
			
			this_thread::sleep_for(chrono::milliseconds(300));
			
			cout << "\nAt each stage of the game, the game will be automatically saved. You can comeback and continue your game any time!";
			
			this_thread::sleep_for(chrono::milliseconds(300));
			
			cout << "\n\nPress any key to continue . . .";
			
			_getch ();
			
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
						cout << blue << '#' << reset;
					else if (map[(j-2)/4][(i-1)/2]==2)
						cout << red <<'*' << reset;
					else
						cout << yellow << '^' << reset;		
                }
            }  
        
            if (j == cols - 1)
                cout << endl;
        }			
		cout << "\nPress esc to access the menu";
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
	
	else if (input == 27){		   //if the esc key gets pressed (to open the menu while in the game)
	    secondaryMenu (info, map);
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
		render (info, map);
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
        //enemy ship has exited the map
        info.enemy_hp = 0;
        info.friendly_hp--;
        destroyEnemy(info, map);
        render(info, map);
    } else {
        //remove the enemy ship from its current position
        for (int i = info.enemy_x; i < info.enemy_x + info.enemy_size; i++)
            for (int j = info.enemy_y; j < info.enemy_y + info.enemy_size; j++)
                if (i >= 0 && i < info.map_size && j >= 0 && j < info.map_size)
                    map[i][j] = 0;

        //move the enemy ship down by one unit
        info.enemy_y++;

        //place the enemy ship in its new position
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
	
	display (8);
	
	char input;
	
	while (true){
	
	cin >> input;
	
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
			break;
		}		
	}
}
}

void lose (data& info) {
	
	display (9);
	
	remove ("document.txt");
	
	cout << "\nPress any key to exit ...";
	
	_getch ();
	
	exit (0);
	
}



void secondaryMenu (data& info,int** map) {
	
	display (11);
	
	char input;
	
	input = getch ();
	
	switch (input) {
		
		case '1':{
			break;
		}
		
		case '2':{
			
			display (12);
			
			break;
		}
		
		case '3': {
			
			exit (0);
			
			break;
		}
		
		case '4': {
			
			remove ("document.txt");
			
			exit (0);
			
			break;
		}
	
		default :{
			
			secondaryMenu (info, map);
		
			break;
		}
	}
}


void saveGame (data& info, int** map, vector<bullet>& bulletVector) {
	
	ofstream FILE ("document.txt");
	
	FILE << info.friendly_hp << " " << info.friendly_x << " " << info.friendly_previous_x << " " << info.friendly_y << " " << info.enemy_name << " " << info.enemy_size << " " << info.enemy_hp << " " << info.enemy_x << " " << info.enemy_y << " " << info.score << " " << info.winningScore << " " << info.map_size;
	
	FILE << endl; 
	
	for (int i = 0; i < info.map_size; i++) {
		for (int j = 0; j < info.map_size; j++){
			FILE << map[i][j] << " ";
			if (j==info.map_size - 1)
			FILE << endl;
		}
	}
		
	FILE << bulletVector.size() << endl;	
	
	for (int i = 0; i<bulletVector.size(); i++)
		FILE << bulletVector[i].x << " " << bulletVector[i].y << " ";	
}


void continueGame (data& info, vector<bullet>& bulletVector) {	
		
	ifstream FILE ("document.txt");
	
	FILE >> info.friendly_hp >> info.friendly_x >> info.friendly_previous_x >> info.friendly_y >> info.enemy_name >> info.enemy_size >> info.enemy_hp >> info.enemy_x >> info.enemy_y >> info.score >> info.winningScore >> info.map_size;
	
	int** map = new int*[info.map_size];		//dynamically allocating memory for all the rows of the map combined.
	
	for (int i = 0; i < info.map_size; i++)		//dynamically allocating memory for every single row of the map.
		map[i] = new int[info.map_size];
	
	for (int i = 0; i < info.map_size; i++)		//setting all the values to 0, meaning that in the start of the game, we have a completely empty map.
		for ( int j = 0; j < info.map_size; j++)
			map[i][j] = 0;
	
	for (int i = 0; i < info.map_size; i++) {
		for (int j = 0; j < info.map_size; j++){
			FILE >> map[i][j];
		}
	}
		
	int size;
		
	FILE >> size;	
	
	for (int i = 0; i<size; i++) {
		
		bullet newBullet;
		
		FILE >> newBullet.x >> newBullet.y;	
	
		bulletVector.push_back(newBullet);}
		
	
		
			if (info.score >= info.winningScore)
				infiniteContinue (info, map, bulletVector);
			else 
				run1 (info, map, bulletVector);
			
}
