/**
 * @file lhash.h
 * @author swordhell
 * @date 2 Nov 2019
 * @brief 简单的hash数据结构
 *
 */
#ifndef _lhash_h_
#define _lhash_h_

/**
 * @brief 定义操作返回值
 */
typedef enum HashOptResult_enum {
  HashOptResult_OK,  /**< 操作成功 */
  HashOptResult_NotFind, /**< 查找失败 */
  HashOptResult_DuplicatedInsert, /**< 重复加入 */
  HashOptResult_MallocFail, /**< 分配内存失败 */
  HashOptResult_InvalidateParam, /**< 参数错误 */
} HashOptResult;

/**
* @brief 创建hash对象
*
* @param _hash_size    hash池大小
* @param _free_size    初始化内存池大小
* @param _name         hash的名称
*
* @return 返回hash对象，创建失败时将返回空
*
*/
void *create_hash( unsigned long _hash_size , unsigned long _free_size, const char* _name );

/**
 * @brief 释放hash对象
 *
 */
void release_hash(void *_hash);

/**
 * @brief 向hash中保存关键字，数据
 *
 * @param _hash        hash对象
 * @param _key         关键字
 * @param _val         设置的数据
 *
 * @return             返回操作结果
 *
 * @see HashOptResult
 *
 */
HashOptResult hash_set(void *_hash, unsigned long _key, unsigned long _val);

/**
 * @brief 从hash对象中通过关键字查找数据
 *
 * @param _hash        hash对象
 * @param _key         关键字
 * @param _val         返回数据
 *
 * @return             返回操作结果
 *
 * @see HashOptResult
 */
HashOptResult hash_find( void *_hash, unsigned long _key, unsigned long* _val );

/**
 * @brief 从hash中删除关键字
 *
 * @param _hash        hash对象
 * @param _key         关键字
 *
 * @return             返回操作结果
 *
 * @see HashOptResult
 *
 */
HashOptResult hash_del( void *_hash, unsigned long key );

/**
 * @brief 查询hash对象，使用情况
 *
 * @param _hash               hash对象
 * @param _use_node_count     使用节点个数
 * @param _remain_free_node   释放节点个数
 * @param _new_count          新分配节点个数
 * @param _max_use_count      历史上最大使用的节点数
 *
 */
void hash_memory_detail( void *_hash, int *_use_node_count, unsigned int *_remain_free_node
		,unsigned int *_new_count, unsigned int *_max_use_count ) ;

#endif // _lhash_h_

