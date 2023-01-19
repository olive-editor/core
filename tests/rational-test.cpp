/***

  Olive - Non-Linear Video Editor
  Copyright (C) 2023 Olive Studios LLC

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

***/

#include <cstring>

#include "util/rational.h"
#include "util/tests.h"

using namespace olive::core;

bool rational_to_from_string_test()
{
  rational r(1, 30);

  std::string s = r.toString();

  rational r2 = rational::fromString(s);

  return r == r2;
}

bool rational_to_from_string_test2()
{
  rational r(69, 420);

  std::string s = r.toString();

  rational r2 = rational::fromString(s);

  return r == r2;
}

int main()
{
  Tester t;

  t.add("rational::toString/fromString", rational_to_from_string_test);
  t.add("rational::toString/fromString2", rational_to_from_string_test2);

  if (t.run()) {
    return 0;
  } else {
    return 1;
  }
}
