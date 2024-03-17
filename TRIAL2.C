#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"
#include <conio.h>

typedef struct
{
    float x, y, velx, vely, radius;
} Ball;

int checkCollision(Ball *ball1, Ball *ball2){
    float dx = ball1 -> x - ball2 -> x;
    float dy = ball1 -> y - ball2 -> y;
    float distance = sqrt(dx*dx + dy*dy);

    return distance <= ball1->radius + ball2->radius;
}

void updatePhysics(Ball *balls, int numBalls, float dt, float gravity){
    int i, j;

    for(i = 0; i < numBalls ; i++){
	balls[i].vely += gravity * dt;

	balls[i].x += balls[i].velx * dt;
	balls[i].y += balls[i].vely * dt;

	if(balls[i].x - balls[i].radius < 0 || balls[i].x + balls[i].radius > 1){
	    balls[i].velx = balls[i].velx * -1;
	}

	if(balls[i].y - balls[i].radius < 0 || balls[i].y + balls[i].radius > 1){
	    balls[i].vely = balls[i].vely * -1;
	}

	for(j = 0; j < numBalls; j++){

	    if( i != j && checkCollision(&balls[i], &balls[j])){

		float tempVx = balls[i].velx;
		float tempVy = balls[i].vely;

		balls[i].velx = balls[j].velx;
		balls[i].vely = balls[j].vely;

		balls[j].velx = tempVx;
		balls[j].vely = tempVy;
	    }
	}
    }
}

void drawBall(Ball *ball) {
    circle((int)(ball->x * getmaxx()), (int)(ball->y * getmaxy()), (int)(ball->radius * getmaxx()));
    }

void main() {

    const float gravity = 0.01;
    const float dt = 0.1;
    char input;

    int numBalls, i, j, iterations, gd = DETECT, gm;

    Ball balls[10];

    printf("Enter the number of Balls: ");
    scanf("%d", &numBalls);

    printf("\nEnter the number of iterations: ");
    scanf("%d", &iterations);

    initgraph(&gd, &gm, "");

    for (i = 0; i < numBalls; i++) {
	balls[i].x = (float)rand() / RAND_MAX;
	balls[i].y = (float)rand() / RAND_MAX;
	balls[i].velx = (float)rand() / RAND_MAX * 0.2 - 0.1;
	balls[i].vely = (float)rand() / RAND_MAX * 0.2 - 0.1;
	printf("\nEnter radius of Ball %d ", i + 1);
	scanf("%f", &balls[i].radius);
    }

    /*printf("\n\nData to be simulated >>> \n Number of balls -> %d\n", numBalls);

    for (i = 0; i < numBalls; i++) {
	printf("BALL %d: \nRadius -> %.2f\n (x, y) coordinates -> (%.2f, %.2f) \n(x, y) Velocities -> (%.2f, %.2f)\n\n", i + 1, balls[i].radius, balls[i].x, balls[i].y, balls[i].velx, balls[i].vely);
    }*/
    balls[1].velx =0;

    for (j = 0; j <= iterations; j++) {
	cleardevice();
	input = getch();

	if(input == 'd'){
	    //printf("\nup");
	    balls[1].velx += 0.1; }

	for (i = 0; i < numBalls; ++i) {
	    drawBall(&balls[i]);
	}

	delay(60);

	updatePhysics(balls, numBalls, dt, gravity);
    }
    closegraph();
}