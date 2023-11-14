#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <ctime>
#include <Windows.h>
#include <string>
#include <vector>
#include <map>
using namespace std;
class Card
{
private:
	string TYPECARD;
	string id;
	string name;
	double account;// счет
	
public:
	Card() : TYPECARD{""} {
		id = "";
		name = "";
		account = 0;
	}
	Card(string name, string typeCard) : TYPECARD{ typeCard } {
		for (size_t i = 0; i < 4; i++)
		{
			id += to_string((1000 + rand() % (10000 - 1000 + 1))) + " ";
		}
		this->name = name;
		account = 0;
	}
	~Card() {}

	virtual void refill(double money) {//пополнение счета
		account += money;
	}
	virtual void payment(double invoice) {//оплата чека
		if (account < invoice)
		{
			cout << "Недостаточно средств для совершения операции." << endl;
		}
		else
		{
			account -= invoice;
			cout << "Чек: " << endl;
			cout << "Сумма: " << invoice << endl;
		}
		
	}
	virtual double withdraw(double amounts) { //снятие
		if (account < amounts)
		{
			cout << "Недостаточно средств для совершения операции." << endl;
			return 0;
		}
		account -= amounts;
		return amounts;
	}
	virtual void printInfo(){
		cout << endl << "Тип карты: " << TYPECARD << endl;
		cout << "Номер карты: " << endl;
		cout << "\t" << id << endl;
		cout << "Имя: " << name << endl;
		cout << "Счет: " << account << endl;
	}

	string getId() {
		return id;
	}
	string getName() {
		return name;
	}
	virtual double getAccount() {
		return account;
	}
	string getTypeCard() {
		return TYPECARD;
	}
	string getTypeCard() const {
		return TYPECARD;
	}

	void setId(string id) {
		this->id = id;
	}
	void setName(string name) {
		this->name = name;
	}
	void setAccount(double account) {
		this->account = account;
	}
	void setTypeCard(string typeCard) {
		TYPECARD = typeCard;
	}
};

class DebitCard : public Card
{
private:
	string surname;
	int code;
	string date;
	
	void setDate() {
		date = to_string((rand() % 12 + 1)) + "/" + to_string(2027);
	}
	void setCode() {
		code = 100 + rand() % (1000 - 100 + 1);
	}
public:
	DebitCard() : Card() {
		surname = "";
		code = 0;
		date = "";
	}
	DebitCard(string name, string surname) : Card(name,"Debit") {
		this->surname = surname;
		setCode();
		setDate();
	}
	~DebitCard() {
		
	}

	string getSurname() {
		return surname;
	}
	int getCode() {
		return code;
	}
	string getDate() {
		return date;
	}

	void setSurname(string surname) {
		this->surname = surname;
	}
	void setCode(int code) {
		this->code = code;
	}
	void setDate(string date) {
		this->date = date;
	}
		
	virtual void printInfo() override {
		cout << "Тип карты: " << getTypeCard() << endl;
		cout << "Номер карты: " << endl;
		cout << "\t" << getId() << endl;
		cout << getName() << " " << surname << endl;
		cout << "Дата: " << date << "\t" << code << endl;
		cout << "Счет: " << getAccount() << endl;
	}
};

class CreditCard : public Card
{
private:
	string surname;
	int code;
	string date;

	double limit;
	double currLimit;
	int percent;
	bool gracePeriod;
	double debt;
	double minPayment;
	int perCommission;

private:
	void setDate() {
		date = to_string((rand() % 12 + 1)) + "/" + to_string(2027);
	}
	void setCode() {
		code = 100 + rand() % (1000 - 100 + 1);
	}
public:
	CreditCard() : Card() {
		surname = "";
		code = 0;
		date = "";
		limit = 0;
		currLimit = limit;
		gracePeriod = false;
		percent = 0;
		debt = 0;
		perCommission = 0;
		minPayment = 0;
		
	}
	CreditCard(string name, string surname) : Card(name, "Credit") {
		this->surname = surname;
		setCode();
		setDate();
		limit = 1000 + rand() % (50000 - 1000 + 1);
		currLimit = limit;
		gracePeriod = rand() % 2;
		if (!gracePeriod)
		{
			percent = 5 + rand() % (20 - 5 + 1);
			debt = limit * (5 + rand() % (50 - 5 + 1)) / 100;
			perCommission = debt * percent / 100;
		}
		else
		{
			percent = 0;
			debt = 0; //сумма которой расплатились
			perCommission = 0; //начисленные проценты
		}
		minPayment = limit * 10 / 100 + limit * percent / 100;
		
	}
	~CreditCard() {}

	string getSurname() {
		return surname;
	}
	int getCode() {
		return code;
	}
	string getDate() {
		return date;
	}
	double getDebt() {
		return debt;
	}
	double getMinPayment() {
		return minPayment;
	}
	
	void setSurname(string surname) {
		this->surname = surname;
	}
	void setCode(int code) {
		this->code = code;
	}
	void setDate(string date) {
		this->date = date;
	}
	void setLimit(double limit) {
		this->limit = limit;
	}
	void setPercent(double percent) {
		this->percent = percent;
	}
	void setGracePeriod(bool gracePeriod) {
		this->gracePeriod = gracePeriod;
	}
	void setDebt(double debt) {
		this->debt = debt;
	}
	void setMinPayment(double minPaiment) {
		this->minPayment = minPaiment;
	}
	void setPerCommission(int perCommission) {
		this->perCommission = perCommission;
	}
	

	virtual void refill(double money) override {//пополнение счета
		if (currLimit + money > limit)
		{
			cout << endl << "Превышение лимита." << endl;
		}
		else if(gracePeriod)
		{
			currLimit += money;
			debt -= money;
		}
		else
		{
			if (money > perCommission)
			{
				money -= perCommission;
				perCommission = 0;
				currLimit += money;
				debt -= money;
			}
			else
			{
				perCommission -= money;
			}
					
			
		}
		
	}
	virtual void payment(double invoice) override {//оплата чека
		if (debt == limit)
		{
			cout << "Недостаточно средств для совершения операции." << endl;
		}
		else
		{
			if (gracePeriod)
			{
				currLimit -= invoice;
				debt += invoice;
			}
			else
			{
				currLimit -= invoice;
				debt += invoice;
				perCommission += invoice * percent / 100;
			}
			cout << endl << "Чек: " << endl;
			cout << "Сумма: " << invoice << endl;
		}

	}
	virtual double withdraw(double amounts) override { //снятие
		if (debt + amounts > limit)
		{
			cout << "Недостаточно средств для совершения операции." << endl;
			return 0;
		}
		double commission = amounts * 20 / 100;
		cout << endl << "Комиссия составляет: " << commission << endl;
		currLimit -= (amounts + commission);
		debt += amounts + commission;
		return amounts;
	}
	virtual void printInfo() override {
		cout << "Тип карты: " << getTypeCard() << endl;
		cout << "Номер карты: " << endl;
		cout << "\t" << getId() << endl;
		cout << getName() << " " << surname << endl;
		cout << "Дата: " << date << "\t" << code << endl;
		cout << "Льготный период: " << (gracePeriod ? "Да." : "Нет.") << endl;
		cout << "Остаток на счете: " << currLimit << endl;
		cout << "Задолжность: " << debt << endl;
		cout << "Проценты: " << perCommission << endl;
	}
};

class Wallet : public Card
{
private:
	
	vector<CreditCard> cCards;
	vector<DebitCard> dCards;
	
public:
	Wallet() : Card(){
		string tmp = "#";
		for (size_t i = 0; i < 2; i++)
		{
			tmp += to_string((1000 + rand() % (10000 - 1000 + 1)));
		}
		setId(tmp);
		
	}
	Wallet(string name) : Card(name, "") {
		string tmp = "#";
		for (size_t i = 0; i < 2; i++)
		{
			tmp += to_string((1000 + rand() % (10000 - 1000 + 1)));
		}
		setId(tmp);
		
	}
	~Wallet() {
		cCards.clear();
		dCards.clear();
	}
	
	virtual void printInfo() override {
		cout << "Кошелек: " <<  endl;
		cout << "Имя: " << getName() << endl;
		cout << "Номер счета: " << getId() << endl;
		cout << "Счет: " << getAccount() << endl << endl;
	}

	DebitCard& getDCards(int key) {
		return dCards[key-1];
	}
	CreditCard& getCCards(int key) {
		return cCards[key-1];
	}
	 vector <DebitCard>& getVectorDCards() {
		return dCards;
	}
	 vector <CreditCard>& getVectorCCards() {
		 return cCards;
	 }
	void addDebitCard(string name, string surname) {
		DebitCard tmp(name, surname);
		dCards.push_back(tmp);
	}
	void addCreditCard(string name, string surname) {
		CreditCard tmp(name, surname);
		cCards.push_back(tmp);
	}
	void printDebitCard() {
		cout << endl << "Дебетовые карты:" << endl;
		for (size_t i = 0; i < dCards.size(); i++)
		{
			cout << i + 1 << ". ";
			dCards[i].printInfo();
			cout << endl;
		}
	}
	void printCreditCard() {
		cout << endl << "Кредитные карты:" << endl;
		for (size_t i = 0; i < cCards.size(); i++)
		{
			cout << i + 1 << ". ";
			cCards[i].printInfo();
			cout << endl;
		}
	}
	void printAllCard() {
		printDebitCard();
		printCreditCard();
		
	}
	void deleteDebitCard(int key) {

		for (size_t i = key - 1; i < dCards.size() - 1; i++)
		{
			dCards[i] = dCards[i + 1];
		}
		dCards.pop_back();
	}
	void deleteCreditCard(int key) {

		for (size_t i = key - 1; i < cCards.size() - 1; i++)
		{
			cCards[i] = cCards[i + 1];
		}
		cCards.pop_back();
	}
	void deleteAllCards() {
		cCards.clear();
		dCards.clear();
	}
};

class Category
{
private:
	string name;//наименование категории
	map<int, double> expenses; // затраты
	double maxSum;
public:
	Category() {
		name = "";
		maxSum = 0;
	}
	Category(string name) {
		this->name = name;
		maxSum = 0;
	}
	~Category() {
		expenses.clear();

	}

	string getName() {
		return name;
	}
	void setName(string name) {
		this->name = name;
	}
	map<int, double>& getExp() {
		return expenses;
	}
	void setMaxSum(double sum) {
		maxSum = sum;
	}
	double getMaxSum() {
		return maxSum;
	}
	void addExpenses(int date, double exp) {
		auto tmp = expenses.find(date);
		if (tmp!=expenses.end())
		{
			tmp->second += exp;
			maxSum += exp;
		}
		else
		{
			expenses[date] = exp;
			maxSum += exp;
		}
	}
	void dayExpenses(int date) {
		auto tmp = expenses.find(date);
		if (tmp != expenses.end())
		{
			cout << "Дата: " << tmp->first << " Сумма: " << tmp->second << endl;
			cout << "Хотите сохранить отчет в файл? 1 - Да, 2 - Нет" << endl;
			int choice;
			cin >> choice;
			cin.get();
			if (choice == 1)
			{
				map<int, double> buf;
				buf[tmp->first] = tmp->second;
				saveToFile(buf);
			}
		}
		else
		{
			cout << "Искомая дата не найдена!" << endl;
		}
	}
	void saveToFile(map<int, double>& saving) {
		string fileName;
		cout << "Введите название файла: " << endl;
		getline(cin, fileName);
		if (fileName.find(".txt") == string::npos)
		{
			fileName += ".txt";
		}
		

		ofstream save( fileName, ios::out | ios::app );
		
		if (!save) {
			cout << "Ошибка открытия файла!" << endl;
			exit(1);
		}

		char* buf = new char[50];
		strcpy(buf, name.c_str());
		int size = strlen(buf) + 1;
		save << buf << "\n";
		for (auto it = saving.begin(); it != saving.end(); it++) {
			save << it->first << " " << it->second << "\n";
		}
		save.close();
		
	}
	void weekExpenses(int date) {
		auto tmp = expenses.find(date);
		map<int, double> buf;
		if (tmp != expenses.end())
		{	
			for (auto it = expenses.begin(); it != expenses.end(); it++)
			{
				if (tmp->first <= 7 && it->first <= 7)
				{
					cout << "Дата: " << it->first << " Сумма: " << it->second << endl;
					buf[it->first] = it->second;
				}
				if (tmp->first > 7 && tmp->first <= 14 && it->first > 7 && it->first <=14)
				{
					cout << "Дата: " << it->first << " Сумма: " << it->second << endl;
					buf[it->first] = it->second;
				}
				if (tmp->first > 14 && tmp->first <= 21 && it->first > 14 && it->first <= 21)
				{
					cout << "Дата: " << it->first << " Сумма: " << it->second << endl;
					buf[it->first] = it->second;
				}
				if (tmp->first > 21 && tmp->first <= 28 && it->first > 21 && it->first <= 28)
				{
					cout << "Дата: " << it->first << " Сумма: " << it->second << endl;
					buf[it->first] = it->second;
				}
				if (tmp->first > 28 && tmp->first <= 31 && it->first > 28 && it->first <= 31)
				{
					cout << "Дата: " << it->first << " Сумма: " << it->second << endl;
					buf[it->first] = it->second;
				}
			}
			
			cout << "Хотите сохранить отчет в файл? 1 - Да, 2 - Нет" << endl;
			int choice;
			cin >> choice;
			cin.get();
			if (choice == 1)
			{
				saveToFile(buf);
			}
		}
		else
		{
			cout << "Искомая дата не найдена!" << endl;
		}
	}
	void monthExpenses(int date) {
		auto tmp = expenses.find(date);
		map<int, double> buf;
		if (tmp != expenses.end())
		{
			for (auto it = expenses.begin(); it != expenses.end(); it++)
			{
				cout << "Дата: " << it->first << " Сумма: " << it->second << endl;
				buf[it->first] = it->second;
			}

			cout << "Хотите сохранить отчет в файл? 1 - Да, 2 - Нет" << endl;
			int choice;
			cin >> choice;
			cin.get();
			if (choice == 1)
			{
				saveToFile(buf);
			}
		}
		else
		{
			cout << "Искомая дата не найдена!" << endl;
		}
	}
};

class System
{
private:

public:
	System() {}
	~System() {}

	void  top3Week(vector<Category>& category, int date) {

		vector<Category> top3;
		double sum;
		for (size_t i = 0; i < category.size(); i++)
		{
			sum = 0;
			for (auto it = category[i].getExp().begin(); it != category[i].getExp().end(); it++)
			{
				if (date <= 7 && it->first <= 7)
				{
					sum += it->second;
				}
				if (date > 7 && date <= 14 && it->first > 7 && it->first <= 14)
				{
					sum += it->second;
				}
				if (date > 14 && date <= 21 && it->first > 14 && it->first <= 21)
				{
					sum += it->second;
				}
				if (date > 21 && date <= 28 && it->first > 21 && it->first <= 28)
				{
					sum += it->second;
				}
				if (date > 28 && date <= 31 && it->first > 28 && it->first <= 31)
				{
					sum += it->second;
				}
			}
			Category cat(category[i].getName());
			cat.setMaxSum(sum);
			top3.push_back(cat);
		}
		for (size_t i = 0; i < top3.size(); i++)
		{
			for (size_t j = i + 1; j < top3.size() - 1; j++)
			{
				if (top3[i].getMaxSum() > top3[j].getMaxSum())
				{
					vector<Category> buff;
					buff.push_back(top3[i]);
					top3[i] = top3[j];
					top3[j] = buff[0];
				}
			}
		}
		for (size_t i = 0; i < 3; i++)
		{
			cout << "Категория: " << top3[i].getName() << endl;
			cout << "Затраты: " << top3[i].getMaxSum() << endl;
		}

		cout << "Хотите сохранить отчет в файл? 1 - Да, 2 - Нет" << endl;
		int choice;
		cin >> choice;
		cin.get();
		if (choice == 1)
		{

			saveToFile(top3);
		}
	}
	void  top3Month(vector<Category>& category, int date) {

		vector<Category> top3;
		double sum;
		for (size_t i = 0; i < category.size(); i++)
		{
			sum = 0;
			for (auto it = category[i].getExp().begin(); it != category[i].getExp().end(); it++)
			{
				sum += it->second;
			}
			Category cat(category[i].getName());
			cat.setMaxSum(sum);
			top3.push_back(cat);
		}
		for (size_t i = 0; i < top3.size(); i++)
		{
			for (size_t j = i + 1; j < top3.size() - 1; j++)
			{
				if (top3[i].getMaxSum() > top3[j].getMaxSum())
				{
					vector<Category> buff;
					buff.push_back(top3[i]);
					top3[i] = top3[j];
					top3[j] = buff[0];
				}
			}
		}
		for (size_t i = 0; i < 3; i++)
		{
			cout << "Категория: " << top3[i].getName() << endl;
			cout << "Затраты: " << top3[i].getMaxSum() << endl;
		}

		cout << "Хотите сохранить отчет в файл? 1 - Да, 2 - Нет" << endl;
		int choice;
		cin >> choice;
		cin.get();
		if (choice == 1)
		{

			saveToFile(top3);
		}
	}
	void  saveToFile(vector<Category>& cat) {
		string fileName;
		cout << "Введите название файла: " << endl;
		getline(cin, fileName);
		if (fileName.find(".txt") == string::npos)
		{
			fileName += ".txt";
		}


		ofstream save(fileName, ios::out | ios::app);

		if (!save) {
			cout << "Ошибка открытия файла!" << endl;
			exit(1);
		}

		char* buf = new char[50];
		strcpy(buf, "Топ 3 затрат:");
		int size = strlen(buf) + 1;
		save << buf << "\n";
		for (size_t i = 0; i < 3; i++)
		{
			save << " Наименование категории: " << cat[i].getName() << " " << "Затраты: " << cat[i].getMaxSum() << "\n";
		}
		save.close();
	}
	void mainMenu(vector<Wallet>& wallets, vector<Category>& category) {
		int choice, choiceWallet, date = 1;
		string name;
		Wallet buff(name);
		Category cat1("Снятие.");
		Category cat2("Прочее.");
		Category cat3(name);
		category.push_back(cat1);
		category.push_back(cat2);
		do
		{
			for (size_t i = 0; i < wallets.size(); i++)
			{
				cout << i + 1 << ".";
				wallets[i].printInfo();

				wallets[i].printDebitCard();

				wallets[i].printCreditCard();
			}
			cout << "Меню: " << endl;
			cout << "1 - Добавить кошелек." << endl;
			cout << "2 - Добавить карту." << endl;
			cout << "3 - Удалить кошелек." << endl;
			cout << "4 - Удалить карту." << endl;
			cout << "5 - Пополнение." << endl;
			cout << "6 - Снятие." << endl;
			cout << "7 - Оплатить." << endl;
			cout << "8 - Добавить категорию." << endl;
			cout << "9 - Удалить категорию." << endl;
			cout << "10 - ТОП - 3 неделя." << endl;
			cout << "11 - ТОП - 3 месяц." << endl;
			cout << "12 - Выход." << endl;
			cout << "Выберите пункт меню: " << endl;
			cin >> choice;
			cin.get();
			switch (choice)
			{
			case 1:
				cout << "Введите наименование кошелька: " << endl;
				getline(cin, name);
				buff.setName(name);
				wallets.push_back(buff);
				break;
			case 2:
				addCards(wallets);
				break;
			case 3:
				cout << "Выберите кошелек: " << endl;
				cin >> choiceWallet;
				cin.get();
				if (choiceWallet < 0 || choiceWallet > wallets.size())
				{
					cout << "Ошибка! Такого кошелька не существует!" << endl;
					choiceWallet = 1;
				}
				for (size_t i = choiceWallet - 1; i < wallets.size() - 1; i++)
				{
					wallets[i] = wallets[i + 1];
				}
				wallets[wallets.size() - 1].deleteAllCards();
				wallets.pop_back();
				break;
			case 4:

				deleteCrds(wallets);

				break;
			case 5:
				topUpCards(wallets);
				break;
			case 6:
				withdrawMoney(wallets, category);
				break;
			case 7:
				paymentMoney(wallets, category);
				break;
			case 8:
				cout << "Введите наименование категории: " << endl;
				getline(cin, name);
				cat3.setName(name);
				category.push_back(cat3);
				break;
			case 9:
				cout << "Выберите категорию: " << endl;
				cin >> choice;
				cin.get();
				if (choice < 0 || choice > category.size())
				{
					cout << "Ошибка! Такой категории не существует!" << endl;
					choice = 1;
				}
				for (size_t i = choice - 1; i < category.size() - 1; i++)
				{
					category[i] = category[i + 1];
				}
				category[category.size() - 1].getExp().clear();
				category.pop_back();
				break;
			case 10:
				cout << "Введите день: " << endl;
				cin >> date;
				cin.get();
				top3Week(category, date);
				break;
			case 11:
				cout << "Введите день: " << endl;
				cin >> date;
				cin.get();
				top3Month(category, date);
				break;
			case 12:
				
				break;
			default:
				cout << "Ошибка! Такого пункта меню нет! Повторите ввод." << endl;
				break;
			}
		} while (choice != 12);
	}
	void addCards(vector<Wallet>& wallets) {
		int choice, choiceWallet = 1;
		string name, surname;
		if (wallets.size() == 0)
		{
			cout << "Ошибка добавления карт. Необходимо создать кошелек!" << endl;
		}
		else
		{
			do
			{

				cout << "1 - Добавить дебитовую карту." << endl;
				cout << "2 - Добавить кредитную карту." << endl;
				cout << "3 - Выбор кошелька." << endl;
				cout << "4 - Выход." << endl;
				cout << "Выберите пункт меню: " << endl;
				cin >> choice;
				cin.get();
				switch (choice)
				{
				case 1:
					cout << "Введите имя: " << endl;
					getline(cin, name);
					cout << "Введите фамилию: " << endl;
					getline(cin, surname);
					wallets[choiceWallet - 1].addDebitCard(name, surname);
					break;
				case 2:
					cout << "Введите имя: " << endl;
					getline(cin, name);
					cout << "Введите фамилию: " << endl;
					getline(cin, surname);
					wallets[choiceWallet - 1].addCreditCard(name, surname);
					break;
				case 3:
					choiceWallet = walletSelection(wallets);
					break;
				case 4:
					break;
				default:
					cout << "Ошибка! Такого пункта меню нет! Повторите ввод." << endl;
					break;
				}
			} while (choice != 4);
		}

	}
	void deleteCrds(vector<Wallet>& wallets) {

		int choice, choiceWallet = 1;
		if (wallets.size() == 0)
		{
			cout << "Ошибка удаления. Нету созданных карт." << endl;
		}
		else
		{
			do
			{

				cout << "Выберите какую карту хотите удалить." << endl;
				cout << "1 - Дебетовая." << endl;
				cout << "2 - Кредитная." << endl;
				cout << "3 - Выбор кошелька." << endl;
				cout << "4 - Выход." << endl;
				cout << "Выберите пункт меню: " << endl;
				cin >> choice;
				cin.get();
				switch (choice)
				{
				case 1:
					for (size_t i = 0; i < wallets.size(); i++)
					{
						wallets[i].printDebitCard();
					}
					cout << "Выберите карту: " << endl;
					cin >> choice;
					cin.get();
					wallets[choiceWallet - 1].deleteDebitCard(choice);
					break;
				case 2:
					for (size_t i = 0; i < wallets.size(); i++)
					{
						wallets[i].printCreditCard();
					}
					cout << "Выберите карту: " << endl;
					cin >> choice;
					cin.get();
					wallets[choiceWallet - 1].deleteCreditCard(choice);
					break;
				case 3:
					choiceWallet = walletSelection(wallets);
					break;
				case 4:
					break;
				default:
					cout << "Ошибка! Такого пункта меню нет! Повторите ввод." << endl;
					break;
				}
			} while (choice != 4);
		}


	}
	int walletSelection(vector<Wallet>& wallets) {
		int choiceWallet = 1;
		for (size_t i = 0; i < wallets.size(); i++)
		{
			cout << i + 1 << ".";
			wallets[i].printInfo();
		}
		cout << "Выберите кошелек: " << endl;
		cin >> choiceWallet;
		cin.get();
		if (choiceWallet < 0 || choiceWallet > wallets.size())
		{
			cout << "Ошибка! Такого кошелька не существует!" << endl;
			return 1;
		}
		return choiceWallet;
	}
	void topUpCards(vector<Wallet>& wallets) {
		int choice, choiceWallet = 1, sum = 0;
		if (wallets.size() == 0)
		{
			cout << "Ошибка пополнения. Нету созданных карт." << endl;
		}
		else
		{
			do
			{

				cout << "Выберите какую карту хотите пополнить." << endl;
				cout << "1 - Дебетовая." << endl;
				cout << "2 - Кредитная." << endl;
				cout << "3 - Выбор кошелька." << endl;
				cout << "4 - Выход." << endl;
				cout << "Выберите пункт меню: " << endl;
				cin >> choice;
				cin.get();
				switch (choice)
				{
				case 1:
					for (size_t i = 0; i < wallets.size(); i++)
					{
						wallets[i].printDebitCard();
					}
					cout << "Выберите карту: " << endl;
					cin >> choice;
					if (choice < 0 || choice > wallets[choiceWallet - 1].getVectorDCards().size())
					{
						cout << "Такой карты не существует." << endl;
						choice = 1;
					}
					else
					{
						cout << "Введите сумму: " << endl;
						cin >> sum;
						cin.get();
						wallets[choiceWallet - 1].getDCards(choice).refill(sum);
					}

					break;
				case 2:
					for (size_t i = 0; i < wallets.size(); i++)
					{
						wallets[i].printCreditCard();
					}
					cout << "Выберите карту: " << endl;
					cin >> choice;
					if (choice < 0 || choice > wallets[choiceWallet - 1].getVectorCCards().size())
					{
						cout << "Такой карты не существует." << endl;
						choice = 1;
					}
					else
					{
						cout << "Введите сумму: " << endl;
						cin >> sum;
						cin.get();
						wallets[choiceWallet - 1].getCCards(choice).refill(sum);
					}
					break;
				case 3:
					choiceWallet = walletSelection(wallets);
					break;
				case 4:
					break;
				default:
					cout << "Ошибка! Такого пункта меню нет! Повторите ввод." << endl;
					break;
				}
			} while (choice != 4);
		}
	};
	void withdrawMoney(vector<Wallet>& wallets, vector<Category>& category) {
		int choice, choiceWallet = 1, sum = 0;
		int date = rand() % 31 + 1;
		if (wallets.size() == 0)
		{
			cout << "Ошибка снятия. Нету созданных карт." << endl;
		}
		else
		{
			do
			{

				cout << "Выберите какую карту с которой хотите снять." << endl;
				cout << "1 - Дебетовая." << endl;
				cout << "2 - Кредитная." << endl;
				cout << "3 - Выбор кошелька." << endl;
				cout << "4 - Выход." << endl;
				cout << "Выберите пункт меню: " << endl;
				cin >> choice;
				cin.get();
				switch (choice)
				{
				case 1:
					for (size_t i = 0; i < wallets.size(); i++)
					{
						wallets[i].printDebitCard();
					}
					cout << "Выберите карту: " << endl;
					cin >> choice;
					if (choice < 0 || choice > wallets[choiceWallet - 1].getVectorDCards().size())
					{
						cout << "Такой карты не существует." << endl;
						choice = 1;
					}
					else
					{

						cout << "Введите сумму: " << endl;
						cin >> sum;
						cin.get();
						if (wallets[choiceWallet - 1].getDCards(choice).withdraw(sum))
						{
							cout << "Вы сняли: " << sum << endl;
							for (size_t i = 0; i < category.size(); i++)
							{
								if (category[i].getName().find("Снятие.") != string::npos)
								{
									category[i].addExpenses(date, sum);
									break;
								}
							}
						}
					}

					break;
				case 2:
					for (size_t i = 0; i < wallets.size(); i++)
					{
						wallets[i].printCreditCard();
					}
					cout << "Выберите карту: " << endl;
					cin >> choice;
					if (choice < 0 || choice > wallets[choiceWallet - 1].getVectorCCards().size())
					{
						cout << "Такой карты не существует." << endl;
						choice = 1;
					}
					else
					{
						cout << "Введите сумму: " << endl;
						cin >> sum;
						cin.get();
						if (wallets[choiceWallet - 1].getCCards(choice).withdraw(sum))
						{
							cout << "Вы сняли: " << sum << endl;
							for (size_t i = 0; i < category.size(); i++)
							{
								if (category[i].getName().find("Снятие.") != string::npos)
								{
									category[i].addExpenses(date, sum);
								}
							}
						}
					}
					break;
				case 3:
					choiceWallet = walletSelection(wallets);
					break;
				case 4:
					break;
				default:
					cout << "Ошибка! Такого пункта меню нет! Повторите ввод." << endl;
					break;
				}
			} while (choice != 4);
		}

	}
	void paymentMoney(vector<Wallet>& wallets, vector<Category>& category) 
	{
		int choice, choiceWallet = 1, sum = 0;
		int date = rand() % 31 + 1;
		if (wallets.size() == 0)
		{
			cout << "Ошибка. Нету созданных карт." << endl;
		}
		else
		{
			do
			{

				cout << "Выберите какую карту с которой хотите оплатить." << endl;
				cout << "1 - Дебетовая." << endl;
				cout << "2 - Кредитная." << endl;
				cout << "3 - Выбор кошелька." << endl;
				cout << "4 - Выход." << endl;
				cout << "Выберите пункт меню: " << endl;
				cin >> choice;
				cin.get();
				switch (choice)
				{
				case 1:
					for (size_t i = 0; i < wallets.size(); i++)
					{
						wallets[i].printDebitCard();
					}
					cout << "Выберите карту: " << endl;
					cin >> choiceWallet;
					if (choiceWallet < 0 || choiceWallet > wallets[choiceWallet - 1].getVectorDCards().size())
					{
						cout << "Такой карты не существует." << endl;
						choice = 1;
					}
					else
					{

						cout << "Введите сумму оплаты: " << endl;
						cin >> sum;
						cin.get();
						for (size_t i = 0; i < category.size(); i++)
						{
							cout << i + 1 << ". " << category[i].getName() << endl;
						}
						cout << "Выберите категорию затрат." << endl;
						cin >> choice;

						if (choice < 0 || choice > category.size())
						{
							cout << "Такой категории не существует." << endl;
							for (size_t i = 0; i < category.size(); i++)
							{
								if (category[i].getName().find("Снятие.") != string::npos)
								{
									choice = i;
									break;
								}
							}
						}
						if (wallets[choiceWallet].getDCards(choice).withdraw(sum))
						{
							cout << "Вы сняли: " << wallets[choiceWallet].getDCards(choice).withdraw(sum) << endl;
							for (size_t i = 0; i < category.size(); i++)
							{
								category[choice].addExpenses(date, sum);
							}
						}
					}

					break;
				case 2:
					for (size_t i = 0; i < wallets.size(); i++)
					{
						wallets[i].printCreditCard();
					}
					cout << "Выберите карту: " << endl;
					cin >> choice;
					if (choice < 0 || choice > wallets[choiceWallet - 1].getVectorDCards().size())
					{
						cout << "Такой карты не существует." << endl;
						choice = 1;
					}
					else
					{

						cout << "Введите сумму оплаты: " << endl;
						cin >> sum;
						cin.get();
						for (size_t i = 0; i < category.size(); i++)
						{
							cout << i + 1 << ". " << category[i].getName() << endl;
						}
						cout << "Выберите категорию затрат." << endl;
						cin >> choice;

						if (choice < 0 || choice > category.size())
						{
							cout << "Такой категории не существует." << endl;
							for (size_t i = 0; i < category.size(); i++)
							{
								if (category[i].getName().find("Снятие.") != string::npos)
								{
									choice = i;
									break;
								}
							}
						}
						if (wallets[choiceWallet - 1].getDCards(choice).withdraw(sum))
						{
							cout << "Вы сняли: " << wallets[choiceWallet - 1].getCCards(choice).withdraw(sum) << endl;
							for (size_t i = 0; i < category.size(); i++)
							{
								category[choice].addExpenses(date, sum);
							}
						}
					}
					break;
				case 3:
					choiceWallet = walletSelection(wallets);
					break;
				case 4:
					break;
				default:
					cout << "Ошибка! Такого пункта меню нет! Повторите ввод." << endl;
					break;
				}
			} while (choice != 4);
		}

	}

};



int main()
{
	srand(time(NULL));
 	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	vector<Wallet> wallets;
	vector<Category> category;
	System sys;
	sys.mainMenu(wallets, category);

}
