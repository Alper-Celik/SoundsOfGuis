#include "_SoundSource.hpp"

#include "ExceptionUtils.hpp"
#include "_ErrorHelper.hpp"

#include <al.h>
#include <fmt/core.h>

#include <algorithm>
#include <stdexcept>
namespace sog {
SoundSource::SoundSource() {
  alGenSources(1, &source_handle);
  al_check_error();
}
SoundSource::SoundSource(unsigned int sound_buffer) {
  alGenSources(1, &source_handle);
  al_check_error();

  alSourcei(source_handle, AL_BUFFER, static_cast<ALint>(sound_buffer));
  al_check_error();
}

SoundSource::SoundSource(SoundSource &&other) {
  alGenSources(1, &source_handle);
  al_check_error();

  std::swap(source_handle, other.source_handle);
}

SoundSource &SoundSource::operator=(SoundSource &&other) {
  std::swap(source_handle, other.source_handle);
  return *this;
}

SoundSource::~SoundSource() { alDeleteSources(1, &source_handle); }
unsigned int SoundSource::get_source_handle() { return source_handle; }
} // namespace sog
