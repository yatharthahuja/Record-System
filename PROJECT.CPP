#include<fstream.h>
#include<conio.h>
#include<process.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<dos.h>

ifstream fin;
ofstream fout;

//CLASS:
class contact{
	private:

		char name[30];

		long int phone_number;

	public:

		contact(){
			strcpy(name,NULL);
			phone_number=NULL;
		}

		void showdata();       //member function to display data

		void getdata();        //member function to accept data

		char *givename();      //member function to return name

		long int givenumber();      //member function to return phone number

};

void contact::showdata(){
	cout<<"\nContact Name: ";puts(name);
	cout<<"Contact phone number: "<<phone_number<<endl;
}

void contact::getdata(){
	cout<<"\nEnter name of the contact..."<<endl;
	gets(name);
	cout<<"Enter phone number of the contact..."<<endl;
	cin>>phone_number;
}

char *contact::givename(){
	return name;
}

long int contact::givenumber(){
	return phone_number;
}


//FUNCTION DECLARATIONS:
void menu();               //function to setup menu interface

void welcome();   	   //function for opening window UI

void create_contact();     //function to create and add a new contact

void display_contacts();   //function to display current contacts'list

void search_contact();     //function to search for a particular contact

void modify_contact();     //function to modify a particular contact

void delete_contact();     //function to delete a particular contact

void contact_diary_renew();//funtion to renew "contact_diary.txt"

void temp_renew();         //funtion to renew "temp.txt"

void screen_outline();	   //function to enhance UI

void press_any_button();   //function to display proceed button

//FUNCTION DEFINITIONS:
void main(){
	clrscr();
	screen_outline();
	welcome();
	menu();
}

void welcome(){
	int i;
	clrscr();
	screen_outline();
	gotoxy(21,8);
	cout<<"              WELCOME!";
	gotoxy(19,12);
	cout<<"COMPUTER SCIENCE PROJECT: CONTACTS' DIARY";
	cout<<endl;
	gotoxy(21,15);
	cout<<"	     	  MADE BY:";
	gotoxy(21,17);
	cout<<"	       YATHARTH AHUJA";
	gotoxy(21,18);
	cout<<"	 DELHI PUBLIC SCHOOL, DWARKA";
	press_any_button();
	getch();
}

void menu(){
	char a='y';
	do{
		clrscr();
		screen_outline();
		int i;
		cout<<"\n\t\t\tWELCOME TO CONTACT DIARY!"<<endl;
		cout<<"\t\t\t-------------------------"<<endl<<endl;
		cout<<"\t\t\tENTER YOUR CHOICE..."<<endl;
		cout<<"\t\t\t1)Create a new contact"<<endl;
		cout<<"\t\t\t2)Display the contact list."<<endl;
		cout<<"\t\t\t3)Search for a contact."<<endl;
		cout<<"\t\t\t4)Modify existing contact."<<endl;
		cout<<"\t\t\t5)Delete existing contact."<<endl;
		cout<<"\t\t\t6)Renew the list."<<endl;
		cout<<"\t\t\t7)Exit."<<endl;
		cout<<"\n\n\tYour input: ";cin>>i;
		clrscr();
		switch(i){

			case 1: screen_outline();
				create_contact();
				break;

			case 2: screen_outline();
				display_contacts();
				break;

			case 3: screen_outline();
				search_contact();
				break;

			case 4: screen_outline();
				modify_contact();
				break;

			case 5: screen_outline();
				delete_contact();
				break;

			case 6: screen_outline();
				contact_diary_renew();
				temp_renew();
				cout<<"File Renewed!"<<endl;
				break;

			case 7: clrscr();
				screen_outline();
				gotoxy(30,11);
				cout<<"Thank you!!"<<endl;
				press_any_button();
				getch();
				exit(0);
				break;

			default:cout<<"Wrong choice!"<<endl;
		};
		cout<<"Do you wish to continue?(y/n)"<<endl;
		cout<<"\nYour input: ";
		cin>>a;
	}while(a=='y' || a=='Y');

	clrscr();
	screen_outline();
	gotoxy(30,11);
	cout<<"Thank you!"<<endl;
	press_any_button();
	getch();
}

void create_contact(){

	contact p,q;    	   //objects
	cout<<"Enter data for new contact..."<<endl;
	p.getdata();
	fin.open("contact_diary.txt",ios::binary|ios::in);
	fin.seekg(0);


	if(!fin.read((char*)&q,sizeof(q))){
		contact_diary_renew();
		fout.open("contact_diary.txt",ios::binary|ios::out);
		fout.write((char*)&p,sizeof(p));
		fout.close();
		fin.close();
	}


	else{

		temp_renew();
		int i;
		fout.open("temp.txt",ios::binary|ios::out);
		fin.seekg(0);

		while(!fin.eof()){
			i=0;
			if( strcmpi(q.givename(),p.givename())<0 ){
				fout.write((char*)&q,sizeof(q));
				fin.read((char*)&q,sizeof(q));
				continue;
			}

			else if( strcmpi(q.givename(),p.givename())>=0 ){
				fout.write((char*)&p,sizeof(p));
				i+=1;
				break;
			}

		}

		if(i==0){
			fout.write((char*)&p,sizeof(p));
		}

		else{
			while(fin.read((char*)&q,sizeof(q))){
				fout.write((char*)&q,sizeof(q));
			}
		}

		fout.close();
		fin.close();

		remove("contact_diary.txt");
		rename("temp.txt","contact_diary.txt");

	}

	cout<<"\nNew contact created successfully!"<<endl;

}

void display_contacts(){
	contact p;	//object
	int count=0;

	fin.open("contact_diary.txt",ios::binary|ios::in);
	fin.seekg(0);

	cout<<"\nContact List:"<<endl;

	while(fin.read((char*)&p,sizeof(p))){
		p.showdata();
		count+=1;
	}

	if(count==0){
		cout<<"List empty!"<<endl;
	}

	else{
		cout<<"\nTotal number of contacts: "<<count<<endl;
	}

	fin.close();
}

void search_contact(){
	contact p;	//object
	int a,count=0;
	cout<<"Enter the method of search..."<<endl;
	cout<<"1)By name\n2)By phone number"<<endl;
	cout<<"\nYour input: ";
	cin>>a;

	switch(a){

		case 1: char c[20];
			cout<<"Enter the name..."<<endl;
			gets(c);

			fin.open("contact_diary.txt",ios::binary|ios::in);

			while(fin.read((char*)&p,sizeof(p))){

				if(strcmpi(p.givename(),c)==0){
					p.showdata();
					count+=1;
				}
				fin.read((char*)&p,sizeof(p));

			}

			fin.close();

			if(count==0){
				cout<<"No matches found!"<<endl;
			}

			else if(count!=0){
				cout<<"\nTotal "<<count<<" matches found!"<<endl;
			}

			break;

		case 2: long int d;
			cout<<"Enter the number..."<<endl;
			cin>>d;
			fin.open("contact_diary.txt",ios::binary|ios::in);

			while(fin.read((char*)&p,sizeof(p))){

				if( p.givenumber()==d ) {
					p.showdata();
					count+=1;
				}


			}

			fin.close();

			if(count==0){
				cout<<"No matches found!"<<endl;
			}

			else if(count!=0){
				cout<<"\nTotal "<<count<<" matches found!"<<endl;
			}

			break;

		default: cout<<"Wrong choice!"<<endl;
	}

}

void modify_contact(){
	contact p,q;	//objects
	int a,count=0;
	cout<<"Enter the method of data selection..."<<endl;
	cout<<"1)By name\n2)By phone number"<<endl;
	cout<<"\nYour input: ";
	cin>>a;

	switch(a){

		case 1: char c[20];
			cout<<"Enter the name..."<<endl;
			gets(c);
			cout<<"Enter new data"<<endl;
			p.getdata();

			fin.open("contact_diary.txt",ios::binary|ios::in);
			fin.seekg(0);
			temp_renew();
			fout.open("temp.txt",ios::binary|ios::app);

			while(fin.read((char*)&q,sizeof(q))){

				if(strcmp(q.givename(),c)==0){

					fout.write((char*)&p,sizeof(p));
					count+=1;
				}

				else{
					fout.write((char*)&q,sizeof(q));
				}

			}
			fout.close();
			fin.close();

			remove("contact_diary.txt");
			rename("temp.txt","contact_diary.txt");

				if(count==0){
				cout<<"No matches found!"<<endl;
			}

			if(count!=0){
				cout<<"Data modified!"<<endl;
				cout<<"\nTotal "<<count<<" contacts modified!"<<endl;
			}

			break;

		case 2: long int d;
			cout<<"Enter the number..."<<endl;
			cin>>d;
			cout<<"Enter new data"<<endl;
			p.getdata();

			fin.open("contact_diary.txt",ios::binary|ios::in);
			fin.seekg(0);
			temp_renew();
			fout.open("temp.txt",ios::binary|ios::app);

			while(fin.read((char*)&q,sizeof(q))){

				if(q.givenumber()==d){
					fout.write((char*)&p,sizeof(p));
					count+=1;
				}

				else{
					fout.write((char*)&q,sizeof(q));
				}

			}
			fout.close();
			fin.close();

			remove("contact_diary.txt");
			rename("temp.txt","contact_diary.txt");

			if(count==0){
				cout<<"No matches found!"<<endl;
			}

			if(count!=0){
				cout<<"Data modified!"<<endl;
				cout<<"\nTotal "<<count<<" contacts modified!"<<endl;
			}

			break;

	}

}

void delete_contact(){
	contact q;	//object
	int a,count=0;

	cout<<"Enter the method of search..."<<endl;
	cout<<"1)By name\n2)By phone number"<<endl;
	cout<<"\nYour input: ";
	cin>>a;

	switch(a){

		case 1: char c[20];
			cout<<"Enter the name..."<<endl;
			gets(c);

			fin.open("contact_diary.txt",ios::binary|ios::in);
			temp_renew();
			fout.open("temp.txt",ios::binary|ios::app);


			while(fin.read((char*)&q,sizeof(q))){

				if(strcmpi(q.givename(),c)==0){
					count+=1;
				}

				else{
					fout.write((char*)&q,sizeof(q));
				}

			}
			fout.close();
			fin.close();

			remove("contact_diary.txt");
			rename("temp.txt","contact_diary.txt");

			if(count==0){
				cout<<"No matches found!"<<endl;
			}

			if(count!=0){
				cout<<"Data deleted!"<<endl;
				cout<<"\nTotal "<<count<<" contacts deleted!"<<endl;
			}

			break;

		case 2: long int d;
			cout<<"Enter the number..."<<endl;
			cin>>d;

			fin.open("contact_diary.txt",ios::binary|ios::in);
			temp_renew();
			fout.open("temp.txt",ios::binary|ios::app);

			while(fin.read((char*)&q,sizeof(q))){

				if(q.givenumber()==d){
					count+=1;
				}

				else{
					fout.write((char*)&q,sizeof(q));
				}

			}

			fout.close();
			fin.close();

			remove("contact_diary.txt");
			rename("temp.txt","contact_diary.txt");

			if(count==0){
				cout<<"No matches found!"<<endl;
			}

			if(count!=0){
				cout<<"Data deleted!"<<endl;
				cout<<"\nTotal "<<count<<" contacts deleted!"<<endl;
			}

			break;

	}

}

void contact_diary_renew(){
	remove("contact_diary.txt");
	fout.open("contact_diary.txt",ios::binary|ios::out);
	fout.close();
}

void temp_renew(){
	remove("temp.txt");
	fout.open("temp.txt",ios::binary|ios::out);
	fout.close();
}

void screen_outline(){
	clrscr();
	int i;
	gotoxy(1,1);
	for(i=0;i<78;i++){
		cout<<"_";
	}
	cout<<endl;

	gotoxy(1,23);
	for(i=0;i<78;i++){
		cout<<"_";
	}
	cout<<endl;

	gotoxy(1,2);
}

void press_any_button(){
	gotoxy(50,22);
	cout<<"Press any key to continue";
}





