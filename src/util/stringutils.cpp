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

#include "stringutils.h"

#include <stdarg.h>
#include <stdexcept>

namespace olive::core {

std::vector<std::string> StringUtils::split(const std::string &s, char separator)
{
  std::vector<std::string> output;

  std::string::size_type prev_pos = 0, pos = 0;

  while((pos = s.find(separator, pos)) != std::string::npos) {
    std::string substring(s.substr(prev_pos, pos-prev_pos));

    output.push_back(substring);

    prev_pos = ++pos;
  }

  output.push_back(s.substr(prev_pos, pos-prev_pos)); // Last word

  return output;
}

std::vector<std::string> StringUtils::split_regex(const std::string &s, const std::regex &regex)
{
  std::vector<std::string> output;

  std::sregex_token_iterator iter(s.begin(), s.end(), regex, -1);
  std::sregex_token_iterator end;
  for ( ; iter != end; iter++) {
    output.push_back(*iter);
  }

  return output;
}

int StringUtils::to_int(const std::string &s, int base, bool *ok)
{
  try {
    int x = std::stoi(s, nullptr, base);
    if (ok) { *ok = true; }
    return x;
  } catch (const std::invalid_argument &e) {
    if (ok) { *ok = false; }
    return 0;
  }
}

std::string StringUtils::format(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);

  int sz = std::vsnprintf(nullptr, 0, fmt, ap);
  std::string r;
  r.resize(sz);
  std::vsnprintf(&r[0], sz, fmt, ap);

  va_end(ap);

  return r;
}

}
