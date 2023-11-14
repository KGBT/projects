#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>
#include <conio.h>
using namespace std;

class Hangman
{
private:
	const int NUMBEROFATT; //количество попыток
	int start;//начало отсчета
	int end;//конец отсчета
	int numberOfAttempts;//количество использованных попыток 
	vector<string> randWord; //список слов
	string searchWord;//слово, которое небходимо отгадать
	string hiddenWord;//видимое для игрока слово
	string alphabet;//алфавит
	string letters;//буквы
	bool endGame;//конец игры

public:
	Hangman() : NUMBEROFATT{ 8 } {
		start = 0;
		end = 0;
		numberOfAttempts = 0;
		inputWord();
		hiddenWord = "";
		alphabet = "";
		letters = "";
		endGame = false;
	
	}
	~Hangman() {
		randWord.clear();
	}

	bool initGame() {
		if (randWord.size() != 0)
		{
			start = 0;
			end = 0;
			numberOfAttempts = 0;
			alphabet = "А Б В Г Д Е \nЖ З И Й К Л М\nН О П Р С Т У\nФ Х Ц Ч Ш Щ Ъ\nЫ Ь Э Ю Я\n";
			hiddenWord = "";
			searchWord = randWord[rand() % randWord.size()];
			
			for (size_t i = 0; i < searchWord.size(); i++)
			{
				hiddenWord += "-";
			}
			letters = "";
			endGame = false;
			return true;
		}
		return false;
		
	}

	void outputWord(const char* word) {

		ofstream words("Hangman words", ios::binary | ios::out | ios::app);
		if (!words) {
			cout << "Ошибка открытия файла!" << endl;
			exit(1);
		}

		int size = strlen(word) + 1;
		string tmp;
		for (size_t i = 0; i < size; i++)
		{
			tmp += toupper(word[i]);

		}

		words.write((char*)&size, sizeof(int));
		words.write((char*)tmp.c_str(), size * sizeof(char));
		words.close();
	}
	void inputWord() {
		ifstream words("Hangman words", ios::in | ios::binary);
		if (!words) {
			cout << "Ошибка открытия файла!" << endl;
			
		}
		else
		{
			char* word = nullptr;
			int size;
			while (words.read((char*)&size, sizeof(int)))
			{
				word = new char[size];
				words.read((char*)word, size * sizeof(char));
				randWord.push_back(word);
				delete[] word;
			}
		
		}
		words.close();

	}
	void deleteWord() {
		bool isFine = false;
		
		printList();
		cout << endl << "Введите слово, которое хотите удалить: " << endl;
		string word;
		getline(cin, word);
		string tmp;
	
		for (size_t i = 0; i < word.size(); i++)
		{
			tmp += toupper(word[i]);
		}
		
		for (size_t i = 0; i < randWord.size(); i++)
		{
			if (tmp == randWord[i])
			{
				isFine = true;
				string temp = randWord[i];
				randWord[i] = randWord[randWord.size() - 1];
				randWord[randWord.size() - 1] = temp;
				randWord.pop_back();
				
			}
		}
		if (isFine)
		{

			cout << "Слово успешно удалено." << endl;
			ofstream words("Hangman words", ios::binary | ios::out);
			for (size_t i = 0; i < randWord.size(); i++)
			{
				
				if (!words) {
					cout << "Ошибка открытия файла!" << endl;
					exit(1);
				}
				int size = strlen(randWord[i].c_str()) + 1;
				words.write((char*)&size, sizeof(int));
				words.write((char*)randWord[i].c_str(), size * sizeof(char));
				
			}
			words.close();
		}
		else
		{
			cout << "Ошибка! Не удалось найти слово." << endl;
			
		}
		
	}

	void setStart() {
		start = clock();
	}
	void setEnd() {
		end = clock();
	}
	int diffTime() {
		return (end - start) / CLOCKS_PER_SEC;
	}

	void setWord(string word) {
		
		string tmp;
		for (size_t i = 0; i < word.size(); i++)
		{
			tmp += toupper(word[i]);

		}
		randWord.push_back(tmp);
	}
	string getAlphabet() {
		return alphabet;
	}
	
	string getLetters() {
		return letters;
	}
	string getHiddenWord() {
		return hiddenWord;
	}
	string getSearchWord() {
		return searchWord;
	}
	int getNumberOfAttempts() {
		return numberOfAttempts;
	}
	int getNUMBEROFATT() {
		return NUMBEROFATT;
	}
	bool getEndGame() {
		return endGame;
	}


	int diffNumOfAtt() {
		return NUMBEROFATT - numberOfAttempts;
	}
	void guessedLetters(string word) {
		
		bool isFind = false;
		for (int i = 0; i < searchWord.size(); i++)
		{
			if (searchWord[i] == word[0])
			{
				isFind = true;
				hiddenWord[i] = word[0];
			}
		}
		
		for (size_t i = 0; i < alphabet.size(); i++)
		{
			if (alphabet[i] == word[0])
			{
				alphabet[i] = ' ';
			}
		}
	
		if (!isFind)
		{
			cout << "Вы не угадали букву! " << endl;
			
			numberOfAttempts++;
		}
		letters += word + " ";
	
	}
	void guessedWord(string word) {
						
		if (searchWord == word)
		{
			endGame = true;
		}
		else
		{
			numberOfAttempts++;
		}

	}

	void printList() {
			
		for (size_t i = 0; i < randWord.size(); i++)
		{
			cout << randWord[i] << endl;
		}
		cout << endl;
	}

	void printVictiry() {
		cout << endl << "Поздравляю! Вы отгадали слово!" << endl;
		cout << "Количество времени в секундах: " << diffTime() << endl;
		cout << "Количество попыток: " << getNumberOfAttempts() << endl;
		cout << "Искомое слово: " << searchWord << endl;
		cout << "Использованные буквы: " << endl;
		cout << letters << endl;
	}
	void printLose() {
		cout << endl << "Вас повесили." << endl;
		cout << "Количество времени в секундах: " << diffTime() << endl;
		cout << "Количество попыток: " << getNumberOfAttempts() << endl;
		cout << "Искомое слово: " << searchWord << endl;
		cout << "Использованные буквы: " << endl;
		cout << letters << endl;
	}
};

void drawHangman(HDC hdc, HPEN Pen) {
	Rectangle(hdc, 10, 0, 250, 250); // Рисуем квадрат
	SelectObject(hdc, Pen); // загружаем созданное перо в контекст
	MoveToEx(hdc, 50, 200, NULL);
	LineTo(hdc, 40, 225);
	MoveToEx(hdc, 50, 200, NULL);
	LineTo(hdc, 60, 225);
	MoveToEx(hdc, 50, 200, NULL);
	LineTo(hdc, 50, 50);
	LineTo(hdc, 150, 50);
}
void drawRope(HDC hdc, HPEN pen) {
	MoveToEx(hdc, 150, 50, NULL);
	SelectObject(hdc, pen);
	LineTo(hdc, 150, 100);
	MoveToEx(hdc, 150, 100, NULL);
	AngleArc(hdc, 150, 120, 15, 90, 360);
}
void drawHead(HDC hdc, HPEN pen) {
	SelectObject(hdc, pen);
	MoveToEx(hdc, 150, 110, NULL);
	AngleArc(hdc, 150, 120, 10, 90, 360);
	MoveToEx(hdc, 150, 130, NULL);
}
void drawBody(HDC hdc, HPEN pen) {
	SelectObject(hdc, pen);
	LineTo(hdc, 150, 200);
}
void drawLeftHand(HDC hdc, HPEN pen) {
	SelectObject(hdc, pen);
	MoveToEx(hdc, 150, 150, NULL);
	LineTo(hdc, 130, 170);
}
void drawRightHand(HDC hdc, HPEN pen) {
	SelectObject(hdc, pen);
	MoveToEx(hdc, 150, 150, NULL);
	LineTo(hdc, 170, 170);
}
void drawLeftLeg(HDC hdc, HPEN pen) {
	SelectObject(hdc, pen);
	MoveToEx(hdc, 150, 200, NULL);
	LineTo(hdc, 130, 220);
}
void drawRightLeg(HDC hdc, HPEN pen) {
	SelectObject(hdc, pen);
	MoveToEx(hdc, 150, 200, NULL);
	LineTo(hdc, 170, 220);
}

void draw(HWND hwnd, HDC hdc, int numberOfAtt)
{
	HPEN Pen1 = CreatePen(PS_SOLID, 10, RGB(255, 0, 0)); // создаем перо
	HPEN Pen2 = CreatePen(PS_SOLID, 8, RGB(0, 0, 255));
	HPEN Pen3 = CreatePen(PS_SOLID, 5, RGB(0, 100, 50));
	HPEN Pen4 = CreatePen(PS_SOLID, 5, RGB(150, 100, 50));
	HPEN Pen5 = CreatePen(PS_SOLID, 5, RGB(255, 255, 0));
	HPEN Pen6 = CreatePen(PS_SOLID, 5, RGB(0, 255, 255));
	switch (numberOfAtt)
	{
	case 0:
		Rectangle(hdc, 10, 0, 250, 250); // Рисуем квадрат
		break;
	case 1:
		drawHangman(hdc, Pen1);
		break;
	case 2:
		drawHangman(hdc, Pen1);
		drawRope(hdc, Pen2);
		break;
	case 3:
		drawHangman(hdc, Pen1);
		drawRope(hdc, Pen2);
		drawHead(hdc, Pen3);
		break;
	case 4:
		drawHangman(hdc, Pen1);
		drawRope(hdc, Pen2);
		drawHead(hdc, Pen3);
		drawBody(hdc, Pen4);
		break;
	case 5:
		drawHangman(hdc, Pen1);
		drawRope(hdc, Pen2);
		drawHead(hdc, Pen3);
		drawBody(hdc, Pen4);
		drawLeftHand(hdc, Pen5);
		break;
	case 6:
		drawHangman(hdc, Pen1);
		drawRope(hdc, Pen2);
		drawHead(hdc, Pen3);
		drawBody(hdc, Pen4);
		drawLeftHand(hdc, Pen5);
		drawRightHand(hdc, Pen5);
		break;
	case 7:
		drawHangman(hdc, Pen1);
		drawRope(hdc, Pen2);
		drawHead(hdc, Pen3);
		drawBody(hdc, Pen4);
		drawLeftHand(hdc, Pen5);
		drawRightHand(hdc, Pen5);
		drawLeftLeg(hdc, Pen6);
		break;
	case 8:
		drawHangman(hdc, Pen1);
		drawRope(hdc, Pen2);
		drawHead(hdc, Pen3);
		drawBody(hdc, Pen4);
		drawLeftHand(hdc, Pen5);
		drawRightHand(hdc, Pen5);
		drawLeftLeg(hdc, Pen6);
		drawRightLeg(hdc, Pen6);
		break;
	}
}

void gotoxy(int x, int y)
{
	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(hConsole, position);
}
int main()
{
	HDC hdc = GetDC(GetConsoleWindow());
	HWND hwnd = GetConsoleWindow();
	
	COLORREF bk = SetBkColor(hdc, RGB(255, 255, 255));
	if (bk == CLR_INVALID) cout << "Color error\n";
	SetTextColor(hdc, RGB(0, 0, 0));
	//TextOutA(hdc, 500, 10, "Красный текст на желтом фоне", 28);
	srand(time(NULL));
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "Добро пожаловать в игру Виселица!" << endl;
	int choice;
	string word;
	Hangman hangman;
	do
	{
		
		cout << "Выберите пункт меню: " << endl;
		cout << "1 - Новая игра." << endl;
		cout << "2 - Добавить слово." << endl;
		cout << "3 - Просмотр списка слов." << endl;
		cout << "4 - Удалить слово из списка." << endl;
		cout << "5 - Выход." << endl;
		cin >> choice;
		cin.get();
		switch (choice)
		{
		case 1:
			system("cls");
			if (hangman.initGame())
			{
				hangman.setStart();
				
				while (true)
				{
					system("cls");
					gotoxy(0, 16);
					Sleep(10);
					draw(hwnd, hdc, hangman.getNumberOfAttempts());
					cout << "Загаданное слово: " << endl;
					cout << hangman.getHiddenWord() << endl;
					cout << "Использованные буквы: " << endl;
					cout << hangman.getAlphabet() << endl;
					cout << "Введите букву или слово целиком: " << endl;
					getline(cin, word);
					string tmp;
					for (size_t i = 0; i < word.size(); i++)
					{
						tmp += toupper(word[i]);
					}
					word = tmp;
					if (word.size() == 1)
					{
					
						hangman.guessedLetters(word);
					}
					else
					{
						hangman.guessedWord(word);
					}
					
					
					if (hangman.getHiddenWord() == hangman.getSearchWord())
					{
						system("cls");
						gotoxy(0, 16);
						Sleep(10);
						draw(hwnd, hdc, hangman.getNumberOfAttempts());
						hangman.setEnd();
						hangman.printVictiry();
						break;
					}
					if (hangman.getEndGame())
					{
						system("cls");
						gotoxy(0, 16);
						Sleep(10);
						draw(hwnd, hdc, hangman.getNumberOfAttempts());
						hangman.setEnd();
						hangman.printVictiry();
						break;
					}
					if (hangman.getNUMBEROFATT() == hangman.getNumberOfAttempts())
					{
						system("cls");
						gotoxy(0, 16);
						Sleep(10);
						draw(hwnd, hdc, hangman.getNumberOfAttempts());
						hangman.setEnd();
						hangman.printLose();
						break;
					}
				}
			}
			else {
				cout << "Ошибка инициализации игры! Добавьте список слов." << endl;
			}
			
			break;
		case 2:
			cout << "Правило добавления слов: " << endl;
			cout << "Добавляемое слово должно быть именем существительным, нарицательным в именительном падеже " << endl;
			cout << "единственного числа, либо множественного числа при отсутствии у слова формы единственного числа." << endl;
			getline(cin, word);
			hangman.outputWord(word.c_str());
			hangman.setWord(word);
			system("cls");
			break;
		case 3:
			cout << endl << "Список слов:" << endl;
			hangman.printList();
			break;
		case 4:
			cout << "Удаление слова." << endl;
			hangman.deleteWord();
			break;
		case 5:
			cout << "Пока-пока!" << endl;
			break;
		default:
			cout << "Ошибка! Повторите ввод!" << endl;
			break;
		}
		
	} while (choice != 5);

}
