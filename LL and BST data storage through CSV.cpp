#include<iostream>
#include<fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

//created a class dataset to store the incoming data from the CSV file each instance will store one data
class DataSet{
	public:
		string country, item, sChannel, order_Date, ship_Date;
		long order_ID;
		
		//constructor function
		DataSet(){
			country = item = sChannel = order_Date = ship_Date = '\0';
			order_ID = 0;
		}
		
		//to load the data into the program
		void LoadData(vector<string> data){
			country = data[0];
			item = data[1];
			sChannel = data[2];
			order_Date = data[3];
			
			stringstream ss(data[4]);
			ss >> order_ID;
			ship_Date = data[5];
		}
		
		//to display the searched data
		string display(){
			stringstream ss;
			ss << order_ID;
			string orderid = ss.str();
			return country + " , " + item + " , " + sChannel + " , " + order_Date + " , " + orderid + " , " + ship_Date + "\n";
		}
};

//a node to store a instance of dataset, linked list is made of nodes
class Node{
	public:
		DataSet data;
		Node *next, *prev;
		Node(Node *p=NULL, Node *n=NULL){
			next = n;
			prev = p;
		}
};

//linkedlist class
class LinkedList{
	Node *head,*tail;
	public:
		//constructor
		LinkedList(){
			head = tail = NULL;
		}
		//destructor
		~LinkedList(){
			while(!isEmpty()){
				removeHead();
			}
		}
		//empty check
		bool isEmpty(){
			if(head == NULL){
				return true;
			}else{
				return false;
			}
		}
		//to add a head of linked list
		void addHead(DataSet n){
			if(isEmpty()){
				head = new Node(NULL,NULL);
				head->data = n;
				tail = head;
			}else{
				Node *p;
				p = new Node(NULL,NULL);
				p->data = n;
				head->prev = p;
				p->next = head;
				head = p;
			}
		}
		
		//to print the linked list
		void traverse(){
			if(isEmpty()){
				cout << "EMPTY";
			}else{
				for(Node *p =head; p!=NULL; p=p->next){
					cout << p->data.display() << "\t";
				}
			}
		}
		
		//to search in the linked list using orderID
		void search(long n){
			int flag = 0;
			for (Node *p = head; p!=NULL; p= p->next){
				if(p->data.order_ID == n){
					flag++;
					cout << "(LL)Found  - " << p->data.display();
					break;
				}
				
			}
			if(flag==0){
					cout << "(LL)Not found\n";
			}
		}
	//to remove head and to return the stored dataset after deleting head
	DataSet removeHead(){
		if(isEmpty()){
			cout << "LL is empty";
		}else if(head == tail){
			DataSet temp = head->data;
			delete head;
			head = tail = NULL;
			return temp;
		}else{
			DataSet temp = head->data;
			Node *p = head;
			head = head->next;
			delete p;
			head->prev = NULL;
			return temp;
		}
	}
	
};


//Binary Search Tree class
class BST 
{ 
    
    public: 
	    DataSet data; 
	    BST *left, *right; 
	    //constructor
		BST(){
	    	left = NULL;
	    	right = NULL;
		}
		//constructor with parameters
	    BST(DataSet value){
	    	data = value; 
    		left = right = NULL; 
		}
		
		//function to insert the coming dataset
	    BST* Insert(BST *root, DataSet value){
	    	if(!root) 
		    { 
		        return new BST(value); 
		    } 
		    if(value.order_ID > root->data.order_ID) 
		    { 
		        root->right = Insert(root->right, value); 
		    } 
		    else
		    { 
		        root->left = Insert(root->left, value); 
		    } 
		
		    return root; 
		} 
	    
		//function for inorder traversal/printing of BST  
	    void Inorder(BST *root){
	    	if(!root) 
		    { 
		        return; 
		    } 
		    Inorder(root->left); 
		    cout << root->data.display() << endl; 
		    Inorder(root->right); 
		}
		
		//Function to search the data in a BST using orderID
		BST search(BST *root, long key){
			// Base Cases: root is null or key is present at root 
		    if (root == NULL || root->data.order_ID == key){
		    	if(root == NULL){
		    		cout << "(BST)Not Found\n";
				}
				else{
					cout << "(BST)Found - " << root->data.display();
				}
		       return root->data; 
		   	}
		    // Key is greater than root's key 
		    if (root->data.order_ID < key) 
		       return search(root->right, key); 
		  
		    // Key is smaller than root's key 
		    return search(root->left, key); 
		}
}; 


//to convert the coming orderID into a INTEGER for better searching algorithm
vector<string> stringBreaker(string line){
	stringstream ss;
	ss << line;
	vector<string> result;
	while( ss.good() )
	{
	    string substr;
	    getline( ss, substr, ',' );
	    result.push_back( substr );
	}
	return result;
}

//Main driving code
int main(){
	LinkedList dataList;
	BST b, *root = NULL;
	ifstream dataFile;
	dataFile.open("DataSet.csv");
	
	//file open check and data loading into BST and LL
	if (dataFile.is_open())
	{
		string line;
		DataSet  temp;
		getline(dataFile, line);
		temp.LoadData(stringBreaker(line));
		dataList.addHead(temp);
		root =  b.Insert(root, temp);
		while ( getline (dataFile,line) )
	    {	
			temp.LoadData(stringBreaker(line));
			dataList.addHead(temp);
			b.Insert(root, temp);
	    }
		
		cout << "Dataset loaded in both BST and LinkedList\n";
	    dataFile.close();
	}
	//searching code
	long id;
	cout << "Enter Order_ID: ";
	cin >> id;
	
	dataList.search(id);
	b.search(root, id);
}
