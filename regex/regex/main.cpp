#include <regex>
#include <iostream>
#include <Windows.h>
#include <string>
#include <iterator>

using namespace std;

bool regex_callback(const match_results < std::string::const_iterator >& x) {
	cout << x[0].str() << endl;
	return true;
}

string &operator<<(string &out, regex_token_iterator<string::const_iterator> &b) {
	out = *b;
	return out;
}

int main() {
	string jeden("na straganie w dzien targowy, takie tocza sie rozmowy na rozne tematy od banana\ndruga linia\n");
	regex stragan_reg(".*stragan.*");
	regex na_reg("$");
	regex a_reg("$");

	smatch m;
	match_results<string::iterator> mi;

	cout << regex_match(jeden, stragan_reg) << endl;
	cout << regex_search(jeden, m, na_reg, (regex_constants::match_not_bow, regex_constants::match_not_bol)) << endl;
	cout << regex_search(jeden.begin(), jeden.end(), mi, a_reg, (regex_constants::match_not_bol, regex_constants::match_not_bow)) << endl;

	string t;
	back_insert_iterator<string> it(t);

	//wyniki wyszukiwania z "na"
	cout << "m.size(): " << m.size() << endl;
	cout << "*m[0].first: " << *m[0].first << endl;
	cout << "*m[0].second: " << *m[0].second << endl;
	cout << "m[0].matched: " << m[0].matched << endl;
	cout << "m.position(): " << m.position() << endl;
	cout << "m.str(): " << m.str() << endl;

	//wyniki wyszukiwania z "a"
	cout << endl << "mi.size(): " << mi.size() << endl;
	cout << "*mi[0].first: " << *mi[0].first << endl;
	cout << "mi[0].matched: " << mi[0].matched << endl;
	cout << "mi.position(): " << mi.position() << endl;
	cout << "mi.str(): " << mi.str() << endl;

	//podmiana i ponowny test
	regex_replace(it, jeden.begin(), jeden.end(), a_reg, string("o"));
	cout << regex_search(t.begin(), t.end(), mi, a_reg, (regex_constants::match_not_bol, regex_constants::match_not_bow)) << endl;

	//po podmianie "a na "o"
	cout << endl << t << endl;
	cout << "mi.size(): " << mi.size() << endl;
	if (mi[0].matched) {
		cout << "*mi[0].first: " << *mi[0].first << endl;
		cout << "mi[0].matched: " << mi[0].matched << endl;
		cout << "mi.position(): " << mi.position() << endl;
		cout << "mi.str(): " << mi.str() << endl;
	}
	else
		cout << "Nie znaleziono \"a\"" << endl;

	sregex_iterator r_it(jeden.begin(), jeden.end(), na_reg);
	sregex_iterator r_it_bol_bow(jeden.begin(), jeden.end(), na_reg, (regex_constants::match_not_bol, regex_constants::match_not_bow, regex_constants::match_not_eol, regex_constants::match_not_eow));
	sregex_iterator end;

	cout << endl;
	for_each(r_it, end, &regex_callback);

	cout << endl << "bol bow: " << endl;
	for_each(r_it_bol_bow, end, &regex_callback);

	string dwa("Karol  Okrasa 51\nPascal    Brodnicki 32\nMarian   Pazdzioch 33");
	cout << dwa << endl;
	regex kilka_reg("([[:alpha:]]+)[[:blank:]]+([[:alpha:]]+[[:blank:]]+)([[:digit:]]{2})");	//mo¿na te¿ szukaæ na przyk³ad daty urodzenia, albo wagi
	int ktore[2] = { 1,3 };
	cout << endl;
	regex_token_iterator<string::const_iterator> token_it(dwa.begin(), dwa.end(), kilka_reg, ktore), tok_end, tmp;
	tmp = token_it;
	for (; token_it != tok_end; token_it++) {
		cout << *token_it << endl;
	}

	string **tablica = new string*[3];		//dwuwymiarowa na przysz³oœæ
	int i = 0;
	for (; tmp != tok_end; tmp++) {
		tablica[i] = new string[1];
		*tablica[i] = *tmp;
		i++;
	}

	for (int j = 0; j < i; j++) {
		cout << *tablica[j];
	}

	system("pause");
	return 0;
	//sprawdziæ jeszcze flagi- czy bêd¹ dzia³aæ jak dodam ten namespace z prezentacji na pocz¹tku pliku
	//mo¿na dodaæ sprawdzanie poprawnoœci wpisanych danych podczas rejestracji w serwisie www (login, has³o, ...)
}