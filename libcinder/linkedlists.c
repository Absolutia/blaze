#include <stdlib.h>
#include <stddef.h>

#include "types.h"

struct linkedlist_t *linkedlist_mknode(){
	struct linkedlist_t *newnode = (struct linkedlist_t *) malloc(sizeof(struct linkedlist_t));
	if(newnode == NULL){
		return NULL;
	}
	newnode->data = NULL;
	newnode->next = NULL;
	return newnode;
}

struct linkedlist_t *linkedlist_crawltoend(struct linkedlist_t *root){
	if(root->next != NULL){
		linkedlist_crawltoend(root->next);
	}
	return root;
}

struct linkedlist_t *linkedlist_crawltoend_accounting(struct linkedlist_t *root, size_t *nodecount){
	if(root->next != NULL){
		linkedlist_crawltoend_accounting(root->next, nodecount++);
	}
	return root;
}

struct linkedlist_t *linkedlist_crawl(struct linkedlist_t *root, size_t *nodecount, size_t *nodenum){
	if(root->next != NULL && nodecount != nodenum){
		linkedlist_crawl(root->next, nodecount++, nodenum);
	}
	return root;
}
