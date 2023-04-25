#include "SoundCode.hpp"
#include "impl/_ErrorHelper.hpp"

#include "static_initilizer.hpp"

#include <al.h>
#include <alc.h>

#include <fmt/core.h>
#include <gsl/gsl>
#include <iostream>
#include <sndfile.hh>

#include <boost/range/adaptor/reversed.hpp>

#include <memory>
#include <optional>
#include <stdexcept>

namespace sog {
SoundManager::SoundManager() {
  if (alcGetCurrentContext() == nullptr) {
    auto device = alcOpenDevice(nullptr);
    auto context = alcCreateContext(device, nullptr);
    alcMakeContextCurrent(context);
    sog::al_check_error();
  }
}

unsigned int load_sound(std::string sound_file_path) {
  auto error_check_sf = [](SndfileHandle &handle) {
    if (int err = handle.error(); err != SF_ERR_NO_ERROR) {
      std::cerr << sf_error_number(err);
      throw_with_trace(std::runtime_error(sf_error_number(err)));
    }
  };

  std::cerr << sound_file_path;
  SndfileHandle sndfile{sound_file_path};
  error_check_sf(sndfile);

  int format = AL_NONE;
  if (sndfile.channels() == 1) {
    format = AL_FORMAT_MONO16;
  } else {
    throw_with_trace(std::runtime_error{
        fmt::format("\"{}\"contains more than 1 channel which is unsupported",
                    sound_file_path)}); // sounds with more than 1 channel
                                        // doesnt have 3d spatialization
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
  return buffer;
}

void SoundManager::load_element(sog::element_type type,
                                ElementInfo element_info,
                                std::optional<std::string> sound_file_path) {
  std::optional<unsigned int> sound_buffer;

  if (sound_file_path.has_value()) {
    sound_buffer = load_sound(*sound_file_path);
  }
  sounds.emplace(type, std::make_pair(sound_buffer, element_info));
}

void SoundManager::add_element(sog::element_type type) {
  ElementInfo info{};
  std::optional<unsigned int> buffer{std::nullopt};
  try {
    auto [_buffer, _info] = sounds.at(type);
    info = _info;
    buffer = _buffer;
  } catch (const std::exception &e) {
    // element might not be defined
    // TODO: proper logging
  }
  SoundSource source{};
  std::cerr << "test1\n";
  if (buffer.has_value()) {
    std::cerr << "test\n";
    source = std::move(SoundSource{*buffer});
  }

  elements.emplace_back(type, info, std::move(source));
}
void SoundManager::remove_last() {
  if (elements.empty())
    throw_with_trace(
        std::runtime_error("can not remove last element from empty sound "
                           "manager \n be carefull you(developer)"
                           "almost trigered an undifend behavior ;)"));
  elements.pop_back();
}
void SoundManager::refresh_sounds() {
  alcSuspendContext(alcGetCurrentContext());
  gsl::finally([] {
    alcProcessContext(alcGetCurrentContext());
  }); // resume context at end of scope or at exception

  Point3<float> last_pos{0, 0, 0};
  for (auto &[name, info, source] : boost::adaptors::reverse(elements)) {
    source.set_position(last_pos);
    last_pos += info.distance_to_other;

    if (source.is_looping() != info.is_looping) {
      source.loop(info.is_looping);
    }
    if (source.is_initial()) {
      source.play();
    }
  }
}
} // namespace sog
