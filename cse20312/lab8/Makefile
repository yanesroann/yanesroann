CXX=		g++
CXXFLAGS=	-g -gdwarf-2 -Wall -std=gnu++11
LD=		g++
LDFLAGS=
AR=		ar
ARFLAGS=	rcs
SHELL=		bash

LIBRARY=	libmap.a
LIB_SRC=	constants.cpp unsorted.cpp sorted.cpp bst.cpp rbtree.cpp treap.cpp
LIB_OBJ=	$(LIB_SRC:.cpp=.o)

PROGRAMS=	map_test map_bench

all:		$(LIBRARY) $(PROGRAMS)

%.o:		%.cpp map.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(LIBRARY):	$(LIB_OBJ)
	$(AR) $(ARFLAGS) $@ $(LIB_OBJ)

map_test:	map_test.o map.h bst.cpp treap.cpp $(LIBRARY)
	$(LD) $(LDFLAGS) -o $@ $< $(LIBRARY)

map_bench:	map_bench.o map.h $(LIBRARY)
	$(LD) $(LDFLAGS) -o $@ $< $(LIBRARY)

clean:
	rm -f $(LIBRARY) $(PROGRAMS) *.o

test:	test-bst test-treap test-benchmark


test-bst: map_test
	@echo "Testing BST Map (Correctness)..."
	@./map_test -b bst

	@echo "Testing BST Map (Memory)..."
	@[ `valgrind --leak-check=full ./map_test -b bst 2>&1 | grep ERROR | awk '{print $$4}'` = 0 ]

test-treap: map_test
	@echo "Testing Treap Map (Correctness)..."
	@echo "-- Trial 1 --"
	@./map_test -b treap
	@echo "-- Trial 2 --"
	@./map_test -b treap
	@echo "-- Trial 3 --"
	@./map_test -b treap
	@echo "-- Trial 4 --"
	@./map_test -b treap
	@echo "-- Trial 5 --"
	@./map_test -b treap
	@echo ""
	@echo "Testing Treap Map (Memory)..."
	@[ `valgrind --leak-check=full ./map_test -b treap 2>&1 | grep ERROR | awk '{print $$4}'` = 0 ]

test-benchmark: map_bench
	@echo "Benchmarking for n = 30,000 ..."
	@echo "== Unsorted =="
	@./map_bench -b unsorted -n 30000 -p 8
	@echo "== Sorted == "
	@./map_bench -b sorted -n 30000 -p 8
	@echo "== BST == "
	@./map_bench -b bst -n 30000 -p 8
	@echo "== RBTree == "
	@./map_bench -b rbtree -n 30000 -p 8
	@echo "== Treap == "
	@./map_bench -b unsorted -n 30000 -p 8
