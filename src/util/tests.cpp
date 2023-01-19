#include "tests.h"

#include <cstddef>
#include <cstdio>
#include <stdarg.h>

namespace olive::core {

bool Tester::run()
{
  size_t index = 1;
  size_t count = test_functions_.size();

  while (!test_functions_.empty()) {
    echo("[%lu/%lu] %s :: ", index, count, test_names_.front());

    if (test_functions_.front()()) {
      echo("PASSED\n");
    } else {
      echo("FAILED\n");
      return false;
    }

    test_names_.pop_front();
    test_functions_.pop_front();
  }

  return true;
}

void Tester::echo(const char *fmt, ...)
{
  va_list a;
  va_start(a, fmt);

  vfprintf(stderr, fmt, a);

  va_end(a);
}

}
