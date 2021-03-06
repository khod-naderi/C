/**
 * @file
 * @brief [Game of life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)
 * implementation
 *
 * @details The Game of Life, also known simply as Life, is a cellular automaton devised by the British
 * mathematician John Horton Conway in 1970. It is a zero-player game, meaning that its evolution is determined
 * by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial
 * configuration and observing how it evolves. It is Turing complete and can simulate a universal constructor or any other Turing machine.
 * @author [Ali Naderi](https://github.com/khod-naderi)
*/

#include <stdio.h>     /// standard input/output
#include <stdlib.h>    /// to generate random number AND memory management 
#include <time.h>      /// get time system for seed random number
#include <unistd.h>    /// for sleep func (usleep)

// define Make fixed values
#define MAX_X 60 // End point X
#define MAX_Y 20 // End point Y


/**
 * @brief Function draw (void)
 * Responsible for showing the world on the console, Hear live cells with @ displayed
 * @param world, Pointer to the beginning of the world in memory
 */
void draw(const char *world){
    #ifdef _WIN32 // for clear screen win/linux
    system("cls");
    #endif
    #ifdef linux
    system("clear");
    #endif 
    
    /**
    * Draw the world
    */
    for(int y=0; y<MAX_Y; y++){
        for(int x=0; x<MAX_X; x++){
            printf("%c", (*(world + MAX_X*y + x) == 1) ? '@' : ' ' ); 
        }
        printf("\n");
    } 
}


/**
 * @brief Function draw 
 * @returns Pointer to the beginning of a new world
 * Responsible in calculating and building new world according to the rules of the game
 * @param world, Pointer to the beginning of the world in memory
 */
char* em(char *world){
    char *newWorld = malloc(1200); // Create a new world to use to avoid interference in today's world
    int live = 0; // Number of living cells around
    if(newWorld == NULL){
        /**
        * Memory error management
        */
        printf("[ERROR] Memory\n\a");
        exit(0);
    }
    
    for(int y=0; y<MAX_Y; y++){
        for(int x=0; x<MAX_X; x++){
            // select cell
            live = 0; // reset live of cells around to 0
            
            
            for(int j=-1; j<2; j++){
                for(int i=-1; i<2; i++){
                    /**
                    * Count the number of living cells around
                    */
                    if( *(world + MAX_X*(y+j) +(x+i)) == 1 ) live++;
                }
            }
            //////////////////////////////////////
            // Investigate death or life
            // The description is on Wikipedia
            /////////////////////////////////////
            if(*(world + MAX_X*y +x) == 1){
                if(live == 3 || live == 4){
                    *(newWorld + MAX_X*y +x) = 1;   
                }else{
                    *(newWorld + MAX_X*y +x) = 0;
                }
            }else{
                if(live == 3){
                    *(newWorld + MAX_X*y +x) = 1;
                }else{
                    *(newWorld + MAX_X*y +x) = 0;
                }
            }
            
            
        }
    }
    
    // return new generation
    return newWorld;
}


/**
 * @brief Main function
 * @returns 0 on exit
 */
int main(){
    char *world = malloc(1200); // create the world
    /**
    * The world parameter is a pointer as array 2d and contains the cells of the world
    */
    srand(time(0)); 
    
    if(world == NULL){ 
        /**
        * Memory error management
        */
        printf("[ERROR] Memory\n\a");
        exit(0);
    } 
    
    ////////////////////////////////////////////////////////////////////////////////////
    // Build the world at random
    // This formula is for moving in memory presentation => *(world + MAX_X*y + x) 
    ////////////////////////////////////////////////////////////////////////////////////
    for(int y=0; y<MAX_Y; y++){
        for(int x=0; x<MAX_X; x++){
            *(world + MAX_X*y + x) = ( (rand() <= (RAND_MAX / 10)) ? 1 : 0);
        }
    } 
    
    
    // The beginning of the eternal cycle of life
    while(1){
        draw(world);           /// Show the creatures of the world
        world = em(world);    /// Calculate the next generation
        usleep(300000);      /// A short break = 0.03 sec
    }
    
    return 0;
}
