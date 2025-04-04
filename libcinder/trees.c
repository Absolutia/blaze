#include <libcinder/cindertypes.h>

tree_t *mktreenode(bool rootf, tree_t *root){
	if(NULL = tree_t *tree = malloc(sizeof(tree_t))){
		return NULL;
	}else{
		tree->type = NULL;
		tree->data = NULL;
		tree->forward_nodes = NULL;
		tree->num_nodes = 0;
		if(rootf){
			tree->root_node = tree;
			return tree;
		}else if(!rootf){
			tree->root_node = root;
			return tree;
		}
	}
}

tree_t *connnode(tree_t *connecter, tree_t *connected){
	connected->numnodes++;
	if(NULL = connected->forward_nodes = realloc(numnodes * sizeof(size_t *))){
		return NULL;
	}else{
		if()
	}
}
