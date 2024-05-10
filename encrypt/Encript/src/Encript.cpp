#include <iostream>
#include <sstream>
using namespace std;


void toUpperCase(string &str){
	for(int i = 0; i < str.length(); i++){
		str.at(i) = toupper(str.at(i));
	}
}

class Vigenere {
private:
string _keyword;
char _table[26][26];
struct Letter{
	char letter; // MUST BE UPPERCASE
	int index;
	string Print(){
		stringstream s;
		s << letter << ": " << index;
		return s.str();
	}
};

Letter _letterIndex[26]; // this holds what combnation of plantext and keyword will result in what output in the Vigenere Table

int GetIndex(Letter l[26], char toCheck){
	toCheck= toupper(toCheck);
	for(int i = 0; i < 26; i++){
		if(l[i].letter == toCheck){
			return l[i].index;
		}
	}
	return -1;
}


public:
	 Vigenere() { // This will be a Vigenere Cypher without a traspotation of the table
		 string Alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		 _keyword = "KEYWORD";
		 for(int i = 0; i < 26; i++){// setting up the Row and Column struct
			 Letter key, cypher;
			 key.index = i;
			 key.letter = Alphabet[i];
			 _letterIndex[i] = key;
		 }
		 /*
		 cout << "Key" << endl;
		 for(int i = 0; i < 26; i++){
			 cout << _letterIndex[i].Print() << endl;
		 }
		*/
		 for(int i = 0; i < 26; i++){
			 for(int j = 0; j < 26; j++){
				 _table[i][j] = Alphabet[(i+j) % 26];
			 }
		 }
	 }
	 Vigenere(string keyword) : Vigenere(){
		 toUpperCase(keyword);
		 _keyword = keyword;

	 }
	 Vigenere(string keyword, string Morph) { // the Morph will Add Morph to the start of the Table Then the Rest of the Alphabet
		 string Alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		 toUpperCase(Morph);
		 for(int i = 0; i < Morph.length(); i++){
			 char check = Morph.at(i);
			 int letterIndex;
			 for(int j = 0; j < 26; j++){
				 if(Alphabet[j] == check){
					 letterIndex = j;
					 break;
				 }
			 }
			 for(int j = letterIndex; j > i; j--){
				 Alphabet[j] = Alphabet[j - 1];

			 }
			 Alphabet[i] = check;
		 }
		 toUpperCase(keyword);
		 _keyword = keyword;
		 for(int i = 0; i < 26; i++){// setting up the Row and Column struct
			 Letter key, cypher;
			 key.index = i;
			 key.letter = Alphabet[i];
			 _letterIndex[i] = key;
		 }
		 for(int i = 0; i < 26; i++){
			 for(int j = 0; j < 26; j++){
				 _table[i][j] = Alphabet[(i+j) % 26];
			 }
		 }
	 }
	 string Decode(string cypherText){
		 string deCypher = "";
		 int key, cypher;
		 for(int i = 0; i < cypherText.length(); i++){
			 cypher = GetIndex(_letterIndex, cypherText.at(i));
			 key = GetIndex(_letterIndex, _keyword.at(i % _keyword.length()));
			 //cout << _letterIndex[key].letter << " " << _letterIndex[cypher].letter << " "<< _table[(cypher - key + 26) % 26][0]<< endl;
			 deCypher += _table[(cypher - key + 26) % 26][0]; // To decode the cypher subtract the Cyphertext
		 }
		 return deCypher;
	 }
	 string Encode(string plainText){
		 string cypherText = "";
		 int key, cypherIndex;
		 toUpperCase(plainText);
		 while(plainText.find(' ') != std::string::npos){ // Removes all spaces from string
			 // cout << plainText<< ": " << plainText.find(' ') << endl;
			 plainText.erase(plainText.find(' '),1);
		 }
		 for(int i = 0; i < plainText.length(); i++){
			 cypherIndex = GetIndex(_letterIndex, plainText.at(i));
			 key = GetIndex(_letterIndex, _keyword.at(i % _keyword.length()));
			 cypherText += _table[cypherIndex][key];
			 //cout << "Character: " << plainText.at(i) << ", Index: " << cypherIndex << endl; // Debug output
		 }
		 return cypherText;
	 }
	 string GetTable(){
		 string table = "";
		 for(int i = 0; i < 26; i++){
			 for(int j = 0; j < 26; j++){
				 table += _table[i][j];
			 }
			 table += "\n";
		 }
		 return table;
	 }
};

int main() {
	string decodedText, text, plainText = "The Big Brown Fox Jumped Over the Lazy River";
	Vigenere v = Vigenere("TEXT");
	text = v.Encode(plainText);
	//cout << v.GetTable() << endl;

	cout << plainText << endl;
	cout << text << endl;
	decodedText = v.Decode(text);
	cout << decodedText << endl;

	return 0;
}
