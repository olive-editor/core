#ifndef TESTS_H
#define TESTS_H

#include <list>

namespace olive::core {

class Tester
{
public:
  Tester() = default;

  typedef bool (*test_t)();

  void add(const char *name, test_t test_function)
  {
    test_names_.push_back(name);
    test_functions_.push_back(test_function);
  }

  bool run();

  static void echo(const char *fmt, ...);

private:
  std::list<const char*> test_names_;
  std::list<test_t> test_functions_;

};

}

#endif // TESTS_H
