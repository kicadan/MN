#include <regex>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

/*Zadanie 1.
Stwórz klasê "session", która bêdzie zawiera³a pola string login oraz bool logged. Zawrzyj w niej, w sekcji public metodê log_in, która w pêtli, przy pomocy bloku try catch bêdzie prowadzi³a logowanie.
W bloku try catch pytaj o login i has³o, i w zale¿noœci od wyniku metody waliduj¹cej, któr¹ zaraz stworzysz rzucaj odpowiedni wyj¹tek. Metodê waliduj¹c¹ nazwij valid_log_data(string&,string&)
i przeprowadzaj wyszukiwanie z pliku login_database.csv , sprawdzaj¹c przy pomocy regex_match() czy znaleziono login, a nastêpnie przy pomocy tej samej funkcji-poprawnoœæ has³a.
Aby móc przeszukaæ plik, otwórz go i zobacz format w jakim jest zapisany.
*/
/*Zadanie 2.
Stworzono klasê "Citizen", zawieraj¹c¹ pole string data oraz napisany konstruktor citizen(string), który bêdzie tworzy³ obiekty tej klasy na podstawie przes³anego ³añcucha. Nastêpnie klasê "Citizen_list",
w której zawarto wektor obiektów klasy Citizen vector<Citizen> data, do którego przy pomocy metody void create(string &file_name) bêdzie rzucaæ kolejne obiekty zawieraj¹ce po jednym wierszu
z pliku citizen_data.csv. Wyszukaj reptilian i wypisuj na konsolê ich kod pocztowy oraz email. Lepiej znaleŸæ wroga zanim on znajdzie nas.
Aby rozpoznaæ reptilianina nale¿y przeprowadziæ analizê DNA.
Odkryto, ¿e dla pewnej sekwencji zasad w kodzie DNA mo¿na stwierdziæ ¿e obywatel jest reptilianinem. Ta sekwencja to kombinacja grup:
z C i/lub G - od dwóch do czterech, T - zero lub jeden, A raz i CGT, po czym ma wyst¹piæ dok³adnie ta sama pasuj¹ca sekwencja która zosta³a dopasowana
na pocz¹tku, np.:
CCA-CGT-CCA tak, ale nie CCA-CGT-CCGA (wszystkie grupy pasuj¹, ale 1 i 3 musz¹ byæ TE SAME). Niewa¿na jest wielkoœæ liter w sekwencjach!! Ca³oœæ nale¿y zapisaæ do pliku, nadpisuj¹c go przy u¿yciu gotowej
metody void save_file(string &file_name). Lepiej zachowaj w pogotowiu oryginalny plik.
*/
/*Zadanie 3.
Napisz metodê, void troll_reptilians(), która pozwoli grupie anonymous przeprowadziæ skuteczn¹ dezinformacjê przeciwnika. Nale¿y znaleŸæ reptilianina, zmieniæ jego adres EMAIL,
oraz KOD POCZTOWY, aby nie mogli siê ze sob¹ skontaktowaæ oraz WAGÊ, aby nie mogli przewidzieæ ile paliwa wzi¹æ na statek. Podmiany danych nale¿y dokonaæ u¿ywaj¹c
funkcji regex_replace(), po wczeœniejszym sprawdzeniu czy dany obywatel jest reptilianinem funkcj¹ regex_match.
*/
/*Zadanie 4.
Nale¿y sporz¹dziæ listê obywateli, którzy s¹ reptilianami. W tym celu nale¿y wczytaæ plik do ³añcucha string przy pomocy gotowej funkcji string take_file(string &file_name). Nastêpnie w metodzie
void collect_rept_info() stworzyæ pêtlê, w której korzystaj¹c z funkcji regex_search() oraz klasy match_result nale¿y wyszukiwaæ wyst¹pienie DNA reptilianina oraz przy pomocy iteratora
regex_token_iterator<string::const_iterator> dodawaæ do pola string list nowoutworzonej klasy Exodus_data kolejne rekordy zawieraj¹ce ju¿ tylko email i kod pocztowy znalezionego
reptilianina (zachowuj¹c format pliku .csv- ";"). Przyda siê to do poinformowania reptilian o zbli¿aj¹cej siê ucieczce z Ziemi. Dodatkowo po znalezieniu reptilianina nale¿y dodaæ jego wagê do pola
int weight tej samej klasy, aby reptilianie mogli wiedzieæ ile potrzeba paliwa do ewakuacji ich rasy z Ziemi.
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

		while (getline(file, tmp, ';')) {			//pobieraj string do delimitera, a¿ nie bêdzie to mo¿liwe
			if (regex_match(tmp, reg_log)) {		//czy pobrany login to ten z bazy, nie liczy siê wielkoœæ liter
				getline(file, tmp);					//jeœli tak, to pobierz resztê linii
				if (regex_match(tmp, reg_psw))		//czy wpisane has³o pasuje do pobranego z bazy
					return true;
				else
					return false;
			}
			getline(file, tmp);						//pobierz resztê linii (drug¹, niepotrzebn¹ czêœæ po delimiterze)
		}
		return false;								//jeœli przesz³a ca³a pêtla i metoda nie zwróci³a true, zwróæ false
	}

public:
	void log_in() {
		string tmp_log;
		string pasw;
		while (true) {								//pêtla koñczy siê dopiero, gdy uda siê zalogowaæ
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
		regex reg_line("([cg]{2,4}[t]{0,1}a)[-]cgt[-]\\1.*;([0-9]{2}-[0-9]{3}).*;([[:alnum:]]+@[[:alnum:]]+.[[:alpha:]]+).*;([[:digit:]]{1,3})\$", regex_constants::icase);	//niewa¿na d³ugoœæ
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
				out = "";			//zerowanie ³añcucha
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