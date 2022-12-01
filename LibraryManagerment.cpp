                       /* Library management using C++ - Ninh Thi Linh  */
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<fstream>
#include<string.h>
#include<conio.h>
#include <sstream>

using namespace std;

class Lib
{
   	private:  		
       	char BookName[100],Author[50],sc[20],sc1[50],Status[20];
       	int q,B,p;
    public:
       	Lib()
       	{
           	strcpy(BookName,"No Book Name");//copy
           	strcpy(Author,"No Author Name");
           	strcpy(sc,"No Book ID");
           	strcpy(sc1,"No Publication name");
           	strcpy(Status,"Unknown");
           	q=0;
           	B=0;
           	p=0;
       	}

	    void mainMenu(); 					//mainmenu
	    void student(); 					//student menu
	    void pass();						//check the password
	    void librarian();					//librarian menu
	    void password();					//change password
	    void getdata();						//get book's data
	    void display(int);					//print book record
	    void booklist(int);					//print the book list
	    void modify();						//add/delete/edit book's record
	    void search(int);					//search book's record 
	    int branch(int);					//book's categories
	    void borrow();						//borrow/return book
	    void der(char[],int,int);			//add or minor the book's quatity
	    int checkId(char[],int);			//check id
	    void fine(int,int,int,int,int,int);	//check for violations when borrowing books
};

int Lib::checkId(char test[], int x)
{
	int i;
    ifstream intf("Booksdata.txt",ios::binary);
	if(!intf)
    {
        cout<<"\n\t\tFile Not Found.\n";
        cout<<"\n\t\t->Press any key to continue.....";
        getch();
        system("cls");
		if(x==1)
        {
        	student();	
		}
        else
        {
        	librarian();	
		}  
    }
	while(!intf.eof())
	{
	    for(i=0;q!=0&&sc[i]!='\0'&&test[i]!='\0'&&test[i]==sc[i];i++);
	    if(sc[i]=='\0'&&test[i]=='\0')
	    {
	        return 1;
	        break;
	    }
	    intf.read((char*)this,sizeof(*this));
	}
	return 0;	
}       
void Lib::getdata()//add more book data 
{		
    int i;
    cout<<"\n\t\tEnter the details :-\n";   
    while(1)
    {
		cout<<"\n\t\tEnter Book's ID : ";
		char test[20];
    	int result=0;
	    fflush(stdin);	//
	    cin.getline(test,20);
	    result = checkId(test,2);
	    if(result==0)
	    {
	    	strcpy(sc,test);
	    	break;
		}
		else
		{
			cout<<"\n\t\tId already exists";
			cout<<"\n\t\tPress any key to continue.....";
    		getch();
    		system("cls");
		}	
	}
    cout<<"\n\t\tEnter Book's Name : ";
    cin.getline(BookName,100);
    //capitalize book title
    for(i=0;BookName[i]!='\0';i++) 				//loop until the end of the book's title string
    {
    	if(BookName[i]>='a'&&BookName[i]<='z') 	//check for non-capitalized characters in book title
    	{
    		BookName[i]-=32; 					//If the character is not uppercase, the ASCII code of that character is minus 32	
		}  
    }
    cout<<"\n\t\tEnter Author's Name : ";
    cin.getline(Author,50);
    cout<<"\n\t\tEnter Publication name : ";
    cin.getline(sc1,50);
	cout<<"\n\t\tEnter Book's Status : ";
	cin.getline(Status,20);    
    q=1;
}
void Lib::display(int i)//display all book data(if i = 1: display for student, if i = 2: display for librian)
{
    cout<<"\n\t\tBook Name : "<<BookName<<endl;
    cout<<"\n\t\tBook's Author Name : "<<Author<<endl;
    cout<<"\n\t\tBook's ID : "<<sc<<endl;
    cout<<"\n\t\tBook's Publication : "<<sc1<<endl;
    if(i==2) //if they are librarians, they can see the number of books and the price of books.
    {
        cout<<"\n\t\tBook's Status : "<<Status<<endl;
        cout<<"\n\t\tBook's Quantity : "<<q<<endl;
        
    }
}
void Lib::booklist(int i)//display all book data
{
    int b,r=0;
    system("cls");
    b=branch(i);
    system("cls");
    ifstream intf("Booksdata.txt",ios::binary);
    if(!intf)	//check file existence
        cout<<"\n\t\tFile Not Found.";
    else
    {
        cout<<"\n\t    ************ Book List ************ \n\n";
        intf.read((char*)this,sizeof(*this));	//read the file
    	while(!intf.eof())
        {
            if(b==B)	//check the categories of book
            {
                if(q==0 && i==1)	//check the quatity of book and the role (if i = 1: for student; if i = 2: for librarian)
                {

                }
                else
                {
                    r++;
                    cout<<"\n\t\t********** "<<r<<". ********** \n";
                    display(i);
                }
            }
            intf.read((char*)this,sizeof(*this)); 
        }
    }
    cout<<"\n\t\tPress any key to continue.....";
    getch();
    system("cls");
    if(i==1)
    {
    	student();
	}    
    else
    {
    	librarian();
	}    
}
void Lib::modify()//adding, rewrite book information, delete book
{
    char ch,st1[100];
    int i=0,b,cont=0;
    system("cls");
    cout<<"\n\t\t>>Please Choose one option :-\n";
    cout<<"\n\t\t1.Modification In Current Books\n\n\t\t2.Add New Book\n\n\t\t3.Delete A Book\n\n\t\t4.Go back\n";
    cout<<"\n\n\t\tEnter your choice : ";
    cin>>i;
    fflush(stdin);
    if(i==1)
    {
        system("cls");
        b=branch(2);	//choose the book branch
        ifstream intf1("Booksdata.txt",ios::binary);	//open file for reading in binary
        if(!intf1)	//if the file is not available 
        {
            cout<<"\n\t\tFile Not Found\n";
            cout<<"\n\t\tPress any key to continue.....";
            getch();
            system("cls");
            librarian();
        }
        fflush(stdin);
        intf1.close();	//close the file
        system("cls");	//clear the console's screen
        cout<<"\n\t\tEnter Book's ID : ";
        cin.getline(st1,100);
        system("cls");
        fstream intf("Booksdata.txt",ios::in|ios::out|ios::ate|ios::binary);
        intf.seekg(0);
        intf.read((char*)this,sizeof(*this));
        while(!intf.eof())//read until end of file
        {
            for(i=0;b==B&&sc[i]!='\0'&&st1[i]!='\0'&&st1[i]==sc[i];i++);//check book ID
            if(sc[i]=='\0'&&st1[i]=='\0')
            {
                cont++;
                getdata();
                intf.seekp(intf.tellp()-sizeof(*this));	//seekp: sets the position where the next character is to be inserted into the output stream.
                    									//tellp: returns the position of the current character in the output stream.
                    									//sizeof this in this case is the size of current data in the file.
                intf.write((char*)this,sizeof(*this));	//write: copies a block of data into file
                    									//"this" in this case is new data we enter in this part.
                break;
            }
            intf.read((char*)this,sizeof(*this));
        }
        intf.close();
    	if(cont==0)
    	{
        	cout<<"\n\t\tBook Not Found.\n";
        	cout<<"\n\t\tPress any key to continue.....";
        	getch();
        	system("cls");
        	modify();
    	}
    	else
    	{
        cout<<"\n\t\tUpdate Successful.\n";
		}     
    }
    else if(i==2)
    {
        system("cls");
        B=branch(2);//choose branch for book
        system("cls");
        getdata();
        ofstream outf("Booksdata.txt",ios::app|ios::binary);
        outf.write((char*)this,sizeof(*this));
        outf.close();
        cout<<"\n\t\tBook added Successfully.\n";
    }
    else if(i==3)
    {
        system("cls");
        b=branch(2);
        ifstream intf1("Booksdata.txt",ios::binary);
        if(!intf1)
        {
            cout<<"\n\t\tFile Not Found\n";
            cout<<"\n\t\tPress any key to continue.....";
            getch();
            intf1.close();
        	system("cls");
            librarian();
        }
        intf1.close();
        fflush(stdin);
        system("cls");
        cout<<"\n\t\tEnter Book's ID : ";
        cin.getline(st1,100);
        ofstream outf("temp.txt",ios::app|ios::binary);
        ifstream intf("Booksdata.txt",ios::binary);
        intf.read((char*)this,sizeof(*this));
        while(!intf.eof())
        {
            for(i=0;b==B&&sc[i]!='\0'&&st1[i]!='\0'&&st1[i]==sc[i];i++);
            if(sc[i]=='\0'&&st1[i]=='\0')
            {
                cont++;
                intf.read((char*)this,sizeof(*this));
            }
            else
            {
                outf.write((char*)this,sizeof(*this));
                intf.read((char*)this,sizeof(*this));
            }
        }
        outf.close();
        intf.close();
        remove("Booksdata.txt");
        rename("temp.txt","Booksdata.txt");
    	if(cont==0)
    	{
        	cout<<"\n\t\tBook Not Found.\n";
        	cout<<"\n\t\tPress any key to continue.....";
        	getch();
        	system("cls");
        	modify();
    	}
    	else
    	{
        cout<<"\n\t\tDeletion Successful.\n";
		}   
	}
    else if(i==4)
    {
    	system("cls");
    	librarian();
    }
    else
    {
    	cout<<"\n\t\tWrong Input.\n";
    	cout<<"\n\t\tPress any key to continue.....";
    	getch();
    	system("cls");
    	modify();
    }
    cout<<"\n\t\tPress any key to continue.....";
    getch();
    system("cls");
    librarian();
}
int Lib::branch(int x)//branch of book
{
    int i;
    cout<<"\n\t\t>>Please Choose one Branch :-\n";
    cout<<"\n\t\t1.Historical Fiction\n\n\t\t2.Classics\n\n\t\t3.Comic Book or Graphic Novel\n\n\t\t4.Go to menu\n";
    cout<<"\n\t\tEnter youur choice : ";
    cin>>i;
    switch(i)
    {
        case 1: return 1;
                break;
        case 2: return 2;
                break;
        case 3: return 3;
                break;
        case 4: system("cls");
                if(x==1)
                {
                	student();
				}  	
                else
                {
                	librarian();
				}                    
        default : cout<<"\n\t\tPlease enter correct option :(";
                getch();
                system("cls");
                branch(x);
    }
}
void Lib::search(int x)//search book
{
    int i,b,r=0,cont=0;
    char ch[100];
    system("cls");
    ifstream intf("Booksdata.txt",ios::binary);
	if(!intf)
    {
        cout<<"\n\t\tFile Not Found.\n";
        cout<<"\n\t\t->Press any key to continue.....";
        getch();
        system("cls");
        if(x==1)
        {
        	student();	
		}
        else
        {
        	librarian();	
		}  
    }
    system("cls");
    cout<<"\n\t\tPlease Choose one option :-\n";
    cout<<"\n\t\t1.Search By Name\n\n\t\t2.Search By Book's ID\n\n\t\t3.Search By Book's categories\n\n\t\t4.Search By Book's author\n\n\t\t5.Go to mainmenu\n";
    cout<<"\n\t\tEnter Your Choice : ";
    cin>>i;
    fflush(stdin);
    intf.read((char*)this,sizeof(*this));
    if(i==1)
    {
        cout<<"\n\t\tEnter Book's Name : ";
        cin.getline(ch,100);
        system("cls");
        while(!intf.eof())
        {
        	for(i=0;q!=0&&BookName[i]!='\0'&&ch[i]!='\0'&&(ch[i]==BookName[i]||ch[i]==BookName[i]+32);i++);
            if(BookName[i]=='\0'&&ch[i]=='\0')
            {
                cout<<"\n\t\tBook Found :-\n";
                display(x);
                cont++;
            }
            intf.read((char*)this,sizeof(*this));
        }
    }
    else if(i==2)
    {
        cout<<"\n\t\tEnter Book's ID : ";
        cin.getline(ch,100);
        system("cls");
        cont=checkId(ch,x);
        if(cont!=0)
        {
        	display(x);
		}
    }
    else if(i==3)
    {
    	system("cls");
    	b=branch(i);
    	system("cls");
    	while(!intf.eof())
        {
            if(b==B)	//check the categories of book
            {
                if(q==0 && i==1)	//check the quatity of book and the role (if i = 1: for student; if i = 2: for librarian)
                {

                }
                else
                {
                	cont++;
                    r++;
                    cout<<"\n\t\t********** "<<r<<". ********** \n";
                    display(i);
                }
            }
            intf.read((char*)this,sizeof(*this)); 
        }
    }	
	else if(i==4)
	{
        cout<<"\n\t\tEnter Book's Author : ";
        cin.getline(ch,100);
        system("cls");
        while(!intf.eof())
        {
        	for(i=0;q!=0&&Author[i]!='\0'&&ch[i]!='\0'&&(ch[i]==Author[i]||ch[i]==Author[i]+32);i++);
            if(Author[i]=='\0'&&ch[i]=='\0')
            {
                cout<<"\n\t\tBook Found :-\n";
                display(x);
                cont++;
            }
            intf.read((char*)this,sizeof(*this));
        }		
	}
	else if(i==5)
	{
		system("cls");
		if(x==1)
    	{
    		student();	
		}
    	else
    	{
    		librarian();	
		} 
	}
    else
    {
        cont++;
        cout<<"\n\t\tPlease enter correct option :(";
        getch();
        system("cls");
        search(x);
    }
    intf.close();
    if(cont==0)
    {
    	cout<<"\n\t\tThis Book is not available :( \n";
	}
    cout<<"\n\t\tPress any key to continue.....";
    getch();
    system("cls");
    if(x==1)
    {
    	student();	
	}
    else
    {
    	librarian();	
	}   
}
void Lib::borrow()//borrow book
{
	char st[50],st1[20],test[20];
    int b,i,j,d,m,y,cont=0;
    do{    	
    	system("cls");
	    cout<<"\n\t\t->Please Choose one option :-\n";
	    cout<<"\n\t\t1.Borrow Book\n\n\t\t2.View Borrowed Book\n\n\t\t3.Search student who Borrowed books\n\n\t\t4.Change Borrow Information\n\n\t\t5.Return Book\n\n\t\t6.Go back to menu\n\n\t\tEnter Your Choice : ";
	    cin>>i;
	    fflush(stdin);
    	switch(i)
		{
    		case 1:
    		{
				int a;
    			system("cls");
			    b=branch(2);
			    system("cls");
			    fflush(stdin);
			    cout<<"\n\t\t->Please Enter Details :-\n";
			    while(1)
			    {
			    	
					cout<<"\n\t\tEnter Book's ID : ";
					char test[20];
			    	int result=0;
				    fflush(stdin);	//
				    cin.getline(test,20);
				    result = checkId(test,2);
				    if(result==0)
				    {
				    	
				    	cout<<"\n\t\tNo book available";
				    	cout<<"\n\t\tPress any key to continue.....";
				    	getch();
						borrow();	
			    		system("cls");
					}
					else
					{
						display(2);
						break;
					}	
				}
			    der(sc,b,1);
			    cout<<"\n\t\tEnter Student Name : ";
			    cin.getline(Author,50);
			    cout<<"\n\t\tEnter Student's ID : ";
			    cin.getline(sc1,20);
			    cout<<"\n\t\tEnter date : ";
			    cin>>q>>B>>p;
			    ofstream outf("student.txt",ios::binary|ios::app);
			    outf.write((char*)this,sizeof(*this));
			    outf.close();
			    cout<<"\n\n\t\tIssue Successfully.\n";
			    getch();
			    break;
			}	
			case 2:
			{
				ifstream intf("student.txt",ios::binary);
			    system("cls");
			    cout<<"\n\t\t->The Details are :-\n";
			    intf.read((char*)this,sizeof(*this));
			    i=0;
			    while(!intf.eof())
			    {
				    i++;
				    cout<<"\n\t\t********** "<<i<<". ********** \n";
				    cout<<"\n\t\tStudent Name : "<<Author<<"\n\t\t"<<"Student's ID : "<<sc1<<"\n\t\t"<<"Book Name : "<<BookName<<"\n\t\t"<<"Book's ID : "<<sc<<"\n\t\t"<<"Date : "<<q<<"/"<<B<<"/"<<p<<"\n";
				    intf.read((char*)this,sizeof(*this));
			    }
			    intf.close();
			    cout<<"\n\n\t\tEnter any key to return...";
				getch(); 
			    break;
			}	
			case 3:
			{
				system("cls");
		        fflush(stdin);
		        cout<<"\n\t\t->Please Enter Details :-\n";
		        cout<<"\n\n\t\tEnter Student's ID : ";
		        cin.getline(st1,20);
		        system("cls");
		        ifstream intf("student.txt",ios::binary);
		        intf.read((char*)this,sizeof(*this));
		        cont=0;
		        while(!intf.eof())
		        {
		            for(i=0;sc1[i]!='\0'&&st1[i]!='\0'&&st1[i]==sc1[i];i++);
		            if(sc1[i]=='\0'&&st1[i]=='\0')
		            {
		                cont++;
		                if(cont==1)
		                {
		                    cout<<"\n\t\t->The Details are :-\n";
		                    cout<<"\n\t\tStudent Name : "<<Author;
		                    cout<<"\n\t\tStudent's ID : "<<sc1;
		                }
		                cout<<"\n\n\t\t******* "<<cont<<". Book details *******\n";
		                cout<<"\n\t\tBook Name : "<<BookName;
		                cout<<"\n\t\tBook's ID : "<<sc;
		                cout<<"\n\t\tDate : "<<q<<"/"<<B<<"/"<<p<<"\n";
		            }
		            intf.read((char*)this,sizeof(*this));
		        }
		        intf.close();
		        if(cont==0)
		        {
		        	cout<<"\n\t\tNo record found.";
				}   
		        cout<<"\n\n\t\tEnter any key to return...";
				getch();
		        break;
			}				
		    case 4:
		    {
		    	system("cls");
			    fflush(stdin);
			    cout<<"\n\t\t->Please Enter Details :-\n";
			    cout<<"\n\n\t\tEnter Student's ID : ";
			    cin.getline(st,50);
			    cout<<"\n\t\tEnter Book's ID : ";
			    cin.getline(st1,20);
			    fstream intf("student.txt",ios::in|ios::out|ios::ate|ios::binary);
			    intf.seekg(0);
			    intf.read((char*)this,sizeof(*this));
			    while(!intf.eof())
			    {
			        for(i=0;sc[i]!='\0'&&st1[i]!='\0'&&st1[i]==sc[i];i++);
			        for(j=0;sc1[j]!='\0'&&st[j]!='\0'&&st[j]==sc1[j];j++);
			        if(sc[i]=='\0'&&sc1[j]=='\0'&&st[j]=='\0'&&st1[i]=='\0')
			        {
			            d=q;
			            m=B;
			            y=p;
			            cout<<"\n\t\tEnter New Date : ";
			            cin>>q>>B>>p;
			            intf.seekp(intf.tellp()-sizeof(*this)); //fn3
			            intf.write((char*)this,sizeof(*this)); //fn5
			            cout<<"\n\n\t\tReissue successfully."; //fn3
			            break;
			        }
			        intf.read((char*)this,sizeof(*this));
			    }
			    intf.close();
			    cout<<"\n\n\t\tEnter any key to return...";
				getch();
		        break;
			}		    	
		    case 5:
		    {
		    	system("cls");
			    b=branch(2);
			    system("cls");
			    fflush(stdin);
			    cout<<"\n\t\t->Please Enter Details :-\n";
			    cout<<"\n\t\tEnter Book's ID : ";
			    cin.getline(st1,20);
			    der(st1,b,2);
			    cout<<"\n\n\t\tEnter Student's ID : ";
			    cin.getline(st,20);
			    cout<<"\n\t\tEnter Present date : ";
			    cin>>d>>m>>y;
			    ofstream outf("temp.txt",ios::app|ios::binary);
			    ifstream intf("student.txt",ios::binary);
			    intf.read((char*)this,sizeof(*this));
			    while(!intf.eof())
			    {
			        for(i=0;sc[i]!='\0'&&st1[i]!='\0'&&st1[i]==sc[i];i++);
			        for(j=0;sc1[j]!='\0'&&st[j]!='\0'&&st[j]==sc1[j];j++);
			        if(sc[i]=='\0'&&sc1[j]=='\0'&&st[j]=='\0'&&st1[i]=='\0'&&cont==0)
			        {
			            cont++;
			        	intf.read((char*)this,sizeof(*this));
			        	fine(q,B,p,d,m,y);
			            cout<<"\n\t\tReturned successfully.";
			        }
			        else
			        {
			            outf.write((char*)this,sizeof(*this));
			            intf.read((char*)this,sizeof(*this));
			        }
				}
			    intf.close();
			    outf.close();
			    remove("student.txt");
			    rename("temp.txt","student.txt");
			    cout<<"\n\n\t\tEnter any key to return...";
				getch();
		        break;
			}		    	
		    case 6:
		    {
		    	system("cls");
    			librarian();
			}		    	
    		default:
    		{
    			cout<<"\n\t\tWrong Input.\n";
				borrow();
			}  
		}
	}while(i!=6);
    system("cls");
    librarian();
}
void Lib::der(char st[],int b,int x)//adding or minus quality of book when issue book
{
    int i,cont=0;
    fstream intf("Booksdata.txt",ios::in|ios::out|ios::ate|ios::binary);
    intf.seekg(0);
    intf.read((char*)this,sizeof(*this));
    while(!intf.eof())
    {
        for(i=0;b==B&&sc[i]!='\0'&&st[i]!='\0'&&st[i]==sc[i];i++);
        if(sc[i]=='\0'&&st[i]=='\0')
        {
            cont++;
            if(x==1)
            {
                q--;
            }
            else
            {
                q++;
            }
            intf.seekp(intf.tellp()-sizeof(*this));
            intf.write((char*)this,sizeof(*this));
            break;
        }
        intf.read((char*)this,sizeof(*this));
    }
    if(cont==0)
    {
        cout<<"\n\t\tBook not found.\n";
        cout<<"\n\n\t\tPress any key to continue.....";
        getch();
        system("cls");
        borrow();
    }
    intf.close();
}
void Lib::mainMenu()//the first menu
{
   	int i;
    cout<<"\n\t*********** LIBRARY MANAGEMENT SYSTEM ***********\n"<<endl;
    cout<<"\n\t\t>>Please Choose Any Option To login \n";
    cout<<"\n\t\t1.Student\n\n\t\t2.Librarian\n\n\t\t3.Close Application\n";
    cout<<"\n\t\tEnter your choice : ";
    cin>>i;
    if(i==1)
    {
        system("cls");
        student();
    }
    else if(i==2)
    {
    	pass();
	}
    else if(i==3)
    {
    	exit(0);
	}       
    else
    {
        cout<<"\n\t\tPlease enter correct option :(";
        getch();
        system("CLS");
        mainMenu();
    }
}
void Lib::student()//the student menu
{
    int i;
    cout<<"\n\t************ WELCOME STUDENT ************\n";
    cout<<"\n\t\t>>Please Choose One Option:\n";
    cout<<"\n\t\t1.View BookList\n\n\t\t2.Search for a Book\n\n\t\t3.Go to main menu\n\n\t\t0.Close Application\n";
    cout<<"\n\t\tEnter your choice : ";
    cin>>i;
    if(i==1)
    {
        booklist(1);
	}    
    else if(i==2)
    {
    	search(1);
	}            
    else if(i==3)
    {
        system("cls");
        mainMenu();
    }
    else if(i==0)
    {
    	exit(0);
	}          
    else
    {
        cout<<"\n\t\tPlease enter correct option :(";
        getch();
        system("cls");
        student();
    }
}
void Lib::pass()//check the password
{
    int i=0;
    char ch,st[21],ch1[21]={"1111"};
    cout<<"\n\t\tEnter Password : ";
    while(1)
    {
	    ch=getch();
	    if(ch==13)//ch==13 char: enter: check the input is 'space' or not
	    {
	        st[i]='\0';
	        break;
	    }
	    else if(ch==8&&i>0)//ch==8 delete or backspace
	    {
	        i--;
	        cout<<"\b \b";
	    }
	    else
	    {
		    cout<<"*";
		    st[i]=ch;
		    i++;
	    }
    }
    ifstream inf("password.txt");
    inf>>ch1;
    inf.close();
    for(i=0;st[i]==ch1[i]&&st[i]!='\0'&&ch1[i]!='\0';i++);
    if(st[i]=='\0'&&ch1[i]=='\0')
    {
        system("cls");
        librarian();
    }
    else
    {
        cout<<"\n\n\t\tWrong Password.\n\n\t\ttry again.....\n";
        getch();
        system("cls");
        mainMenu();
    }
}
void Lib::librarian()//the librian menu
{
	system("cls");
    int i;
    cout<<"\n\t************ WELCOME LIBRARIAN ************\n";
    cout<<"\n\t\t>>Please Choose One Option:\n";
    cout<<"\n\t\t1.View BookList\n\n\t\t2.Search for a Book\n\n\t\t3.Modify/Add Book\n\n\t\t4.Borrow book\n\n\t\t5.Go to main menu\n\n\t\t6.Change Password\n\n\t\t7.Close Application\n";
    cout<<"\n\t\tEnter your choice : ";
    cin>>i;
    switch(i)
    {
        case 1:booklist(2);
                break;
        case 2:search(2);
                break;
        case 3:modify();
                break;
        case 4:borrow();
        		break;
        case 5:system("cls");
            	mainMenu();
                break;
        case 6:password();
            	break;
        case 7:exit(0);
        default:cout<<"\n\t\tPlease enter correct option :(";
        		getch();
        		system("cls");
        		librarian();
    }
}
void Lib::password()//change the password
{
    int i=0,j=0;
    char ch,st[21],ch1[21]={"1111"};
    system("cls");
    cout<<"\n\n\t\tEnter Old Password : ";
    while(1)
    {
    	ch=getch();
    	if(ch==13)
    	{
        	st[i]='\0';
        	break;
    	}
    	else if(ch==8&&i>0)
    	{
        	i--;
        	cout<<"\b \b";
    	}
    	else
    	{
    		cout<<"*";
    		st[i]=ch;
    		i++;
    	}
    }
    ifstream intf("password.txt");
    intf>>ch1;
    intf.close();
    for(i=0;st[i]==ch1[i]&&st[i]!='\0'&&ch1[i]!='\0';i++);
    if(st[i]=='\0'&&ch1[i]=='\0')
    {
        system("cls");
        cout<<"\n\t**The Password Should be less than 20 characters & don't use spaces**\n\n";
        cout<<"\n\t\tEnter New Password : ";
        fflush(stdin);//delete the cache
        i=0;
        while(1)
        {
        	j++;
        	ch=getch();
        	if(ch==13)
        	{
            	for(i=0;st[i]!=' '&&st[i]!='\0';i++);
            	if(j>20 || st[i]==' ')
            	{
                	cout<<"\n\n\t\tYou did't follow the instruction \n\n\t\tPress any key for try again.....";
                	getch();
                	system("cls");
                	password();
                	librarian();
            	}
            	st[i]='\0';
            	break;
        	}
        	else if(ch==8&&i>0)
        	{
            	i--;
            	cout<<"\b \b";
        	}
        	else
        	{
        		cout<<"*";
        		st[i]=ch;
        		i++;
        	}
        }
        ofstream outf("password.txt");
        outf<<st;
        outf.close();
        cout<<"\n\n\t\tYour Password has been changed Successfully.";
        cout<<"\n\t\tPress any key to continue......";
        getch();
        system("cls");
        librarian();
    }
    else
    {
        cout<<"\n\n\t\tPassword is incorrect.....\n";
        cout<<"\n\t\tEnter 1 for retry or 2 for menu";
        cin>>i;
        if(i==1)
        {
        	system("cls");
        	password();
        }
        else
        {
            system("cls");
            librarian();
        }
    }
}
void Lib::fine(int d,int m,int y,int dd,int mm,int yy)//calculate the time borrowing and fine. d/m/y is the date which borrow book, dd/mm/yy is the date which return book 
{
long int n1,n2;
    int years,l,i;
    const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};//day of each months
    n1 = y*365 + d;				//calculate the number of days since A.D. plus the date of borrowing the book  
    for(i=0; i<m - 1; i++)		//calculate number of days by month
    {
    	n1 += monthDays[i]; 
	}
    years = y;
    if (m <= 2)
    {
    	years--;	
	}
    l= years / 4 - years / 100 + years / 400;	//Calculate the number of days in a leap year from AD to the year of borrowing
    n1 += l;	//add the number of February days in a leap year
    
    n2 = yy*365 + dd;
    for(i=0; i<mm - 1; i++)
    {
    	n2 += monthDays[i];
	}
    years = yy;
    if (m <= 2)
    {
    	years--;
	}
    l= years / 4 - years / 100 + years / 400;
    n2 += l;
    n1=n2-n1;
    n2=n1-14;//if the borrow time < 14 day, not be fine
	if(n2<=0)
	{
		cout<<"\n\t\tNo Fine";
	}else{
		cout<<"\n\t\tThe Total Fine is : 1.000.000 vnd";
	}   
}

int main()
{
    Lib obj;
    obj.mainMenu();
    getch();
    return 0;
}

