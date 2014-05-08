/*========================================================================
#   FileName: mempool.h
#     Author: kevinlin
#      Email: linjiang1205@qq.com
#   History:  a mempool , as you can see, it's not a thread-safe lib
# LastChange: 2014-05-07 23:31:10
========================================================================*/
#ifndef _MEM_POOL_H_
#define _MEM_POOL_H_

#include <stddef.h>
#include <stdio.h>
#include <string.h>


template <typename T>
class mempool 
{
    static const size_t INVALID_POINTER = (size_t)(-1);

    struct node{
        node* next; //如果该值为０表示已经分配使用的node,否则next值用来链接空闲链
                    //INVALID_POINTER 表示空闲链尾
        char  data[0];
    };

    struct header{
        size_t max_size;    //最大可分配内存
        size_t alloc_size;  //已经分配的内存大小
        size_t data_size;   //存储的类型大小
        size_t block_size;  // sizeof(node) + sizeof(T)
        size_t free_list;   //空闲链
    };

public:
    int init(void *mem, size_t sz) {

        mem_header_ = (char*)mem;

        //init header_
        _header()->max_size = sz;
        _header()->alloc_size = sizeof(header);
        _header()->data_size = _data_size();
        _header()->block_size = _block_size();
        _header()->free_list = INVALID_POINTER;

        return 0;
    }

    T* malloc(bool be_zero = true) {

        T* p = NULL;

        if(INVALID_POINTER != _header()->free_list ){
            //first, alloc from free_list
            p =  _malloc_from_free_list();
        }
        else{
            //then..
            p =  _malloc_from_mem();
        }

        if(be_zero){
            memset(p, 0 , sizeof(T));
        }

        return p;
    }


    void free(const T* n) {
        node* p = (node*)((char*)n - offsetof(node, data));
        node* free_list = _ref(_header()->free_list);
        p->next = free_list;
        _header()->free_list = _deref(p);
    }

private:

    inline header* _header()const{
        return (header*) mem_header_;
    }
    inline size_t _block_size() const{
        return sizeof(node) + sizeof(T);
    }
    inline size_t _data_size() const{
        return sizeof(T);
    }

    inline node* _ref(size_t offset)const{
        return (node*)(mem_header_ + offset);
    }

    inline size_t _deref(const node* n)const{
        return (char*)n - mem_header_;
    }

    inline bool _is_vaild_node(const node* p)const{
        return ( (char*)p - mem_header_ < _header()->max_size);
    }

    T* _malloc_from_mem() {

        node* p = _ref(_header()->alloc_size);

        if(!_is_vaild_node(p)) {
            return NULL;
        }

        _header()->alloc_size += _block_size();

        p->next = 0;
        return (T*)p->data;
    }

    T* _malloc_from_free_list() {

        node *p = _ref(_header()->free_list);
        _header()->free_list = _deref(p->next);
        return (T*)p->data;
    }


private:
    //header  *header_;
    char    *mem_header_;
};


#endif

