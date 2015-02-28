TARGET=time_wheel_test boost_asio_timer 

all: ${TARGET}
.PHONY : all

time_wheel_test: time_wheel_test.cpp time_wheel.hpp
	g++ $< -o $@


boost_asio_timer: boost_asio_timer.cpp 
	g++ $< -I /usr/local/boost/include /usr/local/boost/lib/libboost_system.a -o $@

clean:
	rm -rf ${TARGET}

.PHONY : clean

