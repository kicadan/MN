#include <regex>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>

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
z pliku citizen_data.csv. Napisz metodê, void trolluj_reptilian(), która pozwoli grupie anonymous przeprowadziæ skuteczn¹ dezinformacjê przeciwnika. Nale¿y znaleŸæ reptilianina, zmieniæ jego adres EMAIL,
oraz KOD POCZTOWY, aby nie mogli siê ze sob¹ skontaktowaæ oraz WAGÊ, aby nie mogli przewidzieæ ile paliwa wzi¹æ na statek. Aby rozpoznaæ reptilianina nale¿y przeprowadziæ analizê DNA. 
Odkryto, ¿e dla pewnej sekwencji zasad w kodzie DNA mo¿na stwierdziæ ¿e obywatel jest reptilianinem. Ta sekwencja to kombinacja grup:
z C i/lub G - od dwóch do czterech, T - zero lub jeden, A raz i CGT, po czym ma wyst¹piæ dok³adnie ta sama pasuj¹ca sekwencja która zosta³a dopasowana 
na pocz¹tku, np.: 
CCA-CGT-CCA tak, ale nie CCA-CGT-CCGA (wszystkie grupy pasuj¹, ale 1 i 3 musz¹ byæ TE SAME). Do przeszukiwania wektora nale¿y u¿yæ funkcji regex_match(), a nastêpnie dokonaæ podmiany danych u¿ywaj¹c
funkcji regex_replace(). Ca³oœæ nale¿y zapisaæ do pliku, nadpisuj¹c go przy u¿yciu gotowej metody void save(string &file_name). Lepiej zachowaj w pogotowiu oryginalny plik.
*/
/*Zadanie 3.
Nale¿y sporz¹dziæ listê obywateli, którzy s¹ reptilianami. W tym celu nale¿y wczytaæ plik do ³añcucha string przy pomocy gotowej funkcji string take_file(string &file_name). Nastêpnie w pêtli,
korzystaj¹c z funkcji regex_search() oraz klasy match_result wyszukiwaæ wyst¹pienie DNA reptilianina oraz przy pomocy iteratora regex_token_iterator<string::const_iterator> dodawaæ do pola
string list nowoutworzonej klasy Exodus_data kolejne rekordy zawieraj¹ce ju¿ tylko email i kod pocztowy znalezionego reptilianina (zachowuj¹c format pliku .csv- ";"). Przyda siê to do
poinformowania reptilian o zbli¿aj¹cej siê ucieczce z Ziemi. Dodatkowo po znalezieniu reptilianina nale¿y dodaæ jego wagê do pola int weight tej samej klasy, 
aby reptilianie mogli wiedzieæ ile potrzeba paliwa do ewakuacji ich rasy z Ziemi.
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