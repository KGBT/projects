#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
using namespace std;
struct Text
{
    int k = 0;
    char text [1000][1000];
    char name[50] = "-";
    char author[50] = "-";
    char year[10] = "-";
};

int FindPos(Text* text, int number) {
    char tName[50]{};

    cout << "Введите название песни: ";
    cin >> tName;
    for (int i = 0; i < number; i++)
    {
        if (strstr(text[i].name, tName) != NULL)
        {

            return i;
            break;
        }
    }
    return -1;
}
void PrintCatalog(Text* text, int number) {

    for (int i = 0; i < number; i++)
    {
        cout << "Название: " << text[i].name << "\tАвтор: " << text[i].author << "\t\tГод: " << text[i].year << endl;

    }

}
void PrintText(Text* text, int number) {

    int position;
    cout << endl << "Отображение текста песни." << endl;
    PrintCatalog(text, number);
    position = FindPos(text, number);
    if (position == -1)
    {
        cout << "Такой песни нет в каталоге!" << endl;
    }
    else
    {

        cout << "Песня найдена!" << endl << endl;
        cout << "Название: " << text[position].name << "\tАвтор: " << text[position].author << "\t\tГод: " << text[position].year << endl;
        cout << "Текст песни: " << endl;
        for (int i = 0; i < text[position].k; i++)
        {
            cout << text[position].text[i] << endl;
        }
    }
}



void DeleteText(Text* text, int number) {

    int position;
    cout << endl << "Удаление текста песни." << endl;
    PrintCatalog(text, number);

    if (position = FindPos(text, number) != 0)
    {
        cout << "Такой песни нет в каталоге!" << endl;
    }
    else
    {

        cout << "Песня найдена!" << endl << endl;
        cout << "Название: " << text[position].name << "\tАвтор: " << text[position].author << "\t\tГод: " << text[position].year << endl;
        
        for (int i = 0; i < text[position].k; i++)
        {
            
            strcpy(text[position].text[i], " ");
        }
        text[position].k = 0;
    }
}

void AddTextManually(Text* &text, int& number) {
	
	cout << "Добавление песни." << endl;
	Text* buf = new Text[++number];
	for (int i = 0; i < number - 1; i++)
	{
		buf[i].k = text[i].k;
		strcpy(buf[i].name,text[i].name);
		strcpy(buf[i].author, text[i].author);
		strcpy(buf[i].year, text[i].year);
		for (int j = 0; j < text[i].k; j++)
		{
			strcpy(buf[i].text[j], text[i].text[j]);
		}
	}
	
	delete[] text;
	
	char* str = new char[1000];
	gets_s(str, 5);
	cout << "Введите название песни: " << endl;
	gets_s(buf[number-1].name, 50);
	cout << "Введите автора песни: " << endl;
	gets_s(buf[number-1].author, 50);
	cout << "Введите год издания песни: " << endl;
	gets_s(buf[number-1].year, 10);

	cout << "Чтобы завершить ввод текста введите \"EXIT\"." << endl;
	cout << "Введите текст песни: " << endl;
	
	while (true)
	{
		gets_s(str,1000);
		if (strcmp("EXIT", str) == 0)
		{
			break;
		}
		strcpy(buf[number-1].text[buf[number-1].k], str);
		buf[number-1].k++;
		
	}
	text = buf;
	PrintText(buf, number);
	delete[] str;
}
void AddTextFile(Text* &text, int& number) {

	cout << "Добавление песни из файла." << endl;
	
	Text* buf = new Text[++number];
	for (int i = 0; i < number - 1; i++)
	{
		buf[i].k = text[i].k;
		strcpy(buf[i].name, text[i].name);
		strcpy(buf[i].author, text[i].author);
		strcpy(buf[i].year, text[i].year);
		for (int j = 0; j < text[i].k; j++)
		{
			strcpy(buf[i].text[j], text[i].text[j]);
		}
	}
	delete[] text;
	text = buf;
	
	struct _finddata_t songs;
	char path[200] = "C:\\1\\";
	long done = _findfirst(strcat(path,"*.txt"), &songs);
	while (_findnext(done, &songs) != -1)
	{
		cout << songs.name << endl;
		
	}
	strcpy(path, "C:\\1\\");
	char* nameF = new char[1000];
	gets_s(nameF, 1000);
	cout << "Введите имя файла: " << endl;
	
	
	gets_s(nameF, 1000);
	strcat(path, nameF);
	strcat(path, ".txt");
	
	FILE* sText;
	if (fopen_s(&sText, path, "r") != NULL)
	{
		cout << "Файл невозможно открыть!" << endl;
	}
	else
	{
		cout << "Файл открыт!" << endl;
		fscanf_s(sText, "%s", buf[number-1].name, 50);
		fscanf_s(sText, "%s", buf[number - 1].author, sizeof(buf[number - 1].author));
		fscanf_s(sText, "%s", buf[number - 1].year, sizeof(buf[number - 1].year));
		fscanf_s(sText, "%d", buf[number - 1].k, sizeof(buf[number - 1].k));
		int i = 0;
		while (!feof(sText))
		{
			fscanf_s(sText, "%s", buf[number - 1].text[i], sizeof(buf[number - 1].text[i]));
			i++;
		}
	}
	PrintText(buf, number);
	
	fclose(sText);
}

void ChangeAllText(Text* text, int number) {
    int position;
    cout << endl << "Редактирование текста песни." << endl;
    PrintCatalog(text, number);

    if (position = FindPos(text, number))
    {
        cout << "Такой песни нет в каталоге!" << endl << endl;
    }
    else
    {
        char* str = new char[1000];
        cout << "Песня найдена!" << endl << endl;
        cout << "Название: " << text[position].name << "\tАвтор: " << text[position].author << "\t\tГод: " << text[position].year << endl;
        cout << "Чтобы завершить ввод текста введите \"EXIT\"." << endl;
        cout << "Введите новый текст песни: " << endl;
        text[position].k = 0;
        while (true)
        {
            cin >> str;
            if (strcmp("EXIT", str) == 0)
            {
                break;
            }
            else
            {
                strcpy(text[position].text[text[position].k], str);
                text[position].k++;
            }
        }
        delete[]str;
       
    }
}
void ChangeStrText(Text* text, int number) {
    int position;
    cout << endl << "Редактирование текста песни." << endl;
    PrintCatalog(text, number);

    if (position = FindPos(text, number))
    {
        cout << "Такой песни нет в каталоге!" << endl << endl;
    }
    else
    {
        int num = 0;
       
        cout << "Песня найдена!" << endl << endl;
        cout << "Название: " << text[position].name << "\tАвтор: " << text[position].author << "\t\tГод: " << text[position].year << endl;
        cout << "Текст песни: " << endl;
        for (int i = 0; i < text[position].k; i++)
        {
            cout << text[position].text[i] << endl;
        }
        cout << "Введите номер строки для редактирования: " << endl;
        cin >> num;
        cout << "Введите новую строку: " << endl;
        cin >> text[position].text[num-1];
        
    }
}
void ChangeWordText(Text* text, int number) {
    int position;
    cout << endl << "Редактирование текста песни." << endl;
    PrintCatalog(text, number);

    if (position = FindPos(text, number))
    {
        cout << "Такой песни нет в каталоге!" << endl << endl;
    }
    else
    {
        char* findWord = new char[1000] {};
        char* changeWord = new char[1000] {};
        bool isFind = false;
        char* answer1 = new char[30] {};
        char* answer2 = new char[30] {};
        cout << "Песня найдена!" << endl << endl;
        cout << "Название: " << text[position].name << "\tАвтор: " << text[position].author << "\t\tГод: " << text[position].year << endl;
        cout << "Текст песни: " << endl;
        for (int i = 0; i < text[position].k; i++)
        {
            cout << text[position].text[i] << endl;
        }
        cout << endl << "Введите заменяемое слово: " << endl;
        cin >> findWord;
        cout << "Введите слово, на которое хотите заменить: " << endl;
        cin >> changeWord;

        for (int i = 0; i < text[position].k; i++)
        {
            if (strstr(text[position].text[i], findWord))
            {
                isFind = true;
                break;
            }
        }

        if (isFind)
        {
            cout << "Заменяемое слово найдено. Хотите заменить все вхождения этого слова в тексте? Yes/No." << endl;
            cin >> answer1;
            for (int i = 0; i < strlen(answer1); i++)
            {
                answer2[i] = (char)tolower(answer1[i]);
            }
            int start = 0;
            char* buf1 = new char[10000] {};
			char* buf2 = new char[10000]{};
			int oWsize = strlen(findWord);
            if (strcmp(answer2, "yes") == 0)
            {
                
				for (int i = 0; i < text[position].k; i++)
				{
					do
					{

						start = strstr(text[position].text[i], findWord) - text[position].text[i];

						buf1[0] = '\0';
						// положим в буфер часть текста до заменяемого слова
						strncat(buf1, text[position].text[i], start);
						//добавим новое слово
						strcat(buf1, changeWord);
						// добавим оставшуюся часть текста
						strcat(buf1, text[position].text[i] + start + oWsize);
						text[position].text[i][0] = '\0';
						strcpy(text[position].text[i], buf1);

					} while (strstr(text[position].text[i], findWord) != nullptr);
				}
               
              
            }
            else
            {
                for (int i = 0; i < text[position].k; i++)
                {
                    if (buf1 = strstr(text[position].text[i], findWord))
                    {
                        start = strlen(text[position].text[i]) - strlen(buf1);
                        strncat(buf2, text[position].text[i], start);
                        strcat(buf2, changeWord);
                        strcat(buf2, (buf1+strlen(findWord)));
                        strcpy(text[position].text[i], buf2);
                        break;
                    }

                }
                
            }
            buf1 = {};
            buf2 = {};
            answer1 = {};
            answer2 = {};
            delete[]buf1;
            delete[]buf2;
            delete[]answer1;
            delete[]answer2;
        }
        else
        {
            cout << "Слово не найдено!" << endl << endl;
        }
        
        delete[]changeWord;
        delete[]findWord;

    }

    

        
    

}
void SubMenu(Text* text, int number) {
    
    int choice;
    do
    {
        cout << endl << "Редактирование текста песни." << endl;
        cout << "1 - Изменить текст целиком." << endl;
        cout << "2 - Изменить строку в тексте." << endl;
        cout << "3 - Изменить слово в тексте." << endl;
        cout << "4 - Выход." << endl;
        cout << "Выберите пункт меню: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            ChangeAllText(text, number);
            break;
        case 2:
            ChangeStrText(text, number);
            break;
        case 3:
            ChangeWordText(text, number);
            break;
        case 4:
            
            break;
        default:
            cout << "Ошибка! Повторите ввод!" << endl;
            break;
        }
    } while (choice != 4);
}

void SubMenu2(Text* text, int number) {

	int choice;
	do
	{
		cout << endl << "Добавление текста песни." << endl;
		cout << "1 - Добавить текст песни вручную." << endl;
		cout << "2 - Загрузить текст из файла." << endl;
		cout << "3 - Выход." << endl;
		cout << "Выберите пункт меню: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			AddTextManually(text, number);
			break;
		case 2:
			AddTextFile(text, number);
			break;
		case 3:
			
			break;
		
		default:
			cout << "Ошибка! Повторите ввод!" << endl;
			break;
		}
	} while (choice != 3);
}

void FindAutor(Text* text, int number) {

    
    cout << endl << "Поиск и отображение всех песен одного автора." << endl;
    PrintCatalog(text, number);

    char tAuthor[50];
    bool isFind = false;
    cout << "Введите автора: ";
    cin >> tAuthor;
    cout << endl;
    for (int i = 0; i < number; i++)
    {
        if (strcmp(text[i].author, tAuthor) == 0)
        {
            isFind = true;
            cout << "Название: " << text[i].name << "\tАвтор: " << text[i].author << "\t\tГод: " << text[i].year << endl;
            cout << "Текст песни: ";
            for (int j = 0; j < text[i].k; j++)
            {
                cout << text[i].text[j] << endl;
            }
            cout << endl;
        }
    }
   
    if (!isFind)
    {
        cout << "Такого автора нет в каталоге!" << endl;
    }
    
}
void FindWord(Text* text, int number) {

   
    cout << endl << "Поиск и отображение всех песен по заданному слову." << endl;
    PrintCatalog(text, number);

    char tWord[50];
    bool isFind = false;
    int position = 0;
    cout << "Введите слово: ";
    cin >>tWord;
    cout << endl;
    for (int i = 0; i < number; i++)
    {
        isFind = false;
        for (int j = 0; j < text[i].k; j++)
        {
            if (strstr(text[i].text[j], tWord) != NULL)
            {
                isFind = true;
                //position = i;
                break;
            }
        }
        if (isFind)
        {
            cout << "Название: " << text[i].name << "\tАвтор: " << text[i].author << "\t\tГод: " << text[i].year << endl;
            cout << "Текст песни: " << endl;
            for (int j = 0; j < text[i].k; j++)
            {
                cout << text[i].text[j] << endl;
            }
            cout << endl;
        }
        
    }

    if (!isFind)
    {
        cout << "Совпадений нет!" << endl;
    }

}

void SaveText(Text* text, int number) {

	char path [20] = "C:\\1\\";
	int position;
	cout << endl << "Сохранение текста песни." << endl;
	PrintCatalog(text, number);
	position = FindPos(text, number);
	if (position == -1)
	{
		cout << "Такой песни нет в каталоге!" << endl;
	}
	else
	{

		cout << "Песня найдена!" << endl << endl;
		cout << "Название: " << text[position].name << "\tАвтор: " << text[position].author << "\t\tГод: " << text[position].year << endl;
	}
	strcat(path, text[position].name);
	strcat(path, ".txt");
	

	FILE* sText;
	if (fopen_s(&sText, path, "w") != NULL)
	{
		cout << "Файл не может быть создан!" << endl;
	}
	else
	{
		cout << "Файл создан!" << endl;
		fprintf(sText, "%s", text[position].name);
		fprintf(sText, "\n");
		fprintf(sText, "%s", text[position].author);
		fprintf(sText, "\n");
		fprintf(sText, "%s", text[position].year);
		fprintf(sText, "\n");
		fprintf(sText, "%d", text[position].k);
		fprintf(sText, "\n");
		for (int i = 0; i < text[position].k; i++)
		{
			fprintf(sText, "%s", text[position].text[i]);
			fprintf(sText, "\n");
		}
	}
	fclose(sText);
}

void Menu(Text* text, int number) {
   
    int choice;
    do
    {
        cout << endl << "Добро пожаловать в приложение \"Каталог текстов песен\"" << endl;
        cout << "1 - Добавить текст песни." << endl;
        cout << "2 - Удалить текст песни." << endl;
        cout << "3 - Изменить текст песни." << endl;
        cout << "4 - Отобразить текст песни." << endl;
        cout << "5 - Сохранить текст песни в файл." << endl;
        cout << "6 - Поиск и отображение всех песен одного автора." << endl;
        cout << "7 - Поиск и отображение всех песен по заданному слову." << endl;
        cout << "8 - Выход." << endl;
        cout << "Выберите пункт меню: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
			SubMenu2(text, number);
            break;
        case 2:
            DeleteText(text, number);
            break;
        case 3:
            SubMenu(text, number);
            break;
        case 4:
            PrintText(text, number);
            break;
        case 5:
			SaveText(text, number);
            break;
        case 6:
            FindAutor(text, number);
            break;
        case 7:
            FindWord(text, number);
            break;
        case 8:
            cout << "До свидания!" << endl;
            break;
        default:
            cout << "Ошибка! Повторите ввод!" << endl;
            break;
        }
    } while (choice != 8);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	Text* text = new Text[1];
	for (int i = 0; i < 1; i++)
	{
		cout << "Введите имя: ";
		gets_s(text[i].name);
	}
	for (int i = 0; i < 1; i++)
	{
		cout << "i" << endl;
		for (int j = 0; j < 1; j++)
		{
			gets_s(text[i].text[j]);

			text[i].k++;
		}
	}
	int number = 1;
    Menu(text, number);
}

