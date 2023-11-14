#include <iostream>
#include <Windows.h>
#include <string>
#define height 12 //высота
#define width 12 //ширина
using namespace std;
int countPlShip[] = { 4, 3, 2, 1 };
int countCoShip[] = { 4, 3, 2, 1 };

void MainMenu();
void PlayGame(int**, int**, char**, char**);
void PlayGame2(int**, int**, char**, char**);
void ShotProc(int**, char**, int, int);

void CheckShipVert1(int** fieldInt, int hitX, int hitY, int lengShip, bool& flag) {

    for (int i = hitY; i > hitY - lengShip; i--)
    {
        if (fieldInt[i][hitX] == 6)
        {
            flag = true;
        }
        else
        {
            flag = false;
            break;
        }
    }
}
void CheckShipVert2(int** fieldInt, int hitX, int hitY, int lengShip, bool& flag) {

    for (int i = hitY; i < hitY + lengShip; i++)
    {
        if (fieldInt[i][hitX] == 6)
        {
            flag = true;
        }
        else
        {
            flag = false;
            break;
        }
    }
}
void CheckShipHor1(int** fieldInt, int hitX, int hitY, int lengShip, bool& flag) {

    for (int i = hitX; i < hitX + lengShip; i++)
    {
        if (fieldInt[hitY][i] == 6)
        {
            flag = true;
        }
        else
        {
            flag = false;
            break;
        }
    }
}
void CheckShipHor2(int** fieldInt, int hitX, int hitY, int lengShip, bool& flag) {

    for (int i = hitX; i > hitX - lengShip; i--)
    {
        if (fieldInt[hitY][i] == 6)
        {
            flag = true;
        }
        else
        {
            flag = false;
            break;
        }
    }
}


void FillAround1(int** fieldInt, char** fieldChar, int hitX, int hitY, int lengShip) {
    for (int i = hitY - lengShip; i <= hitY + 1; i++)
    {
        for (int j = hitX - 1; j <= hitX + 1; j++)
        {
            if (fieldInt[i][j] == 6)
            {
                continue;
            }
            else
            {
                fieldInt[i][j] = 5;
                fieldChar[i][j] = '.';
            }
        }
    }
}
void FillAround2(int** fieldInt, char** fieldChar, int hitX, int hitY, int lengShip) {
    for (int i = hitY - 1; i <= hitY + lengShip; i++)
    {
        for (int j = hitX - 1; j <= hitX + 1; j++)
        {
            if (fieldInt[i][j] == 6)
            {
                continue;
            }
            else
            {
                fieldInt[i][j] = 5;
                fieldChar[i][j] = '.';
            }
        }
    }
}
void FillAround3(int** fieldInt, char** fieldChar, int hitX, int hitY, int lengShip) {
    for (int i = hitY - 1; i <= hitY + 1; i++)
    {
        for (int j = hitX - 1; j <= hitX + lengShip; j++)
        {
            if (fieldInt[i][j] == 6)
            {
                continue;
            }
            else
            {
                fieldInt[i][j] = 5;
                fieldChar[i][j] = '.';
            }
        }
    }
}
void FillAround4(int** fieldInt, char** fieldChar, int hitX, int hitY, int lengShip) {
    for (int i = hitY - 1; i <= hitY + 1; i++)
    {
        for (int j = hitX - lengShip; j <= hitX + 1; j++)
        {
            if (fieldInt[i][j] == 6)
            {
                continue;
            }
            else
            {
                fieldInt[i][j] = 5;
                fieldChar[i][j] = '.';
            }
        }
    }
}

void InitGameField(int**&);
void InitGameField(char**&);
void InputPrintField(int**, char**);
void OutputGameField(char**, char**);
void OutputGameField(int**, int**);

void PlacementOfShips(int**, char**);
void InputVertically(int**, int&, int);
void InputHorizontally(int**, int&, int);

void PlacementOfShipsComp(int**);
void InputVerticallyComp(int**, int&, int);
void InputHorizontallyComp(int**, int&, int);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));

    MainMenu();
   
}

void InitGameField(int** &field) {
    field = new int* [height];
    for (int i = 0; i < height; i++)
    {
        *(field + i) = new int[width];
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            field[i][j] = 0;
        }
    }
       
}
void InitGameField(char** &field) {
    field = new char* [height];
    for (int i = 0; i < height; i++)
    {
		
        *(field + i) = new char[width];
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
			if (i == 0)
			{
				field[i][j] = j;
			}
			if (j == 0)
			{
				field[i][j] = j;
			}
            field[i][j] = '_';
            
        }
    }
    

}
void InputPrintField(int** fieldInt, char** fieldChar) {
    for (int i = 1; i < height-1; i++)
    {
        for (int j = 1; j < width-1; j++)
        {
            if (fieldInt[i][j] == 1 || fieldInt[i][j] == 2 || fieldInt[i][j] == 3 || fieldInt[i][j] == 4)
            {
                fieldChar[i][j] = '*';
            }

        }
    }
}
void OutputGameField(char** fieldPrint, char** enemyFieldPrint) {
    cout << "Наш флот: " << endl;
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            cout << fieldPrint[i][j];
        }
        cout << endl;
    }
    cout << endl;


    cout << "Вражеский флот: " << endl;
    
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            if (enemyFieldPrint[i][j] == '*')
            {
                cout << '_';
            }
            else
            {
                cout << enemyFieldPrint[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}
void OutputGameField(int** fieldPrint, int** enemyFieldPrint) { //служебный метод
    cout << "Наш флот: " << endl;
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            cout << fieldPrint[i][j];
        }
        cout << endl;
    }
    cout << endl;


    cout << "Вражеский флот: " << endl;

    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            cout << enemyFieldPrint[i][j];
        }
        cout << endl;
    }
    cout << endl;
}
void OutputField(char** fieldPrint) {
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            cout << fieldPrint[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

bool PlacementOfShipsPlayer(int** field, char** fieldChar) {
    
    static int countShips[4] = { 4,3,2,1 };
    int choice = 0, i = 0, lengShip = 0;
    do
    {
        cout << endl << endl;
        InputPrintField(field, fieldChar);
        OutputField(fieldChar);
        
        cout << "Расстановка кораблей." << endl;
        cout << "Выберите корабль: " << endl;
        cout << "1 - " << countShips[0] << " - однопалубных." << endl;
        cout << "2 - " << countShips[1] << " - двухпалубных." << endl;
        cout << "3 - " << countShips[2] << " - трехпалубных." << endl;
        cout << "4 - " << countShips[3] << " - четырехпалубный." << endl;
        cout << "5 - Выход." << endl;
        cin >> choice;
        i = choice - 1;
        lengShip = choice;
        switch (choice)
        {
        case 1:
             InputVertically(field, countShips[i], lengShip);
            break;
        case 2:
            do
            {
                cout << "Выберите расположение коробля: " << endl;
                cout << "1 - Вертикальное." << endl;
                cout << "2 - Горизонтальное." << endl;
                cout << "3 - Выход." << endl;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    InputVertically(field, countShips[i], lengShip);
                    choice = 3;
                    break;
                case 2:
                    InputHorizontally(field, countShips[i], lengShip);
                    choice = 3;
                    break;
                case 3:
                    break;
                default:
                    cout << "Ошибка! Повторите ввод!" << endl;
                    break;
                }
            } while (choice != 3);
            break;
        case 3:
            do
            {
                cout << "Выберите расположение коробля: " << endl;
                cout << "1 - Вертикальное." << endl;
                cout << "2 - Горизонтальное." << endl;
                cout << "3 - Выход." << endl;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    InputVertically(field, countShips[i], lengShip);
                    choice = 3;
                    break;
                case 2:
                    InputHorizontally(field, countShips[i], lengShip);
                    choice = 3;
                    break;
                case 3:
                    break;
                default:
                    cout << "Ошибка! Повторите ввод!" << endl;
                    break;
                }
            } while (choice != 3);
            break;
        case 4:
            do
            {
                cout << "Выберите расположение коробля: " << endl;
                cout << "1 - Вертикальное." << endl;
                cout << "2 - Горизонтальное." << endl;
                cout << "3 - Выход." << endl;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    InputVertically(field, countShips[i], lengShip);
                    choice = 3;
                    break;
                case 2:
                    InputHorizontally(field, countShips[i], lengShip);
                    choice = 3;
                    break;
                case 3:
                    break;
                default:
                    cout << "Ошибка! Повторите ввод!" << endl;
                    break;
                }
            } while (choice != 3);
            break;
        case 5:
            return true;
            break;
        default:
            cout << "Ошибка! Повторите ввод!" << endl;
            break;
        }
        
        if (countShips[0] == 0 && countShips[1] == 0 && countShips[2] == 0 && countShips[3] == 0)
        {
            
            return false;
            break;
        }
    } while (true);
}
void InputVertically(int** field, int& counterShips, int lengShip) {
    

    int x, y;
    bool flag;
    if (counterShips != 0)
    {
        do
        {
            flag = true;
            cout << "Введите координаты установки коробля: " << endl;
            cin >> x >> y;
            if (x > 10 || y > 10)
            {
                cout << "Ошибка! Такой координаты нет! Повторите ввод!" << endl;
                flag = false;

            }else if (y - 1 + lengShip > 10)
            {
                for (int i = y - lengShip; i <= y + 1; i++)
                {
                    for (int j = x - 1; j <= x + 1; j++)
                    {
                        if (field[i][j] == 1 || field[i][j] == 2 || field[i][j] == 3 || field[i][j] == 4)
                        {
                            flag = false;
                            break;
                        }
                    }
                    if (!flag)
                    {
                        break;
                    }
                }
                if (flag)
                {
                    for (int i = y; i > y - lengShip; i--)
                    {
                        field[i][x] = lengShip;
                    }
                    counterShips--;
                }
                else
                {
                    cout << "Вы не можете установить корабль по заданным координатам! Повторите ввод!" << endl;
                }

            }
            else
            {

                for (int i = y - 1; i <= y + lengShip; i++)
                {
                    for (int j = x - 1; j <= x + 1; j++)
                    {
                        if (field[i][j] == 1 || field[i][j] == 2 || field[i][j] == 3 || field[i][j] == 4)
                        {
                            flag = false;
                            break;
                        }
                    }
                    if (!flag)
                    {
                        break;
                    }
                }
                if (flag)
                {
                    for (int i = y; i < y + lengShip; i++)
                    {
                        field[i][x] = lengShip;
                    }
                    counterShips--;
                }
                else
                {
                    cout << "Вы не можете установить корабль по заданным координатам! Повторите ввод!" << endl;
                }

            }
            
            
            
        } while (!flag);

    }
    else
    {
        cout << "Ошибка! Вы не можете больше установить корабль данного типа!" << endl;
    }
    
}
void InputHorizontally(int** field, int& counterShips, int lengShip) {
    int x, y;
    bool flag;
    if (counterShips != 0)
    {
        do
        {
            flag = true;
            cout << "Введите координаты установки коробля: " << endl;
            cin >> x >> y;
            if (x > 10 || y > 10)
            {
                cout << "Ошибка! Такой координаты нет! Повторите ввод!" << endl;
                flag = false;

            }
            else if (x - 1 + lengShip > 10)
            {
                for (int i = y - 1; i <= y + 1; i++)
                {
                    for (int j = x - lengShip; j <= x + 1; j++)
                    {
                        if (field[i][j] == 1 || field[i][j] == 2 || field[i][j] == 3 || field[i][j] == 4)
                        {
                            flag = false;
                            break;
                        }
                    }
                    if (!flag)
                    {
                        break;
                    }
                }
                if (flag)
                {
                    for (int j = x; j > x - lengShip; j--)
                    {
                        field[y][j] = lengShip;
                    }
                    counterShips--;
                }
                else
                {
                    cout << "Вы не можете установить корабль по заданным координатам! Повторите ввод!" << endl;
                }

            }
            else
            {

                for (int i = y - 1; i <= y + 1; i++)
                {
                    for (int j = x - 1; j <= x + lengShip; j++)
                    {
                        if (field[i][j] == 1 || field[i][j] == 2 || field[i][j] == 3 || field[i][j] == 4)
                        {
                            flag = false;
                            break;
                        }
                    }
                    if (!flag)
                    {
                        break;
                    }
                }
                if (flag)
                {
                    for (int j = x; j < x + lengShip; j++)
                    {
                        field[y][j] = lengShip;
                    }
                    counterShips--;
                }
                else
                {
                    cout << "Вы не можете установить корабль по заданным координатам! Повторите ввод!" << endl;
                }

            }



        } while (!flag);

    }
    else
    {
        cout << "Ошибка! Вы не можете больше установить корабль данного типа!" << endl;
    }
}

void PlacementOfShipsComp(int** field) {

    int countShips[4] = { 4,3,2,1 };
    int choice = 0, i = 0, lengShip = 0;
    do
    {
        system("cls");
        //OutputGameField(field);
        
        choice = rand() % 4 + 1;
        i = choice - 1;
        lengShip = choice;
        switch (choice)
        {
        case 1:
            InputVerticallyComp(field, countShips[i], lengShip);
            break;
        case 2:
            do
            {

                choice = rand() % 2 + 1;
                switch (choice)
                {
                case 1:
                    InputVerticallyComp(field, countShips[i], lengShip);
                    choice = 3;
                    break;
                case 2:
                    InputHorizontallyComp(field, countShips[i], lengShip);
                    choice = 3;
                    break;

                }
            } while (choice != 3);
            break;
        case 3:
            do
            {

                choice = rand() % 2 + 1;
                switch (choice)
                {
                case 1:
                    InputVerticallyComp(field, countShips[i], lengShip);
                    choice = 3;
                    break;
                case 2:
                    InputHorizontallyComp(field, countShips[i], lengShip);
                    choice = 3;
                    break;
                }
            } while (choice != 3);
            break;
        case 4:
            do
            {

                choice = rand() % 2 + 1;
                switch (choice)
                {
                case 1:
                    InputVerticallyComp(field, countShips[i], lengShip);
                    choice = 3;
                    break;
                case 2:
                    InputHorizontallyComp(field, countShips[i], lengShip);
                    choice = 3;
                    break;

                }
            } while (choice != 3);
            break;

        }

        if (countShips[0] == 0 && countShips[1] == 0 && countShips[2] == 0 && countShips[3] == 0)
        {
            
            break;
        }
    } while (true);
}
void InputVerticallyComp(int** field, int& counterShips, int lengShip) {

    int x, y;
    bool flag;
    if (counterShips != 0)
    {
        do
        {
            flag = true;
            x = rand() % 10 + 1;
            y = rand() % 10 + 1;
           
            if (y - 1 + lengShip > 10)
            {
                for (int i = y - lengShip; i <= y + 1; i++)
                {
                    for (int j = x - 1; j <= x + 1; j++)
                    {
                        if (field[i][j] == 1 || field[i][j] == 2 || field[i][j] == 3 || field[i][j] == 4)
                        {
                            flag = false;
                            break;
                        }
                    }
                    if (!flag)
                    {
                        break;
                    }
                }
                if (flag)
                {
                    for (int i = y; i > y - lengShip; i--)
                    {
                        field[i][x] = lengShip;
                    }
                    counterShips--;
                }
               
            }
            else
            {

                for (int i = y - 1; i <= y + lengShip; i++)
                {
                    for (int j = x - 1; j <= x + 1; j++)
                    {
                        if (field[i][j] == 1 || field[i][j] == 2 || field[i][j] == 3 || field[i][j] == 4)
                        {
                            flag = false;
                            break;
                        }
                    }
                    if (!flag)
                    {
                        break;
                    }
                }
                if (flag)
                {
                    for (int i = y; i < y + lengShip; i++)
                    {
                        field[i][x] = lengShip;
                    }
                    counterShips--;
                }
                
            }

        } while (!flag);

    }
    

}
void InputHorizontallyComp(int** field, int& counterShips, int lengShip) {
    int x, y;
    bool flag;
    if (counterShips != 0)
    {
        do
        {
            x = rand() % 10 + 1;
            y = rand() % 10 + 1;
            flag = true;
             if (x - 1 + lengShip > 10)
            {
                for (int i = y - 1; i <= y + 1; i++)
                {
                    for (int j = x - lengShip; j <= x + 1; j++)
                    {
                        if (field[i][j] == 1 || field[i][j] == 2 || field[i][j] == 3 || field[i][j] == 4)
                        {
                            flag = false;
                            break;
                        }
                    }
                    if (!flag)
                    {
                        break;
                    }
                }
                if (flag)
                {
                    for (int j = x; j > x - lengShip; j--)
                    {
                        field[y][j] = lengShip;
                    }
                    counterShips--;
                }
                
            }
            else
            {

                for (int i = y - 1; i <= y + 1; i++)
                {
                    for (int j = x - 1; j <= x + lengShip; j++)
                    {
                        if (field[i][j] == 1 || field[i][j] == 2 || field[i][j] == 3 || field[i][j] == 4)
                        {
                            flag = false;
                            break;
                        }
                    }
                    if (!flag)
                    {
                        break;
                    }
                }
                if (flag)
                {
                    for (int j = x; j < x + lengShip; j++)
                    {
                        field[y][j] = lengShip;
                    }
                    counterShips--;
                }
               
            }

        } while (!flag);

    }
    
}


void MainMenu() {
    
    int choice, choiceMode;

    int** fieldCompShips;
    char** fieldCompShipsPrint;

    int** fieldPlayerShips;
    char** fieldPlayerShipsPrint;

    bool isPlacement;

    
    
    do
    {
        cout << "Меню игры: " << endl;
        cout << "1 - Новая игра." << endl;
        cout << "2 - Выход. " << endl;
        cout << "Выберите пункт меню: " << endl;
        cin >> choice;
        switch (choice)
        {
        
        case 1:
            do
            {

                isPlacement = true;
                InitGameField(fieldPlayerShips);
                InitGameField(fieldPlayerShipsPrint);

                InitGameField(fieldCompShips);
                InitGameField(fieldCompShipsPrint);
                cout << "Выберите режим игры: " << endl;
                cout << "1 - Человек - компьютер." << endl;
                cout << "2 - Компьютер - компьютер." << endl;
                cout << "3 - Вернутся к меню игры." << endl;
                cout << "Выберите пункт меню: " << endl;
                cin >> choiceMode;
                switch (choiceMode)
                {
                case 1:
                    do
                    {
                        cout << "Выберите расстановку кораблей: " << endl;
                        cout << "1 - Расставить корабли вручную." << endl;
                        cout << "2 - Расставит корабли компьютер." << endl;
                        cout << "3 - Вернутся к меню игры." << endl;
                        cout << "4 - В бой!" << endl;
                        cout << "Выберите пункт меню: " << endl;
                        cin >> choiceMode;
                        switch (choiceMode)
                        {
                        case 1:
                            if (isPlacement)
                            {
                                
                                isPlacement = PlacementOfShipsPlayer(fieldPlayerShips, fieldPlayerShipsPrint);
                                PlacementOfShipsComp(fieldCompShips);
                                InputPrintField(fieldPlayerShips, fieldPlayerShipsPrint);
                                InputPrintField(fieldCompShips, fieldCompShipsPrint);
                                cout << "Расстановка короблей завершена!" << endl;
                                
                            }
                            
                            break;
                        case 2:
                            if (isPlacement)
                            {
                                PlacementOfShipsComp(fieldPlayerShips);
                                PlacementOfShipsComp(fieldCompShips);
                                InputPrintField(fieldPlayerShips, fieldPlayerShipsPrint);
                                InputPrintField(fieldCompShips, fieldCompShipsPrint);
                                cout << "Расстановка короблей завершена!" << endl;
                                isPlacement = false;
                            }
                            break;
                        case 3:
                            break;
                        case 4:
                            PlayGame(fieldPlayerShips, fieldCompShips, fieldPlayerShipsPrint, fieldCompShipsPrint);
                            break;
                        default:
                            cout << "Ошибка! Повторите ввод!" << endl;
                            break;
                        }
                    } while (choiceMode != 3);
                    break;
                case 2:
                    do
                    {
                        cout << "Выберите расстановку кораблей: " << endl;
                        cout << "1 - Расставить корабли вручную." << endl;
                        cout << "2 - Расставит корабли компьютер." << endl;
                        cout << "3 - Вернутся к меню игры." << endl;
                        cout << "4 - В бой!" << endl;
                        cout << "Выберите пункт меню: " << endl;
                        cin >> choiceMode;
                        switch (choiceMode)
                        {
                        case 1:
                            if (isPlacement)
                            {
                                isPlacement = PlacementOfShipsPlayer(fieldPlayerShips, fieldPlayerShipsPrint);
                                isPlacement = PlacementOfShipsPlayer(fieldCompShips, fieldCompShipsPrint);
                                InputPrintField(fieldPlayerShips, fieldPlayerShipsPrint);
                                InputPrintField(fieldCompShips, fieldCompShipsPrint);
                                cout << "Расстановка короблей завершена!" << endl;
                                
                            }
                            
                            break;
                        case 2:
                            if (isPlacement)
                            {
                                PlacementOfShipsComp(fieldPlayerShips);
                                PlacementOfShipsComp(fieldCompShips);
                                InputPrintField(fieldPlayerShips, fieldPlayerShipsPrint);
                                InputPrintField(fieldCompShips, fieldCompShipsPrint);
                                isPlacement = false;
                                cout << "Расстановка короблей завершена!" << endl;
                            }
                            
                            break;
                        case 3:
                            break;
                        case 4:
                            PlayGame2(fieldPlayerShips, fieldCompShips, fieldPlayerShipsPrint, fieldCompShipsPrint);
                            break;
                        default:
                            cout << "Ошибка! Повторите ввод!" << endl;
                            break;
                        }
                    } while (choiceMode != 3);
                    break;
                case 3:
                    break;
                default:
                    cout << "Ошибка! Повторите ввод!" << endl;
                    break;
                }
            } while (choiceMode != 3);
            break;
        case 2:
            cout << "До свидания!" << endl;
            break;
        default:
            cout << "Ошибка! Повторите ввод!" << endl;
            break;
        }
    } while (choice != 2);
}

void PlayGame(int** fieldPlayer, int** fieldComp, char** fieldPlayerPrint, char** fieldCompPrint) {
    
    int hitX, hitY;
    bool endGamePl = false, endGameCo = false;
    int lengShip = 0;
    //OutputGameField(fieldPlayer, fieldComp);
    OutputGameField(fieldPlayerPrint, fieldCompPrint);
    while (true)
    {
              
        do
        {
            cout << "Введите координаты выстрела X, Y:" << endl;
            cin >> hitX >> hitY;
            ShotProc(fieldComp, fieldCompPrint, hitX, hitY);
            //system("cls");
            OutputGameField(fieldPlayerPrint, fieldCompPrint);
            if (fieldComp[hitY][hitX] == 5)
            {
                break;
            }
        } while ((fieldComp[hitY][hitX] != 0));
    
        do
        {
            cout << "Ход компьютера..." << endl;
            Sleep(2000);
            hitX = rand() % 10 + 1;
            hitY = rand() % 10 + 1;
            if (fieldPlayer[hitY][hitX] == 5 || fieldPlayer[hitY][hitX] == 6)
            {
                while (true)
                {
                    hitX = rand() % 10 + 1;
                    hitY = rand() % 10 + 1;
                    if (fieldPlayer[hitY][hitX] != 6 || fieldPlayer[hitY][hitX] != 5)
                    {
                        break;
                    }
                }

            }
            cout << "Координата по X: " << hitX << endl;
            cout << "Координата по Y: " << hitY << endl;
            ShotProc(fieldPlayer, fieldPlayerPrint, hitX, hitY);
            //system("cls");
            OutputGameField(fieldPlayerPrint, fieldCompPrint);
            if (fieldPlayer[hitY][hitX] == 5 || fieldPlayer[hitY][hitX] == 0)
            {
                break;
            }

        } while (true);
        
		for (int i = 1; i < height - 1; i++)
		{
			for (int j = 0; j < width - 1; j++)
			{
				if (fieldPlayer[i][j] > 4 || fieldPlayer[i][j] == 0)
				{
					endGamePl = true;

				}
				else if (fieldPlayer[i][j] >= 1 && fieldPlayer[i][j] <= 4)
				{
					endGamePl = false;
					break;
				}
			}
			if (!endGamePl)
			{
				break;
			}
		}
		for (int i = 1; i < height - 1; i++)
		{
			for (int j = 0; j < width - 1; j++)
			{
				if (fieldComp[i][j] > 4 || fieldComp[i][j] == 0)
				{
					endGameCo = true;

				}
				else if (fieldComp[i][j] >= 1 && fieldComp[i][j] <= 4)
				{
					endGameCo = false;
					break;
				}
			}
			if (!endGameCo)
			{
				break;
			}
		}
		if (endGamePl)
		{
			cout << "Поздравляем! Выйграл Компьютер!" << endl;
			break;
		}
		if (endGameCo)
		{
			cout << "Поздравляем! Выйграл Игрок!" << endl;
			break;
		}



    }
    
}
void PlayGame2(int** fieldPlayer, int** fieldComp, char** fieldPlayerPrint, char** fieldCompPrint) {

    bool endGamePl = false, endGameCo = false;
    int hitX, hitY;
    
    int lengShip = 0;
    
    string enter;
    //OutputGameField(fieldPlayer, fieldComp);
   
    while (true)
    {

        do
        {
            cout << "Ход компьютера 1..." << endl;
            //Sleep(2000);
            hitX = rand() % 10 + 1;
            hitY = rand() % 10 + 1;

            if (fieldComp[hitY][hitX] == 5 || fieldComp[hitY][hitX] == 6)
            {
                while (true)
                {
                    hitX = rand() % 10 + 1;
                    hitY = rand() % 10 + 1;
                    if (fieldComp[hitY][hitX] != 6 || fieldComp[hitY][hitX] != 5)
                    {
                        break;
                    }
                }

            }
            cout << "Координата по X: " << hitX << endl;
            cout << "Координата по Y: " << hitY << endl;

            ShotProc(fieldComp, fieldCompPrint, hitX, hitY);
            //system("cls");
            cout << endl << endl;
            cout << "Компьютер 1." << endl;
            OutputGameField(fieldPlayerPrint, fieldCompPrint);
            //getline(cin, enter);

            if (fieldComp[hitY][hitX] == 5 || fieldComp[hitY][hitX] == 0)
            {
                break;
            }

        } while (true);

        do
        {
            cout << "Ход компьютера 2..." << endl;
            //Sleep(2000);
            hitX = rand() % 10 + 1;
            hitY = rand() % 10 + 1;
            if (fieldPlayer[hitY][hitX] == 5 || fieldPlayer[hitY][hitX] == 6)
            {
                while (true)
                {
                    hitX = rand() % 10 + 1;
                    hitY = rand() % 10 + 1;
                    if (fieldPlayer[hitY][hitX] != 6 || fieldPlayer[hitY][hitX] != 5)
                    {
                        break;
                    }
                }

            }
            cout << "Координата по X: " << hitX << endl;
            cout << "Координата по Y: " << hitY << endl;
            ShotProc(fieldPlayer, fieldPlayerPrint, hitX, hitY);
            //system("cls");
            cout << endl << endl;
            cout << "Компьютер 2." << endl;
            OutputGameField(fieldCompPrint, fieldPlayerPrint);
            //getline(cin, enter);
            if (fieldPlayer[hitY][hitX] == 5 || fieldPlayer[hitY][hitX] == 0)
            {
                break;
            }

        } while (true);

        for (int i = 1; i < height - 1; i++)
        {
            for (int j = 0; j < width - 1; j++)
            {
                if (fieldPlayer[i][j] > 4 || fieldPlayer[i][j] == 0)
                {
                    endGamePl = true;

                }
                else if (fieldPlayer[i][j] >= 1 && fieldPlayer[i][j] <= 4)
                {
                    endGamePl = false;
                    break;
                }
            }
            if (!endGamePl)
            {
                break;
            }
        }
        for (int i = 1; i < height - 1; i++)
        {
            for (int j = 0; j < width - 1; j++)
            {
                if (fieldComp[i][j] > 4 || fieldComp[i][j] == 0)
                {
                    endGameCo = true;

                }
                else if (fieldComp[i][j] >= 1 && fieldComp[i][j] <= 4)
                {
                    endGameCo = false;
                    break;
                }
            }
            if (!endGameCo)
            {
                break;
            }
        }
        if (endGamePl)
        {
            cout << "Поздравляем! Выйграл Компьютер 2!" << endl;
            break;
        }
        if (endGameCo)
        {
            cout << "Поздравляем! Выйграл Компьютер 1!" << endl;
            break;
        }

    }
}

void ShotProc(int** fieldInt, char** fieldChar, int hitX, int hitY) {

    bool flag = false;
    int lengShip;
    if (fieldInt[hitY][hitX] == 1)
    {
        lengShip = 1;
        fieldInt[hitY][hitX] = 6;
        fieldChar[hitY][hitX] = 'x';

        FillAround1(fieldInt, fieldChar, hitX, hitY, lengShip);

    }

    if (fieldInt[hitY][hitX] == 2)
    {
        lengShip = 2;
        fieldInt[hitY][hitX] = 6;
        fieldChar[hitY][hitX] = 'x';
        if (fieldInt[hitY - 1][hitX] == 6)
        {
            FillAround1(fieldInt, fieldChar, hitX, hitY, lengShip);
        }
        if (fieldInt[hitY + 1][hitX] == 6)
        {
            FillAround2(fieldInt, fieldChar, hitX, hitY, lengShip);
        }
        if (fieldInt[hitY][hitX + 1] == 6)
        {
            FillAround3(fieldInt, fieldChar, hitX, hitY, lengShip);
        }
        if (fieldInt[hitY][hitX - 1] == 6)
        {
            FillAround4(fieldInt, fieldChar, hitX, hitY, lengShip);
        }
    }
    if (fieldInt[hitY][hitX] == 3)
    {
        lengShip = 3;
        fieldInt[hitY][hitX] = 6;
        fieldChar[hitY][hitX] = 'x';
        if (fieldInt[hitY - 1][hitX] == 6)
        {
            CheckShipVert1(fieldInt, hitX, hitY, lengShip, flag);

            if (flag)
            {
                FillAround1(fieldInt, fieldChar, hitX, hitY, lengShip);
            }
        }
        if (fieldInt[hitY + 1][hitX] == 6)
        {
            CheckShipVert2(fieldInt, hitX, hitY, lengShip, flag);
            if (flag)
            {
                FillAround2(fieldInt, fieldChar, hitX, hitY, lengShip);
            }

        }

        if (fieldInt[hitY][hitX + 1] == 6)
        {
            CheckShipHor1(fieldInt, hitX, hitY, lengShip, flag);
            if (flag)
            {
                FillAround3(fieldInt, fieldChar, hitX, hitY, lengShip);
            }

        }
        if (fieldInt[hitY][hitX - 1] == 6)
        {
            CheckShipHor2(fieldInt, hitX, hitY, lengShip, flag);
            if (flag)
            {
                FillAround4(fieldInt, fieldChar, hitX, hitY, lengShip);
            }

        }

    }
    if (fieldInt[hitY][hitX] == 4)
    {
        lengShip = 4;
        fieldInt[hitY][hitX] = 6;
        fieldChar[hitY][hitX] = 'x';
        if (fieldInt[hitY - 1][hitX] == 6)
        {
            CheckShipVert1(fieldInt, hitX, hitY, lengShip, flag);

            if (flag)
            {
                FillAround1(fieldInt, fieldChar, hitX, hitY, lengShip);
            }
        }
        if (fieldInt[hitY + 1][hitX] == 6)
        {
            CheckShipVert2(fieldInt, hitX, hitY, lengShip, flag);
            if (flag)
            {
                FillAround2(fieldInt, fieldChar, hitX, hitY, lengShip);
            }

        }

        if (fieldInt[hitY][hitX + 1] == 6)
        {
            CheckShipHor1(fieldInt, hitX, hitY, lengShip, flag);
            if (flag)
            {
                FillAround3(fieldInt, fieldChar, hitX, hitY, lengShip);
            }

        }
        if (fieldInt[hitY][hitX - 1] == 6)
        {
            CheckShipHor2(fieldInt, hitX, hitY, lengShip, flag);
            if (flag)
            {
                FillAround4(fieldInt, fieldChar, hitX, hitY, lengShip);
            }

        }
    }
    if (fieldInt[hitY][hitX] == 0)
    {
        fieldInt[hitY][hitX] = 5;
        fieldChar[hitY][hitX] = '.';
    }
}







/*
 if (fieldPlayer[hitY][hitX] == 3)
                {
                    fieldPlayer[hitY][hitX] = 6;
                    fieldPlayerPrint[hitY][hitX] = 'x';
                    remember = true;
                    if (remember)
                    {
                        rhitX = hitX;
                        rhitY = hitY;
                    }
                    direction = rand() % 2 + 1;
                    if (direction == 1)
                    {
                        do
                        {
                            do
                            {
                                hitY = rand() % ((hitY + 1) - (hitY - 1) + 1) + hitY - 1;

                            } while (fieldPlayer[hitY][hitX] != 0);

                            ShotProc(fieldComp, fieldCompPrint, hitX, hitY);

                        } while (fieldComp[hitY][hitX] != 6);

                    }
                    else
                    {

                        do
                        {
                            hitX = rand() % ((hitX + 1) - (hitX - 1) + 1) + hitX - 1;


                        } while (fieldPlayer[hitY][hitX] != 0);

                        ShotProc(fieldComp, fieldCompPrint, hitX, hitY);
                    }

                }
*/




/*if (fieldInt[hitY - 1][hitX] == 6)
        {
            for (int i = hitY; i > hitY - lengShip; i--)
            {
                if (fieldInt[i][hitX] == 6)
                {
                    flag = true;
                }
                else
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                for (int i = hitY - lengShip; i <= hitY + 1; i++)
                {
                    for (int j = hitX - 1; j <= hitX + 1; j++)
                    {
                        if (fieldInt[i][j] == 6)
                        {
                            continue;
                        }
                        else
                        {
                            fieldInt[i][j] = 5;
                            fieldChar[i][j] = '.';
                        }
                    }
                }
            }
        }*/

/*
         if (fieldComp[hitY][hitX] == 1)
         {
             fieldComp[hitY][hitX] = 6;
             fieldCompPrint[hitY][hitX] = 'x';

             for (int i = hitY-1; i <= hitY+1; i++)
             {
                 for (int j = hitX-1; j <= hitX+1; j++)
                 {
                     if (fieldComp[i][j] == 6)
                     {
                         continue;
                     }
                     else
                     {
                         fieldComp[i][j] = 5;
                         fieldCompPrint[i][j] = '.';
                     }
                 }
             }

         }
         if (fieldComp[hitY][hitX] == 2)
         {
             lengShip = 2;
             fieldComp[hitY][hitX] = 6;
             fieldCompPrint[hitY][hitX] = 'x';
             if (fieldComp[hitY - 1][hitX] == 6)
             {
                 for (int i = hitY - lengShip; i <= hitY + 1; i++)
                 {
                     for (int j = hitX - 1; j <= hitX + 1; j++)
                     {
                         if (fieldComp[i][j] == 6)
                         {
                             continue;
                         }
                         else
                         {
                             fieldComp[i][j] = 5;
                             fieldCompPrint[i][j] = '.';
                         }
                     }
                 }
             }
             if (fieldComp[hitY + 1][hitX] == 6)
             {
                 for (int i = hitY - 1; i <= hitY + lengShip; i++)
                 {
                     for (int j = hitX - 1; j <= hitX + 1; j++)
                     {
                         if (fieldComp[i][j] == 6)
                         {
                             continue;
                         }
                         else
                         {
                             fieldComp[i][j] = 5;
                             fieldCompPrint[i][j] = '.';
                         }
                     }
                 }
             }
             if (fieldComp[hitY][hitX + 1] == 6)
             {
                 for (int i = hitY - 1; i <= hitY + 1; i++)
                 {
                     for (int j = hitX - 1; j <= hitX + lengShip; j++)
                     {
                         if (fieldComp[i][j] == 6)
                         {
                             continue;
                         }
                         else
                         {
                             fieldComp[i][j] = 5;
                             fieldCompPrint[i][j] = '.';
                         }
                     }
                 }
             }
             if (fieldComp[hitY][hitX - 1] == 6)
             {
                 for (int i = hitY - 1; i <= hitY + 1; i++)
                 {
                     for (int j = hitX - lengShip; j <= hitX + 1; j++)
                     {
                         if (fieldComp[i][j] == 6)
                         {
                             continue;
                         }
                         else
                         {
                             fieldComp[i][j] = 5;
                             fieldCompPrint[i][j] = '.';
                         }
                     }
                 }
             }
         }
         if (fieldComp[hitY][hitX] == 3)
         {
             lengShip = 3;
             fieldComp[hitY][hitX] = 6;
             fieldCompPrint[hitY][hitX] = 'x';
             flag = false;

             if (fieldComp[hitY - 1][hitX] == 6)
             {
                 for (int i = hitY; i > hitY - lengShip; i--)
                 {
                     if (fieldComp[i][hitX] == 6)
                     {
                         flag = true;
                     }
                     else
                     {
                         flag = false;
                         break;
                     }
                 }

                 if (flag)
                 {
                     for (int i = hitY - lengShip; i <= hitY + 1; i++)
                     {
                         for (int j = hitX - 1; j <= hitX + 1; j++)
                         {
                             if (fieldComp[i][j] == 6)
                             {
                                 continue;
                             }
                             else
                             {
                                 fieldComp[i][j] = 5;
                                 fieldCompPrint[i][j] = '.';
                             }
                         }
                     }
                 }
             }
             if (fieldComp[hitY + 1][hitX] == 6)
             {
                 for (int i = hitY; i < hitY + lengShip; i++)
                 {
                     if (fieldComp[i][hitX] == 6)
                     {
                         flag = true;
                     }
                     else
                     {
                         flag = false;
                         break;
                     }
                 }
                 if (flag)
                 {
                     for (int i = hitY - 1; i <= hitY + lengShip; i++)
                     {
                         for (int j = hitX - 1; j <= hitX + 1; j++)
                         {
                             if (fieldComp[i][j] == 6)
                             {
                                 continue;
                             }
                             else
                             {
                                 fieldComp[i][j] = 5;
                                 fieldCompPrint[i][j] = '.';
                             }
                         }
                     }
                 }

             }

             if (fieldComp[hitY][hitX + 1] == 6)
             {
                 for (int i = hitX; i < hitX + lengShip; i++)
                 {
                     if (fieldComp[hitY][i] == 6)
                     {
                         flag = true;
                     }
                     else
                     {
                         flag = false;
                         break;
                     }
                 }
                 if (flag)
                 {
                     for (int i = hitY - 1; i <= hitY + 1; i++)
                     {
                         for (int j = hitX - 1; j <= hitX + lengShip; j++)
                         {
                             if (fieldComp[i][j] == 6)
                             {
                                 continue;
                             }
                             else
                             {
                                 fieldComp[i][j] = 5;
                                 fieldCompPrint[i][j] = '.';
                             }
                         }
                     }
                 }

             }
             if (fieldComp[hitY][hitX - 1] == 6)
             {
                 for (int i = hitX; i > hitX - lengShip; i--)
                 {
                     if (fieldComp[hitY][i] == 6)
                     {
                         flag = true;
                     }
                     else
                     {
                         flag = false;
                         break;
                     }
                 }
                 if (flag)
                 {
                     for (int i = hitY - 1; i <= hitY + 1; i++)
                     {
                         for (int j = hitX - lengShip; j <= hitX + 1; j++)
                         {
                             if (fieldComp[i][j] == 6)
                             {
                                 continue;
                             }
                             else
                             {
                                 fieldComp[i][j] = 5;
                                 fieldCompPrint[i][j] = '.';
                             }
                         }
                     }
                 }

             }

         }
         if (fieldComp[hitY][hitX] == 4)
         {
             lengShip = 4;
             fieldComp[hitY][hitX] = 6;
             fieldCompPrint[hitY][hitX] = 'x';
             flag = false;
             if (fieldComp[hitY - 1][hitX] == 6)
             {
                 for (int i = hitY; i > hitY - lengShip; i--)
                 {
                     if (fieldComp[i][hitX] == 6)
                     {
                         flag = true;
                     }
                     else
                     {
                         flag = false;
                         break;
                     }
                 }
                 if (flag)
                 {
                     for (int i = hitY - lengShip; i <= hitY + 1; i++)
                     {
                         for (int j = hitX - 1; j <= hitX + 1; j++)
                         {
                             if (fieldComp[i][j] == 6)
                             {
                                 continue;
                             }
                             else
                             {
                                 fieldComp[i][j] = 5;
                                 fieldCompPrint[i][j] = '.';
                             }
                         }
                     }
                 }
             }
             if (fieldComp[hitY + 1][hitX] == 6)
             {
                 for (int i = hitY; i < hitY + lengShip; i++)
                 {
                     if (fieldComp[i][hitX] == 6)
                     {
                         flag = true;
                     }
                     else
                     {
                         flag = false;
                         break;
                     }
                 }
                 if (flag)
                 {
                     for (int i = hitY - 1; i <= hitY + lengShip; i++)
                     {
                         for (int j = hitX - 1; j <= hitX + 1; j++)
                         {
                             if (fieldComp[i][j] == 6)
                             {
                                 continue;
                             }
                             else
                             {
                                 fieldComp[i][j] = 5;
                                 fieldCompPrint[i][j] = '.';
                             }
                         }
                     }
                 }

             }
             if (fieldComp[hitY][hitX + 1] == 6)
             {
                 for (int i = hitX; i < hitX + lengShip; i++)
                 {
                     if (fieldComp[hitY][i] == 6)
                     {
                         flag = true;
                     }
                     else
                     {
                         flag = false;
                         break;
                     }
                 }
                 if (flag)
                 {
                     for (int i = hitY - 1; i <= hitY + 1; i++)
                     {
                         for (int j = hitX - 1; j <= hitX + lengShip; j++)
                         {
                             if (fieldComp[i][j] == 6)
                             {
                                 continue;
                             }
                             else
                             {
                                 fieldComp[i][j] = 5;
                                 fieldCompPrint[i][j] = '.';
                             }
                         }
                     }
                 }

             }
             if (fieldComp[hitY][hitX - 1] == 6)
             {
                 for (int i = hitX; i > hitX - lengShip; i--)
                 {
                     if (fieldComp[hitY][i] == 6)
                     {
                         flag = true;
                     }
                     else
                     {
                         flag = false;
                         break;
                     }
                 }
                 if (flag)
                 {
                     for (int i = hitY - 1; i <= hitY + 1; i++)
                     {
                         for (int j = hitX - lengShip; j <= hitX + 1; j++)
                         {
                             if (fieldComp[i][j] == 6)
                             {
                                 continue;
                             }
                             else
                             {
                                 fieldComp[i][j] = 5;
                                 fieldCompPrint[i][j] = '.';
                             }
                         }
                     }
                 }

             }
         }
         if (fieldComp[hitY][hitX] == 0)
         {
             fieldComp[hitY][hitX] = 5;
             fieldCompPrint[hitY][hitX] = '.';
         }
         */



/*
if (fieldComp[hitY][hitX] == 1)
            {
                lengShip = 1;
                fieldComp[hitY][hitX] = 6;
                fieldCompPrint[hitY][hitX] = 'x';
                FillAround1(fieldComp, fieldCompPrint, hitX, hitY, lengShip);
            }
            else
            {

                if (fieldComp[hitY][hitX] == 2)
                {
                    fieldComp[hitY][hitX] = 6;
                    fieldCompPrint[hitY][hitX] = 'x';
                    direction = rand() % 2 + 1;
                    if (direction == 1)
                    {
                        if (fieldComp[hitY + 1][hitX] == 0 || fieldComp[hitY - 1][hitX] == 0)
                        {
                            do
                            {
                                hitY = rand() % ((hitY + 1) - (hitY - 1) + 1) + hitY - 1;

                            } while (fieldComp[hitY][hitX] != 0);
                            ShotProc(fieldComp, fieldCompPrint, hitX, hitY);
                        }


                    }
                    else
                    {

                        if (fieldComp[hitY][hitX + 1] == 0 || fieldComp[hitY][hitX - 1] == 0)
                        {
                            do
                            {
                                hitX = rand() % ((hitX + 1) - (hitX - 1) + 1) + hitX - 1;

                            } while (fieldComp[hitY][hitX] != 0);
                            ShotProc(fieldComp, fieldCompPrint, hitX, hitY);
                        }

                    }

                }

            }
*/

/*
if (fieldPlayer[hitY][hitX] == 1)
            {
                lengShip = 1;
                fieldPlayer[hitY][hitX] = 6;
                fieldPlayerPrint[hitY][hitX] = 'x';
                FillAround1(fieldPlayer, fieldPlayerPrint, hitX, hitY, lengShip);
            }
            else
            {

                if (fieldPlayer[hitY][hitX] == 2)
                {
                    fieldPlayer[hitY][hitX] = 6;
                    fieldPlayerPrint[hitY][hitX] = 'x';
                    direction = rand() % 2 + 1;
                    if (direction == 1)
                    {
                        if (fieldPlayer[hitY + 1][hitX] == 0 || fieldPlayer[hitY - 1][hitX] == 0)
                        {
                            do
                            {
                                hitY = rand() % ((hitY + 1) - (hitY - 1) + 1) + hitY - 1;

                            } while (fieldPlayer[hitY][hitX] != 0);
                            ShotProc(fieldPlayer, fieldPlayerPrint, hitX, hitY);
                        }


                    }
                    else
                    {

                        if (fieldPlayer[hitY][hitX + 1] == 0 || fieldPlayer[hitY][hitX - 1] == 0)
                        {
                            do
                            {
                                hitX = rand() % ((hitX + 1) - (hitX - 1) + 1) + hitX - 1;

                            } while (fieldPlayer[hitY][hitX] != 0);
                            ShotProc(fieldPlayer, fieldPlayerPrint, hitX, hitY);
                        }

                    }

                }

            }


*/