
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 127

typedef struct __node_t__ {
	int value;
	int degree;
	struct __node_t__ *child;
	struct __node_t__ *parent;
	struct __node_t__ *brother;
} node_t;

typedef struct __heap_t__ {
	node_t *head;
} heap_t;

node_t *node_init( int value )
{
	node_t *node = malloc( sizeof ( node_t ) );
	node->value = value;
	node->degree = 0;
	return node;
}

heap_t *heap_init()
{
	heap_t *heap = malloc( sizeof ( heap_t ) );
	heap->head = NULL;
	return heap;
}

node_t *heap_merge( heap_t *heap1, heap_t *heap2 )
{
	if( heap1->head == NULL ) return heap2->head;
	if( heap2->head == NULL ) return heap1->head;

	node_t *head;
	node_t *h1It = heap1->head;
	node_t *h2It = heap2->head;
	node_t *tail;

	if( heap1->head->degree <= heap2->head->degree )
	{
		head = heap1->head;
		h1It = h1It->brother;
	}
	else
	{
		head = heap2->head;
		h2It = h2It->brother;
	}
	tail = head;
	while( h1It != NULL && h2It != NULL )
	{
		if( h1It->degree <= h2It->degree )
		{
			tail->brother = h1It;
			h1It = h1It->brother;
		}
		else
		{
			tail->brother = h2It;
			h2It = h2It->brother;
		}

		tail = tail->brother;
	}

	tail->brother = ( h1It != NULL ) ? h1It : h2It;

	return head;
}

node_t *heap_union( heap_t *original, heap_t *uni )
{
	node_t *new_head = heap_merge( original, uni );

	original->head = NULL;
	uni->head = NULL;

	if( new_head == NULL )
		return NULL;

	node_t *prev = NULL;
	node_t *aux = new_head;
	node_t *next = new_head->brother;

	while( next != NULL )
	{
		if( aux->degree != next->degree || ( next->brother != NULL && next->brother->degree == aux->degree ) )
		{
			prev = aux;
			aux = next;
		}
		else
		{
			if( aux->value < next->value )
			{
				aux->brother = next->brother;
				next->parent = aux;
				next->brother = aux->child;
				aux->child = next;
				aux->degree++;
			}
			else
			{
				if( prev == NULL )
					new_head = next;
				else
					prev->brother = next;

				aux->parent = next;
				aux->brother = next->child;
				next->child = aux;
				next->degree++;

				aux = next;
			}
		}

		next = aux->brother;
	}

	return new_head;
}

void heap_insert( heap_t *heap, int value )
{
	node_t *node = node_init( value );
	heap_t *temp = heap_init();
	temp->head = node;
	heap->head = heap_union( heap, temp );
	free( temp );
}


void heap_remove( heap_t *heap, node_t *head, node_t *bef )
{
	if( head == heap->head )
		heap->head = head->brother;
	else
		bef->brother = head->brother;

	node_t *new_head = NULL;
	node_t *child = head->child;

	while( child != NULL )
	{
		node_t *next = child->brother;
		child->brother = new_head;
		child->parent = NULL;
		new_head = child;
		child = next;
	}

	heap_t *temp = heap_init();
	temp->head = new_head;
	heap->head = heap_union( heap, temp );
	free( temp );
}


node_t *heap_min( heap_t *heap )
{
	if( heap->head == NULL ) return NULL;

	node_t *min = heap->head;
	node_t *min_prev = NULL;
	node_t *next = min->brother;
	node_t *next_prev = min;

	while( next != NULL )
	{
		if( next->value < min->value )
		{
			min = next;
			min_prev = next_prev;
		}

		next_prev = next;
		next = next->brother;
	}

	heap_remove( heap, min, min_prev );
	return min;
}

void heap_free( heap_t *h )
{
	while( heap_min( h ) );
	free( h );
}

int
main()
{
	heap_t *heap = heap_init();
	char buf[MAX_BUFFER_SIZE];

	while( fgets( buf, MAX_BUFFER_SIZE, stdin ) != NULL )
	{
		char op;
		int value;
		sscanf( buf, "%c %d", &op, &value );
		switch( op )
		{
			case 'i': // insert
				heap_insert( heap, value );
			break;
			case 'a': // remove
			{
				node_t *min = heap_min( heap );
				if( min != NULL )
					printf( "%d\n", min->value );
			}
			break;
			case 'r': // ?
			break;
		}
	}

	heap_free( heap );
	return 0;
}
