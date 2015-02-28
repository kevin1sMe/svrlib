TARGET=time_wheel_test boost_asio_timer 

all: ${TARGET}
.PHONY : all

time_wheel_test: time_wheel_test.cpp
	g++ $^ -o $@


boost_asio_timer: boost_asio_timer.cpp 
	g++ $^ -o $@ -I /usr/local/boost/include /usr/local/boost/lib/libboost_system.a 

clean:
	rm -rf ${TARGET}

.PHONY : clean

