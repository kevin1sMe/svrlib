#include "time_wheel.hpp"
#include <unistd.h>

void print_client_data(client_data* cd)
{
    printf("sockfd:%d buf:%s\n", cd->sockfd, cd->buf);
}

int main()
{
    time_wheel tw;

    //添加一个1s后的定时器
    tw_timer* timer1 = tw.add_timer(1);

    client_data cd;
    cd.sockfd = 1986;
    snprintf(cd.buf, sizeof(cd.buf), "%s", "timer for one second");
    timer1->user_data = &cd;
    timer1->cb_func = print_client_data;         

    //添加一个5s后的定时器
    tw_timer* timer2 = tw.add_timer(5);

    client_data cd2;
    cd2.sockfd = 5555;
    snprintf(cd2.buf, sizeof(cd2.buf), "%s", "timer for 5 second");
    timer2->user_data = &cd2;
    timer2->cb_func = print_client_data;         



    int time = 10;
    while(time--)
    {
        usleep(1000000);
        tw.tick();
    };

    return 0;
}
