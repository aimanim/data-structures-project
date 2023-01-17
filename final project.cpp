//program needs c++11 to run
#include<iostream>
#include<string>
#include <windows.h>
#include <stdlib.h>
#include<conio.h>
#include<fstream>
#include<vector>
using namespace std;
const size_t alphabets = 26;

//functions for case 5
int min(int a, int b, int c)
{
    if (a <= b && a <= c)
        return a;
    else if (b <= a && b <= c)
        return b;
    else
        return c;
}
int align(const string &a, const string &b, int alpha_gap, 
        int alpha[alphabets][alphabets], string &a_aligned, 
        string &b_aligned)
{
    size_t n = a.size();
    size_t m = b.size();

    int A[n + 1][m + 1];

    for (size_t i = 0; i <= m; ++i)
        A[0][i] = alpha_gap * i;
    for (size_t i = 0; i <= n; ++i)
        A[i][0] = alpha_gap * i;
//m=sequence
    for (size_t i = 1; i <= n; ++i)
    {
        for (size_t j = 1; j <= m; ++j)
        {
            char x_i = a[i-1];
            char y_j = b[j-1];
            A[i][j] = min(A[i-1][j-1] + alpha[x_i - 'A'][y_j - 'A'],
                          A[i-1][j] + alpha_gap,
                          A[i][j-1] + alpha_gap);
        }
    }

    // print2DVector(A);
	for(int k=0;k<=n;k++)
	{
		for(int l=0;l<=m;l++)
		cout<<A[k][l]<<"\t";
		cout<<endl;
	}
    a_aligned = "";
    b_aligned = "";
    size_t j = m;
    size_t i = n;
   	cout<<i<<'\t'<<j<<endl;
    for (; i >= 1 && j >= 1; --i)
    {
        char x_i = a[i-1];
        char y_j = b[j-1];
        if (A[i][j] == A[i-1][j-1] + alpha[x_i - 'A'][y_j - 'A'])
        {
            /*
             * I think prepending chars this way to a std::string is very inefficient.
             * Is there any better way of doing this without using C-style strings?
             */
            a_aligned = x_i + a_aligned;
            b_aligned = y_j + b_aligned;
            --j;
        }
        else if (A[i][j] == A[i-1][j] + alpha_gap)
        {
            a_aligned = x_i + a_aligned;
            b_aligned = '-' + b_aligned;
        }
        else
        {
            a_aligned = '-' + a_aligned;
            b_aligned = y_j + b_aligned;
            --j;
        }
    }
	cout<<i<<'\t'<<j<<endl;
    while (i >= 1 && j < 1)
    {
        a_aligned = a[i-1] + a_aligned;
        b_aligned = '-' + b_aligned;
        --i;
    }
    while (j >= 1 && i < 1)
    {
        a_aligned = '-' + a_aligned;
        b_aligned = b[j-1] + b_aligned;
        --j;
    }

    return A[n][m];
}

//node for BST and singly linked list
class Node {
  public:
  //the key in this is the register number
  //variables for the criminal
  int register_no;
  string name;
  int age;
  string crime_commit;
  string area; //where they live 
  int level;
  int years; //they spend in jail 
  string DNA;
  Node *left; Node *right;

  Node() { //default constructor initialize to zero
    register_no = 0;
    left = NULL; right =NULL;
  }
  Node(int register_no, string name,  int age,  string crime_commit,  string area,  int level,  int years,  string DNA) { //parameterized const
  this->register_no = register_no;
  this->name = name;
  this->age = age;
  this->crime_commit= crime_commit;
  this->level = level;
  this->area = area; 
  this->years = years; 
  this->DNA = DNA;
  left=NULL; right=NULL;
  }
  void print(){
  	cout<<endl<<register_no<<"\t\t\t"<<name<<"\t\t\t"<<age<<"\t\t\t"<<crime_commit<<"\t\t\t"<<level;
	cout<<"\t\t\t"<<area<<"\t\t"<<years<<"\t\t"<<DNA;
  }
};

// BST for case 4a
class BST {
	public:
	Node* root;
	BinaryTree()
	{
		root = NULL;
	}
	BinaryTree(Node* n)
	{
		root = n;
	}
	void addNode(Node *n)
	{
		if (root == NULL) {
			root = n;
		}
		else {
			Node* temp = root;
			while (true)
			{
				if (n->register_no < temp->register_no && temp->left == NULL) {
					temp->left = n;
					break;
				}
				if (n->register_no > temp->register_no && temp->right == NULL) {
					temp->right = n;
					break;
				}
				if (n->register_no < temp->register_no && temp->left != NULL) {
					temp = temp->left;
				}
				if (n->register_no > temp->register_no && temp->right != NULL) {
					temp = temp->right;
				}
			}
		}
	}
	void printInorder(Node* n)
	{
		if (n == NULL) {
			return;
		}
		printInorder(n->left);
		n->print();
		printInorder(n->right);
	}
};

// linked list for case 4b
class SinglyLinkedList {
  public:
    Node * head; 
	Node* sorted = NULL;
  SinglyLinkedList() {
    head = NULL; // initialized to null
  }
  SinglyLinkedList(Node * n) {
    head = n; 
  }

  // Check if node exists using key value
  Node * nodeExists(int k) {
    Node * temp = NULL;

    Node * ptr = head; //this is done so we can start from head
    while (ptr != NULL) { //goes till last node
      if (ptr -> register_no == k) { //check if we can find the key that we were looking for
        temp = ptr; 
      }
      ptr = ptr -> right; 

	  }
    return temp; 
  }

  //adding another node at the end
  void appendNode(Node * n) { 
    if (nodeExists(n -> register_no) != NULL) {
       
    } else {
      if (head == NULL) { 
        head = n; //assign n to head
        
      } else {
        Node * ptr = head; 
        while (ptr -> right != NULL) { 
          ptr = ptr -> right; 
        }
        ptr -> right = n; //ptr next assign node after the loop breaks
      }
    }
  }
  //sorting using insertion sort
  void new_sort( Node* newnode) { 
  	if(sorted==NULL || sorted ->level >= newnode->level) 
	{
		newnode ->right = sorted; 
		sorted = newnode; 
	}
	else
	{
		 Node* temp = sorted; 
		while(temp->right !=NULL && temp->right->level < newnode->level) {
			temp = temp->right;
		}
			newnode ->right = temp->right; 
			temp->right = newnode; 
	}
	}
	void insertionSort(){
		Node* current = head; 
		
		while(current !=NULL) {
			Node* next = current->right; 
			new_sort(current); 
			current = next;
		}
		head = sorted; 
	}

  // printing
  void printList() {
    if (head == NULL) {
	
    } else {
     cout<<"REGISTER		NAME			AGE			CRIMES COMMITTED	LEVEL			AREA		YEARS OF JAIL	DNA SEQUENCE"<<endl;
      Node * temp = head;

      while (temp != NULL) {
     	temp->print();
        temp = temp -> right;
      }
    }
  }
};


//case 1
void createCriminalProfile() {
	cout<<"------------INPUT CRIMINAL CREDENTIALS------------"<<endl;

	Node * n1 = new Node();
	fstream file; //creating the obj
	
	file.open("srime.txt",ios::app|ios::binary);
	
	cout<<"Register number: ";
	int register_no;
	cin >> register_no;
	cout<<"Name: ";
	string name;
	cin>>name;
	cout<<"Age: ";
	int age;
	cin >> age;
	cout<<"Enter Crime name and level Respectively: "<<endl;
	int level; string crime_commit;
	cin >> crime_commit;
	cin >> level;
	cout<<"Area: ";
	string area;
	cin >> area;
	cout<<"Years spend in jail: ";
	int years;
	cin >> years;
	string DNA;
	cout<<"DNA sequence: ";
	cin>>DNA;
  	
  	//input record into file
	file<<endl<<register_no<<"\t\t\t"<<name<<"\t\t\t"<<age<<"\t\t\t"<<crime_commit<<"\t\t\t"<<level;
	file<<"\t\t\t"<<area<<"\t\t"<<years<<"\t\t"<<DNA;
	file.close();
}

//case 2
void print_all_data(){
	fstream file2;
 	string line;
    // Opening file in input mode
    file2.open("srime.txt", ios::in|ios::binary);
	while(!file2.eof()){
		getline(file2,line);
		cout<<line<<endl;
	}
	file2.close();		
}

//case 3
void linearSearch(){
	//linear search implemented instead of binary search because data in our text file is not sorted
	int r; int flag=0;
	cout<<"\n\t\t\t\tEnter register number of the criminal you want to search for: ";
	cin>>r;
	cout<<endl;
	fstream file("srime.txt",ios::in);
	string line;
	string registerno,name,age,level,crime,area,years,dna;
	getline(file,line);
	getline(file,line);
	int count=0;
	while(getline(file,line)!=NULL){
		count++;
	}
	file.close();
	Node n;
	fstream f("srime.txt",ios::in);
	getline(f,line);
	for(int i=0;i<count;i++){
		f>>registerno;f>>name;f>>age;f>>crime;f>>level;f>>area;f>>years;f>>dna;
		if(stoi(registerno)==r){
			cout<<"\t\t\t\t---Record found---"<<endl<<endl;
			cout<<"REGISTER		NAME			AGE			CRIMES COMMITTED	LEVEL			AREA		YEARS OF JAIL	DNA SEQUENCE"<<endl;
			cout<<registerno<<"\t\t\t"<<name<<"\t\t\t"<<age<<"\t\t\t"<<crime<<"\t\t\t"<<level;
			cout<<"\t\t\t"<<area<<"\t\t"<<years<<"\t\t"<<dna<<endl;
			flag=1;
			break;
		}
	}
	if(flag==0){
		cout<<"\t\t\t\tCriminal record with that register number not found."<<endl;
	}
	f.close();
}

//case 4a
void readIntoBST(){
	fstream f("srime.txt",ios::in);
	string line;
	string registerno,name,age,level,crime,area,years,dna;
	getline(f,line);
	BST *bt = new BST(); //initialize BST
	cout<<"REGISTER		NAME			AGE			CRIMES COMMITTED	LEVEL			AREA		YEARS OF JAIL	DNA SEQUENCE"<<endl;
	while(f>>registerno!=NULL){
		f>>name;f>>age;f>>crime;f>>level;f>>area;f>>years;f>>dna;
		Node *n = new Node();
		n->register_no=stoi(registerno);
		n->name=name;
		n->age=stoi(age);
		n->crime_commit=crime;
		n->level=stoi(level);
		n->area=area;
		n->years=stoi(years);
		n->DNA=dna;
		bt->addNode(n);
	}
	bt->printInorder(bt->root);	
	cout<<endl;
	f.close();
}

//case 4b
void readIntoLL(){
	fstream f("srime.txt",ios::in);
	string line;
	string registerno,name,age,level,crime,area,years,dna;
	getline(f,line);
	SinglyLinkedList s;	//initiliaze single linked list
	while(f>>registerno!=NULL){
		f>>name;f>>age;f>>crime;f>>level;f>>area;f>>years;f>>dna;
		Node *n = new Node();
		n->register_no=stoi(registerno);
		n->name=name;
		n->age=stoi(age);
		n->crime_commit=crime;
		n->level=stoi(level);
		n->area=area;
		n->years=stoi(years);
		n->DNA=dna;
		s.appendNode(n);
	}
	s.insertionSort();
	s.printList();
	cout<<endl;
	f.close();
}

//case 5
void compareDNA(){
	
	int r1, r2, flag1=0, flag2=0, count=0;
	string dna1, name1, dna2, name2;
	fstream file("srime.txt",ios::in);
	string line;
	string registerno,name,age,level,crime,area,years,dna;
	getline(file,line);
	getline(file,line);
	while(getline(file,line)!=NULL){
		count++;
	}
	file.close();
	cout<<"\n\t\t\t\tEnter register number of criminal 1: ";
	cin>>r1;
	cout<<endl;
	//find record of criminal 1 in the file and store his DNA
	fstream f1("srime.txt",ios::in);
	getline(f1,line);
	for(int i=0;i<count;i++){
		f1>>registerno;f1>>name1;f1>>dna1;f1>>dna1;f1>>dna1;f1>>dna1;f1>>dna1;f1>>dna1;
		if(stoi(registerno)==r1){
			flag1=1;
			break;
		}
	}
	if(flag1==0){
		cout<<"\t\t\t\tCriminal record with that register number not found."<<endl;
		return;
	}
	f1.close();
	cout<<"\n\t\t\t\tEnter register number of criminal 2: ";
	cin>>r2;
	cout<<endl;
	//find record of criminal 1 in the file and store his DNA
	fstream f2("srime.txt",ios::in);
	getline(f2,line);
	for(int i=0;i<count;i++){
		f2>>registerno;f2>>name2;f2>>dna2;f2>>dna2;f2>>dna2;f2>>dna2;f2>>dna2;f2>>dna2;
		if(stoi(registerno)==r2){
			flag2=1;
			break;
		}
	}
	if(flag2==0){
		cout<<"\t\t\t\tCriminal record with that register number not found."<<endl;
		return;
	}
	f2.close();
	
	int gap_penalty = 2;

    /* 
     * alpha[i][j] = penalty for matching the ith alphabet with the
     *               jth alphabet.
     * Here: Penalty for matching an alphabet with anoter one is 1 
     *       Penalty for matching an alphabet with itself is 0
     */
    int alpha[alphabets][alphabets];
    cout<<"MATRIX SCORES: "<<endl;
    for (size_t i = 0; i < alphabets; ++i)
    {
        for (size_t j = 0; j < alphabets; ++j)
        {
            if (i == j) alpha[i][j] = 0;
            else alpha[i][j] = 1;
        }
    }

    // Aligned sequences
    string a2, b2;
    int penalty = align(dna1, dna2, gap_penalty, alpha, a2, b2);

    cout << "\t\t\tCriminal 1: " << name1 << "\tDNA:" << dna1 << endl;
    cout << "\t\t\tCriminal 2: " << name2 << "\tDNA:" << dna2 << endl;
    cout << "\t\t\tNeedleman-Wunsch Score: " << penalty << endl;
    cout << "\t\t\tAligned sequences: " << endl;
    cout << "\t\t\t" << a2 << endl;
    cout << "\t\t\t" << b2 << endl;
	

	int score = 100-((penalty*100)/6);
	cout<<"\n\t\t\tthe percentage match for the sample is = "<<score;
	if(score>=90){
		cout<<"\n\t\t\tthere is more than a 90% match"<<endl;
		cout<<"\t\t\t||||||||||||| S A M E   P E R S O N |||||||||||||"<<endl;		
		}
	
}

//function for the loading screen 
void gotoxy(int x,int y)
{
	COORD CRD;
    CRD.X = x;
    CRD.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),CRD);
}

void mainscreen(){
	int x; double y;
	char head1[40]= "F O R E N S I C S  A N A L Y S I S";
	char head2[40]= "F O R";
	char head3[60]= "C R I M I N A L  D N A  P R O F I L I N G";


    system("cls");
    system("COLOR 70"); //COLOR 30
    gotoxy(12,1);
    cout<<"=============================================================================================";
	
	gotoxy(45,6);
    for(x=0; head1[x]!='\0'; x++){
   	
    	cout<<head1[x];

      	for(y=0; y<=9999999; y++)
      	{
      	}
   }
   gotoxy(49,9);
   cout<<"\t    ";
    for(x=0; head2[x]!='\0'; x++){
   	
    	cout<<head2[x];

      	for(y=0; y<=9999999; y++)
      	{
      	}
   }
   gotoxy(27,12);
   cout<<"\t\t  ";
    for(x=0; head3[x]!='\0'; x++){
   	
    	cout<<head3[x];

      	for(y=0; y<=9999999; y++)
      	{
      	}
   }
   
    gotoxy(12,18);
	printf("=============================================================================================\n");
}

const char pass[20]="12345"; //PASSWORD
void admin_window(){
	
	int j;
    char passcode[50];
    int option, o;
	int flag=1;
	
    system("cls");
	gotoxy(20,8);
	cout<<"\tLogin Account";
	gotoxy(20,10);
	gotoxy(20,11);
	cout<<"\tEnter password :"; 
	gotoxy(20,12);
	gotoxy(42,11);
	while( j<10)
	{
	    passcode[j]=getch();
	    char s=passcode[j];
	    if(s==13)
		{ break;
		 } 
	    else cout<<"*";
	    j++;
	}
	passcode[j]='\0';
    if(strcmp(passcode,pass)==0)
	{
		system("cls");
	
	while(flag)
    {
        
        cout<<"\n\n\t";
        
        cout<<"\t\t\t\t\t\tCRIMINAL DATABASE OPTIONS:\n";
        cout<<"\t\t\t\t\t___________________________________________________\n\t";

        cout<<"\n\n\t\t\t\t1. Create Criminal profile";
        cout<<"\n\n\t\t\t\t2. Read All Criminal Data";
        cout<<"\n\n\t\t\t\t3. Search Criminal"; 
        cout<<"\n\n\t\t\t\t4. Print Sorted Data in ascending order"; 
        cout<<"\n\n\t\t\t\t5. Compare DNA By Entering Existing DNA With Sample";
        cout<<"\n\n\t\t\t\t6. Exit\n\t";

        cout<<"\n\n\t\t\t\t Choose Option : ";
        cin>>option;
		
		switch(option){
			case 1:
				createCriminalProfile();
				cout<<endl<<"Press any key to go back";
				getch();
				system("cls");
				break;

			case 2: 
				print_all_data();
				cout<<endl<<"Press any key to go back";
				getch();
				system("cls");
				break;
			
			case 3:
				linearSearch();
				cout<<endl<<"Press any key to go back";
				getch();
				system("cls");
				break;
				
			case 4:
				cout<<"\n\n\t\t\t\t1. Sort data according to the register number of the criminal";
				cout<<"\n\n\t\t\t\t2. Sort data according to the crime level of each criminal\n\n\t\t\t\tchoice: ";	
				cin>>o; 
				cout<<endl;
				if(o==1){
					readIntoBST();
				}
				else if(o==2){
					readIntoLL();
				}
				else{
					cout<<"invalid choice.";
				}
				cout<<endl<<"Press any key to go back";
				getch();
				system("cls");
				break;
				
			case 5:
				compareDNA();
				cout<<endl<<"Press any key to go back";
				getch();
				system("cls");
				break;
			
			case 6:
				flag=0;
				break;
		}
    }
    }
    else
    {
        cout<<endl<<"\t\t\tIncorrect Password";
        getch();
    	admin_window();
    }
}

int main(){
	mainscreen();
	gotoxy(45,20);
    cout<<"Press Any Key To Enter";
    getch();
    admin_window();
}
