#include <regex>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>

using namespace std;

/*Zadanie 1.
Stw�rz klas� "session", kt�ra b�dzie zawiera�a pola string login oraz bool logged. Zawrzyj w niej, w sekcji public metod� log_in, kt�ra w p�tli, przy pomocy bloku try catch b�dzie prowadzi�a logowanie.
W bloku try catch pytaj o login i has�o, i w zale�no�ci od wyniku metody waliduj�cej, kt�r� zaraz stworzysz rzucaj odpowiedni wyj�tek. Metod� waliduj�c� nazwij valid_log_data(string&,string&)
i przeprowadzaj wyszukiwanie z pliku login_database.csv , sprawdzaj�c przy pomocy regex_match() czy znaleziono login, a nast�pnie przy pomocy tej samej funkcji-poprawno�� has�a.
Aby m�c przeszuka� plik, otw�rz go i zobacz format w jakim jest zapisany.
*/
/*Zadanie 2.
Stworzono klas� "Citizen", zawieraj�c� pole string data oraz napisany konstruktor citizen(string), kt�ry b�dzie tworzy� obiekty tej klasy na podstawie przes�anego �a�cucha. Nast�pnie klas� "Citizen_list",
w kt�rej zawarto wektor obiekt�w klasy Citizen vector<Citizen> data, do kt�rego przy pomocy metody void create(string &file_name) b�dzie rzuca� kolejne obiekty zawieraj�ce po jednym wierszu
z pliku citizen_data.csv. Napisz metod�, void trolluj_reptilian(), kt�ra pozwoli grupie anonymous przeprowadzi� skuteczn� dezinformacj� przeciwnika. Nale�y znale�� reptilianina, zmieni� jego adres EMAIL,
oraz KOD POCZTOWY, aby nie mogli si� ze sob� skontaktowa� oraz WAG�, aby nie mogli przewidzie� ile paliwa wzi�� na statek. Aby rozpozna� reptilianina nale�y przeprowadzi� analiz� DNA. 
Odkryto, �e dla pewnej sekwencji zasad w kodzie DNA mo�na stwierdzi� �e obywatel jest reptilianinem. Ta sekwencja to kombinacja grup:
z C i/lub G - od dw�ch do czterech, T - zero lub jeden, A raz i CGT, po czym ma wyst�pi� dok�adnie ta sama pasuj�ca sekwencja kt�ra zosta�a dopasowana 
na pocz�tku, np.: 
CCA-CGT-CCA tak, ale nie CCA-CGT-CCGA (wszystkie grupy pasuj�, ale 1 i 3 musz� by� TE SAME). Do przeszukiwania wektora nale�y u�y� funkcji regex_match(), a nast�pnie dokona� podmiany danych u�ywaj�c
funkcji regex_replace(). Ca�o�� nale�y zapisa� do pliku, nadpisuj�c go przy u�yciu gotowej metody void save(string &file_name). Lepiej zachowaj w pogotowiu oryginalny plik.
*/
/*Zadanie 3.
Nale�y sporz�dzi� list� obywateli, kt�rzy s� reptilianami. W tym celu nale�y wczyta� plik do �a�cucha string przy pomocy gotowej funkcji string take_file(string &file_name). Nast�pnie w p�tli,
korzystaj�c z funkcji regex_search() oraz klasy match_result wyszukiwa� wyst�pienie DNA reptilianina oraz przy pomocy iteratora regex_token_iterator<string::const_iterator> dodawa� do pola
string list nowoutworzonej klasy Exodus_data kolejne rekordy zawieraj�ce ju� tylko email i kod pocztowy znalezionego reptilianina (zachowuj�c format pliku .csv- ";"). Przyda si� to do
poinformowania reptilian o zbli�aj�cej si� ucieczce z Ziemi. Dodatkowo po znalezieniu reptilianina nale�y doda� jego wag� do pola int weight tej samej klasy, 
aby reptilianie mogli wiedzie� ile potrzeba paliwa do ewakuacji ich rasy z Ziemi.
*/
//Zad. 1
class session {
	string login;
	bool logged;

	bool valid_log_data(string &log, string &psw) {		//metoda do logowania
		ifstream file;
		string tmp;
		regex reg_log(log, regex_constants::icase);
		regex reg_psw(psw);

		file.open("login_database.csv", ios::in);

		while (getline(file, tmp, ';')) {			//pobieraj string do delimitera, a� nie b�dzie to mo�liwe
			if (regex_match(tmp, reg_log)) {		//czy pobrany login to ten z bazy, nie liczy si� wielko�� liter
				getline(file, tmp);					//je�li tak, to pobierz reszt� linii
				if (regex_match(tmp, reg_psw))		//czy wpisane has�o pasuje do pobranego z bazy
					return true;
				else
					return false;
			}
			getline(file, tmp);						//pobierz reszt� linii (drug�, niepotrzebn� cz�� po delimiterze)
		}
		return false;								//je�li przesz�a ca�a p�tla i metoda nie zwr�ci�a true, zwr�� false
	}

public:
	void log_in() {
		string tmp_log;
		string pasw;
		while (true) {								//p�tla ko�czy si� dopiero, gdy uda si� zalogowa�
			try {
				cout << "Podaj login";
				getline(cin, tmp_log);
				cout << "Wpisz haslo";
				getline(cin, pasw);
				if (valid_log_data(tmp_log, pasw))
					throw 'a';
				else
					throw 1;
			}
			catch (char) {
				cout << "Udalo sie zalogowac" << endl;
				login = tmp_log;
				break;
			}
			catch (int) {
				cout << "Nie udalo sie zalogowac" << endl;
			}
		}
	}

};
//Zad. 2
class Citizen
{
	string data;
public:
	Citizen(string _data = "") : data(_data) {}
	~Citizen() {}
};

class Citizen_list {
	vector<Citizen> list;
public:
	Citizen_list() {}
	~Citizen_list() {}

	void create(string &file_name)
	{
		ifstream file;
		string line;
		file.open(file_name, ios::in);
		if (file.good())
		{
			while (getline(file, line))
			{
				Citizen c1 = Citizen(line);
				list.push_back(c1);
			}
			file.close();
		}
	}

};

int main() {
	session actual;
	string tmp;
	return 0;
}