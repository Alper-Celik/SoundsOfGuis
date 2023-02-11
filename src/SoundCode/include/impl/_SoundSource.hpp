#pragma once
#include "point3.hpp"

namespace sog {
class SoundSource {

  unsigned int source_handle;

public:
  SoundSource();
  SoundSource(unsigned int sound_buffer);
  SoundSource(SoundSource &&other);
  SoundSource &operator=(SoundSource &&other);
  ~SoundSource();

  SoundSource(const SoundSource &) = delete;
  SoundSource &operator=(const SoundSource &) = delete;

  unsigned int get_source_handle();
  void play();
  void stop();
  bool is_playing();
  /// source is initial until it is played
  bool is_initial();
  void loop(bool loop = true);
  bool is_looping();
  void set_position(Point3 pos);
  Point3 get_position();
};
} // namespace sog
