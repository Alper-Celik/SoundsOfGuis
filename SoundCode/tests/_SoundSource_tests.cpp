#include "SoundCode.hpp"
#include "impl/_ErrorHelper.hpp"
#include "impl/_SoundSource.hpp"

#include <alc.h>
#include <catch2/catch_test_macros.hpp>

#include <filesystem>
#include <thread>
namespace
{
std::filesystem::path metarial_dir{TEST_METARIAL_DIR};
}
TEST_CASE("invariant of SoundSource", "[internal][SoundCode]")
{
    using namespace sog;
    SoundManager s; // initilize al context

    SECTION("empty constractor")
    {
        SoundSource source;
    };
    SECTION("constract from buffer")
    {
        ALuint buffer;
        alGenBuffers(1, &buffer);
        sog::al_check_error();
        SoundSource source{buffer};
        ALuint last_buffer;
        alGetSourcei(source.get_source_handle(), AL_BUFFER,
                     reinterpret_cast<int *>(&last_buffer));
        CHECK(buffer == last_buffer);
    }

    SECTION("move constractor")
    {
        SoundSource first;
        auto handle_first = first.get_source_handle();
        SoundSource second{std::move(first)};
        CHECK(handle_first == second.get_source_handle());
    }
    SECTION("move assignment")
    {
        SoundSource first, second;
        auto handle_first = first.get_source_handle();
        auto handle_second = second.get_source_handle();
        first = std::move(second);
        CHECK(handle_first == second.get_source_handle());
        CHECK(handle_second == first.get_source_handle());
    }
}

constexpr auto min_sound_duration = std::chrono::milliseconds{500};
TEST_CASE("play stop test", "[internal][SoundCode]")
{
    using namespace sog;
    SoundManager s; // initilize al context

    auto sound_file_path = metarial_dir / "mono_sound.wav";
    SoundSource s1{load_sound(sound_file_path.string())};
    SECTION("sound should not be playing after sound ended")
    {
        s1.play();
        CHECK(s1.is_playing());
        std::this_thread::sleep_for(min_sound_duration);
        CHECK_FALSE(s1.is_playing());
    }
    SECTION("start stop")
    {
        CHECK(s1.is_initial());

        s1.play();
        CHECK(s1.is_playing());
        CHECK_FALSE(s1.is_initial());

        s1.stop();
        CHECK_FALSE(s1.is_playing());
    }
}

TEST_CASE("loop test", "[internal][SoundCode]")
{

    using namespace sog;
    SoundManager s; // initilize al context

    auto sound_file_path = metarial_dir / "mono_sound.wav";
    SoundSource s1{load_sound(sound_file_path.string())};

    s1.loop();
    CHECK(s1.is_looping());
    CHECK(s1.is_initial()); // setting loop does not affect initial state
    s1.play();
    CHECK(s1.is_playing());

    std::this_thread::sleep_for(min_sound_duration);
    CHECK(s1.is_playing());

    s1.loop(false);
    CHECK_FALSE(s1.is_looping());
    std::this_thread::sleep_for(min_sound_duration);
    CHECK_FALSE(s1.is_playing());
}

TEST_CASE("position test", "[internal][SoundCode]")
{
    using namespace sog;
    SoundManager s; // initilize al context

    SoundSource s1;
    CHECK(s1.get_position() == point3{0, 0, 0});
    s1.set_position({1, 2, 3});
    CHECK(s1.get_position() == point3{1, 2, 3});
}
