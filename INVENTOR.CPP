		//************************
		//   INVENTORY CONTROL
		//************************

		//	MADE BY : SACHIN GUPTA
		//	CLASS   : XII A
		//	ROLL NO : 23

#include <iostream.h>
#include <fstream.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>

class MENU
{
	public :
			void main_menu() ;
			void con_menu();
			void supp_menu();
			void item_menu();
}m;

class CONSUMER
{
	int c_no,qty;
	char c_name[20],i_code[10];
	struct date d;
    public :

	CONSUMER()
	{
	  c_no=0;
	  qty=0;
	}
	int get_con_code();
	void entry();
	void display();
	void modify();
	void del();
}con;

class SUPPLIER
{
	  char i_code[10],code[10],sup[20],name[20];
	  double cost,total;
	  long qty;
	  struct date d;
    public:

	  void entry();
	  void display();
	  void modify();
	  void del();
}supp;

class ITEM
{
	char code[10],name[20];
	long qty;
   public:
	void display();
	char sup_entry(char [], long ,char []);
	char sup_update(char [], long, long);
	int cus_entry(char [], long);
	char cus_update(char [],long, long);
	void del();
}it;

void SUPPLIER :: entry()
{
  clrscr();
  char ans;
  fstream file("supp.dat",ios::app);
  file.seekg(0);
  cout<<"                  É=============================»\n";
  cout<<"                  ºENTER DETAIL ABOUT SUPPLIER  º\n";
  cout<<"                  È=============================¼";
  gotoxy(26,9);
  cout<<"ENTER SUPPLIER CODE  ->";
  cin>>code;
  gotoxy(26,11);
  cout<<"ENTER SUPPLIER NAME ->";
  gets(sup);
  gotoxy(26,13);
  cout<<"ENTER ITEM CODE ->";
  cin>>i_code;
  gotoxy(26,15);
  cout<<"ENTER ITEM NAME ->";
  gets(name);
  gotoxy(26,17);
  cout<<"ENTER ITEM QUANTITY ->";
  cin>>qty;
  gotoxy(26,19);
  cout<<"ENTER THE COST OF ITEM ->";
  cin>>cost;
  total = cost * qty;
  getdate(&d);
  ans = it.sup_entry(i_code ,qty ,name);
  if(ans =='y' || ans == 'Y')
    file.write((char *)&supp,sizeof(supp));
  file.close();
}

void SUPPLIER :: modify()
{
  int qt,f2=0;
  char cod[10],ans;
  long mqty;
  fstream file("supp.dat",ios::out|ios::in);
  file.seekg(0);
  gotoxy(20,9);
  cout<<"ENTER THE SUPPLIER CODE TO MODIFY ->";
  cin>>cod;
  while(file.read((char *)&supp,sizeof(supp)))
  {
	   if(strcmp(cod,supp.code)==0)
	   {
		f2=1;
		clrscr();
		mqty = supp.qty;
		cout<<"                  É======================================»\n";
		cout<<"                  ºENTER DETAIL ABOUT SUPPLIER TO MODIFY º\n";
		cout<<"                  È======================================¼";
		gotoxy(26,9);
		cout<<"ENTER SUPPLIER CODE  ->";
		cin>>supp.code;
		gotoxy(26,11);
		cout<<"ENTER SUPPLIER NAME ->";
		gets(supp.sup);
		gotoxy(26,13);
		cout<<"ENTER ITEM NAME ->";
		gets(supp.name);
		gotoxy(26,15);
		cout<<"ENTER ITEM QUANTITY ->";
		cin>>supp.qty;
		gotoxy(26,17);
		cout<<"ENTER THE COST OF ITEM ->";
		cin>>supp.cost;
		supp.total = supp.cost * supp.qty;
		ans = it.sup_update(supp.i_code ,mqty ,supp.qty);
		if(ans =='n')
		{
		  file.close();
		  return;
		}
		double size=sizeof(supp);
		file.seekg(-size,ios::cur);
		file.write((char *)&supp,sizeof(supp));
		gotoxy(26,24);
		cout<<"******Record Modified .. Press <enter>******";
		getch();
	   }
	}
       if(f2==0)
	  {
	  clrscr();
	  gotoxy(26,15);
	  cout<<"ENETRED SUPPLIER CODE DOES NOT EXISTS";
	  getch();
	  }
}

char ITEM :: sup_update(char i_code[],long sq,long aq)
{
  int flag = 0;
  char ans='n';
  fstream file("item.dat",ios::in|ios::out);
  if(file == NULL)
  {
    cout<<"UNABLE TO OPEN";
    getch();
  }
  while(file.read((char *)&it,sizeof(it)))
  {
    if(strcmp(it.code,i_code)==0)
    {
      flag = 1;
      ans = 'y';
      qty = qty - sq;
      qty = qty + aq;
      long len = sizeof(it);
      file.seekg(-len,ios::cur);
      file.write((char *)&it, sizeof(it));
    }
  }
  if(flag == 0)
  {
    clrscr();
    gotoxy(13,12);
    cout<<"SORRY! ENTERED ITEM NOT AVAILBLE IN STOCK";
    getch();
  }
  file.close();
  return ans;
}

char ITEM :: sup_entry(char i_code[],long q,char n[])
{
  int flag = 0;
  char ans='n';
  fstream file("item.dat",ios::in|ios::out);
  if(file == NULL)
  {
    cout<<"UNABLE TO OPEN";
    getch();
  }
  while(file.read((char *)&it,sizeof(it)))
  {
    if(strcmp(it.code,i_code)==0)
    {
      flag = 1;
      qty = qty + q;
      long len = sizeof(it);
      file.seekg(-len,ios::cur);
      file.write((char *)&it, sizeof(it));
      ans ='y';
      return ans;
    }
   }
  if(flag == 0)
  {
    clrscr();
    gotoxy(13,12);
    cout<<"SORRY! ENTERED ITEM NOT AVAILBLE IN STOCK";
    gotoxy(13,13);
    cout<<"DO YOU WANT TO ADD ITEM IN STOCK <Y/N> ";
    fflush(stdin);
    ans = getchar();
  }
  if(ans == 'y' || ans =='Y')
  {
    file.close();
    file.open("item.dat",ios::app);
    qty = q;
    strcpy(code,i_code);
    strcpy(name,n);
    file.write((char *)&it,sizeof(it));
  }
  else
  {
    gotoxy(13,14);
    cout<<"SUPPLIER INFORMATION WILL NOT BE ENTERED";
    getch();
  }
  file.close();
  return ans;
}

void SUPPLIER :: display()
{
  int day,mon,year;
  gotoxy(2,3);
  cout<<"DATE";
  gotoxy(15,3);
  cout<<"ITEM CODE";
  gotoxy(26,3);
  cout<<"SUP CODE";
  gotoxy(36,3);
  cout<<"SUP NAME";
  gotoxy(50,3);
  cout<<"ITEM QTY";
  gotoxy(60,3);
  cout<<"ITEM COST";
  gotoxy(70,3);
  cout<<"TOTAL COST";
  gotoxy(2,4);
  cout<<"-------------------------------------------------------------------------------";
  int y=5;
  ifstream file;
  file.open("supp.dat",ios::in);
  if(file == NULL)
  {
    clrscr();
    cout<<"UNABLE TO OPEN ";
    getch();
    return;
  }
  file.seekg(0);
  while( file.read((char *)&supp,sizeof(supp)))
  {
	day = d.da_day;
	mon = d.da_mon;
	year = d.da_year;
	gotoxy(2,y);
	cout<<day<<"/"<<mon<<"/"<<year;
	gotoxy(15,y);
	cout<<i_code;
	gotoxy(26,y);
	cout<<code;
	gotoxy(36,y);
	cout<<sup;
	gotoxy(50,y);
	cout<<qty;
	gotoxy(60,y);
	cout<<cost;
	gotoxy(70,y);
	cout<<total;
	y=y+2;
      if(y>23)
      {
	y=5;
	getch();
	gotoxy(2,3);
	cout<<"DATE";
	gotoxy(15,3);
	cout<<"ITEM CODE";
	gotoxy(26,3);
	cout<<"SUP CODE";
	gotoxy(36,3);
	cout<<"SUP NAME";
	gotoxy(50,3);
	cout<<"ITEM QTY";
	gotoxy(60,3);
	cout<<"ITEM COST";
	gotoxy(70,3);
	cout<<"TOTAL COST";
	gotoxy(2,4);
	cout<<"-------------------------------------------------------------------------------";
      }
   }
  file.close();
}

void SUPPLIER :: del()
{
  fstream file1,file2;
  char cod[10];
  int flag = 0;
  file1.open("supp.dat",ios::in);
  file1.seekg(0);
  file2.open("temp1.dat",ios::out);
  file2.seekg(0);
  cout<<"               É================================================»\n";
  cout<<"               º      ENTER DETAIL FOR DELETE THE CONSUMENR     º\n";
  cout<<"               È================================================¼";
  gotoxy(22,14);
  cout<<"ENTER THE SUPPLIER CODE TO DELETE ->";
  cin>>cod;
  while(file1.read((char *)&supp,sizeof(supp)))
  {
      if(strcmp(cod,supp.code)!=0)
	file2.write((char *)&supp,sizeof(supp));
	flag = 1;
  }
  file1.close();
  file2.close();
  remove("supp.dat");
  rename("temp1.dat","supp.dat");
  if(flag == 0)
  {
    gotoxy(22,18);
    cout<<"SORRY! SUPPLIER INFORMATION NOT AVAILABLE";
  }
  gotoxy(22,20);
  cout<<"PRESS ENTER TO CONTINUE.........";
  getch();
}

void ITEM::display()
{
  gotoxy(2,3);
  cout<<"ITEM CODE";
  gotoxy(30,3);
  cout<<"ITEM NAME";
  gotoxy(50,3);
  cout<<"QUANTITY";
  gotoxy(2,4);
  cout<<"---------------------------------------------------------------------";
  int y=5;
  ifstream file("item.dat",ios::in);
  if(file == NULL)
  {
    clrscr();
    cout<<"UNABLE TO OPEN ";
    getch();
    return;
  }
  file.seekg(0);
  while(file.read((char *)&it,sizeof(it)))
  {
      gotoxy(3,y);
      cout<<it.code;
      gotoxy(30,y);
      cout<<it.name;
      gotoxy(50,y);
      cout<<it.qty;
      y=y+2;
      if(y>23)
      {
	y=5;
	getch();
	gotoxy(2,3);
	cout<<"ITEM CODE";
	gotoxy(30,3);
	cout<<"ITEM NAME";
	gotoxy(50,3);
	cout<<"QUANTITY";
	gotoxy(2,4);
	cout<<"---------------------------------------------------------------------";
      }
     }
  file.close();
}

void ITEM :: del()
{
  fstream file1,file2;
  char cod[10];
  int flag = 0;
  file1.open("item.dat",ios::in);
  file1.seekg(0);
  file2.open("temp1.dat",ios::out);
  file2.seekg(0);
  cout<<"               É================================================»\n";
  cout<<"               º      ENTER DETAIL FOR DELETE THE CONSUMENR     º\n";
  cout<<"               È================================================¼";
  gotoxy(22,14);
  cout<<"ENTER THE ITEM CODE TO DELETE ->";
  cin>>cod;
  while(file1.read((char *)&it,sizeof(it)))
  {
      if(strcmp(cod,it.code)!=0)
	file2.write((char *)&it,sizeof(it));
	flag = 1;
   }
  file1.close();
  file2.close();
  remove("item.dat");
  rename("temp1.dat","item.dat");
  if(flag == 0)
  {
    gotoxy(22,18);
    cout<<"SORRY! ITEM NOT AVAILABLE IN STOCK";
  }
  gotoxy(26,20);
  cout<<"PRESS ENTER TO CONTINUE.........";
  getch();
}

int CONSUMER:: get_con_code()
{
     int temp=0;
     fstream file("cons.dat",ios::in);
     if(file == NULL )
       return temp;
     file.seekg(0);
     while(!file.eof())
     {
     file.read((char *)&con,sizeof(con));
     temp=c_no;
    }
    return temp;
}

void CONSUMER:: entry()
{
  clrscr();
  int code;
  fstream file;
  file.open("cons.dat",ios::app);
  file.seekg(0);
  code=get_con_code();
  code = code + 1;
  cout<<"                  É=============================»\n";
  cout<<"                  ºENTER DETAIL ABOUT CUSTOMER  º\n";
  cout<<"                  È=============================¼";
  gotoxy(26,9);
  cout<<"THE CONSUMER CODE  ->"<<code;
  c_no = code;
  gotoxy(26,11);
  cout<<"ENTER CONSUMER NAME ->";
  gets(c_name);
  gotoxy(26,13);
  cout<<"ENTER ITEM CODE ->";
  cin>>i_code;
  gotoxy(26,15);
  cout<<"ENTER ITEM QUANTITY ->";
  cin>>qty;
  getdate(&d);
  int ret = it.cus_entry(i_code,qty);
  if(ret == 1)
    file.write((char *)&con,sizeof(con));
  file.close();
}

void CONSUMER :: modify()
{
  int qt,cod,f2=0;
  char ans;
  long mqty;
  fstream file("cons.dat",ios::out|ios::in);
  file.seekg(0);
  gotoxy(20,9);
  cout<<"ENTER THE CONSUMER CODE TO MODIFY ->";
  cin>>cod;
  while(file.read((char *)&con,sizeof(con)))
  {
	   if(cod == con.c_no)
	   {
		f2=1;
		clrscr();
		mqty = con.qty;
		cout<<"                  É======================================»\n";
		cout<<"                  ºENTER DETAIL ABOUT CONSUMER TO MODIFY º\n";
		cout<<"                  È======================================¼";
		gotoxy(26,11);
		cout<<"ENTER CONSUMER NAME ->";
		gets(con.c_name);
		gotoxy(26,15);
		cout<<"ENTER ITEM QUANTITY ->";
		cin>>con.qty;
		ans = it.cus_update(con.i_code ,mqty ,con.qty);
		if(ans =='n')
		{
		  file.close();
		  return;
		}
		double size=sizeof(con);
		file.seekg(-size,ios::cur);
		file.write((char *)&con,sizeof(con));
		gotoxy(26,24);
		cout<<"******Record Modified .. Press <enter>******";
		getch();
	   }

      }

      if(f2==0)
	   {
	   clrscr();
	   gotoxy(26,15);
	   cout<<"ENTERED CONSUMER CODE DOES NOT EXISTS";
	   getch();
	   }
  file.close();
}
char ITEM :: cus_update(char i_code[],long aq,long sq)
{

  int flag = 0;
  char ans='n';
  fstream file("item.dat",ios::in|ios::out);
  if(file == NULL)
  {
    cout<<"UNABLE TO OPEN";
    getch();
  }
  while(file.read((char *)&it,sizeof(it)))
  {
    if(strcmp(it.code,i_code)==0)
    {
      if(qty < sq)
      {
	cout<<"SORRY! ENTERED QUANTITY IS GREATER THAN STOCK QUANTITY";
	cout<<"UNABLE TO MODIFY";
	getch();
	ans = 'n';
	file.close();
	return ans;
      }
      flag = 1;
      ans = 'y';
      qty = qty + aq;
      qty = qty - sq;
      long len = sizeof(it);
      file.seekg(-len,ios::cur);
      file.write((char *)&it, sizeof(it));
    }
  }
  if(flag == 0)
  {
    clrscr();
    gotoxy(13,12);
    cout<<"SORRY! ENTERED ITEM NOT AVAILBLE IN STOCK";
    getch();
  }
  file.close();
  return ans;
}

int ITEM :: cus_entry(char i_code[],long q)
{
  int flag = 0;
  fstream file("item.dat",ios::in|ios::out);
  if(file == NULL)
  {
    cout<<"UNABLE TO OPEN";
    getch();
  }
  while(file.read((char *)&it,sizeof(it)))
  {
    if(strcmp(it.code,i_code)==0)
    {
      if(qty < q)
      {
	cout<<"SORRY! ENTERED QUANTITY IS GREATER THAN STOCK QUANTITY";
	file.close();
	return flag;
      }
      else
      {
	flag = 1;
	qty = qty - q;
	long len = sizeof(it);
	file.seekg(-len,ios::cur);
	file.write((char *)&it, sizeof(it));
      }
    }
  }
  if(flag == 0)
  {
    clrscr();
    gotoxy(13,12);
    cout<<"SORRY! ENTERED ITEM IS OUT OF STOCK";
    getch();
  }
  file.close();
  return flag;
}

void CONSUMER::display()
{
  int day,mon,year;
  gotoxy(2,3);
  cout<<"CON CODE";
  gotoxy(15,3);
  cout<<"DATE";
  gotoxy(30,3);
  cout<<"CONSUMER NAME";
  gotoxy(50,3);
  cout<<"ITEM CODE";
  gotoxy(65,3);
  cout<<"QUANTITY";
  gotoxy(2,4);
  cout<<"---------------------------------------------------------------------";
  int y=5;
  ifstream file;
  file.open("cons.dat",ios::in);
  if(file == NULL)
  {
    clrscr();
    cout<<"UNABLE TO OPEN ";
    getch();
    return;
  }
  file.seekg(0);
  while(file.read((char *)&con,sizeof(con)))
  {
      gotoxy(3,y);
      cout<<con.c_no;
      gotoxy(15,y);
      day = con.d.da_day;
      mon = con.d.da_mon;
      year = con.d.da_year;
      cout<<day<<"/"<<mon<<"/"<<year;
      gotoxy(30,y);
      cout<<con.c_name;
      gotoxy(50,y);
      cout<<con.i_code;
      gotoxy(65,y);
      cout<<con.qty;
      y=y+2;
      if(y>23)
      {
	y=5;
	getch();
	gotoxy(2,3);
	cout<<"CON CODE";
	gotoxy(15,3);
	cout<<"DATE";
	gotoxy(30,3);
	cout<<"CONSUMER NAME";
	gotoxy(50,3);
	cout<<"ITEM CODE";
	gotoxy(65,3);
	cout<<"QUANTITY";
	gotoxy(2,4);
	cout<<"--------------------------------------------------------------";
      }
  }
  file.close();
}

void CONSUMER::del()
{
  fstream file1,file2;
  int code,flag = 0;
  file1.open("cons.dat",ios::in);
  file1.seekg(0);
  file2.open("temp1.dat",ios::out);
  file2.seekg(0);
  cout<<"               É================================================»\n";
  cout<<"               º      ENTER DETAIL FOR DELETE THE CONSUMENR     º\n";
  cout<<"               È================================================¼";
  gotoxy(22,14);
  cout<<"ENTER THE CONSUMER CODE TO DELETE ->";
  cin>>code;
  while(file1.read((char *)&con,sizeof(con)))
  {
      if(code != con.c_no)
	file2.write((char *)&con,sizeof(con));
	flag=1;
  }
  file1.close();
  file2.close();
  remove("cons.dat");
  rename("temp1.dat","cons.dat");
  if(flag == 0)
  {
    gotoxy(22,18);
    cout<<"SORRY! CUSTOMER INFORMATION NOT AVALABLE";
    getch();
  }
  gotoxy(22,20);
  cout<<"PRESS ENTER TO CONTINUE.........";
  getch();
}

void main()
{

  m.main_menu();
}

void MENU :: main_menu()
{
  clrscr();
  int ch;
  do
  {
	  clrscr();
	  gotoxy(22,4);
	  cout<<"**********MAIN MENU**************";
	  gotoxy(26,8);
	  cout<<"É=========================»";
	  gotoxy(26,9);
	  cout<<"º                         º";

	  gotoxy(26,10);
	  cout<<"º SUPPLIER DETAIL______1  º";
	  gotoxy(26,11);
	  cout<<"º                         º";
	  gotoxy(26,12);
	  cout<<"º CONSUMER DETAIL______2  º";
	  gotoxy(26,13);
	  cout<<"º                         º";
	  gotoxy(26,14);
	  cout<<"º ITEMS DETAIL_____3      º";
	  gotoxy(26,15);
	  cout<<"º                         º";
	  gotoxy(26,16);
	  cout<<"º EXIT_______________4    º";
	  gotoxy(26,17);
	  cout<<"º                         º";
	  gotoxy(26,18);
	  cout<<"È=========================¼";
	  gotoxy(29,22);
	  cout<<"***********";
	  gotoxy(26,25);
	  cout<<"ENTER YOUR CHOICE->";
	  cin>>ch;
	  switch(ch)
	  {
	     case 1: clrscr(); m.supp_menu();  break;
	     case 2: clrscr(); m.con_menu();   break;
	     case 3: clrscr(); m.item_menu();  break;
	     case 4:  exit(0);
	  }
  }while(ch!=4);
  getch();
}

void MENU :: con_menu()
{
  clrscr();
  int ch1;
  do
  {
    clrscr();
    gotoxy(22,4);
    cout<<"**********CONSUMER MENU**************";
    gotoxy(26,8);
    cout<<"É========================»";
    gotoxy(26,9);
    cout<<"º ADD NEW CONSUMER______1º";
    gotoxy(26,10);
    cout<<"º                        º";
    gotoxy(26,11);
    cout<<"º DISPLAY CONSUMER______2º";
    gotoxy(26,12);
    cout<<"º                        º";
    gotoxy(26,13);
    cout<<"º MODIFY CONSUMER_______3º";
    gotoxy(26,14);
    cout<<"º                        º";
    gotoxy(26,15);
    cout<<"º DELETE CONSUMER_______4º";
    gotoxy(26,16);
    cout<<"º                        º";
    gotoxy(26,17);
    cout<<"º RETURN________________5º";
    gotoxy(26,18);
    cout<<"È========================¼";
    gotoxy(29,22);
    cout<<"***********";
    gotoxy(26,25);
    cout<<"ENTER YOUR CHOICE->";
    cin>>ch1;
    switch(ch1)
   {
     case 1: clrscr(); con.entry();          break;
     case 2: clrscr(); con.display(); getch(); break;
     case 3: clrscr(); con.modify();     break;
     case 4: clrscr(); con.del();break;
     case 5:  break;
   }
  }while(ch1!=5);
}

void MENU :: supp_menu()
{
  clrscr();
  int ch1;
  do
  {
    clrscr();
    gotoxy(22,4);
    cout<<"**********SUPPLIER MENU**************";
    gotoxy(26,8);
    cout<<"É========================»";
    gotoxy(26,9);
    cout<<"º ADD NEW SUPPLIER______1º";
    gotoxy(26,10);
    cout<<"º                        º";
    gotoxy(26,11);
    cout<<"º DISPLAY SUPPLIER______2º";
    gotoxy(26,12);
    cout<<"º                        º";
    gotoxy(26,13);
    cout<<"º MODIFY SUPPLIER_______3º";
    gotoxy(26,14);
    cout<<"º                        º";
    gotoxy(26,15);
    cout<<"º DELETE SUPPLIER_______4º";
    gotoxy(26,16);
    cout<<"º                        º";
    gotoxy(26,17);
    cout<<"º RETURN________________5º";
    gotoxy(26,18);
    cout<<"È========================¼";
    gotoxy(29,22);
    cout<<"***********";
    gotoxy(26,25);
    cout<<"ENTER YOUR CHOICE->";
    cin>>ch1;
    switch(ch1)
   {
     case 1: clrscr(); supp.entry();          break;
     case 2: clrscr(); supp.display(); getch(); break;
     case 3: clrscr(); supp.modify();     break;
     case 4: clrscr(); supp.del();break;
     case 5:  break;
   }
  }while(ch1!=5);
}
void MENU :: item_menu()
{
  clrscr();
  int ch1;
  do
  {
    clrscr();
    gotoxy(22,4);
    cout<<"**********ITEM MENU**************";
    gotoxy(26,8);
    cout<<"É========================»";
    gotoxy(26,9);
    cout<<"º                        º";
    gotoxy(26,10);
    cout<<"º VIEW ITEM______1       º";
    gotoxy(26,11);
    cout<<"º                        º";
    gotoxy(26,12);
    cout<<"º DELETE ITEM______2     º";
    gotoxy(26,13);
    cout<<"º                        º";
    gotoxy(26,14);
    cout<<"º RETURN_______3         º";
    gotoxy(26,15);
    cout<<"º                        º";
    gotoxy(26,16);
    cout<<"È========================¼";
    gotoxy(29,22);
    cout<<"***********";
    gotoxy(26,25);
    cout<<"ENTER YOUR CHOICE->";
    cin>>ch1;
    switch(ch1)
   {
     case 1: clrscr(); it.display();getch();  break;
     case 2: clrscr(); it.del();  break;
     case 3:  break;
   }
  }while(ch1!=3);
}
