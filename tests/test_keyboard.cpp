#include<stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include<conio.h>
#include<time.h>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <termios.h>

int get_next_key(){
	char key_words[8];
	key_words[0] = 'q';
	key_words[1] = 'w';
	key_words[2] = 'e';
	key_words[3] = 'a';
	key_words[4] = 's';
	key_words[5] = 'd';
	key_words[6] = 'c';
	key_words[7] = ' ';
	srand((int)time(0));
 	int rand_num = rand();
	char c = key_words[rand_num % 8];
	return (c == ' ') ? 28 : (65 + c - 'a');
}

int main(int argc, char** argv){
	int num = 0;
	//legal 
	for(int i = 0; i < 10; i++){
		while(num != 65 + 'x' - 'a'){
	        num = get_next_key();
			keybd_event(num, 0, 0, 0);
		} 
		move(argc, argv);
	}
	//illegal 
	keybd_event(rand()%64, 0, 0, 0);
	move(argc, argv);
}
