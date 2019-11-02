/**
 * @file lhash.h
 * @author swordhell
 * @date 2 Nov 2019
 * @brief 简单的双向list数据结构
 *
 */
#ifndef _llist_h_
#define _llist_h_

#ifdef _WIN32
#define INLINE 
#else
#define INLINE __inline__
#endif

typedef struct list_head {
        struct list_head *next, *prev;
} list_head ;

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
        struct list_head name = LIST_HEAD_INIT(name)

#define INIT_LIST_HEAD(ptr) do { \
        (ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)

/**
 * @brief 在连表中两个节点之间插入一个节点
 *
 * @param it      需要插入的节点
 * @param prev    前置节点
 * @param next    后继节点
 *
 */
static INLINE void __list_add(struct list_head * it, struct list_head * prev, struct list_head * next)
{
        next->prev = it;
        it->next = next;
        it->prev = prev;
        prev->next = it;
}

/**
 * @brief 向一个连表的头部插入一个元素
 *
 * @param it      需要插入的节点
 * @param head:   连表头
 *
 */
static INLINE void llist_add(struct list_head *it, struct list_head *head)
{
        __list_add(it, head, head->next);
}

/**
 * @brief 向一个连表的尾部插入一个元素
 *
 * @param it      需要插入的节点
 * @param head:   连表头
 *
 */
static INLINE void list_add_tail(struct list_head *it, struct list_head *head)
{
        __list_add(it, head->prev, head);
}

/**
 * @brief 将两个节点直接连接起来，用于从双链表中删除中间的节点
 *
 * @param prev      前置节点
 * @param next:     后继节点
 *
 */
static INLINE void __list_del(struct list_head * prev,
                                  struct list_head * next)
{
        next->prev = prev;
        prev->next = next;
}

/**
 * @brief 将本身节点从连表中删除
 *
 * @param entry     当前节点
 *
 */
static INLINE void list_del(struct list_head *entry)
{
        __list_del(entry->prev, entry->next);
}


/**
 * @brief 将本身节点从连表中删除，并且将本身连表指针清理
 *
 * @param entry     当前节点
 *
 */
static INLINE void list_del_init(struct list_head *entry)
{
        __list_del(entry->prev, entry->next);
        INIT_LIST_HEAD(entry); 
}

/**
 * @brief 将本身节点从连表中删除，并且将本身连表指针清理
 *
 * @param entry     当前节点
 *
 */
static INLINE int list_empty(struct list_head *head)
{
        return head->next == head;
}

/**
 * @brief 将一个连表赋值给另外一个节点
 *
 * @param dest     目标对象
 * @param src      源对象
 *
 */
static INLINE void list_assign( struct list_head *dest, struct list_head* src )
{
    *dest = *src;
    if( list_empty( src ) ) {
        INIT_LIST_HEAD( dest );
    } else {
        src->next->prev = dest;
        src->prev->next = dest;
    } 
}

/**
 * @brief 将一个连表连接到另一个连表的头部
 *
 * @param list     需要并入其他连表的连表对象
 * @param head     接纳其他连表的连表对象
 *
 */
static INLINE void list_splice(struct list_head *list, struct list_head *head)
{
        struct list_head *first = list->next;

        if (first != list) {
                struct list_head *last = list->prev;
                struct list_head *at = head->next;

                first->prev = head;
                head->next = first;

                last->next = at;
                at->prev = last;
        }
}

/**
 * @brief 将一个连表连接到另一个连表的尾部
 *
 * @param list     需要并入其他连表的连表对象
 * @param head     接纳其他连表的连表对象
 *
 */
static INLINE void list_splice_tail(struct list_head *list, struct list_head *head)
{
        if(!list_empty(list) ) {
            struct list_head *first = list->next;
            struct list_head *last = list->prev;
            struct list_head *at = head->prev;
            
            at->next = first;
            first->prev = at;

            last->next = head;
            head->prev = last;
        }
}

/**
* @brief 从节点数据，通过偏移指针反出原始struct对象
*
* @param ptr:     原始对象
* @param type:    需要反出的struct定义
* @member:        在struct中list_struct成员变量名称
*
*/
#define list_entry(ptr, type, member) \
        ((type *)((char *)(ptr) - ((unsigned long)(&((type*)1)->member) - 1) ))


/**
* @brief 正序遍历连表
*
* @param pos:     当前节点
* @param head:    指针对象
*
*/
#define list_for_each(pos, head) \
        for (pos = (head)->next; pos != (head); pos = pos->next)
                

 /**
 * @brief 安全正序遍历连表，使用了n来缓存pos对象
 *
 * @param pos:     当前节点
 * @param n        下一个节点
 * @param head:    指针对象
 *
 */
#define list_for_each_safe(pos, n, head) \
        for (pos = (head)->next, n = pos->next; pos != (head); pos = n, n = pos->next)

 /**
 * @brief 反序遍历连表
 *
 * @param pos:     当前节点
 * @param head:    指针对象
 *
 */
#define list_for_each_prev(pos, head) \
        for (pos = (head)->prev; pos != (head); pos = pos->prev )

 /**
 * @brief 交换两个节点
 *
 * @param _old:    老节点
 * @param _new:    新节点
 *
 */
static INLINE void list_replace(struct list_head *_old,
                                struct list_head *_new)
{
        _new->next = _old->next;
        _new->next->prev = _new;
        _new->prev = _old->prev;
        _new->prev->next = _new;
}

/**
* @brief 替换某个节点，将老节点的指针清理掉
*
* @param _old:    老节点
* @param _new:    新节点
*
*/
static INLINE void list_replace_init(struct list_head *_old,
                                        struct list_head *_new)
{
        list_replace(_old, _new);
        INIT_LIST_HEAD(_old);
}

#endif


