ALL = mempool_test

all: ${ALL}

CXXFLAGS = -g

mempool_test: mempool_test.cpp mempool.h
	g++ ${CXXFLAGS} $< -o $@


clean:
	rm ${ALL}
