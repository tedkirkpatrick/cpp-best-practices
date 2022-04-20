#include <iostream>

static constexpr int test_val = 5;

// Following example based upon
// https://github.com/github/codeql/blob/main/cpp/ql/src/Critical/GlobalUseBeforeInit.cpp

int g_callCtr; // NOLINT cppcoreguidelines-avoid-non-const-global-variables

void initGlobals() {
	g_callCtr = 0;
}

// CodeQL query only requires that there be a global function named "socket"
// See code for 'predicate allocateDescriptorCall' at:
// https://github.com/github/codeql/blob/b433f08cef9038d60e2bdf50bfedaf112f35d3f6/cpp/ql/lib/semmle/code/cpp/pointsto/PointsTo.qll#L699

int socket (int aVal) {
  return aVal;
}

void close(int socket) {
  // Must use parameter
  [[maybe_unused]] int _ = socket;
}

// Following from example
// https://github.com/github/codeql/blob/main/cpp/ql/src/Critical/DescriptorMayNotBeClosed.cpp
int f(int chVal) {
	try {
	        int sockfd = socket(chVal);
		return sockfd; //if there are no exceptions, the socket is returned
	} catch (int do_stuff_exception) {
		return -1; //return error value, but sockfd may still be open
	}
}

// My own example
int g(int chVal) {
  int sockfd = socket(chVal);
  if (sockfd != -1) {
    close(sockfd);
    return 0;
  }
  return sockfd;
  //return 0;
}

// NOLINTNEXTLINE [cppcoreguidelines-special-member-functions,hicpp-special-member-functions]
class Test {
 public:
  Test() = default;
  explicit Test(int a) : m_a(a) {}
  Test(Test const & t) = default;

  int get_a() const { return m_a; }

 private:
  int m_a {};
};

int main (int argc, char**) {
  std::cout << Test(test_val).get_a() << '\n';

  std::cout << g_callCtr << '\n';
  initGlobals();

  g(argc);
}
