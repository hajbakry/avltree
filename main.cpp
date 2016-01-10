/*******************************************************************************/
////////////////////////////// Customer Database ////////////////////////////////
//
// Programmed by: Talal Haj-Bakri
// AVL Tree Implementation by: Talal Haj-Bakri
//
// ************************ IMPORTANT *******************************************
//
// DO NOT compile this code using Microsoft Visual C++.
// The program will NOT work as expected.
//
// Please use the GCC compiler.
// This program was coded and tested on Mac OS X version 10.4.4 using Xcode 2.0
//
/*******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

/*******************************************************************************/
////////////////////////////// Global Declarations //////////////////////////////
/*******************************************************************************/

const static string separator = "________________________________________________________________________________\n";

const static string app_name = "Customer Database";

// A pause message, halts program until users presses the "Enter" key
const static void pause(string message)
{
	cout << message;
	cin.get();
}

const static void clearscreen()
{
	/* Change system message when compiling on different platforms 
	( DOS/Windows: cls , UNIX/Linux/Mac OS X: clear ) */
	system("clear"); 
}

// A generic function to ask the user to confirm an action, returns true if 'y' is entered and false if 'n' is entered  
bool choice(string message)
{
	char choice;
	cout << message;
	do
		choice = getchar();
	while ( choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N' );
	
	if ( choice == 'y' || choice == 'Y' )
		return true;
	return false;
}

// A function to return the maximum of two integers
int get_max_int(int v1, int v2)
{
	if( v1 > v2 )
		return v1;
	else
		return v2;
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


/*******************************************************************************/
//////////////////////////////// CLASS: treenode ////////////////////////////////
/*******************************************************************************/

template <typename keyType, typename dataType>
class AVL_Tree;

template <typename keyType, typename dataType>
class treenode
{

private:
	treenode(); // Constructor

	keyType key;
	dataType data;
	int height;
	
	// pointers to left and right subtrees
	//////////////////////////////////////
	treenode* right;
	treenode* left;
	
public:
	// get() functions
	/////////////////////
	keyType get_key();
	dataType get_data();
	
	friend class AVL_Tree<keyType,dataType>;
};


// treenode(): Constructor
/////////////////////////

template <typename keyType, typename dataType>
treenode<keyType,dataType>::treenode()
{
	right = NULL;
	left = NULL;
	height = -1;
}

// get_key(): Returns key
/////////////////////////

template <typename keyType, typename dataType>
keyType treenode<keyType,dataType>::get_key()
{
	return key;
}

// get_data(): Returns data
///////////////////////////

template <typename keyType, typename dataType>
dataType treenode<keyType,dataType>::get_data()
{
	return data;
}

/*******************************************************************************/
//////////////////////////////// CLASS: AVL_Tree ////////////////////////////////
/*******************************************************************************/

template <typename keyType, typename dataType>
class AVL_Tree
{
private:
	
	treenode<keyType,dataType>* root; // Pointer to root
	int count; // Number of nodes in the tree
	
	// Tree Modification and Searching *********************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	bool tree_insert( treenode<keyType,dataType>* , treenode<keyType,dataType>* ); // Inserts a subtree
	bool tree_remove( treenode<keyType,dataType>* tree, keyType ); // Removes a node
	bool tree_search( treenode<keyType,dataType>* tree, keyType , dataType& ); // Searches for a node
	bool tree_update( treenode<keyType,dataType>* tree, keyType , dataType ); // Updates the data of a node

	// Tree Traversal: Traverses the tree starting from node and passes the output to the output stream/
	///////////////////////////////////////////////////////////////////////////////////////////////////
	
	void in_order_private( treenode<keyType,dataType>* , ostream& );
	void post_order_private( treenode<keyType,dataType>* , ostream& );
	void pre_order_private( treenode<keyType,dataType>* , ostream& );
	
	// Tree Rotation ****************************************************************/
	/////////////////////////////////////////////////////////////////////////////////
	
	treenode<keyType,dataType>* right_rotation( treenode<keyType,dataType>* );
	treenode<keyType,dataType>* left_rotation( treenode<keyType,dataType>* );
	treenode<keyType,dataType>* right_rotation_double( treenode<keyType,dataType>* );
	treenode<keyType,dataType>* left_rotation_double( treenode<keyType,dataType>* );

	// Tree Balancing ******************************************************************/ 
	////////////////////////////////////////////////////////////////////////////////////
	
	// balances the tree by following a search path
	treenode<keyType,dataType>* make_balanced( treenode<keyType,dataType>* , keyType& );
	
	// returns the height of the subtree
	int height( treenode<keyType,dataType>* );

	// returns the balance factor of a subtree
	int balance( treenode<keyType,dataType>* );
	
	// counts the nodes in a subtree
	int count_nodes( treenode<keyType,dataType>* ); 
	
	// Auxiliary Methods ***********************************************/
	////////////////////////////////////////////////////////////////////
	
	// Passes the output of a node to the output stream
	void stream_node( treenode<keyType,dataType>* , ostream& );
	
	// Prints the nodes in a tree form on the screen
	void tree_output( treenode<keyType,dataType>* , int ); 
	
	// finds and returns the minimum node in a subtree
	treenode<keyType,dataType>* find_min( treenode<keyType,dataType>* );
	
	// removes the minimum node in the right subtree and takes its contents to replace it with the root of the subtree
	void remove_min( treenode<keyType,dataType>* );
	
	// removes a node and all its subtrees
	void tree_dispose( treenode<keyType,dataType>* ); 
	
public:
	
	AVL_Tree(); // Constructor
	~AVL_Tree(); // Destructor
	
	// Public Tree Modification and Searching ***************************************************/
	/////////////////////////////////////////////////////////////////////////////////////////////
	
	bool insert( keyType , dataType ); // inserts a node with a new key containing data
	bool remove( keyType ); // removes nodes with the corresponding key
	bool search( keyType, dataType& ); // finds a node and returns the data through the parameter
	bool update( keyType, dataType ); // updates the node with new data
	
	// Public Tree Traversal ***/
	////////////////////////////
	void in_order( ostream& );
	void post_order( ostream& );
	void pre_order( ostream& );
	
	// Public Auxiliary Methods ****************************************/
	////////////////////////////////////////////////////////////////////
	
	void show_tree(); // Prints all the nodes in a tree form
	void clear(); // Deletes all the nodes in the tree
	bool is_empty(); // Checks if the tree is empty
	int get_count(); // Returns the number of nodes in the tree
};

/*****************************************/
//////////// AVL_Tree: Public /////////////
/*****************************************/

//////////////////////////////////////// AVL_Tree() ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

template <typename keyType, typename dataType>
AVL_Tree<keyType,dataType>::AVL_Tree()
{
	root = NULL;
	count = 0;
}

/////////////////////////////////////// ~AVL_Tree() ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

template <typename keyType, typename dataType>
AVL_Tree<keyType,dataType>::~AVL_Tree()
{
	clear();
}

////////////////////////////////////////// insert() ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

template <typename keyType, typename dataType>
bool AVL_Tree<keyType,dataType>::insert( keyType new_key, dataType new_data)
{
	treenode<keyType,dataType>* node = new treenode<keyType,dataType>; // Create new node
	
	node->key = new_key; // Set key in new node
	node->data = new_data; // Set data in new node
	
	bool inserted = tree_insert( root , node ); // Calls the private insert function
	
	if (inserted) // Node inserted?
		++count; // Yes, increment counter
	return inserted;
}

////////////////////////////////////////// remove() ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

template <typename keyType, typename dataType>
bool AVL_Tree<keyType,dataType>::remove( keyType key )
{	
	bool removed;
	dataType nothing; // dummy
	
	if ( search(key, nothing) ) // Is node in the tree? 
		removed = tree_remove( root , key ); // Yes, calls the private remove function
	else removed = false; // No
	
	if (removed) // Node removed?
		--count; // Yes, decrement counter
	return removed;
}

////////////////////////////////////////// update() ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

template <typename keyType, typename dataType>
bool AVL_Tree<keyType,dataType>::update( keyType key , dataType data )
{	
	bool updated = tree_update( root , key, data ); // Calls the private update function
	return updated;
}

////////////////////////////////////////// remove() ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

template <typename keyType, typename dataType>
bool AVL_Tree<keyType,dataType>::search( keyType key , dataType& data )
{	
	bool found = tree_search( root , key, data ); // Calls the private search function
	return found;
}

///////////////////////////////////////// in_order() ///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

template <typename keyType, typename dataType>
void AVL_Tree<keyType,dataType>::in_order( ostream& output )
{
	in_order_private( root , output );
}

//////////////////////////////////////// post_order() //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

template <typename keyType, typename dataType>
void AVL_Tree<keyType,dataType>::post_order( ostream& output )
{
	post_order_private( root , output );
}

//////////////////////////////////////// pre_order() ///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

template <typename keyType, typename dataType>
void AVL_Tree<keyType,dataType>::pre_order( ostream& output )
{
	pre_order_private( root , output );
}

//////////////////////////////////////// show_tree() ///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

template <typename keyType, typename dataType>
void AVL_Tree<keyType,dataType>::show_tree()
{
	tree_output( root, 0 );
}

////////////////////////////////////////// clear() /////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
template <typename keyType, typename dataType>
void AVL_Tree<keyType,dataType>::clear()
{
	tree_dispose( root );
	count = 0;
}

//////////////////////////////////////// is_empty() ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
template <typename keyType, typename dataType>
bool AVL_Tree<keyType,dataType>::is_empty()
{
	return ( root == NULL );
}

//////////////////////////////////////// get_count() ///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

template <typename keyType, typename dataType>
int AVL_Tree<keyType,dataType>::get_count()
{
	return count;
}

/*****************************************/
//////////// AVL_Tree: Private ////////////
/*****************************************/

/////////////////////////////////////// tree_insert() //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Returns true if insertion is successful, false otherwise.

template <typename keyType, typename dataType>
bool AVL_Tree<keyType,dataType>::tree_insert(treenode<keyType,dataType>* tree_start, treenode<keyType,dataType>* tree)
{
	if( is_empty() )
	{
		root = tree; // Insert at root
		return true; // Inserted!
	}
	
	else if( tree_start->key < tree->key )
	{
		// Check right node
		if ( tree_start->right == NULL ) // Space avalible?
		{
			tree_start->right = tree; // Yes, Insert
			root = make_balanced( root , tree->key ); // Balance path
			return true; // Inserted!
		}
		return tree_insert( tree_start->right, tree ); // No, call function again to the right subtree
	}
	
	else if ( tree_start->key > tree->key )
	{
		// Check left node
		if ( tree_start->left == NULL ) // Space avalible? 
		{
			tree_start->left = tree; // Yes, Insert
			root = make_balanced( root , tree->key ); // Balance path
			return true; // Inserted!
		}
		return tree_insert( tree_start->left , tree ); // No, call function again to the left subtree 
	}
	else if ( tree_start->key == tree->key ) // Key already exists?
		return false; // Yes, don't insert
	return false; // Don't insert otherwise
}

/////////////////////////////////////// tree_remove() //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Returns true if removal is successful, false otherwise.

template <typename keyType, typename dataType>
bool AVL_Tree<keyType,dataType>::tree_remove( treenode<keyType,dataType>* tree, keyType search_key ) {
	
	if ( tree == NULL ) // Node not found
		return false; // Do nothing
	
	if ( count == 1 ) // Only one node in the tree, which is the root
	{
		delete root; // Delete root
		root = NULL; // Reset root pointer
		return true; // Deleted! No balance necessary
	}
	
	else
	{
		if ( search_key < tree->key )
		{
			// Check left
			if ( tree->left->key != search_key ) // Is the node to be deleted on the left?
				return tree_remove( tree->left,  search_key ); // No, call function again to the left
			else // Yes, check the case of the node
			{
				treenode<keyType,dataType>* del = tree->left;
				
				// Case 1: Node is leaf node
				if ( del->left == NULL && del->right == NULL )
				{
					tree->left = NULL;
					delete del;
					root = make_balanced( root , tree->key ); // Balance along the path
					return true; // Deleted!
				}
				
				// Case 2: Node has only right subtree
				else if ( del->left == NULL ) 
				{
					tree->left = del->right;
					delete del;
					root = make_balanced( root , tree->key ); // Balance along the path
					return true; // Deleted!
				} 
				
				// Case 3: Node has only left subtree
				else if ( del->right == NULL ) 
				{    
					tree->left = del->left;
					delete del;
					root = make_balanced( root , tree->key ); // Balance along the path
					return true;  // Deleted!
				}
				
				// Case 4: Node has both left and right subtrees
				else 
				{
					remove_min( del ); // Remove minimum node in subtree and assign its values to the current node
					root = make_balanced( root , tree->key ); // Balance along the path
					return true;  // Deleted!
				}
				del = NULL;
			}
			
		}
		
		else if ( search_key > tree->key ) 
		{
			if ( tree->right->key != search_key )
				return tree_remove( tree->right,  search_key );
			else
			{
				treenode<keyType,dataType>* del = tree->right;
				
				// Case 1: Node is leaf node
				if ( del->left == NULL && del->right == NULL )
				{
					tree->right = NULL;
					delete del;
					root = make_balanced( root , tree->key ); // Balance along the path
					return true; // Deleted!
				}
				
				// Case 2: Node has only right subtree
				else if ( del->left == NULL ) 
				{
					tree->right = del->right;
					delete del;
					root = make_balanced( root , tree->key ); // Balance along the path
					return true; // Deleted!
				} 
				
				// Case 3: Node has only left subtree
				else if ( del->right == NULL ) 
				{    
					tree->right = del->left;
					delete del;
					root = make_balanced( root , tree->key ); // Balance along the path
					return true; // Deleted!
				}
				
				// Case 4: Node has both left and right subtrees
				else 
				{
					remove_min( del ); // Remove minimum node in subtree and assign its values to the current node
					root = make_balanced( root , tree->key ); // Balance along the path
					return true; // Deleted!
				}
				del = NULL;
			}
		}
		
		else if ( tree->key == search_key )
		{
			remove_min( tree ); // Remove minimum node in subtree and assign its values to the current node
			root = make_balanced( root , tree->key ); // Balance along the path
			return true; // Deleted!
		}
	}
	return false;
}

/////////////////////////////////////// tree_search() //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Returns true if search is successful, false otherwise.

template <typename keyType, typename dataType>
bool AVL_Tree<keyType,dataType>::tree_search( treenode<keyType,dataType>* tree, keyType search_key , dataType& data )
{
	if ( tree == NULL ) // Node not found
		return false;
	else
	{
		if ( search_key < tree->key )
			// Check left
			return tree_search( tree->left , search_key, data );
		else if ( search_key > tree->key )
			// Check right
			return tree_search( tree->right , search_key , data );
		else
		{
			// Found!
			data = tree->data; // Pass data to the parameter
			return true;
		}
	}
}

/////////////////////////////////////// tree_update() //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Returns true if update is successful, false otherwise.

template <typename keyType, typename dataType>
bool AVL_Tree<keyType,dataType>::tree_update( treenode<keyType,dataType>* tree, keyType search_key , dataType data )
{
	if ( tree == NULL ) // Node not found
		return false;
	else
	{
		if ( search_key < tree->key )
			// Check left
			return tree_update( tree->left , search_key, data );
		else if ( search_key > tree->key )
			// Check right
			return tree_update( tree->right , search_key , data );
		else
		{
			// Found
			tree->data = data; // Update node
			return true;
		}
	}
}

//////////////////////////////////// in_order_private() ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

template <typename keyType, typename dataType>
void AVL_Tree<keyType,dataType>::in_order_private(treenode<keyType,dataType>* tree, ostream& output)
{
	if( tree == NULL )
	{
		return;
	}
	in_order_private( tree->left , output );
	stream_node( tree , output ); // Stream node contents to the output stream
	in_order_private(tree->right , output );
}

////////////////////////////////// post_order_private() ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

template <typename keyType, typename dataType>
void AVL_Tree<keyType,dataType>::post_order_private(treenode<keyType,dataType>* tree, ostream& output)
{
	if( tree == NULL )
	{
		return;
	}
	post_order_private( tree->left , output );
	post_order_private( tree->right , output );
	stream_node( tree , output ); // Stream node contents to the output stream
}


/////////////////////////////////// pre_order_private() ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

template <typename keyType, typename dataType>
void AVL_Tree<keyType,dataType>::pre_order_private(treenode<keyType,dataType>* tree, ostream& output)
{
	if( tree == NULL )
	{
		return;
	}
	stream_node( tree , output ); // Stream node contents to the output stream
	pre_order_private( tree->left , output );
	pre_order_private( tree->right , output );
}

///////////////////////////////////// right_rotation() /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Returns the new rotated subtree if rotation is successful, or the same subtree otherwise

template <typename keyType, typename dataType>
treenode<keyType,dataType>* AVL_Tree<keyType,dataType>::right_rotation(treenode<keyType,dataType>* root)
{
	if ( root != NULL )
		if ( root->left != NULL )
			{
				treenode<keyType,dataType>* new_root = root->left;
				root->left = new_root->right;
				new_root->right = root;
		
				return new_root;
			}
				return root;
}

///////////////////////////////////// left_rotation() //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Returns the new rotated subtree if rotation is successful, or the same subtree otherwise

template <typename keyType, typename dataType>
treenode<keyType,dataType>* AVL_Tree<keyType,dataType>::left_rotation(treenode<keyType,dataType>* root)
{
	if ( root != NULL )
		if ( root->right != NULL )
			{
				treenode<keyType,dataType>* new_root = root->right;
				root->right = new_root->left;
				new_root->left = root;
				
				return new_root;
			}
				return root;
}

///////////////////////////////// right_rotation_double() //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Returns the new rotated subtree if rotation is successful, or the same subtree otherwise

template <typename keyType, typename dataType>
treenode<keyType,dataType>* AVL_Tree<keyType,dataType>::right_rotation_double(treenode<keyType,dataType>* root)
{
	root->left = left_rotation( root->left );
	return right_rotation( root );
}

///////////////////////////////// left_rotation_double() ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Returns the new rotated subtree if rotation is successful, or the same subtree otherwise

template <typename keyType, typename dataType>
treenode<keyType,dataType>* AVL_Tree<keyType,dataType>::left_rotation_double(treenode<keyType,dataType>* root)
{
	root->right = right_rotation( root->right );
	return left_rotation( root );
}

///////////////////////////////////// make_balanced() //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Balances the tree along a path and returns the balanced tree

template <typename keyType, typename dataType>
treenode<keyType,dataType>* AVL_Tree<keyType,dataType>::make_balanced( treenode<keyType,dataType>* tree , keyType& search_key )
{
	if ( tree != NULL )
	{
		// Traverse to the node with key "search_key"
		if ( tree->key > search_key )
			tree->left = make_balanced( tree->left, search_key );
		else if (  tree->key < search_key )
			tree->right = make_balanced( tree->right , search_key );
		
		// Case 1: Right subtree is higher
		if ( balance( tree ) == 2 )
		{
			if( balance( tree->right ) == 1 || balance( tree->right ) == 0 )
				return left_rotation( tree );
			else if ( balance( tree->right ) == -1 )
				return left_rotation_double( tree );
		}
		
		// Case 2: Left subtree is higher
		else if ( balance( tree ) == -2 )
		{
			if( balance( tree->left ) == -1 || balance( tree->left ) == 0  )
				return right_rotation( tree );
			else if ( balance( tree->left ) == 1 )
				return right_rotation_double( tree );
		}
		// Case 3: No balance needed
		else 
			return tree;
	}
	return tree;
}

///////////////////////////////////////// height() /////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Returns the height of a subtree

template <typename keyType, typename dataType>
int AVL_Tree<keyType,dataType>::height(treenode<keyType,dataType>* tree)
{
	if( tree == NULL )
		return -1;
	else
		return 1 + get_max_int( height(tree->left) , height(tree->right) );
}

//////////////////////////////////////// balance() /////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Returns the balance factor of a subtree

template <typename keyType, typename dataType>
int AVL_Tree<keyType,dataType>::balance( treenode<keyType,dataType>* tree )
{
	if (tree != NULL)
		return ( height( tree->right ) - height( tree->left ) );
	return 0;
}

////////////////////////////////////// count_nodes() ///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Returns the number of nodes in a subtree

template <typename keyType, typename dataType>
int AVL_Tree<keyType,dataType>::count_nodes(treenode<keyType,dataType>* tree)
{
	if( tree == NULL )
		return 0;
	else
		return 1 + count(tree->left) + count(tree->right);
}

////////////////////////////////////// stream_node() ///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Streams the contents of a node to the output stream

template <typename keyType, typename dataType>
void AVL_Tree<keyType,dataType>::stream_node( treenode<keyType,dataType>* tree , ostream& output )
{
	output << tree->key <<  " " << tree->data << endl;
}

////////////////////////////////////// tree_output() ///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Prints the nodes of a subtree in a tree form with the balance factors 

template <typename keyType, typename dataType>
void AVL_Tree<keyType,dataType>::tree_output( treenode<keyType,dataType>* tree , int spaces )
{
	while ( tree != NULL )
	{
		tree_output( tree->right, spaces + 6 );
		for (int i = 0; i <= spaces; ++i)
			cout << " ";
		cout << tree->key << "(" << balance(tree) << ")" << endl;
		tree = tree->left;
		spaces += 6;
	}
}

//////////////////////////////////////// find_min() ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Finds and returns the minimum node in a subtree 

template <typename keyType, typename dataType>
treenode<keyType,dataType>* AVL_Tree<keyType,dataType>::find_min(treenode<keyType,dataType>* tree)
{
	if( tree == NULL )
		return NULL;
	else
		if( tree->left == NULL )
			return tree;
	else
		return find_min( tree->left );
}

/////////////////////////////////////// remove_min() ///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//  removes the minimum node in the right subtree and takes its contents to replace it with the root of the subtree 

template <typename keyType, typename dataType>
void AVL_Tree<keyType,dataType>::remove_min(treenode<keyType,dataType>* root)
{
	treenode<keyType,dataType>* min;
	keyType min_key;
	dataType min_data;
	
	min = find_min( root->right ); // Find minimum in the right subtree
	
	// Take contents
	min_key = min->key;
	min_data = min->data;
	
	tree_remove( root , min_key ); // Remove minimum
	
	// Set contents to the root
	root->key = min_key;
	root->data = min_data;
}

////////////////////////////////////// tree_dispose() //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Removes a node and all its subtrees

template <typename keyType, typename dataType>
void AVL_Tree<keyType,dataType>::tree_dispose( treenode<keyType,dataType>* tree )
{
	if ( tree != NULL )
	{
		tree_dispose( tree->left );
		tree_dispose( tree->right );
		delete tree;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////


/*******************************************************************************/
//////////////////////////////// CLASS: Database ////////////////////////////////
/*******************************************************************************/

////////////////////////////////////////////
// Database manager and program interface //
////////////////////////////////////////////

class Database
{
private:
	AVL_Tree<int, string> database; // Database container (AVL Tree: keys of type int and data of type string)
	
	void display_data(); // Displays data
	void display_header(); // Displays program header
	void display_status(); // Displays database status
	void display_menu(); // Displays program help menu
	void display_command_message(); // Displays message from last executed command
	
	bool file_load(string); // Loads database from a text file
	bool file_save(string); // Saves database into a text file
	
	void set_error( string ); // Registers command error
	void set_command_message( string ); // Registers command message
	
	void command_handler(bool&); // Command handler: Handles and interprets commands from the user
	
	bool occupied; // Database container status
	int last_count; // Last count of records since the last save
	string data_file; // Path to database file
	
	string cmd_msg; // Command execution message
	string last_cmd; // Last executed command
	string error_msg; // Command execution error message
	bool cmd_success; // Command execution status
	
public:
		
	Database(char* file = "database.txt");
	
	void start_manager();
	
	int get_count() {return database.get_count();}
	int get_last_count() {return last_count;}
	const bool isOccupied() const {return occupied;}
};

// Helper Functions ***********************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////// seperate_record_fields() //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Separates a record into 2 strings and passes them to the parameter

bool seperate_record_fields( string line, string& id, string& name )
{
	if ( line == "" || line[0] == '#' || line[0] == ' ' ) // Is line a record?
		return false; // No, return false
	
	else // Yes, start separating 
	{
		id = "";
		name = "";
		int i = 0;
		while( line[i] != ' ' )
		{
			id += line[i];
			++i;
		}
		++i;
		
		while( line[i] != '\0' )
		{
			name += line[i];
			++i;
		}
		return true;
	}
	return false;
}

///////////////////////////////////// check_command() //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Compares a command to a list of choices, returns true if cmd is found in the array

bool check_command( string cmd, string choices[] )
{
	int i = 0;
	while ( choices[i] != "~")
	{
		if ( cmd == choices[i] )
			return true;
		++i;
	}
	return false;
}

/*****************************************/
//////////// Database: Public /////////////
/*****************************************/

//////////////////////////////////////// Database() ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Constructor: Creates database container by loading the contents of a database text file 

Database::Database(char* file)
{
	// Initilaize database manager
	occupied = cmd_success = false;
	data_file = last_cmd = error_msg = cmd_msg = "";
	
	// Check database text file
	if (file != NULL) // Database filename provided?
	{
		data_file = file; // Set private member
		ifstream test( file ); // a test stream to check if the file exists
		if ( !test ) // Does file exist?
			file_save( data_file ); // No, make new file
	}
	file_load( data_file ); // Load database file into database container 
	last_count = database.get_count();
}


///////////////////////////////////// start_manager() //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Database manager invoker, keeps program in loop until an exit command is issued by the user

void Database::start_manager()
{	
	bool exit_editor = false;
	
	do
	{
		clearscreen();
		display_header();
		display_command_message();
		cout << endl << separator;
		display_status();
		cout << "Enter command (type \"help\" for list of commands): ";
		command_handler(exit_editor);
	} while(!exit_editor);
	
	// Clear the screen before exit
	clearscreen();
}

/*****************************************/
/////////// Database: Private /////////////
/*****************************************/

////////////////////////////////////// display_data() //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Displays all records on the screen in sorted order

void Database::display_data()
{
	if ( !database.is_empty() )
		database.in_order( cout );
	else cout << endl << " > Database is empty < " << endl;
}

///////////////////////////////////// display_header() /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Displays program header

void Database::display_header()
{
	cout << "Database file: " << data_file << endl;
	cout << separator << endl;
}

///////////////////////////////////// display_status() /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Displays database status

void Database::display_status()
{
	cout << "Status: ( Number of records: " << database.get_count() << " )" << endl;
	if ( !cmd_success && last_cmd != "" ) // Is there an error in the last command?
		cerr << error_msg << endl; // Yes, display error message
	else cout << endl;
}

////////////////////////////////////// display_menu() //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Displays program help menu

void Database::display_menu()
{
	clearscreen();
	
	cout << "List of commands:" << endl << separator
		<< "Command Name      Shortcut      Description" << endl << separator << endl
		<< "insert            i             Inserts a record (needs an ID and name)." << endl
		<< "remove , delete   r or d        Deletes a record (needs an ID)." << endl
		<< "update            u             Updates a record (needs an ID and name)." << endl
		<< "find , search     f or s        Finds a record (needs an ID)." << endl
		<< "display , view    v             Displays records in sorted order by ID." << endl
		<< "open                            Opens a database and discards changes." << endl
		<< "save                            Saves changes to the current database." << endl
		<< "saveas                          Saves changes to another database." << endl
		<< "quit or exit      q             Quits program and saves changes." << endl
		<< "quit! or exit!    q!            Quits program and discards changes." << endl;
	pause("\nPress the \"Enter\" key to go back... ");
}

//////////////////////////////// display_command_message() /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Displays message from last executed command

void Database::display_command_message()
{
	if ( cmd_msg != "" ) cout << cmd_msg << endl;
	else cout << endl;
}

/////////////////////////////////////// file_load() ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Loads database from a text file

bool Database::file_load( string filename )
{
	if ( filename.length() != 0 ) // Is there a valid string?
	{
		int isvalidtext = filename.find(".txt"); // Valid filetype checker
		if ( isvalidtext != string::npos  && isvalidtext != 0 && isvalidtext == filename.length() - 4) // Is filename valid?
		{
			ifstream file( filename.c_str() ); // Create input stream
			if (file) // Can open file?
			{
				cout << "Opening Database..." << endl;
				if ( !database.is_empty() ) database.clear(); // Clear database cotainer if not empty
				string line, name, id_str;
				int id;
				while ( getline( file, line ) ) // Get lines while not end of file 
				{
					if ( seperate_record_fields( line, id_str, name ) ) // Is a valid record?
					{
						// Insert record
						id = atoi( id_str.c_str() );
						database.insert( id, name );
					}
					line = "";
				}
				occupied = true;
				data_file = filename;
				return true;
			}
			else cerr << "Error: Unable to open file." << endl;
			return false;
		}
		else cerr<< "Error: Invalid file type. Only \".txt\" are accepted." << endl;
		return false;
	}
	else cerr<< "Error: No input file" <<endl;
	return false;
}

/////////////////////////////////////// file_save() ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Saves database into a text file

bool Database::file_save(string filename)
{	
	if ( filename != "" ) // Is there a valid string?
	{
		int isvalidtext = filename.find(".txt"); // Valid filetype checker
		if ( isvalidtext != string::npos  && isvalidtext != 0 && isvalidtext == filename.length() - 4) // Is filename valid?
		{
			ofstream file( filename.c_str() ); // Create output stream
			if (file) // Can open file?
			{
				// Insert header comments
				file << "# Customer Database\n";
				file << "# Number of Records: " << database.get_count() << "\n\n";
				// Output records to file
				database.pre_order( file );
				last_count = database.get_count();
				return true;
			}
			else cerr << "Error: Unable to save file." << endl;
			return false;
		}
		else cerr<< "Error: Invalid file type and/or file name. Only \".txt\" are accepted." << endl;
		return false;
	}
	else cerr<< "Error: No destination file" <<endl;
	return false;	
} 

/////////////////////////////////////// set_error() ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Registers command error

void Database::set_error( string error )
{
	cmd_success = false;
	error_msg = error;
}

///////////////////////////////// set_command_message() ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Registers command message

void Database::set_command_message( string msg )
{
	cmd_msg = msg;
}

///////////////////////////////// set_command_message() ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Command handler: Handles and interprets commands from the user

void Database::command_handler(bool& exit_editor)
{
	
	string fullcmd = "", cmd = "", arg1_str = "", arg2 = "";
	int arg1 = 0, i = 0;
	
	// Clear last command
	/////////////////////
	
	error_msg = cmd_msg = "";
	cmd_success = true;
	
	// Input command, with all arguments
	////////////////////////////////////
	cin >> ws;
	getline( cin , fullcmd );
	fullcmd += '\0'; // to mark end of command;
	last_cmd = fullcmd;
	
	// Method to separate the arguments from the command, and places each in seperate variables
	///////////////////////////////////////////////////////////////////////////////////////////
	
	while( fullcmd[i] != ' ' && fullcmd[i] != '\0' )
	{
		cmd += fullcmd[i];
		++i;
	}
	++i;
	
	while( fullcmd[i] != ' ' && fullcmd[i] != '\0' )
	{
		arg1_str += fullcmd[i];
		++i;
	}
	arg1 = atoi(arg1_str.c_str());
	++i;
	
	while( fullcmd[i] != ' ' && fullcmd[i] != '\0' )
	{
		arg2 += fullcmd[i];
		++i;
	}
	
	// Command Interpretation
	/////////////////////////
	
	string help[] = {"help", "HELP", "h", "H", "~"};
	string insert[] = {"insert", "INSERT", "i", "I", "~"};
	string remove[] = {"remove", "REMOVE", "r", "R", "delete" , "DELETE" , "d" , "D" , "~"};
	string search[] = {"search", "SEARCH", "s", "S", "find" , "FIND" , "f" , "F" , "~"};
	string update[] = {"update", "UPDATE", "u", "U", "~"};
	string display[] = {"display", "DISPLAY", "view" , "VIEW" , "v" , "V" , "~"};
	string open[] = {"open", "OPEN", "~"};
	string save[] = {"save", "SAVE", "~"};
	string saveas[] = {"saveas", "SAVEAS", "~"};
	string quit_save[] = {"quit", "QUIT", "q" , "Q" , "exit" , "EXIT" , "e" , "E" , "~"};
	string quit_nosave[] = {"quit!", "QUIT!", "q!" , "Q!" , "exit!" , "EXIT!" , "e!" , "E!" , "~"};
	
	// Display Help
	if ( check_command( cmd , help ) )
		display_menu();
	
	// Insert Record
	else if ( check_command( cmd , insert ) )
	{
		if( arg1_str != "" && arg2 != "")
		{
			if( (arg1 == 0 && arg1_str != "0") || arg1_str == "" )
				set_error("You have not entered a valid ID, only numbers are allowed for IDs");
			else if( arg2 == " " || arg2 == "" )
				set_error("You have not entered a name, please enter a name");
			else if ( !database.insert(arg1, arg2) )
				set_command_message("Record already exists");
			else set_command_message("Record inserted!");
		}
		else set_error("You have not entered enough details, please provide a name and ID");
	}
	
	// Remove Record
	else if ( check_command( cmd , remove ) )
	{
		if( arg1_str != "" )
		{
			if( (arg1 == 0 && arg1_str != "0") )
				set_error("You have not entered a valid ID, only numbers are allowed for IDs");
			else if ( !database.remove(arg1) )
				set_command_message("Record does not exist");
			else set_command_message("Record removed!");
		}
		else set_error("You have not entered enough details, please provide an ID");
	}
	
	// Find Record
	else if ( check_command( cmd , search ) )
	{
		if( arg1_str != "" )
		{
			string find;
			if( (arg1 == 0 && arg1_str != "0") )
				set_error("You have not entered a valid ID, only numbers are allowed for IDs");
			else if ( !database.search(arg1, find) )
				set_command_message("Record does not exist");
			else set_command_message("Record found: " + arg1_str + " " + find);
		}
		else set_error("You have not entered enough details, please provide an ID");
	}
	
	// Update Record
	else if ( check_command( cmd , update ) )
	{
		if( arg1_str != "" && arg2 != "")
		{
			if( (arg1 == 0 && arg1_str != "0") || arg1_str == "" )
				set_error("You have not entered a valid ID, only numbers are allowed for IDs");
			else if( arg2 == " " || arg2 == "" )
				set_error("You have not entered a name, please enter a name");
			else if ( !database.update(arg1, arg2) )
				set_command_message("Record does not exist");
			else set_command_message("Record updated!");
		}
		else set_error("You have not entered enough details, please provide a name and ID");
	}
	
	// Display database
	else if ( check_command( cmd , display ) )
	{
		clearscreen();
		if ( arg1_str == "tree" ) // Display in form of tree option?
			database.show_tree();
		else display_data();
		cout << endl;
		pause("Press the \"Enter\" key to continue...");
	}
	
	// Open database text file
	else if ( check_command( cmd , open ) )
	{
		if (choice("Are you sure you want to close this file before saving (y or n)? "))
		{
			string target_file;
			cout << endl << "Enter file name: ";
			cin >> ws;
			getline( cin, target_file );
			if (!file_load(target_file))
				pause("\nPress the \"Enter\" key to go back... ");
		}
	}
			
	// Save database text file
	else if ( check_command( cmd , save ) )
	{
		if (choice("Are you sure you want to save and overwrite the current file (y or n)? "))
		{
			file_save( data_file );
			set_command_message("File saved!");
		}
			
	}
	
	// Save database text as another file
	else if ( check_command( cmd , saveas ) )
	{
		do
		{
			string target_file;
			cout << endl << "Enter file name: ";
			cin >> ws;
			getline( cin, target_file );
			ifstream check( target_file.c_str() );
			
			if (!check)
			{
				if ( file_save( target_file ) )
				{
					set_command_message("File saved!");
					break;
				}
					
			}
			else if (check && choice("File already exists, overwrite (y or n)? "))
			{
				if ( file_save( target_file ) )
				{
					set_command_message("File saved!");
					break;
				}
			}
		} while (true);
	}
	
	// Quit and save changes
	else if ( check_command( cmd , quit_save ) ) 
	{
		if (choice("Are you sure you want to exit and save changes, the file will be overwritten (y or n)? "))
		{
			file_save( data_file );
			exit_editor = true;
		}
	}
	
	// Quit and discard changes
	else if ( check_command( cmd , quit_nosave ) ) 
	{
		if (choice("Are you sure you want to exit and discard changes (y or n)? "))
			exit_editor = true;
	}
	
	// No valid command entered
	else set_error("Invalid Command");
}



int main (int argc, char * const argv[])
{
	char* filename = "database.txt";
	if ( argv[1] == NULL )
		cout << "Using default database... ";
	else filename = argv[1];
	
	Database customers( filename );
	
	if (customers.isOccupied())
	{
		customers.start_manager();
		cout << "Number of records in database: " << customers.get_last_count() << endl;
		cout << endl << app_name << endl << "Programmed by Talal Haj-Bakri" << endl << endl;
	}
	
	return 0;
}






