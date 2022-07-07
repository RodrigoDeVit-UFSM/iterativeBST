// A non-recursive (iterative) function to travel into a Binary Search Tree (BST)

#include <stdio.h>
#include <stdlib.h>

// The type of the BST can be given by:
struct tree {
	int info;
	struct tree* left;
	struct tree* right;
};
typedef struct tree Tree;

// The tree is represented by the pointer to the root node. 
// The empty tree is initialized assigning null to the variable representing 
// the tree. A simple function of startup is shown below:
Tree* init (void) {
	return NULL;
}

// Once a search tree is built, we can print tree's values in ascending order 
//by traveling the nodes in symmetrical order:
void showTree (Tree* a) {
	if (a != NULL) {
		showTree(a->left);
		printf("%d ",a->info);
		showTree(a->right);
	}
}

// These are functions analogous to common binary trees, as they do not 
// exploit the sorting of search trees. However, the operations that are 
// interested in analyzing in detail are:
//
// Search: function that seeks an element in the tree;
// Insert: function that inserts a new element into the tree;
// Remove: function that removes an element from the tree.

// Search Operation: serves to seek a tree element and explores the tree ordering 
// property, with computational performance proportional to its height (O (log n) 
// for the balanced tree case). An implementation of the search function is given 
// by:
Tree* search (Tree* r, int v) {
	if (r == NULL) return NULL;
	else if (r->info > v) return search (r->left, v);
	else if (r->info < v) return search (r->right, v);
	else return r;
}

// Insert Operation: adds a tree element in the correct position for the fundamental 
// property to be maintained. To insert a value v in a tree we use its recursive 
// structure, and the sorting specified in the fundamental property. If the 
// (sub-) tree is empty, it should be replaced by a tree whose only node (the root 
// node) contains the value v. If the tree is not empty, we compare v with the 
// value at the root of the tree, and insert v in the left sub-tree or the right 
// sub-tree, as the result of the comparison. The function below illustrates the 
// implementation of this operation. The function has as its return value the 
// eventual new root node of the (sub-) tree.
Tree* insert (Tree* a, int v) {
	if (a==NULL) {
		a = (Tree*)malloc(sizeof(Tree));
		a->info = v;
		a->left = a->right = NULL;
	}
	else if (v < a->info)
		a->left = insert(a->left,v);
	else /* v < a->info */
		a->right = insert(a->right,v);
	return a;
}

// The code below illustrates the implementation of the function to remove an 
// element of the binary search tree. The function has the value of return to 
// the eventual new root of the (sub-) tree.
Tree* removeNode (Tree* r, int v)
{
	if (r == NULL)
		return NULL;
	else if (r->info > v)
		r->left = removeNode(r->left, v);
	else if (r->info < v)
		r->right = removeNode(r->right, v);
	else { /* found the node */
		if (r->left == NULL && r->right == NULL) { /* childless node */
			free (r);
			r = NULL;
		}		
		else if (r->left == NULL) { /* There are child only on the right */
			Tree* t = r;
			r = r->right;
			free (t);
		}
		else if (r->right == NULL) { /* There are child only on the left */
			Tree* t = r;
			r = r->left;
			free (t);
		}
		else { /* has two children */
			Tree* father = r;
			Tree* f = r->left;
			while (f->right != NULL) {
				father = f;
				f = f->right;
			}
			r->info = f->info; /* shift the information */
			f->info = v;
			r->left = removeNode(r->left,v);
		}	
	}
	return r;
}

// Is tree empty?
int empty(Tree* a)
{
	return a==NULL;
}

// Once a search tree is built, we can print tree's values in ascending order 
// by traveling the nodes in symmetrical order; this is an alternative way - show
// the tree in text mode
void showTreeAlt (Tree* a, int root) {
	if (!empty(a)){
		if (a->info == root)
			printf("<");
		printf("%d", a->info); /* show root */
		printf("<");
		showTreeAlt(a->left, root); /* show lST */
		printf(">");
		printf("<");
		showTreeAlt(a->right, root); /* show RST */
		printf(">");
		if (a->info == root)
			printf(">");
	}
}	

// Count the nodes number 
int countNodes (Tree* a, int* count) {
	if (a != NULL) {
		countNodes(a->left, count); 
		*count += 1; 
		countNodes(a->right, count); 
	}
	return *count;
}

// Dynamic vector to stock a stack
struct tree1 {
	Tree* nodeAddress; 
};
typedef struct tree1 Tree1;

// Insert in the stack
int push (Tree1* stack, Tree* a, int top) {
	stack[++top].nodeAddress = a; 
	return top;
}

// Remove from the stack
Tree* pop (Tree1* stack, int top) {
	return stack[top].nodeAddress;
}

// Once a search tree is built, we can print tree's values in ascending order 
// by traveling the nodes in symmetrical order; this is an alternative way - non
// recursive function

void showIterative (Tree* a) {
	
 	int count = 0;

 	Tree1* stack = (Tree1*) malloc(countNodes(a, &count)*sizeof(Tree1));
 	printf("NODES NUMBER: %d\n\n",count);
 	int top = 0, visited = 0;	

	while(visited < count) {
		while (a != NULL) {
			top = push (stack, a, top);
			printf("VISITED %d\n",a->info); visited++;
			if(a->left == NULL) break;
			a = a->left;
		}
		a = pop (stack, top--); 
		while(a->right == NULL) a = pop (stack, top--);
		a = a->right;
	}
}

void main() {
	Tree* tree = init();
	tree = insert(tree, 6);
	tree = insert(tree, 8);
	tree = insert(tree, 2);
	tree = insert(tree, 1);
	tree = insert(tree, 4);
	tree = insert(tree, 3);
	int root = tree->info; // Get root node
	puts("Show the tree in a recursive (and common) way: "); showTree(tree);
	puts("\n\nShow the tree in a textual hierarchical way: \n<ROOT<LEFT><RIGHT>>: "); showTreeAlt (tree, root); puts("\n");
	puts("Show the tree in a iterative (and incommon) way: "); showIterative (tree);
}
