# vtable check demo Makefile
# 演示 GameSvr 用 dlopen 加载两个 SO（good/bad）并校验 vtable 一致性。

CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g -Wno-pmf-conversions -fPIC
LDFLAGS  := -ldl -rdynamic

TARGET   := vtable_check_demo
SRCS     := vtable_check_demo.cpp room_impl.cpp

# 两个被加载的 SO
GOOD_SO  := libgood_so.so
BAD_SO   := libbad_so.so

.PHONY: all
all: $(TARGET) $(GOOD_SO) $(BAD_SO)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

$(GOOD_SO): good_so.cpp room.hpp
	$(CXX) $(CXXFLAGS) -shared -o $(GOOD_SO) good_so.cpp

$(BAD_SO): bad_so.cpp room.hpp
	$(CXX) $(CXXFLAGS) -shared -o $(BAD_SO) bad_so.cpp

.PHONY: run clean
run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) $(GOOD_SO) $(BAD_SO)
