#pragma once

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
};
} // namespace sog
