#include "lhash.h"
#include "llist.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#define bzero ZeroMemory
#endif

#ifdef Linux
#include <strings.h>
#define closesocket close
#endif

typedef struct hash_node {
    list_head		link_;
    list_head		hash_;

    unsigned long	key_;
    unsigned long	val_;
} hash_node ;

typedef struct hash_host {

    char			*tag_name_;
    unsigned long	hash_size_;
    list_head		*hash_table_;

	unsigned int	new_total_;
    unsigned long	pow2;

    list_head		link_member_;
    unsigned int	use_count_;
	unsigned int	max_use_count_;
	unsigned int	new_count_;

    hash_node		*free_node_array_;
    unsigned long	free_list_size_;
    list_head		link_free_;

} hash_host ;

void *
create_hash( unsigned long _hash_size , unsigned long _free_size, const char* _name ) {

    hash_host *host = NULL;
    int size        = 0;
    unsigned long i = 0;


    host = ( hash_host * )malloc( sizeof( hash_host ) );
    bzero( host, sizeof( hash_host ) );


    size                    = strlen( _name );
    host->tag_name_         = malloc( size + 1 );
    host->tag_name_[ size ] = '\0';
    memcpy( host->tag_name_, _name, size );


    for ( i = 1; i < 32; i ++ ) {
        if( _hash_size <= (unsigned long)( 1 << i ) ) break;
    }
    
    host->use_count_		= 0;
	host->max_use_count_	= 0;
	host->new_count_		= 0;
    host->free_list_size_	= _free_size;

    host->pow2				= i;
    host->hash_size_		= ( 1 << i );

    host->hash_table_ = ( list_head * )malloc( sizeof( list_head ) * host->hash_size_ );
    for(i = 0; i < host->hash_size_; ++i ) {
        INIT_LIST_HEAD( &host->hash_table_[i] );
    }

    host->free_node_array_ = ( hash_node * )malloc( sizeof( hash_node ) * _free_size );
    INIT_LIST_HEAD( &host->link_free_ );
    for ( i = 0; i < _free_size; i++ ) {
        list_add_tail( &host->free_node_array_[ i ].link_, &host->link_free_ );
    }
    INIT_LIST_HEAD( &host->link_member_ );

    return host;
}

void
release_hash( void *_hash ) {

    hash_host *host = ( hash_host * )_hash;
    int index       = 0;
    unsigned long i = 0;
    list_head *curr, *shift;
	hash_node *node;


	list_for_each_safe( curr, shift, &host->link_member_ ) {

        node = list_entry( curr, hash_node, link_ );

        list_del( &node->hash_ );
        list_del( &node->link_ );

        index = node - host->free_node_array_;
        if(index >= 0 && (unsigned long)index < host->free_list_size_) {
            llist_add( &(node->link_), &host->link_free_ );
        } else {
            free( node );
			host->new_total_ --;
        }

		host->use_count_ --;
    }

    for(i = 0; i < host->hash_size_; ++i) {
        INIT_LIST_HEAD(&(host->hash_table_[i]));
    }

    host->use_count_ = 0;
	host->new_count_ = 0;
    INIT_LIST_HEAD(&host->link_member_);

    free( host->tag_name_ );
    free( host->hash_table_ );
    free( host->free_node_array_ );

    free( host );
}

HashOptResult
hash_find( void *_hash, unsigned long _key, unsigned long* _val ) {
    hash_host *host		= ( hash_host * )_hash;
    int index			= _key & ( host->hash_size_ - 1 );
    list_head *pos		= NULL;

	if (_hash == NULL || _val == NULL)
	{
		return HashOptResult_InvalidateParam;
	}

    list_for_each( pos, &(host->hash_table_[index]) ) {
        hash_node *node = list_entry( pos, hash_node, hash_ );
        if( node->key_ == _key ) {
            (*_val) = node->val_;
            return HashOptResult_OK;
        }
    }
    return HashOptResult_NotFind;
}

HashOptResult 
hash_set( void *_hash, unsigned long _key, unsigned long _val ) {
    hash_host *host = ( hash_host *)_hash;
    hash_node *node = NULL;
    list_head *pos  = NULL;

	if (_hash == NULL )
	{
		return HashOptResult_InvalidateParam;
	}

    int index = _key & ( host->hash_size_ - 1 );
    list_for_each( pos, &(host->hash_table_[ index ]) ) {
        node = list_entry( pos, hash_node, hash_ );
        if( node->key_ == _key ) {
            node->val_ = _val;
            return HashOptResult_DuplicatedInsert;
        }
    }

    if( list_empty(&host->link_free_) ) {
        node = ( hash_node * )malloc( sizeof( hash_node ) );
		if ( node ) {
			host->new_count_ ++;
		}
    } else {
        pos = host->link_free_.next;
        list_del(pos);
        node = list_entry( pos, hash_node, link_ );

    }

    if( node == NULL) {
		printf("[HASH] hash_set fail, malloc node fail\n");
		return HashOptResult_MallocFail;
	}

	node->key_ = _key;
	node->val_ = _val;

	llist_add( &(node->hash_), &(host->hash_table_[index]) );
	llist_add( &(node->link_), &host->link_member_ );
	host->use_count_ ++;

	if ( host->use_count_ > host->max_use_count_ ) {
		host->max_use_count_ = host->use_count_;
	}

	return HashOptResult_OK;
}

HashOptResult 
hash_del( void *_hash, unsigned long _key ) {
    hash_host *host = ( hash_host *)_hash;
    int index       = _key & ( host->hash_size_ - 1 );
    list_head *curr = NULL;
    hash_node *node = NULL;

	if (_hash == NULL)
	{
		return HashOptResult_InvalidateParam;
	}

    list_for_each( curr, &(host->hash_table_[index]) ) {
        node = list_entry( curr, hash_node, hash_ );
        if( node->key_ == _key ) {
            list_del( &(node->hash_) );
            list_del( &(node->link_) );

            index = node - host->free_node_array_;
            if(index >= 0 && (unsigned long)index < host->free_list_size_) {
                llist_add( &(node->link_), &host->link_free_ );
            } else {
                free( node );
				host->new_total_ --;
            }

            host->use_count_ --;
            return HashOptResult_OK;
        }
    }
    return HashOptResult_NotFind;
}

void 
hash_memory_detail( void *_hash, int *_use_node_count, unsigned int *_remain_free_node
		,unsigned int *_new_count, unsigned int *_max_use_count ) {
	hash_host *host = NULL;
	if (_hash == NULL 
		|| _use_node_count == NULL
		|| _remain_free_node == NULL
		|| _new_count == NULL
		|| _max_use_count == NULL)
	{
		printf("[HASH] hash_memory_detail input param error!");
		return;
	}
	host = ( hash_host *)_hash;

	(*_use_node_count)		= host->use_count_;
	(*_remain_free_node)	= host->free_list_size_ - (host->use_count_); 
	if ( (*_remain_free_node) < 0 ) {
		(*_remain_free_node) = 0;
	}

	(*_new_count)			= host->new_count_;
	(*_max_use_count)		= host->max_use_count_;

}

