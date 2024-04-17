using namespace std;

/**** Declaration of the node structure ****/
struct node{
 	int data;                       // Data variable stores the value of the node
 	struct node *left;              // Pointer pointing to the left node
 	struct node *right;		// Pointer pointing to the right node
}*root;


extern ofstream out;


/**** avl_tree class declaration and declaration of functions for AVL tree operations****/
class avl_tree{
	public:
		node* insert(node *, int);
		node* deletion(node *, int);
		void delete_tree(node *);
		void search(node *, int);
		node* replace_left(node*);
		node* replace_right(node*);
		
		node* balance(node *);
		int check_balance(node *);
		int height(node *);
		
		void display(node *,int);
		void preorder(node *);
		void inorder(node *);
		void postorder(node *);
		
		node* leftleft_rotation(node *);
		node* rightright_rotation(node *);
		node* leftright_rotation(node *);
		node* rightleft_rotation(node *);
};


/**** insert() function inserts a new node into the existing AVL tree or also can initiate a new tree ****/
node *avl_tree::insert(node *traverse, int data)
{
	if(traverse == NULL)                            // Checks whether the assigned pointer is empty
	{
		traverse = new node;                    // New node is created and assigned to the pointer
		traverse->data = data;                  // Data is assigned to the node
		traverse->left = NULL;                  // Left pointer of the node is assigned as a NULL pointer
		traverse->right = NULL;                 // Right pointer of the node is assigned as a NULL pointer
		return traverse;                        // The new node pointer is returned to the calling function
	}
	else if(data < traverse->data)                           // Checks whether the data is smaller than the existing node data
	{
		traverse->left = insert(traverse->left, data);   // Recursively calls the insert function by assigning the left pointer
		traverse = balance(traverse);                    // Checks the balance from the current node
		
	}
	else if(data > traverse->data)                               // Checks whether the data is greater than the existing node data 
	{
		traverse->right = insert(traverse->right, data);     // Recursively calls the insert function by assigning the right pointer
		traverse = balance(traverse);                        // Checks the balance from the current node
	}
	else                                                         // This condition exists if the node data is already present
	{
		cout << "The data "<< traverse->data << " entered already exists.\n";          
		out << "The data "<< traverse->data << " entered already exists.\n";          
	}
	
	return traverse;
}


/**** replace_right() function gives location the rightmost node ****/
node* avl_tree::replace_left(node *traverse)
{
	node *temp;                         // Assigns a temporary node
	
	temp = traverse->left;              // Assigns the left node to the temporary node
	
	while(temp->right)                  // Checks whether the right node pointer is empty
	{
		temp = temp->right;         // Assigns the right node to the temporary node
	}
	
	return temp;                        // Returns the final assigned pointer to the calling function
}


/**** replace_left() function gives location the leftmost node ****/
node* avl_tree::replace_right(node *traverse)
{
	node *temp;                         // Assigns a temporary node
	
	temp = traverse->right;             // Assigns the right node to the temporary node
	
	while(temp->left)                   // Checks whether the left node pointer is empty
	{
		temp = temp->left;          // Assigns the left node to the temporary node
	}
	
	return temp;                        // Returns the final assigned pointer to the calling function
}


/**** deletion() function deletes a node from the existing tree ****/
node* avl_tree::deletion(node *traverse, int data)
{
	if(traverse == NULL)                                         // Checks whether the assigned pointer is empty 
	{                                                                // in order to determine whether the daata is 
		cout << "\nNode cannot be found. Deletion cannot be performed\n";                 // present in the tree or not
		out << "\nNode cannot be found. Deletion cannot be performed\n";
		return traverse;                                     // Returns the assigned pointer
	}
	
  	if(data < traverse->data)                                    // Checks whether data is smaller than the existing node data
	{
		traverse->left = deletion(traverse->left, data);     // Recursively calls the deletion function by assigning the left node pointer
	}
	else if(data > traverse->data)                               // Checks whether data is greater than the existing node data
	{
		traverse->right = deletion(traverse->right, data);   // Recursively calls the deletion function by assigning the right node pointer
	}	
	else                                                         // This condition is accessed if the data is equal to the existing node data
	{
		
		if(!(traverse->left && traverse->right))             // This condition is accessed if one or both the pointers are NULL pointers
		{
			if(traverse->left)                           // The main node is assigned the left child node 
				traverse = traverse->left;           
			else if(traverse->right)
				traverse = traverse->right;          // The main node is assignd the right child node
			else
				traverse = NULL;                     // The main node is made a empty node
		}
		else                                                                        // This condition is accessed if both the the child nodes
		{                                                                               // are not NULL pointers 
			if(check_balance(traverse) > 0)                                     // Checks whether the left child node has a greater height
			{
				node *temp = replace_left(traverse);                        // The temporary node is assigned the leftmost node with data
				traverse->data = temp->data;                                // The current node data is updated with leftmost node data
				traverse->left = deletion(traverse->left, temp->data);      // The leftmost node is deleted
			}
			else                                                                // Checks whether the right child node has a greater height
			{
				node *temp = replace_right(traverse);                       // The temporary node is assigned the rightmost node with data
				traverse->data = temp->data;                                // The current node data is updated with rightmost node data
				traverse->right = deletion(traverse->right, temp->data);    // The rightmost node is deleted
			}		
		}
	}
	
	if(traverse == NULL)
		return traverse;
	  
	traverse = balance(traverse);     // The current node is balanced
	
	return traverse;
}


/**** delete_tree() function deletes the entire existing tree ****/
void avl_tree::delete_tree(node *traverse)
{
	if(traverse != NULL)                           // Checkes whether the current node is a NULL pointer
	{
		delete_tree(traverse->left);           // Recursively calls the left subtree
		delete_tree(traverse->right);          // Recursively calls the right subtree
		delete traverse;                       // Deletes the current node
	}
}


/**** height() function outuputs the height at which the node is located ****/
int avl_tree::height(node *traverse)
{
	int h = 0;                                             // Assigns the variable for the height of the tree
	int left_height;                                       // Assigns the variable for the height of the left sub tree
	int right_height;                                      // Assigns the variable for the height of the right sub tree

	if(traverse != NULL)                                   // Checks whether the current node is a Null pointer
	{
		left_height = height(traverse->left);          // Recursively calls the height function to determine the height of left subtree
		right_height = height(traverse->right);        // Recursively calls the height function to determine the height of right subtree
		h = max(left_height, right_height) + 1;	       // The maximum height out of left and right subtree is chosen as the tree height
	}	

	return h;                                              // The height is returned to the calling function 
}


/**** search() function searches for the given node and gives height at which it is present ****/
void avl_tree::search(node *traverse, int data)
{
	if(traverse != NULL)                                   // Checks whether the current node is a Null pointer
	{
		if(traverse->data == data)                     // Checks whether the current data is equal to the node data
		{
			int h = height(traverse);	       //  The height of the tree is determined
			cout << "Data: " << data << "\n";
			cout << "Height: " << h << "\n\n";
			out << "Data: " << data << "\n";
			out << "Height: " << h << "\n\n";
		}

		if (data < traverse->data)
		{
			search(traverse->left, data);          // Recursively enters left sub tree        
		}
		else
		{
			search(traverse->right, data);         // Recursively enters right sub tree
		} 
	}
}


/**** preorder() function outputs the data in node left right order ****/
void avl_tree::preorder(node *traverse)
{
	if(traverse != NULL)                         // Checks whether the current node is a Null pointer
	{	
		cout << traverse->data << " ";       // Prints the data value
		out << traverse->data << " ";
		preorder(traverse->left);            // Recursively calls the function by assigning the left subtree
		preorder(traverse->right);	     // Recursively calls the function by assigning the right subtree
	}
}


/**** inorder() function outputs the data in left node right order ****/
void avl_tree::inorder(node *traverse)
{
	if(traverse != NULL)
	{
		inorder(traverse->left);             // Recursively calls the function by assigning the left subtree
		cout << traverse->data << " ";       // Prints the data value
		out << traverse->data << " ";
		inorder(traverse->right);            // Recursively calls the function by assigning the right subtree
		
	}
}


/**** postorder() function outputs the data in left right node order ****/
void avl_tree::postorder(node *traverse)
{
	if(traverse != NULL)
	{
		postorder(traverse->left);           // Recursively calls the function by assigning the left subtree
		postorder(traverse->right);          // Recursively calls the function by assigning the right subtree
		cout << traverse->data << " ";       // Prints the data value
		out << traverse->data << " ";
	}
}


/**** leftleft_rotation() function performs for left left rotation operation ****/
node* avl_tree::leftleft_rotation(node *traverse)
{
	node* top;                                   // New parent node is assigned
	
	top = traverse->left;                        // Left sub node is assigned to new node
	traverse->left = top->right;                 // Right temporary sub node is assigned to the parent left node
	top->right = traverse;                       // Parent node is assigned to the new parent right node
	
	return top;
}


/**** rightright_rotation() function performs for right right rotation operation ****/
node* avl_tree::rightright_rotation(node *traverse)
{
	node* top;                                   // New parent node is assigned

	top = traverse->right;                       // Right sub node is assigned to new node
	traverse->right = top->left;                 // Left temporary sub node is assigned to the parent right node
	top->left = traverse;                        // Parent node is assigned to the new parent left node
	
	return top;
}


/**** leftright_rotation() function performs for left right rotation operation ****/
node* avl_tree::leftright_rotation(node *traverse)
{
	node* top;                                   // New parent node is assigned

	top = traverse->left;                        // Left sub node is assigned to new node
	traverse->left = rightright_rotation(top);   // Right right rotation is performed on new node and assigned to parent left node
	return leftleft_rotation(traverse);          // Left left rotation is performed on the parent node and assigned new parent right node
}


/**** rightleft_rotation() function performs for right left rotation operation ****/
node* avl_tree::rightleft_rotation(node * traverse)
{
	node* top;                                   // New parent node is assigned

	top = traverse->right;                       // Right sub node is assigned to new node
	traverse->right = leftleft_rotation(top);    // Left left rotation is performed on new node and assigned to parent right node
	return rightright_rotation(traverse);        // Right right rotation is performed on the parent node and assigned new parent left node
}


/**** check_balance() function outputs the difference of the heights of the left and right nodes ****/
int avl_tree::check_balance(node *traverse)
{
	int diff;
	diff = height(traverse->left) - height(traverse->right);    // Left subtree and right subtree heights are obtained the balance of the node is deteremined
	return diff;
}


/**** balance() function balances the existing node to keep the AVL tree order ****/
node* avl_tree::balance(node *traverse)
{
	int balance;                                                // Variable to check balance is assigned
	int sub_balance;

	balance = check_balance(traverse);                          // Balance of the tree is determined

	if(balance > 1)                                             // Condition for left subtree is performed
	{
		sub_balance = check_balance(traverse->left);        // Left tree balance is checked
		if(sub_balance > 0)
		{
			traverse = leftleft_rotation(traverse);     // Left left rotation is performed on node
		}
		else
		{
			traverse = leftright_rotation(traverse);    // Left right rotation is performed on node
		}
	}
	else if(balance < -1)                                       // Condition for right subtree is performed
	{
		sub_balance = check_balance(traverse->right);       // Right tree balance is checked
		if(sub_balance > 0)
		{
			traverse = rightleft_rotation(traverse);    // Right left rotation is performed on the node
		}
		else
		{
			traverse = rightright_rotation(traverse);   // Right right rotation is performed on the node
		}
	}
	
	return traverse;                                            // Balanced node is returned
}

