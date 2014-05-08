#include <assert.h>
#include <stdlib.h>
#include "mempool.h"

struct mydata {
    int  age;
    char name[16];
};

#define ALLOC_BYTES  128

int 
main(int argc, char** argv) {
    void *mem = malloc(ALLOC_BYTES);

    mempool<mydata> pool;
    
    pool.init(mem, ALLOC_BYTES);

    struct mydata *data = pool.malloc();
    printf("data:%p mem:%p\n",data, mem);

    struct mydata *tmp = data;

    data->age = 28;
    snprintf(data->name, sizeof(data->name), "%s", "kevin");

    printf("data:%p [%s] age:%d\n",data,  data->name, data->age);

    data = pool.malloc();
    data->age = 2;
    snprintf(data->name, sizeof(data->name), "%s", "kevin's son");

    printf("data:%p [%s] age:%d\n", data, data->name, data->age);


    //free one
    pool.free(tmp);

    //realloc
    data = pool.malloc();
    printf("data:%p\n", data);


    free(mem);


    return 0;
}
