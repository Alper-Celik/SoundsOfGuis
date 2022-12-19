#include "SoundCode.hpp"
#include "impl/_ErrorHelper.hpp"

#include "static_initilizer.hpp"

#include <al.h>
#include <alc.h>

#include <fmt/core.h>
#include <sndfile.hh>

#include <memory>
#include <stdexcept>

namespace sog {

static_init init_sound_systems{[]() { /// TODO: dont use global initilazition
  auto device = alcOpenDevice(nullptr);
  auto context = alcCreateContext(device, nullptr);
  alcMakeContextCurrent(context);
  al_check_error();
}};

void SoundManager::load_sound(std::string name, std::string file) {

  auto error_check_sf = [](SndfileHandle &handle) {
    if (auto err = handle.error(); err != SF_ERR_NO_ERROR) {
      throw_with_trace(std::runtime_error(sf_error_number(err)));
    }
  };

  SndfileHandle sndfile{file};
  error_check_sf(sndfile);

  int format = AL_NONE;
  if (sndfile.channels() == 1) {
    format = AL_FORMAT_MONO16;
  } else {
    throw_with_trace(std::runtime_error{fmt::format(
        "\"{}\"contains more than 1 channel which is unsupported", file)});
  }
  auto soundData = std::make_unique<short[]>(
      static_cast<size_t>(sndfile.channels() * sndfile.frames()));

  sf_count_t frameCount = sndfile.readf(soundData.get(), sndfile.frames());
  error_check_sf(sndfile);

  ALuint buffer = 0;

  alGenBuffers(1, &buffer);
  al_check_error();
  auto dataSize = static_cast<ALsizei>(
      static_cast<unsigned long long>(frameCount * sndfile.channels()) *
      sizeof(short));

  alBufferData(buffer, format, soundData.get(), dataSize, sndfile.samplerate());
  al_check_error();

  sounds[name] = buffer;
}

} // namespace sog
