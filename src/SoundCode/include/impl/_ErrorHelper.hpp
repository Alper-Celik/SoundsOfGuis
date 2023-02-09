#pragma once
#include "ExceptionUtils.hpp"

#include <al.h>

#include <string>

namespace sog {

inline std::string get_al_err_code_name(ALenum err_code) {
  using namespace std::string_literals;
  switch (err_code) {
  case AL_NO_ERROR:
    return "AL_NO_ERROR"s;
  case AL_INVALID_ENUM:
    return "AL_INVALID_ENUM"s;
  case AL_INVALID_NAME:
    return "AL_INVALID_NAME"s;
  case AL_INVALID_VALUE:
    return "AL_INVALID_VALUE"s;
  case AL_INVALID_OPERATION:
    return "AL_INVALID_OPERATION"s;
  case AL_OUT_OF_MEMORY:
    return "AL_OUT_OF_MEMORY"s;
  default:
    return "unknown error code : "s + std::to_string(err_code);
  }
}

inline void al_check_error() {
  if (auto err_code = alGetError(); err_code != AL_NO_ERROR) {
    throw_with_trace(std::runtime_error(get_al_err_code_name(err_code)));
  }
}
} // namespace sog
