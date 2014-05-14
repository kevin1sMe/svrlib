#include <assert.h>
#include <stdlib.h>
#include "mempool.h"

struct mydata {
    char name[9];
    int  age;
};

#define ALLOC_BYTES  128

int 
main(int argc, char** argv) {

    printf("sizeof(mydata):%lu\n", sizeof(mydata));
    void *mem = malloc(ALLOC_BYTES);

    mempool<mydata> pool;
    
    pool.init(mem, ALLOC_BYTES);

    printf("Dump:%s\n", pool.DumpHeader().c_str());

    struct mydata *data = pool.malloc();
    printf("data:%p mem:%p\n",data, mem);

    struct mydata *tmp = data;

    data->age = 28;
    snprintf(data->name, sizeof(data->name), "%s", "kevin");

    printf("data:%p [%s] age:%d\n",data,  data->name, data->age);
    printf("Dump:%s\n", pool.DumpHeader().c_str());


    data = pool.malloc();
    data->age = 2;
    snprintf(data->name, sizeof(data->name), "%s", "kevin's son");

    printf("data:%p [%s] age:%d\n", data, data->name, data->age);

    printf("Dump:%s\n", pool.DumpHeader().c_str());

    //free one
    pool.free(tmp);

    printf("Dump:%s\n", pool.DumpHeader().c_str());


    //realloc
    data = pool.malloc();
    printf("data:%p\n", data);



    free(mem);


    return 0;
}
