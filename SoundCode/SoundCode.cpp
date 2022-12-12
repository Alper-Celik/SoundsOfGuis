#include "SoundCode.hpp"

#include <al.h>
#include <alc.h>

#include <sndfile.hh>

#include <memory>
#include <stdexcept>

namespace sog {
void init_sound_system() {
  if (alcGetCurrentContext() == nullptr) {
    auto device = alcOpenDevice(nullptr);
    auto context = alcCreateContext(device, nullptr);
    alcMakeContextCurrent(context);
  }
}
void SoundManager::load_sound(std::string name, std::string file) {

  SndfileHandle sndfile{file};

  int format = AL_NONE;
  switch (sndfile.channels()) {
  case 1:
    format = AL_FORMAT_MONO16;
    break;
  case 2:
    format = AL_FORMAT_STEREO16;
    break;
  default:
    throw std::runtime_error{"unspported format"};
  }
  auto soundData = std::make_unique<short[]>(
      static_cast<size_t>(sndfile.channels() * sndfile.frames()));

  sf_count_t frameCount = sndfile.readf(soundData.get(), sndfile.frames());

  ALuint buffer = 0;

  // TODO: better error handling
  alGenBuffers(1, &buffer);
  auto dataSize = static_cast<ALsizei>(
      static_cast<unsigned long long>(frameCount * sndfile.channels()) *
      sizeof(short));

  alBufferData(buffer, format, soundData.get(), dataSize, sndfile.samplerate());

  sounds[name] = buffer;
}

} // namespace sog
