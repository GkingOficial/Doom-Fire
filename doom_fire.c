#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#define fire_height 30
#define fire_width 60
#define INTENSITY 5

const int fire_lenght = fire_height * fire_width;
int fire_array[fire_height * fire_width];
int fire_copy[fire_height * fire_width];
int fire_color[][3] = {{7, 7, 7}, {31, 7, 7}, {47, 15, 7}, {71, 15, 7}, {87, 23, 7}, {103, 31, 7}, {119, 31, 7}, {143, 39, 7}, {159, 47, 7}, {175, 63, 7}, {191, 71, 7}, {199, 71, 7}, {223, 79, 7}, {223, 87, 7}, {223, 87, 7}, {215, 95, 7}, {215, 95, 7}, {215, 103, 15}, {207, 111, 15}, {207, 119, 15}, {207, 127, 15}, {207, 135, 23}, {199, 135, 23}, {199, 143, 23}, {199, 151, 31}, {191, 159, 31}, {191, 159, 31}, {191, 167, 39}, {191, 167, 39}, {191, 175, 47}, {183, 175, 47}, {183, 183, 47}, {183, 183, 55}, {207, 207, 111}, {223, 223, 159}, {239, 239, 199}, {255, 255, 255}};

void CreateStructure();
void CalculatePropagation();
void CalculateIntensity(int );
void RenderFire();
void CreateFireSource();
void DrawBackground();

int main(){
    puts("");
    
    CreateStructure();
    
    CreateFireSource();
    
    DrawBackground();
    
    RenderFire();
    
    while(true) {
        srand(time(NULL));
        CalculatePropagation();
    }
}

void CreateStructure(){
    int i;
    for(i = 0; i < fire_lenght; i++){
        fire_array[i] = 0;
        fire_copy[i] = 0;
    }
}

void CalculatePropagation(){
    int i, j, pixel_index;
    for(i = 0; i < fire_width; i++){
        for(j = 0; j < fire_height; j++){
            pixel_index = i + fire_width * j;
            CalculateIntensity(pixel_index);
        }
    }
    RenderFire();
}

void DrawBackground(){
    int i, j, r = fire_array[0], g = fire_array[1], b = fire_array[1];
    printf("\033[H\033[J");
    for(i = 0; i < fire_height; i++){
        for(j = 0; j < fire_width; j++){
            printf("\033[%d;%dH\033[48;2;%d;%d;%dm \033[0m", i, j, r, g, b);
        }
        puts("");
    }
    puts("");
}

void RenderFire(){
    int i, j, r, g, b;
    printf("\033[H");
    for(i = 0; i < fire_height; i++){
        for(j = 0; j < fire_width; j++){
            
            r = fire_color[fire_array[j + fire_width * i]][0];
            g = fire_color[fire_array[j + fire_width * i]][1];
            b = fire_color[fire_array[j + fire_width * i]][2];
            
            if(fire_array[j + fire_width * i] != fire_copy[j + fire_width * i] || fire_copy[j + fire_width * i]){
                printf("\033[%d;%dH\033[48;2;%d;%d;%dm \033[0m", i, j, r, g, b);
                fire_copy[j + fire_width * i] = fire_array[j + fire_width * i];
            }
        }
        puts("");
    }
    puts("");
}

void CreateFireSource(){
    int i, pixel_index;
    for(i = 0; i < fire_width; i++){
        pixel_index = (fire_width * fire_height - fire_width) + i;
        fire_array[pixel_index] = 36;
    }
}

void CalculateIntensity(int index){
    int new_index = index + fire_width, decay, intensity;
    
    if(new_index >= fire_width * fire_height){
        return;
    }
    
    decay = rand() % INTENSITY;
    
    intensity = fire_array[new_index] - decay >= 0 ? fire_array[new_index] - decay : 0;
    fire_array[index - decay] = intensity;
}
