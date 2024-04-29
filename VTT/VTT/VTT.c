#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TEAMS 64
#define MAX_TEAM_NAME_LENGTH 50

typedef char* string;

int determine_matches(int number_of_teams);

int main(void) {
	int number_of_teams;
	printf("Enter Number Teams: ");
	scanf_s("%d", &number_of_teams);

	if (number_of_teams % 2 != 0) {
		printf("INVALID NUMBER OF TEAMS: number of teams can't be odd\n");
		return 1;
	}

	if (number_of_teams <= 0 || number_of_teams > MAX_TEAMS) {
		printf("INVALID NUMBER OF TEAMS: number of teams can't be more then %i\n", MAX_TEAMS);
		return 2;
	}

	printf("\t\t\t\tWelcome to VTT!\n");

	determine_matches(number_of_teams);

	system("pause");

	return 0;
}

void shuffle(int array[], int size) {
	srand(time(NULL));
	for (int i = size - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		int temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}

int determine_matches(int number_of_teams) {
	string* team_names = (string*)malloc(number_of_teams * sizeof(string));

	if (team_names == NULL) {
		printf("Memory allocation failed\n");
		return 3;
	}

	for (int i = 0; i < number_of_teams; i++) {
		team_names[i] = (string)malloc((MAX_TEAM_NAME_LENGTH + 1) * sizeof(char));
		if (team_names[i] == NULL) {
			printf("Memory allocation failed\n");
			return 3;
		}

		printf("Enter Name of the Team #%i: ", i + 1);
		if (scanf_s("%s", team_names[i], MAX_TEAM_NAME_LENGTH + 1) != 1) {
			printf("Error reading input\n");
			return 4;
		}
	}

	bool* paired = (bool*)malloc(number_of_teams * sizeof(bool));
	if (paired == NULL) {
		printf("Memory allocation failed\n");
		return 3;
	}

	for (int i = 0; i < number_of_teams; i++) {
		paired[i] = false;
	}

	string maps[10] = { "Ascent", "Bind", "Breeze", "Fracture", "Haven", "Icebox", "Lotus", "Pearl", "Split", "Sunset" };

	int total_width = 2 * (MAX_TEAM_NAME_LENGTH + 1) + strlen("Map") + 5; // 5 is for the separators and additional spaces

	// Print the top horizontal line
	printf("\n");
	for (int i = 0; i < total_width; i++) {
		printf("-");
	}
	printf("\n");

	// Print the table headers
	printf("| Team 1(A)");
	for (int i = 0; i < MAX_TEAM_NAME_LENGTH - strlen("Team 1"); i++)
	{
		printf(" ");
	}
	printf("| Team 2(D)");
	for (int i = 0; i < MAX_TEAM_NAME_LENGTH - strlen("Team 2"); i++)
	{
		printf(" ");
	}
	printf("| Map   |\n");

	printf("\n");
	for (int i = 0; i < total_width; i++) {
		printf("-");
	}
	printf("\n");

	for (int i = 0; i < number_of_teams / 2; i++) {
		int index1, index2;

		do
		{
			index1 = srand(time(NULL)) % number_of_teams;
		} while (paired[index1]);
		paired[index1] = true;

		do
		{
			index2 = rand() % number_of_teams;
		} while (paired[index2] || index2 == index1);
		paired[index2] = true;

		int map = (rand() % 10 + 1) - 1;

		printf("| %s", team_names[index1]);
		for (int j = 0; j < MAX_TEAM_NAME_LENGTH - strlen(team_names[index1]); j++)
		{
			printf(" ");
		}
		printf("| %s", team_names[index2]);
		for (int j = 0; j < MAX_TEAM_NAME_LENGTH - strlen(team_names[index2]); j++)
		{
			printf(" ");
		}
		printf("| %s |\n", maps[map]);
	}

	for (int i = 0; i < total_width; i++)
	{
		printf("-");
	}
	printf("\n");

	for (int i = 0; i < number_of_teams; i++)
	{
		free(team_names[i]);
	}
	free(team_names);
	free(paired);

	return -1;
}