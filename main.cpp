#include<bits/stdc++.h>
using namespace std;
class Entry{
	public:
		string word,meaning;
		Entry *parent,*leftChild,*rightChild;
		int height;

		Entry();
		Entry(string,string);
};
Entry::Entry(){
	this->height = 0;
	this->word.push_back('\0');
	this->meaning.push_back('\0');
	this->parent = NULL;
	this->rightChild = NULL;
	this->leftChild = NULL;
}

Entry::Entry(string wordInp,string meaningInp){
	for(int i=0;i<wordInp.size();i++)
		this->word.push_back(wordInp[i]);
	for(int i=0;i<meaningInp.size();i++)
		this->meaning.push_back(meaningInp[i]);
	this->height = 0;
	this->parent = NULL;
	this->rightChild = NULL;
	this->leftChild = NULL;
}
class AVLtree{
	private:
			int size;
			Entry *root;
	public:
			AVLtree();
			~AVLtree();
			int count;
			int getSize();
			int max(int,int);
			int getHeightDif(Entry*);
			Entry* getRoot();
			Entry* newNode(string,string);
			Entry* rotateRight(Entry*);
			Entry* rotateLeft(Entry*);
			void insert(Entry*);
			void remove(string);
			Entry* search(string);
			Entry* findPreSuc(string);
			void showAllInRange(Entry*,string,string);
			void printInOrder(Entry*);
			void printInLevel();
};


AVLtree::AVLtree(){
	this->root = NULL;
	this->size = 0;
	this->count = 0;
}

AVLtree::~AVLtree(){
	if(root == NULL)
		return;
	queue<Entry*> q;
	q.push(root);
	while(!q.empty()){
			if(q.front()->leftChild != NULL)
				q.push(q.front()->leftChild);
			if(q.front()->rightChild != NULL)
				q.push(q.front()->rightChild);
			free(q.front());
			q.pop();
		}
	cout<<"\nProgram terminated succesfully.\n";
}

int AVLtree::getSize(){
	return this->size;
}

int AVLtree::max(int a,int b)
{
	if(a>=b)
		return a;
	else
		return b;
}

int AVLtree::getHeightDif(Entry *e){
	if(e == NULL)
		return 0;
	else if( e->leftChild == NULL && e->rightChild == NULL)
		return 0;
	else if(e->leftChild == NULL)
		return (-1-(e->rightChild->height));
	else if(e->rightChild == NULL)
		return (e->leftChild->height+1);
	else
		return (e->leftChild->height - e->rightChild->height);
}

Entry*  AVLtree::getRoot(){
	return this->root;
}

Entry* AVLtree::newNode(string word, string meaning){
	Entry *ptr = new Entry(word,meaning);
	return ptr;
}

Entry* AVLtree::rotateRight(Entry* y){
	Entry *x = y->leftChild;
	Entry *T2 = x->rightChild;

  x->rightChild = y;
  y->leftChild = T2;
	if(T2!=NULL)
		T2->parent = y;
	y->parent = x;

	if(y->leftChild != NULL && y->rightChild != NULL)
			y->height = 1 + max(y->leftChild->height, y->rightChild->height);
	else if(y->leftChild != NULL)
			y->height = 1 + y->leftChild->height;
	else if(y->rightChild !=NULL)
			y->height = 1 + y->rightChild->height;
	else
			y->height = 0;

  if(x->leftChild != NULL && x->rightChild != NULL)
			x->height = 1 + max(x->leftChild->height, x->rightChild->height);
	else if(x->leftChild != NULL)
			x->height = 1 + x->leftChild->height;
	else if(x->rightChild !=NULL)
			x->height = 1 + x->rightChild->height;
	else
			x->height = 0;

  return x;
}

Entry* AVLtree::rotateLeft(Entry* y){
	Entry *x = y->rightChild;
  Entry *T2 = x->leftChild;

    x->leftChild = y;
    y->rightChild = T2;
		if(T2!=NULL)
			T2->parent = y;
		y->parent = x;

	if(y->leftChild != NULL && y->rightChild != NULL)
			y->height = 1 + max(y->leftChild->height, y->rightChild->height);
	else if(y->leftChild != NULL)
			y->height = 1 + y->leftChild->height;
	else if(y->rightChild !=NULL)
			y->height = 1 + y->rightChild->height;
	else
			y->height = 0;
  if(x->leftChild != NULL && x->rightChild != NULL)
			x->height = 1 + max(x->leftChild->height, x->rightChild->height);
	else if(x->leftChild != NULL)
			x->height = 1 + x->leftChild->height;
	else if(x->rightChild !=NULL)
			x->height = 1 + x->rightChild->height;
	else
			x->height = 0;

    return x;
}

void AVLtree::insert(Entry* e){
	Entry *node = root;
	this->size++;

// Normal BST insertion
	if(root == NULL){
		root = newNode(e->word,e->meaning);
		return;
	}
	int f =1;
	while(f){
			if(node->word < e->word){
				if(node->rightChild == NULL){
					e->parent = node;
					node->rightChild = e;
					f=0;
				}
				else
					node = node->rightChild;
			}
			else if(node->word > e->word){
				if(node->leftChild == NULL){
					e->parent = node;
					node->leftChild = e;
					f=0;
				}
				else
					node = node->leftChild;
			}
			else{
				node->meaning = e->meaning;
				this->size--;
				return;
			}
	}

	// Incresing Height
	node = e->parent;
	while(node != NULL){
		if(node->leftChild != NULL && node->rightChild != NULL)
			node->height = 1 + max(node->leftChild->height, node->rightChild->height);
		else if(node->leftChild != NULL)
			node->height = 1 + node->leftChild->height;
		else if(node->rightChild != NULL)
			node->height = 1 + node->rightChild->height;
		else
			node->height = 0;
		node = node->parent;
	}

	// Balancing Height
	Entry *z,*y,*x,*p;
	z = e->parent;
	y = e;
	x = NULL;
	int heightDiff;
	while(z != NULL){
		heightDiff = getHeightDif(z);
		if((heightDiff > 1) || (heightDiff<(-1))){
			p = z->parent;
			if(z->leftChild == y && y->leftChild == x){
				node = rotateRight(z);
			}
			else if(z->leftChild == y && y->rightChild == x){
				node = rotateLeft(y);
				node->parent = z;
				z->leftChild = node;
				node = rotateRight(z);
			}
			else if(z->rightChild == y && y->rightChild == x){
				node = rotateLeft(z);
			}
			else{
				node = rotateRight(y);
				node->parent = z;
				z->rightChild = node;
				node = rotateLeft(z);
			}
			if(p!=NULL){
				node->parent = p;
				if(p->rightChild == z)
					p->rightChild = node;
				else
					p->leftChild = node;
			}
			else{
				root = node;
				node->parent = NULL;
			}
			node = node->parent;
			while(node != NULL){
				if(node->leftChild != NULL && node->rightChild != NULL)
					node->height = 1 + max(node->leftChild->height, node->rightChild->height);
				else if(node->leftChild != NULL)
					node->height = 1 + node->leftChild->height;
				else if(node->rightChild != NULL)
					node->height = 1 + node->rightChild->height;
				else
					node->height = 0;
				node = node->parent;
			}
		}
		x=y;
		y=z;
		z=z->parent;
	}
}

Entry* AVLtree::findPreSuc(string word){
	Entry *e= search(word);
	if(e != NULL){
		if(e->leftChild !=NULL){
			e = e->leftChild;
			while(e->rightChild !=NULL)
				e=e->rightChild;
			return e;
		}
		else if(e->rightChild !=NULL){
			e = e->rightChild;
			while(e->leftChild !=NULL)
				e=e->leftChild;
			return e;
		}
		else
			return e->parent;
	}
	else
		return NULL;
}

void AVLtree::remove(string word){
	Entry *p,*e = search(word);
	if(e == NULL)
		cout<<"\n No such word found in dictionary !\n";
	else{
		this->size--;

		//Deleting Node
		if(e->leftChild == NULL && e->rightChild == NULL){
			p = e->parent;
			if(p!=NULL){
				if(p->leftChild == e)
					p->leftChild = NULL;
				else
					p->rightChild = NULL;
			}
			else
				root = NULL;
			free(e);
		}
		else if(e->leftChild == NULL){
			p=e->parent;
			if(p != NULL){
				if(p->leftChild == e)
					p->leftChild = e->rightChild;
				else
					p->rightChild = e->rightChild;
			}
			else
				root = e->rightChild;
			free(e);
		}
		else if(e->rightChild == NULL){
			p=e->parent;
			if(p != NULL){
				if(p->leftChild == e)
					p->leftChild = e->leftChild;
				else
					p->rightChild = e->leftChild;
			}
			else
				root = e->leftChild;
			free(e);
		}
		else{
			Entry *temp = findPreSuc(word);
			e->word = temp->word;
			e->meaning = temp->meaning;
			p = temp->parent;
			if(temp->leftChild == NULL && temp->rightChild == NULL){
				if(p!=NULL){
					if(p->leftChild == temp)
						p->leftChild = NULL;
					else
						p->rightChild = NULL;
				}
				else
					root = NULL;
				free(temp);
			}
			else if(temp->leftChild != NULL){
				if(p != NULL){
					if(p->leftChild == temp)
						p->leftChild = temp->leftChild;
					else
						p->rightChild = temp->leftChild;
				}
				else
					root = temp->leftChild;
				free(temp);
			}
			else if(temp->rightChild != NULL){
				if(p != NULL){
					if(p->leftChild == temp)
						p->leftChild = temp->rightChild;
					else
						p->rightChild = temp->rightChild;
				}
				else
					root = temp->rightChild;
				free(temp);
			}
		}

		//Balancing Height
		Entry *z,*y,*x;
		int h,hDiff;
		while(p != NULL){
			h = p->height;
			if(p->leftChild != NULL && p->rightChild != NULL)
					p->height = 1 + max(p->leftChild->height, p->rightChild->height);
				else if(p->leftChild != NULL)
					p->height = 1 + p->leftChild->height;
				else if(p->rightChild != NULL)
					p->height = 1 + p->rightChild->height;
				else
					p->height = 0;
			hDiff = getHeightDif(p);
			if(h == p->height)
				break;
			else if(hDiff <=1 && hDiff>= (-1)){
				p = p->parent;
			}
			else{
				z = p;
				p = p->parent;
				if(z->leftChild != NULL && z->rightChild != NULL){
					if(z->leftChild->height >= z->rightChild->height)
						y = z->leftChild;
					else
						y = z->rightChild;
				}
				else if(z->leftChild != NULL)
					y = z->leftChild;
				else
					y = z->rightChild;
				if(y->leftChild != NULL && y->rightChild != NULL){
					if(y->leftChild->height >= y->rightChild->height)
						x = y->leftChild;
					else
						x = y->rightChild;
				}
				else if(y->leftChild != NULL)
					x = y->leftChild;
				else if(y->rightChild != NULL)
					x = y->rightChild;
				else
					x = NULL;
				Entry *node;
				if(z->leftChild == y && y->leftChild == x){
					node = rotateRight(z);
				}
				else if(z->leftChild == y && y->rightChild == x){
					node = rotateLeft(y);
					node->parent = z;
					z->leftChild = node;
					node = rotateRight(z);
				}
				else if(z->rightChild == y && y->rightChild == x){
					node = rotateLeft(z);
				}
				else{
					node = rotateRight(y);
					node->parent = z;
					z->rightChild = node;
					node = rotateLeft(z);
				}
				if(p!=NULL){
					node->parent = p;
					if(p->rightChild == z)
						p->rightChild = node;
					else
						p->leftChild = node;
				}
				else{
					root = node;
					node->parent = NULL;
				}
			}
		}
		cout<<" Word Removed !\n";
	}
}

Entry* AVLtree::search(string word){
	if(root == NULL)
		return root;
	Entry *node = root;
	while(1){
		if(node == NULL || node->word == word)
				return node;
		else if(node->word < word)
				node = node->rightChild;
		else if(node->word > word)
				node = node->leftChild;
	}
}

void AVLtree::showAllInRange(Entry *e,string w1,string w2){
	if(e==NULL)
		return;
	if(e->word > w1)
		 showAllInRange(e->leftChild,w1,w2);
	if((e->word >= w1) && (e->word <= w2)){
		cout<<e->word<<"  :  "<<e->meaning<<endl;
		this->count++;
	}
	if(e->word < w2)
		showAllInRange(e->rightChild,w1,w2);
}

void AVLtree::printInOrder(Entry *e){
	if(e==NULL)
		return;
	printInOrder(e->leftChild);
	cout<<e->word<<"  :  "<<e->meaning<<endl;
	printInOrder(e->rightChild);
}

void AVLtree::printInLevel(){
	if(root == NULL)
		return;
	queue<Entry*> q;
	q.push(root);
	while(!q.empty()){
		int c = q.size();
		while(c--){
			cout<<q.front()->word<<" ";
			if(q.front()->leftChild != NULL)
				q.push(q.front()->leftChild);
			if(q.front()->rightChild != NULL)
				q.push(q.front()->rightChild);
			q.pop();
		}
		cout<<endl;
	}
}
void mainMenu(AVLtree&);
void addNewWord(AVLtree&);
void removeWord(AVLtree&);
void searchWord(AVLtree&);
void getNumOfWord(AVLtree&);
void showAllInRange(AVLtree&);
void readFileData(AVLtree&);


void mainMenu(AVLtree& avlTree){
	int ch;
	do{
		cout<<"\n  ***** MAIN MENU *****\n\n"
				<<" 1 ) Read file Data\n 2 ) Add new word\n"
				<<" 3 ) Remove a word\n 4 ) Search for a word\n"
				<<" 5 ) Get number of words\n"
				<<" 6 ) Show in range\n 7 ) Print In Order\n 8 ) Print In Level\n"
				<<"Enter your choice : ";
		cin>>ch;
		switch(ch){
			case 1 : readFileData(avlTree);
						break;
			case 2 : addNewWord(avlTree);
						break;
			case 3 : removeWord(avlTree);
						break;
			case 4 : searchWord(avlTree);
						break;
			case 5 : getNumOfWord(avlTree);
						break;
			case 6 : showAllInRange(avlTree);
						break;
			case 7 : avlTree.printInOrder(avlTree.getRoot());
						break;
			case 8 : avlTree.printInLevel();
						break;
			default : cout<<" INVALID CHOICE \n";
		}

	}while(ch>=1 && ch<=8);
}

void readFileData(AVLtree& avlTree){
	Entry *e;
	string word,meaning;
	ifstream fin;
	cout<<"Enter file name : ";
	cin>>word;
	fin.open(word);
	if(!fin.is_open())
		cout<<"\nError in file opening.\n";
	else{
		cout<<"File reading succesful.\n";
		while(fin>>word){
			getline(fin,meaning);
			meaning[0]=' ';
			if(word[0]>='A' && word[0]<='Z')
				word[0]+=32;
			e = new Entry(word,meaning);
			avlTree.insert(e);
		}
	}
	fin.close();
}

void addNewWord(AVLtree& avlTree){
	string word, meaning;
	cout<<"\nEnter word :  ";
	cin>>word;
	cout<<"Enter meaning :  ";
	cin>>meaning;
	Entry *e = new Entry(word,meaning);
	avlTree.insert(e);
	cout<<" Entry added.\n";
}

void removeWord(AVLtree& avlTree){
	string word;
	cout<<"Enter the word to removed :\n";
	cin>>word;
	avlTree.remove(word);
}

void searchWord(AVLtree& avlTree){
	string word;
	cout<<"Enter the word to be searched for :\n";
	cin>>word;
	Entry *e=avlTree.search(word);
	if(e==NULL)
		cout<<" Sorry, No match found !\n";
	else
		cout<<e->word<<"  :  "<<e->meaning<<endl;
}

void getNumOfWord(AVLtree& avlTree){
	cout<<"Total number of words  :  "<<avlTree.getSize()<<endl;
}

void showAllInRange(AVLtree& avlTree){
	string w1,w2;
	cout<<"Enter lower limit of range  :  ";
	cin>>w1;
	cout<<"Enter upper limit of range  :  ";
	cin>>w2;
	avlTree.count=0;
	cout<<endl;
	avlTree.showAllInRange(avlTree.getRoot(),w1,w2);
	cout<<"\n  Total words in range  :  "<<avlTree.count<<endl;
//	avlTree.showAllInRange(avlTree.getRoot(),w1,w2);

}

int main(){
	char choice;
	AVLtree avlTree;
	cout<<"\n===== DICTIONARY =====\n\n";
	cout<<"Read word meaning file ? (y/n)\n";
	cin>>choice;
	if( choice == 'y' || choice == 'Y' ){
		readFileData(avlTree);
		mainMenu(avlTree);
	}
	else
		mainMenu(avlTree);
return 0;
}
