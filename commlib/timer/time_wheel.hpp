#ifndef TIME_WHEEL_TIMER
#define TIME_WHEEL_TIMER

#include <time.h>
//#include <netinet/in.h>
#include <stdio.h>

#define BUFFER_SIZE 64

class tw_timer;

struct client_data
{
    //socketaddr_in address;
    int sockfd;
    char buf[BUFFER_SIZE];
    tw_timer* timer;
};

//定时器类
class tw_timer
{
public:
    tw_timer(int rot, int ts) : next(NULL), prev(NULL), rotation(rot), time_slot(ts){}
    
public:
    int rotation; //定时器在时间轮转多少圈后生效
    int time_slot; //定时器属于时间轮上哪个槽
    void (*cb_func) (client_data*); //定时器回调函数
    client_data* user_data; //客户数据
    tw_timer* next;
    tw_timer* prev;
};

class time_wheel
{
public:
    time_wheel() : cur_slot(0)
    {
        for(int i=0; i < N; ++i)
        {
            slots[i] = NULL; //初始化每个槽的头结点
        }
    }

    ~time_wheel()
    {
        //遍历每个槽，并销毁其中的定时器
        for(int i=0; i < N; ++i)
        {
            tw_timer* tmp = slots[i];
            while(tmp)
            {
                slots[i] = tmp->next;
                delete tmp;
                tmp = slots[i];
            }
        }
    }

    //根据timeout的值创建定时器，并插入到合适的槽中
    tw_timer* add_timer(int timeout)
    {
        if(timeout < 0)
        {
            return NULL;
        }

        int ticks = 0; //计算超时时间在时间轮转多少个滴答后触发
        if( timeout < SI)
        {
            ticks = 1;
        }
        else
        {
            ticks = timeout/SI;
        }

        //计算待插入的定时器在时间轮转动多少圈后被触发
        int rotation = ticks / N;

        //计算定时器应该被插入到哪个槽中
        int ts = (cur_slot + (ticks % N)) % N;

        //创建新的定时器，它在时间轮转动rotation圈之后被触发，且位于第ts个槽上
        tw_timer* timer = new tw_timer(rotation , ts);

        //如果第ts个槽中尚无任何定时器，则把新建的定时器插入到其中，并将该定时器设置为该槽头结点
        if(!slots[ts])
        {
            printf("add timer, rotation is %d, ts is %d, cur_slot is %d\n",
                    rotation, ts, cur_slot);
            slots[ts] = timer;
        }
        else //否则将定时器插入到第ts个槽中
        {
            timer->next = slots[ts];
            slots[ts]->prev = timer;  
            slots[ts] = timer; //想想为什么插入到头结点
        }
        return timer; 
    }

    //删除定时器
    //定时器是否需要删除方法，这是一个有争议的话题
    void del_timer(tw_timer* timer)
    {
        if(!timer)
        {
            return;
        }

        int ts = timer->time_slot;
        if(timer == slots[ts]) //如果定时器是头结点，则要修改其next的结点的属性
        {
            slots[ts] = slots[ts]->next;
            if(slots[ts])
            {
                slots[ts]->prev = NULL;
            }
            delete timer;
        }
        else
        {
            timer->prev->next = timer->next;
            if(timer->next)
            {
                timer->next->prev = timer->prev;
            }
            delete timer;
        }
    }

    //SI时间到后，调用该函数，时间轮向前滚动一个槽的间隔
    void tick()
    {
        tw_timer* tmp = slots[cur_slot];
        printf("current slot is %d\n", cur_slot);
        while(tmp)
        {
            printf("tick the timer once\n");

            //如果定时器的rotation>0则在这轮不起作用
            if(tmp->rotation > 0)
            {
                tmp->rotation--;
                tmp = tmp->next;
            }
            else //否则说明定时器到期，于是执行定时任务， 然后删除该定时器
            {
                tmp->cb_func(tmp->user_data);
                tw_timer* del = tmp;
                tmp = del->next;
                del_timer(del);
           }
        }

        cur_slot = (++cur_slot) % N;
    }

private:
    //时间轮上槽的数目
    static const int N = 60;
    //每1s时间轮转动一次，即槽间隔为1s
    static const int SI = 1;
    //时间轮的槽，其中每个元素指向定时器链表，链表无序
    tw_timer* slots[N];
    //时间轮的当前槽
    int cur_slot;
};

#endif

