#include <iostream>  //library input dan output (cin dan cout)
#include <stdlib.h>  //library Linked List
#include <stdio.h>   //library input dan output (printf, scanf)
#include <conio.h>   //library getch()
#include <windows.h> //library warna program

using namespace std;

void setcolor(unsigned short color){
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon,color);
}

#define max 100
string judul_buku[max];
int stok_buku[max];
int temp[max];
int pos = 0;
int x;
int pos_link = 1;

enum{DISPLAY = 1, TAMBAH, PINJAM, KEMBALIKAN, HAPUS, EDIT_JUDUL, EDIT_STOK, SELESAI};

struct node{
	int info;
	struct node *link;
};

void display(struct node *start); //fungsi untuk menampilkan list buku
struct node *addatbeg(struct node *start, int kode_buku); //method untuk menambah kode buku diawal (linked list)
void addatend(struct node *start, int kode_buku); //fungsi untuk menambah kode buku (linked list)
void addtitle(); //fungsi untuk menambah judul buku dan kode buku (array)
void pinjam_buku(struct node *start); //fungsi untuk meminjam buku (array)
void kembalikan_buku(struct node *start); //fungsi untuk mengembalikan buku (array)
void count(struct node *start); //fungsi untuk menghitung jumlah buku didalam list (linked list)
void count_stok(); //fungsi untuk menghitung jumlah stok buku (array)
int pospos(struct node *start, int kode_buku); //method untuk mencari posisi linked list
void deltitle(int pos_link); //fungsi untuk menghapus judul dan stok buku (array)
struct node *delete_node(struct node *start, int kode_buku); //method untuk menghapus kode buku(linked list)
void change_book(); //fungsi untuk mengubah judul buku (array)
void change_stok(); //fungsi untuk mengubah stok buku (array)

int main(){
	system("color 0F");
	struct node *start = NULL;
	
while(1){
	int menu;
	int kode_buku;

	system("cls");
	
	setcolor(15);
	cout << " =================================" << endl;
	cout << " |";
	setcolor(10);
	cout << " SISTEM INFORMASI PERPUSTAKAAN ";
	setcolor(15);
	cout << "|" << endl;
	cout << " =================================" << endl;
	cout << " |\t    MAIN MENU\t         |" << endl;
	cout << " =================================" << endl;
	cout << " | 1. Tampilkan List Buku        |" << endl;
	cout << " | 2. Tambah Buku Kedalam List   |" << endl;
	cout << " | 3. Pinjam Buku \t         |" << endl;
	cout << " | 4. Kembalikan Buku \t         |" << endl;
	cout << " | 5. Hapus Buku Didalam List    |" << endl;
	cout << " | 6. Ubah Judul Buku            |" << endl;
	cout << " | 7. Ubah Stok Buku             |" << endl;
	cout << " | 8. SELESAI \t\t\t |" << endl;
	cout << " =================================" << endl;
	cout << "   Input Pilihan Menu : "; cin >> menu; 
	
	switch(menu){
		case DISPLAY : {
			display(start);
			cout << "\nKlik ENTER untuk kembali ke MAIN MENU!" << endl;
			getch();
			break;
		}
		case TAMBAH : {
			system("cls");
			display(start);
			cout << "|           TAMBAH BUKU KEDALAM LIST \t\t|" << endl;
			cout << "=================================================" << endl;
			cout << "| ";
			setcolor(4);
			cout << "* NOTE : - Kode Buku Berupa Integer";
			setcolor(15);
			cout << "\t\t| " << endl;
			setcolor(4);
			cout << "\t   - Judul Buku (5 - 12 Karakter)";
			setcolor(15);
			cout << "\t|" << endl;
			cout << "=================================================" << endl;
			cout << "Masukkan Kode Buku  : ";
			cin >> kode_buku;			
			if(start == NULL){
				start = addatbeg(start, kode_buku);
			}else{
				addatend(start, kode_buku);
			}
			addtitle();
			system("cls");
			display(start);
			cout << "\nBuku Berhasil Ditambahkan Kedalam List" << endl;
			cout << "\nKlik ENTER untuk kembali ke MAIN MENU!" << endl;
			getch();
			break;
			}
		case PINJAM : {
			display(start);
			if(pos>0){
			pinjam_buku(start);
			}else{
				cout << "\nSilahkan Tambah Buku Terlebihdahulu!" << endl;
				getch();
			}
			break;
		}
		case KEMBALIKAN : {
			display(start);
			if(pos>0){
				kembalikan_buku(start);
			}else{
				cout << "\nSilahkan Tambah Buku Terlebihdahulu!" << endl;
				getch();
			}
			break;
		}
		case HAPUS : {
			display(start);
			if(pos>0){
			cout << "Masukkan KODE BUKU Yang Ingin Dihapus : ";cin >> kode_buku;
		
			pospos(start, kode_buku);
			deltitle(pos_link);
			start = delete_node(start, kode_buku);
			display(start);
			
			cout << "\nBuku Berhasil Dihapus Dari List" << endl;
			cout << "\nKlik ENTER untuk kembali ke MAIN MENU!" << endl;
			pos_link = 1;
			getch();
			}else{
			cout << "\nSilahkan Tambah Buku Terlebihdahulu!" << endl;
			getch();
			}
			break;
		}
		case EDIT_JUDUL : {
			display(start);
			if(pos>0){
			change_book();
			display(start);
			cout << "\nJudul Buku Berhasil Diubah" << endl;
			cout << "\nKlik ENTER untuk kembali ke MAIN MENU!" << endl;
			}else{
				cout << "\nSilahkan Tambah Buku Terlebihdahulu!" << endl;
			}
			getch();
			break;
		}
		case EDIT_STOK : {
			display(start);
			if(pos>0){
			change_stok();
			display(start);
			cout << "\nStok Buku Berhasil Diubah" << endl;
			cout << "\nKlik ENTER untuk kembali ke MAIN MENU!" << endl;
			}else{
				cout << "\nSilahkan Tambah Buku Terlebihdahulu!" << endl;
			}
			getch();
			break;
		}
		case SELESAI : {
			exit(0);
			break;
		}
		default : {
			cout << "\nInvalid Choice!" << endl;
			getch();
			break;
		}
	}
		}
}



void display(struct node *start){
	int nomor_buku = 1;
	
	system("cls");
		setcolor(15);
	cout << "=========================================================" << endl;
	cout << "|";
		setcolor(10);
	cout << "        LIST BUKU SISTEM INFORMASI PERPUSTAKAAN     ";
		setcolor(15);
	cout << "   |" << endl;
	cout << "=========================================================" << endl;
	cout << "| Nomor Buku | Kode Buku | Judul Buku\t    | Stok Buku |" << endl;
	cout << "---------------------------------------------------------" << endl;
	
	struct node *p;
	if(start == NULL){
		cout << "| \t\tList buku kosong \t\t\t|" << endl;
		cout << "=========================================================" << endl;
	}
	p = start;
	int a = 0;
	
	while(p != NULL && a < pos){
		cout  << "| " << nomor_buku << ".\t     | "  << p -> info << "\t | " << judul_buku[a] << "\t    | " <<  stok_buku[a] << " " << "\t|" << endl;
		cout << "---------------------------------------------------------" << endl;
		p = p -> link;
		a++;
		nomor_buku++;
	}
	cout << "| ";
	count(start);
	cout << "\t | ";
	count_stok();
	cout << "\t\t|" << endl;
	cout << "---------------------------------------------------------" << endl;
}

struct node *addatbeg(struct node *start, int kode_buku){
	struct node *temp;
	temp = (struct node *)malloc(sizeof(struct node)); //malloc digunakan untuk mengalokasi memory sebuah node
	temp -> info = kode_buku;
	temp -> link = start;
	start = temp;
	return start;
}

void addatend(struct node *start, int kode_buku){
	struct node *temp, *p;
	temp = (struct node *)malloc(sizeof(struct node));
	temp -> info = kode_buku;
	p = start;
	while(p -> link != NULL){
		p = p -> link;
	}
	p ->link = temp;
	temp -> link = NULL;

	
}

void addtitle(){
	if(pos < max){
		cin.ignore();
		cout << "Masukkan Judul Buku : ";getline(cin, judul_buku[pos]);
		cout << "Masukkan Stok Buku  : ";cin >> stok_buku[pos];
		temp[pos] = stok_buku[pos];
		pos++;
		
}else {
	cout << "\nKapasitas Memori Penuh" << endl;
}
}

void pinjam_buku(struct node *start){
	if(pos > 0){
		cout << "| ";
		setcolor(4);
		cout << "*NOTE : -Ketik '0' Untuk Kembali Ke MAIN MENU";
		setcolor(15);
		cout << " | " << endl;
		cout << "=================================================" << endl;
		cout << "Masukkan NOMOR BUKU Yang Ingin Anda Pinjam : ";cin >> x;
			for(int i = 0;i < pos;i++){
				if(x == i+1){
					if(stok_buku[i] > 0){
						stok_buku[i] = stok_buku[i] - 1;
						display(start);
						cout << "\nBerhasil Meminjam Buku " << judul_buku[i] << "!" << endl;
						cout << "\nKlik ENTER untuk kembali ke MAIN MENU!" << endl;
						getch();}
					else if(x != i+1){
					cout << "\nInvalid Choice!" << endl;
					cout << endl;
					pinjam_buku(start);}
					else{
					cout << "\nStok Buku " << judul_buku[i] << " Sudah Habis!" << endl;
					getch();
					cout << endl;
					pinjam_buku(start);}
				}else if(x == 0){
				return;}
			}
	}else{
	cout << "\nSilahkan Tambah Buku Terlebihdahulu!" << endl;
	getch();}
}

void kembalikan_buku(struct node *start){
	if(pos > 0){
		cout << "| ";
		setcolor(4);
		cout << "*NOTE : -Ketik '0' Untuk Kembali Ke MAIN MENU";
		setcolor(15);
		cout << " | " << endl;
		cout << "=================================================" << endl;
		cout << "Masukkan NOMOR BUKU Yang Ingin Anda Kembalikan : ";cin >> x;
			for(int i = 0;i < pos;i++){
				if(x == i+1){
					if(stok_buku[i] < temp[i]){
						stok_buku[i] = stok_buku[i] + 1;
						display(start);
						cout << "\nBerhasil Mengembalikan Buku " << judul_buku[i] << "!" << endl;
						cout << "\nKlik ENTER untuk kembali ke MAIN MENU!" << endl;
						getch();}
					else if(x != i+1){
						cout << "\nInvalid Choice!" << endl;
						cout << endl;
						kembalikan_buku(start);}
					else{
						cout << "\nStok Buku " << judul_buku[i] << " Sudah Full!" << endl;
						getch();
						cout << endl;
						kembalikan_buku(start);}
				}else if(x == 0 ){
					return;}
			}
	}else{
		cout << "\nSilahkan Tambah Buku Terlebihdahulu!" << endl;
		getch();}
}

void count(struct node *start){
	struct node *p;
	
	int count = 0;
	p = start;
	while(p != NULL){
		p = p -> link;
		count++;
	}
	cout << "TOTAL BUKU : " << count;	
}

void count_stok(){
	int jumlah;
	for(int i = 0;i < pos;i++){
		jumlah = jumlah + stok_buku[i];
	}
	cout << "TOTAL STOK : " << jumlah;
}

int pospos(struct node *start, int kode_buku){
	struct node *p;
	p = start;
	while(p != NULL){
		if(p -> info == kode_buku){	
			return pos_link;}
		p = p -> link;
		pos_link++;}
}

void deltitle(int pos_link){
		for(int i = pos_link;i <pos;i++){
			judul_buku[i-1] = judul_buku[i];
			stok_buku[i-1] = stok_buku[i];
			temp[i-1] = temp[i];}
		pos--;
}

struct node *delete_node(struct node *start, int kode_buku){
	struct node *temp, *p;
	
	if(start == NULL){
		cout << "List is Empty" << endl;
		return start;}
	if(start -> info == kode_buku){
		temp = start;
		start = start -> link;
		free(temp);
		return start;}
	p = start;
	while(p -> link != NULL){
		if(p -> link -> info == kode_buku){
			temp = p -> link;
			p -> link = temp -> link;
			free(temp);
			return start;}
		p = p -> link;}
	return start;
}

void change_book(){
	int ubah;	
	cout << "Masukkan NOMOR BUKU Yang Ingin Diubah : ";cin >> ubah;
	cin.ignore();
	cout << "Ubah Judul Buku Menjadi               : ";getline(cin,judul_buku[ubah-1]);
}

void change_stok(){
	int ubah;	
	cout << "Masukkan NOMOR BUKU Yang Ingin Diubah : ";cin >> ubah;
	cin.ignore();
	cout << "Ubah Stok Buku Menjadi                : ";cin >> stok_buku[ubah-1];
	temp[ubah-1] = stok_buku[ubah-1];
}
