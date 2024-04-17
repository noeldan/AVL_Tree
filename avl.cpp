#include<iostream>
#include<fstream>
#include"avl_tree.h"

using namespace std;

//struct node *root;

ofstream out;

int main()
{
	int Option;               // Variable for storing option is chosen
	int temp;                 // Temporary variable for data storage is chosed
 	ifstream in;              // Variable for collecting input data from file is assigned
	struct node *traverse;    // Temporary node structure is assigned
	avl_tree avl;             // AVL tree class is assigned

	
	out.open("output.txt");   // Output file is opened
	
	do
	{
		cout << "Select from the options below\n";
		cout << "1 - Create Tree\n";
		cout << "2 - Insert Data\n";
		cout << "3 - Delete Data\n";
		cout << "4 - Search\n";
		cout << "5 - Traversal\n";
		cout << "6 - Delete Tree\n";
		cout << "7 - Check Balance\n";
		cout << "8 - Exit\n\n";
		cout << "Option = ";
		cin >> Option;	
		
		switch (Option)
		{
			case 1: avl.delete_tree(root);                    // Root tree is deleted
				root = NULL;
				in.open("input.txt");                     // Input file is selected
				          
				while(true)
				{
					in >> temp;
					if(in.eof()) break;               // End of file is checked
					root = avl.insert(root, temp);    // New data is assigned to the tree
					root = avl.balance(root);                // Tree is balanced
				}
				in.close();

				cout << "Create Tree: ";
				out << "Create Tree: ";
				avl.preorder(root);                       // Pre order traversal is performed
				cout << "\n\n";
				out << "\n\n";
				
				break;

			case 2:
				cout << "Data = ";
				out << "Data = ";
				cin >> temp;
				out << temp;
				cout << "\n";
				out << "\n";
				
				root = avl.insert(root, temp);                 // New data is inserted into the tree
				avl.balance(root);                             // Tree is balanced
				
				cout << "Data Inserted: " << temp << "\n";
				out << "Data Inserted: " << temp << "\n";
				
				cout << "\nTree: ";
				out << "\nTree: ";
				
				avl.preorder(root);                            // Pre order traversal is performed
				cout << "\n\n";
				out << "\n\n";
				
				break;			

			case 3: 
				if(root == NULL)                                    // Condition is checked for empty tree
				{
					cout << "Node cannot be deleted. Empty Tree!\n\n";
					out << "Node cannot be deleted. Empty Tree!\n\n";
				}
				else
				{
					cout << "Enter the data to be deleted = ";
					out << "Enter the data to be deleted = ";
					cin >> temp;
					out << temp;
					
					root = avl.deletion(root, temp);            // Data entered is deleted from the tree
					
					cout << "\nTree: ";
					out << "\nTree: ";
					avl.preorder(root);                         // Pre order traversal is performed
						
					cout << "\n\n";
					out << "\n\n";
				}
				break;

			case 4:
				if(root == NULL)                       // Condition is checked for empty tree
				{
					cout << "Tree is empty.\n\n";
					out << "Tree is empty.\n\n";
				}
				else
				{
					cout << "\nTree: ";
					out << "\nTree: ";
					
					avl.preorder(root);            // Pre order traversal is performed
					cout << "\n";
					out << "\n";
					
					cout << "Data = ";
					out << "Data = ";
					
					cin >> temp;
					out << temp;
					cout << "\n\n";
					out << "\n\n";
					
					avl.search(root, temp);        // Given data is searched in the tree
				}
				break;
			

			case 5:
				if(root == NULL)                                   // Condition is checked for empty tree
				{
					cout << "Tree is empty.\n\n";
					out << "Tree is empty.\n\n";
				}
				else
				{
					cout << "Enter from options\n";
					cout << "1 - Pre_order\n";
					cout << "2 - Post_order\n";
					cout << "3 - In_order\n";
					cout << "Option = ";				
					cin >> temp;
					switch (temp)
					{
						case 1: 
							cout << "Pre_order: ";
							out << "Pre_order: ";
							avl.preorder(root);        // Pre order traversal is performed
							cout << "\n\n";
							out << "\n\n";
							break;

						case 2: 
							cout << "Post_order: ";
							out << "Post_order: ";
							avl.postorder(root);       // Post order order traversal is performed
							cout << "\n\n";
							out << "\n\n";
							break;
					
						case 3: 
							cout << "In_order: ";
							out << "In_order: ";
							avl.inorder(root);         // In order traversal is performed
							cout << "\n\n";
							out << "\n\n";
							break;

						default:
							cout << "Wrong Choice";
							out << "Wrong Choice";
							break;
					}
				}
					break;

			case 6:
				if(root == NULL)                         // Condition is checked for empty tree
				{
					cout << "Tree is empty.\n\n";
				}
				else
				{
					cout << "Delete Tree: ";
					out << "Delete Tree: ";
					avl.delete_tree(root);           // Entire tree is deleted
					root = NULL;
					cout << "Tree Deleted\n\n";
					out << "Tree Deleted\n\n";
					
				}
				break;

			case 7:
				if(root == NULL)                         // Condition is checked for empty tree
				{
					cout <<	"Tree is empty\n\n";
					out <<	"Tree is empty\n\n";
				}
				else			
				{
					cout << "Check Balance = " << avl.check_balance(root) << "\n\n";      // Balance of the tree is determined
					out << "Check Balance = " << avl.check_balance(root) << "\n\n";
				}
				break;

			case 8:
				avl.delete_tree(root);           // Entire tree is deleted
				cout << "Exit\n";
				out << "Exit\n";
				break;

			default:
				cout << "Wrong Choice\n\n";
				out << "Wrong Choice\n\n";
				break;			
		}

	


	}while(Option != 8);	

	in.close();
	out.close();
	return 0;
}	
	

