#include "impl/_SoundSource.hpp"

#include "ExceptionUtils.hpp"
#include "impl/_ErrorHelper.hpp"

#include <al.h>
#include <fmt/core.h>

#include <algorithm>
#include <stdexcept>
namespace sog
{
SoundSource::SoundSource()
{
    alGenSources(1, &source_handle);
    sog::al_check_error();
}
SoundSource::SoundSource(unsigned int sound_buffer)
{
    alGenSources(1, &source_handle);
    sog::al_check_error();

    alSourcei(source_handle, AL_BUFFER, static_cast<ALint>(sound_buffer));
    sog::al_check_error();
}

SoundSource::SoundSource(SoundSource &&other)
{
    alGenSources(1, &source_handle);
    sog::al_check_error();

    std::swap(source_handle, other.source_handle);
}

SoundSource &SoundSource::operator=(SoundSource &&other)
{
    std::swap(source_handle, other.source_handle);
    return *this;
}

SoundSource::~SoundSource()
{
    alDeleteSources(1, &source_handle);
}
unsigned int SoundSource::get_source_handle()
{
    return source_handle;
}

void SoundSource::play()
{
    if (!is_playing())
    { // sound restarts if we play sound while it is playing
        alSourcePlay(source_handle);
        sog::al_check_error();
    }
};
void SoundSource::stop()
{
    alSourceStop(source_handle);
    sog::al_check_error();
}
bool SoundSource::is_playing()
{
    int playing;
    alGetSourcei(source_handle, AL_SOURCE_STATE, &playing);
    sog::al_check_error();
    if (playing == AL_PLAYING)
        return true;
    else
        return false;
}
bool SoundSource::is_initial()
{
    int playing;
    alGetSourcei(source_handle, AL_SOURCE_STATE, &playing);
    sog::al_check_error();
    if (playing == AL_INITIAL)
        return true;
    else
        return false;
}

void SoundSource::loop(bool loop)
{
    alSourcei(source_handle, AL_LOOPING, loop);
    sog::al_check_error();
}
bool SoundSource::is_looping()
{
    int is_looping;
    alGetSourcei(source_handle, AL_LOOPING, &is_looping);
    sog::al_check_error();
    return is_looping;
}

void SoundSource::set_position(point3 pos)
{
    alSource3f(source_handle, AL_POSITION, pos.x, pos.y, pos.z);
    sog::al_check_error();
}
point3 SoundSource::get_position()
{
    point3 out;
    alGetSource3f(source_handle, AL_POSITION, &out.x, &out.y, &out.z);
    sog::al_check_error();
    return out;
}
} // namespace sog
