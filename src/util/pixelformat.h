#ifndef PIXELFORMAT_H
#define PIXELFORMAT_H

namespace olive::core {

class PixelFormat
{
public:
  enum Format {
    INVALID = -1,
    U8,
    U16,
    F16,
    F32,
    FORMAT_COUNT
  };

  PixelFormat(Format f = INVALID) { f_ = f; }

  operator Format() const { return f_; }

  static int byte_count(Format f)
  {
    switch (f) {
    case INVALID:
    case FORMAT_COUNT:
      break;
    case U8:
      return 1;
    case U16:
    case F16:
      return 2;
    case F32:
      return 4;
    }

    return 0;
  }

  int byte_count() const
  {
    return byte_count(f_);
  }

  bool is_float(Format f)
  {
    switch (f) {
    case INVALID:
    case FORMAT_COUNT:
    case U8:
    case U16:
      break;
    case F16:
    case F32:
      return true;
    }

    return false;
  }

private:
  Format f_;

};

}

#endif // PIXELFORMAT_H
