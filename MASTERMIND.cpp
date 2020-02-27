#include<iostream>
#include<cstdlib>
#include<ctime>
#include<stdio.h>
#include<locale.h>
using namespace std;
const int MAX_ATTEMPTS = 10;
const int MAX_COLORS = 6;
const int MAX_IN_ROW = 4;
const char COLORS[MAX_COLORS] = { 'r', 'z', 'n', 'f', 'p', 's' };

void instruction() 
{
	cout << "Witaj w grze Mastermind!" << endl << "Twoim zadanie jest odgadniêcie kolorów wylosowanych przez drugiego gracza!" << endl;
	cout << "Oto litery, którym odpowiadaj¹ kolejne kolory!" << endl;
	cout << "r:  ró¿owy" << endl;
	cout << "z:  zielony" << endl;
	cout << "n:  niebieski" << endl;
	cout << "f:  fioletowy" << endl;
	cout << "p:  pomarañczowy" << endl;
	cout << "s:  szary" << endl;
	cout << "Twoje próby zostan¹ ocenione za pomoc¹ poni¿szych liter:" << endl;
	cout << "b:  odpowiedni kolor lecz na z³ym miejscu" << endl;
	cout << "c:  odpowiedni kolor" << endl;
}

struct game_state 
{
	char current_attempt[MAX_IN_ROW]; 
	char coded_colors[MAX_IN_ROW]; 
	char game_response[MAX_IN_ROW]; 
};

void generate_random_colors(char* colors) 
{ 
	for (int i = 0; i < MAX_IN_ROW; i++)
	{
		int index = (rand() % MAX_COLORS);
		colors[i] = COLORS[index];
	}
}

void erase_table(char* table, int size) 
{
	for (int i = 0; i < size; i++) 
	{
		table[i] = ' ';
	}
}

void initialize_game(game_state* game)
{
	generate_random_colors(game->coded_colors);
	erase_table(game->current_attempt, MAX_IN_ROW);
	erase_table(game->game_response, MAX_IN_ROW);
	instruction();
}

void read_input(char* attempt) 
{
	for (int i = 0; i < MAX_IN_ROW; i++) 
	{
		cin >> attempt[i];
	}
}

void show(char* attempt) 
{
	for (int i = 0; i < MAX_IN_ROW; i++)
	{
		cout << "  |  " << attempt[i];
	}
	cout << "  |" << endl;
}

void check_game(char*attempt,char*colors,char*result) 
{
	for (int i = 0; i < MAX_IN_ROW; i++) 
	{

		if (attempt[i] == colors[i])
		{
			result[i] = 'c';
			continue;
		}
		for (int b = 0; b <MAX_IN_ROW; b++)
		{	
			if (attempt[i]==colors[b] && result[i]!='c' && result[i]!='b')
			{
				result[i] ='b';		
				break;
			}
		}
		if (result[i]!='b' && result[i]!='c' && result[i]!='#')
		{
			result[i] ='#';		
			continue;
		}
	}
}

bool win_lose(char*result) 
{
	bool wygrana = true;
	for (int j = 0; j <MAX_IN_ROW; j++)
	{
		if (result[j] != 'c')
		{
			wygrana = false;
			continue;
		}
	}
	if (wygrana)
	{
		cout <<endl << "Wygra³ gracz odgaduj¹cy" <<endl;
	}
	return wygrana;
}

void play_game(game_state* game) 
{
	initialize_game(game);
	for (int i = 0; i < MAX_ATTEMPTS; i++) 
	{
		erase_table(game->current_attempt, MAX_IN_ROW);
		erase_table(game->game_response, MAX_IN_ROW);
		cout<<"próba nr:  "<<i + 1 <<"  Podaj swoje typy kolorów:"<<endl;
		read_input(game->current_attempt);
		show(game->current_attempt);
		check_game(game->current_attempt, game->coded_colors, game->game_response);
		show(game->game_response);
		if(win_lose(game->game_response)) 
		{
			return;
		}
	}
	cout<<"Wygra³ gracz koduj¹cy"<<endl;
}

void play_or_end(game_state* game)
{
	bool first_game = true;
	while(true)
	{
		char a;
		if (!first_game) 
		{
			cout<<"Czy chcesz zagraæ ponownie w MasterMind?" << endl <<"Jeœli tak to wciœnij: t oraz ENTER"<<endl;
			cout<<"Jeœli nie to wciœnij: dowolny przycisk oraz ENTER"<<endl;
			cin >> a;
			if (a == 't' || a == 'T') 
			{
				play_game(game);
			}
			else if (a != 't') 
			{
				return;
			}
		}
		else
		{
			play_game(game);
			first_game = false;
		}
	}
}

int main()
{
	setlocale(LC_ALL,"polish");
	srand((int)time(NULL));
	game_state mastermind;
	game_state* mastermind_ptr = &mastermind;
	play_or_end(mastermind_ptr);
	return 0;
}
	


