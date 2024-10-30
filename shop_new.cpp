#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct nodeList
{
	int code;
	string product;
	string brand;
	int amount;
	float price;
	nodeList* next;
};

class List
{
	private:
		nodeList* head;
		nodeList* tail;
		int num_list;
	
	public:
		List();
		void mainMenuStock();
		void addItem(int co, string pro, string brd, int total, float p);
		void display();
		void sortList();
		void searchListCODE();
		nodeList* mid_node(nodeList* start, nodeList* end);
		nodeList* binarySearch(int co);
		void searchListPRO(string pro);
		void update(nodeList* temp);
		void deItem(int key);
};

List::List()
{
	head = NULL;
	tail = NULL;
	num_list = 0;
}

void List::mainMenuStock()
{
	int choice;
	int i;	
	int co;
	int no;
	int key;
	int total;
	float p;
	string name;
	string brd;
	string pro;
	
	cout << endl;
	
	cout << ":::::::: Stock Management System ::::::::\n\n";
	
	cout << "        1. Display all product\n";
	cout << "        2. Add product to stock\n";
	cout << "        3. Search in stock\n";
	cout << "        4. Delete a product\n";
	cout << "        5. Exit\n";

	cout << "\nEnter your choice: ";
	cin >> choice;
	
	switch(choice)
	{
		case 1:
			cout << "\nSort\n";
			sortList();
			display();
			cout << "\nTotal product in the stock: " << num_list;
			break;
		case 2:
			cout << "\n..............Adding a product..............\n";
			cout << "Enter code: ";
			cin >> co;
			cout << "Enter product: ";
			cin.ignore();
			getline(cin, pro);
			cout << "Enter brand: ";
		//	cin.ignore();
			getline(cin, brd); 
			cout << "Enter product's amount: ";
			cin >> total;
			cout << "Enter price: ";
			cin >> p;
			addItem(co, pro, brd, total, p);
			cout << "\nThe product " << pro << ", " << brd << " with code " << co
				 << " successfully added!\n";
			break;	
		case 3:
			cout << "\nSearch in stock\n";
			cout << "1. by code\n";
			cout << "2. by product\n";
			cout << "3. Exit\n";
			cout << "\nOption: ";
			cin >> i;
			if(i == 1)
				searchListCODE();
			if (i == 2)
			{
				cout << "Enter product to search : ";
				cin.ignore();
				getline(cin, name);
				searchListPRO(name);
			}
			break;
		case 4:
			cout << "\nEnter code product to delete: ";
			cin >> key;
			deItem(key);
			break;	
		case 5:
			exit(1);
		default:
			cout << "Invalid choice! Please enter again";			
	}
}

void List::addItem(int co, string pro, string brd, int total, float p)
{
	nodeList* newNode = new nodeList();
	
	newNode->code = co;
	newNode->product = pro;
	newNode->brand = brd;
	newNode->amount = total;
	newNode->price = p;
	newNode->next = NULL;
	
	if(head == NULL && tail == NULL)
	{   
		head = newNode;   
		tail = newNode;
	}
	else 
	{
		tail->next = newNode;
		tail = tail->next;
	}
	num_list++;
}

void List::display()
{
	nodeList* ptr = head;
	if(head == NULL)
	{
		cout << "Empty list\n";
		return;
	}
	else
	{
		cout << "-----------------------------------------------------------------------\n";
		cout << setw(5) << "CODE" << setw(22) << "Product" << setw(15) << "Brand"
			 << setw(13) << "Amount" << setw(13) <<"Price(RM)" << endl;
		cout << "-----------------------------------------------------------------------\n";
		while(ptr != NULL)
		{
			cout.setf(ios::fixed);
			cout.setf(ios::showpoint);
			cout.precision(2);
			cout << setw(5) << ptr->code << setw(22) << ptr->product << setw(15)
			 	 << ptr->brand << setw(13) << ptr->amount << setw(10) << ptr->price;
	 		cout << endl;
			ptr = ptr->next;
		}		
	}	
}

void List::sortList()
{
	nodeList* temp = new nodeList();
	nodeList* ptr = NULL;
	nodeList* index = NULL;
	if (head == NULL)
		return;
	else
	{
		int opt;
	
		cout << "1. by code\n";
		cout << "2. alphabetically\n";
		cout << "\nOption: ";
		cin >> opt;
		
		for(ptr = head; ptr->next != NULL; ptr = ptr->next)
		{
			for(index = ptr->next; index != NULL; index = index->next)
			{
				if(opt == 1)
				{
					if(ptr->code > index->code)
					{
						temp->code = ptr->code;
						temp->product = ptr->product;
						temp->brand = ptr->brand;
						temp->amount = ptr->amount;
						temp->price = ptr->price;
					
						ptr->code = index->code;
						ptr->product = index->product;
						ptr->brand = index->brand;
						ptr->amount = index->amount;
						ptr->price = index->price;
					
						index->code = temp->code;
						index->product = temp->product;
						index->brand = temp->brand;
						index->amount = temp->amount;
						index->price = temp->price;
					}
			
				}
				else if(opt == 2)
				{
					if(ptr->product > index->product)
					{
						temp->code = ptr->code;
						temp->product = ptr->product;
						temp->brand = ptr->brand;
						temp->amount = ptr->amount;
						temp->price = ptr->price;
					
						ptr->code = index->code;
						ptr->product = index->product;
						ptr->brand = index->brand;
						ptr->amount = index->amount;
						ptr->price = index->price;
					
						index->code = temp->code;
						index->product = temp->product;
						index->brand = temp->brand;
						index->amount = temp->amount;
						index->price = temp->price;
					}
				}
				else
					cout << "Invalid option!\n";		
			}
		}
	}
}

nodeList* List::mid_node(nodeList* start, nodeList* end)
{
	if(start == NULL)
		return NULL;
	nodeList* slow = start;
	nodeList* fast = start->next;
	while(fast != end)
	{
		fast = fast->next;
		if(fast != end)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	return slow;
} 

nodeList* List::binarySearch(int co)
{
	nodeList* start = head;
	nodeList* end = NULL;
	do
	{
		nodeList* mid = mid_node(start, end);	
		if(mid == NULL)	 
			return NULL;
		if(mid->code == co)
			return mid;
		else if(mid->code < co)
			start = mid->next;	
		else
			end = mid;
	}while(end == NULL || end != start);
	return NULL;
}
//binary search only can be used in sorted element, so before search by code should always do sorting first
void List::searchListCODE()
{
	int no;
	int n;
	cout << "Enter code to search for product: ";
	cin >> no;

	if(binarySearch(no) == NULL)
	{
		cout <<"Not found!";
	}
	else
	{
		nodeList* ptr;
		ptr = binarySearch(no);
		
		cout << "-----------------------------------------------------------------------\n";
		cout << setw(5) << "CODE" << setw(22) << "Product" << setw(15) << "Brand"
			 << setw(13) << "Amount" << setw(13) <<"Price(RM)" << endl;
		cout << "-----------------------------------------------------------------------\n";
		
		cout.setf(ios::fixed);
		cout.setf(ios::showpoint);
		cout.precision(2);
		cout << setw(5) << ptr->code << setw(22) << ptr->product << setw(15)
			 << ptr->brand << setw(13) << ptr->amount << setw(10) << ptr->price;
		cout << endl;
		cout << "\nYou can - 1. Update\n"	
			 << "          2. Exit\n";
				
		cout << "Option: ";
		cin >> n;
				
		switch(n)
		{
			case 1:
				update(ptr);
				break;
			case 2:
				break;
			default:
				cout << "Invalid option!\n";
		}	
	}
}

void List::searchListPRO(string pro)
{
	nodeList* temp;
	temp = head;
	int flag;
	int n;
	if(head == NULL)
		cout << "Empty. No item to search\n";
	else
	{
		cout << "-----------------------------------------------------------------------\n";
		cout << setw(5) << "CODE" << setw(22) << "Product" << setw(15) << "Brand"
			 << setw(13) << "Amount" << setw(13) <<"Price(RM)" << endl;
		cout << "-----------------------------------------------------------------------\n";
		while(temp != NULL)
		{
			if(temp->product == pro)
			{
				flag = 0;
				cout.setf(ios::fixed);
				cout.setf(ios::showpoint);
				cout.precision(2);
				cout << setw(5) << temp->code << setw(22) << temp->product << setw(15)
			 	   	 << temp->brand << setw(13) << temp->amount << setw(10) << temp->price;
		       	cout << endl;	
		       	cout << "\nYou can - 1. Update\n"	
					 << "          2. Exit\n";
				
				cout << "Option: ";
				cin >> n;
				
				switch(n)
				{
					case 1:
						update(temp);
						break;
					case 2:
						break;
					default:
						cout << "Invalid option!\n";
				}
			}
			else
				flag++;
		
			temp = temp->next;
		}
			if(flag >= num_list)
				cout << "\nNot found!";	
	}
}
 
void List::update(nodeList* temp)
{
	int opt;
	do
	{
		cout << endl;
		cout << "Update - 1.Code   2. Product   3. Brand   4. Amount   5. Price   6. Exit\n";
		cout <<"\nOption: ";
		cin >> opt;
		
		switch(opt)
		{
			case 1: 
				cout << "\nUpdate code : ";
				cin >> temp->code;
				cout << endl;
				cout << setw(5) << temp->code << setw(20) << temp->product << setw(15)
			 	   	 << temp->brand << setw(13) << temp->amount << setw(10) << temp->price;
		       	cout << endl;
				break;
			case 2:
				cout << "\nUpdate product : ";
				cin.ignore();
				getline(cin, temp->product);
				cout << endl;
				cout << setw(5) << temp->code << setw(20) << temp->product << setw(15)
			 	   	 << temp->brand << setw(13) << temp->amount << setw(10) << temp->price;
		       	cout << endl;
				break;
			case 3:
				cout << "\nUpdate brand : ";
				cin.ignore();
				getline(cin, temp->brand);
				cout << endl;
				cout << setw(5) << temp->code << setw(20) << temp->product << setw(15)
			 	   	 << temp->brand << setw(13) << temp->amount << setw(10) << temp->price;
		       	cout << endl;
				break;
			case 4:
				cout << "\nUpdate amount : ";
				cin >> temp->amount;
				cout << endl;
				cout << setw(5) << temp->code << setw(20) << temp->product << setw(15)
			 	   	 << temp->brand << setw(13) << temp->amount << setw(10) << temp->price;
		       	cout << endl;
				break;
			case 5:
				cout << "\nUpdate price : ";
				cin >> temp->price;
				cout << endl;
				cout << setw(5) << temp->code << setw(20) << temp->product << setw(15)
			 	   	 << temp->brand << setw(13) << temp->amount << setw(10) << temp->price;
		       	cout << endl;
				break;
			case 6:
				break;
			default:
				cout << "Invalid option!\n";	
		}
	}while(opt != 6);	
}

void List::deItem(int key)
{
	nodeList* temp = head;
	nodeList* prev = NULL;
	if(temp != NULL && temp->code == key)
	{
		head = temp->next;
		delete temp;
		return;
	}
	else
	{	//keep searching until reach the key
		while(temp != NULL && temp->code != key)
		{
			prev = temp;
			temp = temp->next;
		}
		if(temp == NULL)
		{
			cout << "\nCode not found\n";
			return;
		}
		cout << "Deleting..................\n";
		cout << "The product " << temp->product << ", " << temp->brand 
			 <<" with code " << temp->code; 	
		prev->next = temp->next;
		delete temp;
		cout << " delete successful!\n";
		num_list--;
	}	
}
		 
		 
struct nodeQ{
	string nameQ;
	int dayQ;
	nodeQ* link;
};

class jobQ{
	private:
		nodeQ* front;
		int t_num;
		
	public:
		jobQ();
		void insert(int day, string name);
		void deQueue();
		void browse();
		void searchName();
		void searchDay();
		void modifyQ();
		void mainMenuSche();
};

jobQ::jobQ()
{
	front = NULL;
	t_num = 0;
}

void jobQ::mainMenuSche()
{
	int option;
	int ans;
	int s_option;
	string n;
	int d;

		cout << endl;
		cout << "::::::: Schedule Management System ::::::\n\n";
		cout << "        1.   Browse schedule\n";
		cout << "        2. Insert to schedule\n";
		cout << "        3. Search in schedule\n";
		cout << "        4. Delete a schedule\n";
		cout << "        5.      Modify\n";
		cout << "        6.       Exit\n";
		cout << "\nOption: ";
		cin >> option;
	
		switch (option)
		{
			case 1:
				browse();
				break;
			case 2:
				cout << "\n..................Adding a schedule.................\n";
				cout << "1 - Monday, 2 - Tuesday, 3 - Wednesday, 4 - Thursday\n";
				cout << "5 - Friday, 6 - Saturday, 7 - Sunday\n";
				cout << "\nEnter name: ";
				cin.ignore();
				getline(cin, n);
				cout << "\nEnter work's day: ";
				cin >> d;
				insert(d, n);
				break;
			case 3:
				cout << "\nSearch in shcedule\n";
				cout << "1. by name\n";
				cout << "2. by day\n";
				cout << "\nOption: ";
				cin >> s_option;
				if(s_option == 1)
					searchName();			
				else if(s_option == 2)
					searchDay();
				else
					cout << "Invalid option!\n";
				break;
			case 4:
				deQueue();
				break;
			case 5:
				modifyQ();
				break;
			case 6:
				exit(1);	
			default:
				cout << "INVALID OPTION\n";	
		}		
}

void jobQ::insert(int day, string name)
{
	nodeQ* temp, * ptr;
	temp = new nodeQ();
	temp->nameQ = name;
	temp->dayQ = day;
	if(front == NULL || day < front->dayQ)
	{
		temp->link = front;
		front = temp;	
	}
	else
	{
		ptr = front;
		while (ptr->link != NULL && ptr->link->dayQ <= day)
			ptr = ptr->link;
		temp->link = ptr->link;
		ptr->link = temp;
	}
	t_num++;
}

void jobQ::deQueue()
{
	nodeQ* temp;
	if(front == NULL)
		cout << "Empty. Queue Underflow\n";
	else
	{
		temp = front;
		cout << "Deleting......\n" << "Name : " << temp->nameQ
			 << "       Day : " << temp->dayQ << endl;
		front = front->link;
		free(temp);
		t_num--;
	}
}

void jobQ::browse()
{
	nodeQ* ptr;
	ptr = front;
	if(front == NULL)
		cout << "Empty. No work's day to show\n";
	else
	{
		cout << "\n---------------------------------------\n";
		cout << setw(10) << "NAME" << setw(15) << "Day";
		cout << "\n---------------------------------------\n";
		
		while(ptr != NULL)
		{
			cout << setw(10) << ptr->nameQ << setw(14) << ptr->dayQ;
			cout << endl;
			ptr = ptr->link; 
		}
	}	
}

void jobQ::searchName()
{
	string name;
	int i = 0;
	int flag;	
	
	cout << "Enter name you wish to search: ";
	cin.ignore();
	getline(cin, name);
	
	nodeQ* ptr;
	ptr = front;
	if(front == NULL)
		cout << "Empty queue. No data to search.\n";
	else
	{
		cout << "Searching..............\n";
		cout << setw(5) <<"NAME" << setw(10) << "DAY\n"; 
		while(ptr != NULL)
		{
			if(ptr->nameQ == name)
			{
				flag = 0;

				cout << setw(5) << ptr->nameQ << setw(10) << ptr->dayQ;
				cout << endl;
			}
			else
			{
				flag++;
			}
			ptr = ptr->link;
		}
		if(flag >= t_num)
		{
			cout << "NOT FOUND!";
		}    
	}
	   	
}

void jobQ::searchDay()
{
	int day;
	int flag;	
	
	cout << "Enter day you wish to search: ";
	cin >> day;
	
	nodeQ* ptr;
	ptr = front;
	if(front == NULL)
		cout << "Empty queue. No data to search.\n";
	else
	{
		cout << "Searching..............\n";
		cout << setw(5) <<"NAME" << setw(10) << "DAY\n"; 
		while(ptr != NULL)
		{
			if(ptr->dayQ == day)
			{
				flag = 0;

				cout << setw(5) << ptr->nameQ << setw(10) << ptr->dayQ;
				cout << endl;
			}
			else
			{
				flag++;
			}
			ptr = ptr->link;
		}
		if(flag >= t_num)
		{
			cout << "NOT FOUND!";
		}    
	}   	
}

void jobQ::modifyQ()
{	
	int d;
	string na;
	int flag;	
	
	cout << "Enter name and day you wish to modify- Name: ";
	cin.ignore();
	getline(cin, na);
	cout << "                                     - Day : " ;
	cin >> d;
	
	nodeQ* ptr;
	ptr = front;
	if(front == NULL)
		cout << "Empty queue";
	else
	{
		while(ptr != NULL)
		{
			if(ptr->nameQ == na && ptr->dayQ == d)
			{
				flag = 0;
				cout << "Update name: ";
				cin.ignore();
				getline(cin, ptr->nameQ);
				cout << "Update day: ";
				cin >> ptr->dayQ;
			}
			else
				flag++;
			ptr = ptr->link;	
		}
		if(flag >= t_num)
			cout << "NOT FOUND!"; 
	}	 	
}


int main()
{
	List stock;
	stock.addItem(102, "Bottle", "Rest", 23, 25.8);
	stock.addItem(103, "Bottle", "Puma", 15, 60);
	stock.addItem(101, "Frypan", "Tefal", 15, 55);
	stock.addItem(106, "Dish detergent", "Atomy", 20, 29);
	jobQ sche;
	sche.insert(2, "Ahmad");
	sche.insert(5, "Peter");
	sche.insert(4, "Jessica");
	sche.insert(1, "Ahmad");
	sche.insert(2, "Rain");
	
	cout <<  "\n----- This is shop management system -----\n";	
	int option;
	do
	{
		cout << "\n      <<<<<<<<  MAIN MENU  >>>>>>>>           \n\n";

		cout << "        1. Stock Management\n";
		cout << "        2. Schedule Management\n";
		cout << "        3. Exit\n";

		cout << "\nOPTION: ";
		cin >> option;
	
		if(option == 1)
		{	
			char ans;
			stock.mainMenuStock();
			do
			{
				cout << "\nContinue? (y/n)" 
					 <<"\ny back to sub menu, n back to main menu: ";
				cin >> ans;
				if(ans == 'y')
					stock.mainMenuStock();

			}while(ans != 'n');
		}
		if(option == 2)
		{	
			char ans;
			sche.mainMenuSche();
			do
			{
				cout << "\nContinue? (y/n)" 
					 <<"\ny back to sub menu, n back to main menu: ";
				cin >> ans;	
				if(ans == 'y')
					sche.mainMenuSche();
					
			}while(ans != 'n');
		}
	}while(option != 3);
	
	return 0;
}