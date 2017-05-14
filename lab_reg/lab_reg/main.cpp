#include <regex>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>

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
z pliku citizen_data.csv. Wyszukaj reptilian i wypisuj na konsol� ich kod pocztowy oraz email. Lepiej znale�� wroga zanim on znajdzie nas.
Aby rozpozna� reptilianina nale�y przeprowadzi� analiz� DNA.
Odkryto, �e dla pewnej sekwencji zasad w kodzie DNA mo�na stwierdzi� �e obywatel jest reptilianinem. Ta sekwencja to kombinacja grup:
z C i/lub G - od dw�ch do czterech, T - zero lub jeden, A raz i CGT, po czym ma wyst�pi� dok�adnie ta sama pasuj�ca sekwencja kt�ra zosta�a dopasowana
na pocz�tku, np.:
CCA-CGT-CCA tak, ale nie CCA-CGT-CCGA (wszystkie grupy pasuj�, ale 1 i 3 musz� by� TE SAME). Niewa�na jest wielko�� liter w sekwencjach!! Ca�o�� nale�y zapisa� do pliku, nadpisuj�c go przy u�yciu gotowej
metody void save_file(string &file_name). Lepiej zachowaj w pogotowiu oryginalny plik.
*/
/*Zadanie 3.
Napisz metod�, void troll_reptilians(), kt�ra pozwoli grupie anonymous przeprowadzi� skuteczn� dezinformacj� przeciwnika. Nale�y znale�� reptilianina, zmieni� jego adres EMAIL,
oraz KOD POCZTOWY, aby nie mogli si� ze sob� skontaktowa� oraz WAG�, aby nie mogli przewidzie� ile paliwa wzi�� na statek. Podmiany danych nale�y dokona� u�ywaj�c
funkcji regex_replace(), po wcze�niejszym sprawdzeniu czy dany obywatel jest reptilianinem funkcj� regex_match.
*/
/*Zadanie 4.
Nale�y sporz�dzi� list� obywateli, kt�rzy s� reptilianami. W tym celu nale�y wczyta� plik do �a�cucha string przy pomocy gotowej funkcji string take_file(string &file_name). Nast�pnie w metodzie
void collect_rept_info() stworzy� p�tl�, w kt�rej korzystaj�c z funkcji regex_search() oraz klasy match_result nale�y wyszukiwa� wyst�pienie DNA reptilianina oraz przy pomocy iteratora
regex_token_iterator<string::const_iterator> dodawa� do pola string list nowoutworzonej klasy Exodus_data kolejne rekordy zawieraj�ce ju� tylko email i kod pocztowy znalezionego
reptilianina (zachowuj�c format pliku .csv- ";"). Przyda si� to do poinformowania reptilian o zbli�aj�cej si� ucieczce z Ziemi. Dodatkowo po znalezieniu reptilianina nale�y doda� jego wag� do pola
int weight tej samej klasy, aby reptilianie mogli wiedzie� ile potrzeba paliwa do ewakuacji ich rasy z Ziemi.
*/
//Zad. 1
class session {
	string login;
	bool logged;

	bool valid_log_data(string &log, string &psw) {		//metoda do logowania
		ifstream file;
		string tmp;
		regex reg_log(log);
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
				cout << "Podaj login\n";
				getline(cin, tmp_log);
				cout << "Wpisz haslo\n";
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
class Citizen {
public:
	string data;
	Citizen(string &_data) : data(_data) {}
	~Citizen() {}

};

class Citizen_list {
	vector<Citizen> list;
public:
	Citizen_list() {}
	~Citizen_list() {}

	void take_file(string &file_name) {
		ifstream file;
		string line;
		file.open(file_name, ios::in);
		if (file.good()) {
			while (getline(file, line)) {
				if (line.size() > 0) {
					Citizen c1 = Citizen(line);
					list.push_back(c1);
				}
			}
			file.close();
		}
	}

	void save_file(string &file_name)
	{
		ofstream file;
		file.open(file_name, ios::out);
		if (file.good()) {
			vector<Citizen>::iterator it = list.begin();
			for_each(list.begin(), list.end(), [&](Citizen &c) { file << c.data << endl; });
			file.close();
		}
	}

	void search_mail() {
		regex reg_line("([cg]{2,4}[t]{0,1}a)[-]cgt[-]\\1.*;([0-9]{2}-[0-9]{3}).*;([[:alnum:]]+@[[:alnum:]]+.[[:alpha:]]+).*;([[:digit:]]{1,3})\$", regex_constants::icase);	//niewa�na d�ugo��
		smatch m;
		for (vector<Citizen>::iterator it = list.begin(); it != list.end(); ++it) {
			regex_search((*it).data, m, reg_line);
			if (m[0].matched) {
				cout << string(m[2].first, m[2].second) << "  " << string(m[3].first, m[3].second) << endl;
			}
		}
	}

	//Zad. 3
	void troll_reptilians() {
		regex reg_line("([cg]{2,4}[t]{0,1}a)[-]cgt[-]\\1.*;([0-9]{2}-[0-9]{3}).*;([[:alnum:]]+@[[:alnum:]]+.[[:alpha:]]+).*;([[:digit:]]{1,3})\$", regex_constants::icase);

		regex reg_repl("([0-9]{2}-[0-9]{3});([[:alnum:]]+@[[:alnum:]]+.[[:alpha:]]+);([[:digit:]]{1,3})\$");
		string replacement("69-666;daj.kamienia@reptilianinie.hehe;1");

		string out;
		back_insert_iterator<string> p(out);

		for (vector<Citizen>::iterator it = list.begin(); it != list.end(); ++it) {
			if (regex_match((*it).data, reg_line)) {
				out = "";			//zerowanie �a�cucha
				regex_replace(p, (*it).data.begin(), (*it).data.end(), reg_repl, replacement);
				(*it).data = out;
			}
		}
	}

};
//Zad. 4
class Exodus_data {
	string list;
	int weight;
public:
	Exodus_data(string _list = "", int _weight = 0) : list(_list), weight(_weight) {}
	~Exodus_data() {}

	void collect_rept_info(string &all_data) {
		regex reg_line("([cg]{2,4}[t]{0,1}a)[-]cgt[-]\\1;.*([0-9]{2}-[0-9]{3});([[:alnum:]]+@[[:alnum:]]+.[[:alpha:]]+);([[:digit:]]{1,3})\$", regex_constants::icase);
		int fields[] = { 2,3 };
		regex_token_iterator<string::const_iterator>
			p1(all_data.begin(), all_data.end(), reg_line, fields),
			p2(all_data.begin(), all_data.end(), reg_line, 4),
			p_end;
		int i = 0;
		for (; p1 != p_end; ++p1) {
			list += *p1;
			if (i % 2 == 0)
				list += ";";
			else
				list += "\n";
			i++;
		}
		for (; p2 != p_end; ++p2) {
			weight += stoi(*p2);
		}
	}
	void save_file(string &file_name) {
		ofstream file;
		file.open(file_name, ios::out);
		if (file.good()) {
			file << list;
			file.close();
		}
	}
};

string file_to_string(string &file_name)
{
	string output = "";
	ifstream file;
	string line;
	file.open(file_name, ios::in);
	if (file.good()) {
		while (getline(file, line)) {
			if (line.size() > 0) {
				output += line + "\n";
			}
		}
		file.close();
	}
	return output;
}


int main() {
	session actual;
	actual.log_in();

	//anonymous fight reptilians
	Citizen_list cl1;
	string civil_base = "baza.csv";
	cl1.take_file(civil_base);
	cl1.search_mail();
	cl1.troll_reptilians();
	string output_file = "baza_test.csv";
	cl1.save_file(output_file);

	//reptilians want to leave Earth
	string all_data = file_to_string(civil_base);
	Exodus_data ed;
	ed.collect_rept_info(all_data);
	string output_rept = "reptilians_test.csv";
	ed.save_file(output_rept);

	return 0;
}