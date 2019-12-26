#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//  Author: John Cody
//  Date created: 03/28/2018
//  Program Description: This program don't do nothing. 

typedef struct {
	char listing_name[20];
	double acres;
	int price_per_acre;
	double length;
	double width;
	double price;
} Parcel;

void scan_listings(Parcel *x, FILE *in); 
void print_listings(Parcel *x); 
void selection(Parcel *x[], int size);
void swap(Parcel *x, Parcel *y);

int main(void) {

	int i = 0;
	FILE *input = fopen("Land_Listings.txt", "r"); 

	if (input == NULL) {
		printf("The file Land_Listings.txt could not be opened.\n");
		return -1;
	}

	Parcel *land[10];

	for (i = 0; i < 10; i++) {
		land[i] = (Parcel*)malloc(sizeof(Parcel));
		scan_listings(land[i], input);
	}

	selection(land, 10);

	for (i = 0; i < 10; i++) {
		print_listings(land[i]);
	}

	return 0;
}

void scan_listings (Parcel *x, FILE *in) {
	fscanf(in, " %s %lf %lf %lf", x->listing_name, &(x->length), &(x->width), &(x->price));
	x->acres = ((x->length)*(x->width)) / 43560.174;
	x->price_per_acre = round(x->price / x->acres);
}

void print_listings (Parcel *x) {
	printf("The %s property costs $%d per acre.\n", x->listing_name, x->price_per_acre);
}

void selection(Parcel *x[], int size) { // selection sort
	int i, j;
	int max;
	for (i = 0; i < size; i++) {
		max = i; // start searching from currently unsorted
		for (j = i; j < size; j++) {
			if (x[j]->price_per_acre > x[max]->price_per_acre) // if found a bigger element
				max = j; // move it to the front
		}
		swap(x[i], x[max]);
	}
}

void swap(Parcel *x, Parcel *y) {
	Parcel temp = *x;
	*x = *y; 
	*y = temp;
}