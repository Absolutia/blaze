/** Linked lists */
struct linkedlist_t{
	void *data;
	struct linkedlist_t *next;
};

struct clinkedlist_t{
	void *data;
	struct clinkedlist_t *next;
	struct clinkedlist_t *start;
};

struct dlinkedlist_t{
	void *data;
	struct dlinkedlist_t *next;
	struct dlinkedlist_t *prev;
};

struct cdlinkedlist_t {
	void *data;
	struct cdlinkedlist_t *next;
	struct cdlinkedlist_t *prev;
	struct cdlinkedlist_t *start;
};
