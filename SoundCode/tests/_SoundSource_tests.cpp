#include "SoundCode.hpp"
#include "impl/_ErrorHelper.hpp"
#include "impl/_SoundSource.hpp"

#include <alc.h>
#include <catch2/catch_test_macros.hpp>
#include <sndfile.h>

TEST_CASE("invariant of SoundSource", "[internal][SoundCode]") {
  using namespace sog;

  SECTION("empty constractor") { SoundSource source; };
  SECTION("constract from buffer") {
    ALuint buffer;
    alGenBuffers(1, &buffer);
    al_check_error();
    SoundSource source{buffer};
    ALuint last_buffer;
    alGetSourcei(source.get_source_handle(), AL_BUFFER,
                 reinterpret_cast<int *>(&last_buffer));
    CHECK(buffer == last_buffer);
  }

  SECTION("move constractor") {
    SoundSource first;
    auto handle_first = first.get_source_handle();
    SoundSource second{std::move(first)};
    CHECK(handle_first == second.get_source_handle());
  }
  SECTION("move assignment") {
    SoundSource first, second;
    auto handle_first = first.get_source_handle();
    auto handle_second = second.get_source_handle();
    first = std::move(second);
    CHECK(handle_first == second.get_source_handle());
    CHECK(handle_second == first.get_source_handle());
  }
}
