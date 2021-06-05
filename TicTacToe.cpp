#include<iostream>

using namespace std;


char allSigns[4] = { 'x','o','X','O' };
char allTeams[4] = { 'A','B','A','B' };
const int kazananlar[10][4] = {
	{1,2,3,4},
	{5,6,7,8},
	{9,10,11,12},
	{13,14,15,16},
	{1,5,9,13},                          ///////////Bu kısımda oyunu kazandıran hamle kombinasyonları tanımlandı
	{2,6,10,14},
	{3,7,11,15},
	{4,8,12,16},
	{1,6,11,16},
	{4,7,10,13}
};
class Player {
private :
		/////////////////Bu Kısımda Oyuncu sınıfı oluşturuldu ve fonksiyon ve değişken tanımlanmaları yapıldı
	string name;
	char teams;
	char sign;
	int turn;
	int moves[4];
	int k = 0;

public:
	Player() {		//////////// varsayılan constructor oluşturuldu
		name = "isimsiz";
		sign = '|';
		turn = 0;
		teams = '|';
		moves[0] = 0;
		moves[1] = 0;
		moves[2] = 0;
		moves[3] = 0;
	}
	Player(string name, char sign,char teams) { /////////////Constructor overload edildi 
		this->name = name;
		this->sign = sign;
		this->teams = teams;
		
		
	}

	
	void addMove(int move) {
		
		moves[k] = move;
		k++;
	}
	int* getMove() {
		return moves;
	}
	void setinfo(char sign, char teams,int turn) {
		this->sign = sign;
		this->teams = teams;
		this->turn = turn;
	}
	void setname(string name) {
		this->name = name;
	}
	void getinfo() {

		cout << "name is : " << name<<"\n";
		cout << "Sign is : " << sign << "\n";
		cout << "team is : " << teams << "\n";
		cout << "turn is : " << turn << "\n\n\n";

	}
	string getname() {
		return name;
	}
	char getsign() {
		return sign;
	}

	int* operator + (const Player& players) {  	///////
		static int temp[8];			///////	bir takımdaki iki oyuncunun hamlelerini birleştirmek için '+' operatoru overload edildi.
		int k = 0;				///////
		for (int i = 0; i < 4;i++) {
			temp[k] = players.moves[i];
			temp[k + 1] = this->moves[i];
			k+=2;
		}
		return temp;

	}
};

Player PlayerList[4];   

class Cell {  /////////// oyunun oynacagı tahta hücrelere bölündü  

private :
	char value;

public :
	Cell() {
		value = '.';
	}
	Cell(char val) {
		value = val;
	}

	void setCell(char val) {
		value = val;
	}
	char getCell() {
		return value;
	}
};
Cell Table[16];

void start() {  ////////////////// oyunu başlatan fonksiyon
	for (int i = 0; i < 4; i++) {
		Player player;
		player.setinfo(allSigns[i], allTeams[i],i+1);
		PlayerList[i] = player;
	}
	
	cout << "------------- Hosgeldiniz---------------\n";
	cout << "bilgilendirici metin\n";
	for (int i = 0; i < 4; i++) {
		string tempname;
		cout << "isminiz :";
		cin >> tempname;
		PlayerList[i].setname(tempname);
		cout << "--------player "<<i+1<< "---------\n" ;
		PlayerList[i].getinfo();

	}
	cout << "           Team A : " << PlayerList[0].getname() << "  &  " << PlayerList[2].getname()<<"\n\n";
	cout << "           Team B : " << PlayerList[1].getname() << "  &  " << PlayerList[3].getname()<<"\n\n\n\n";
	cout << "-------------------Basarilar Dileriz-------------------           \n\n";
}

void init() {     /////////////hücreler oluşturuldu ve def constructur ile ilk atamalar da yapılmış oldu
					
	for (int i = 0; i < 16; i++) {
		Cell cell;	
		Table[i] = cell;	///nesneler bir listeye atandı.
	}
}

void draw() {   //tahtayı herseferinde çizdiren fonksiyon
	
	cout << "\n                  " << "  " << "A" << "   " << "B" << "   " << "C" << "   " << "D" << "  " << '\n';
	cout << "                 " << "-------------------\n";
	cout <<"                1 "<< "| " << Table[0].getCell() << " | " << Table[1].getCell() << " | " << Table[2].getCell() << " | " << Table[3].getCell() << " |" << '\n';
	cout << "                 "<< "-------------------\n";
	cout << "                2 "<< "| " << Table[4].getCell() << " | " << Table[5].getCell() << " | " << Table[6].getCell() << " | " << Table[7].getCell() << " |" << '\n';
	cout << "                 "<< "-------------------\n";
	cout << "                3 "<< "| " << Table[8].getCell() << " | " << Table[9].getCell() << " | " << Table[10].getCell() << " | " << Table[11].getCell() << " |" << '\n';
	cout << "                 "<< "-------------------\n";
	cout << "                4 " << "| " << Table[12].getCell() << " | " << Table[13].getCell() << " | " << Table[14].getCell() << " | " << Table[15].getCell() << " |" << '\n';
	cout << "                 "<< "-------------------\n";
}

bool chckMove(int move) {  // Hamlenin geçerliliğini kontrol eden fonksiyon
	if (move == 0 )
		return 0;
	if (Table[move - 1].getCell() != '.')
		return 0;
	return 1;
}
bool chckWin(Player player1,Player player2) {  //her hamleden sonra oyunun bitip bitmediğini kontrol eden fonksiyon
	

	int takimlistesi[8];
	int k = 0;
	for (int i = 0; i < 4; i++) {
		takimlistesi[k] =  player1.getMove()[i];
		takimlistesi[k+1] =  player2.getMove()[i];
		k+=2;

	}
	

	for (int i = 0; i < 10; i++) {
		int counter = 0;
		for (int j = 0; j < 4; j++) {
			for(int k =0;k<8;k++){
				if (kazananlar[i][j] == takimlistesi[k])
					counter++;
			}
		}
		if (counter == 4)
			return 1;

	}
	return 0;
}

int convertNotation(string moveString) {
	int tempint = moveString[1] - '0';
	char tempchar = moveString[0] ;
	string tempString;
	
	while (!(tempint < 5 && tempint > 0)) {
		cout << "hamleyi tekrar giriniz \n";
		cin >> tempString;
		tempint = tempString[1] - '0';
		tempchar = tempString[0];
	}
	if (tempchar == 'A' || tempchar == 'a')
		return 1 +((tempint-1)*4);
	else if (tempchar == 'B' || tempchar == 'b')
		return 2 + ((tempint - 1) * 4);
	else if (tempchar == 'C' || tempchar == 'c')
		return 3 + ((tempint - 1) * 4);
	else if (tempchar == 'D' || tempchar == 'd')
		return 4 + ((tempint - 1) * 4);
	return 0;
}


	
	

void play() {  /////oyunun her turunda sürekli çağırılan ana fonksiyon
	cout << "1 den 16 ya kadar kareler vardir hamle yapmak istediginiz h�creyi girmek yeterlidir ex(A3) \n";
	int tempMove;
	string tempMoveString;
	
	draw();
	for (int i = 0; i < 16; i++) {
		
		cout << PlayerList[i % 4].getname() << " lutfen hamlenizi giriniz : ";
		cin >> tempMoveString;
		tempMove = convertNotation(tempMoveString.substr(0, 2));

		while (!chckMove(tempMove)) {
			
			cout << PlayerList[i % 4].getname() << "\nlutfen hamlenizi tekrar giriniz  : ";
			
			cin >> tempMoveString;
			tempMove = convertNotation(tempMoveString.substr(0,2));
		}
		PlayerList[i % 4].addMove(tempMove);

		if (chckWin(PlayerList[i % 4], PlayerList[(i + 2) % 4])) {
			cout << "\n\n\n----------bitti-----------\n";
			cout << "tebrikler : " << PlayerList[i % 4].getname() << "  &  " << PlayerList[(i + 2) % 4].getname();
			cout << "\n----------bitti-----------\n";
			Table[tempMove - 1].setCell(PlayerList[i % 4].getsign());
			draw();
			return ;
			 
		}
		Table[tempMove - 1].setCell(PlayerList[i % 4].getsign());
		
		draw();

	}
	
	cout << "\n\n\n----------berabera-----------\n";
	cout << "            0           ";
	cout << "\n----------berabere-----------\n";



}
void analiz(int liste[]) {

	int kosegen[8] = {1,6,11,16,4,7,10,13 };
	int counter = 0,counter1 =0;
	for (int i = 0; i < 8; i++) {
		if (liste[i] != 0)
			counter++;
		for (int j = 0; j < 8; j++) {
			if (liste[i] == kosegen[j]) {
				counter1++;
			}
		}
	}
	
	cout << "\nsatir - sutun yuzdesi  : %  " << (counter / 16.00) * 100.00<<"\n";
	cout<<"capraz yuzdesi : %  "<< (counter1 / 8.00) * 100.00 << "\n";

}


int main() {
	init();
	start();
	play();
	int teamMoves1[8];
	int teamMoves2[8];
	for (int i = 0; i < 8; i++) {

		teamMoves1[i] = (PlayerList[0] + PlayerList[2])[i];
		teamMoves2[i] = (PlayerList[1] + PlayerList[3])[i];
	}
	analiz(teamMoves1);
	analiz(teamMoves2);

	return 0;
}
