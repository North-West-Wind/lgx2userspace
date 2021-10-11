#ifndef LGX2USERSPACE_LGXDEVICE_H
#define LGX2USERSPACE_LGXDEVICE_H

#include <functional>
#include <cstdint>
#include "FrameBuilder.h"

namespace lgx2 {

    class Stream {
    public:
        virtual void streamSetupCommands() = 0;

        virtual void queueFrameRead(std::function<void(uint8_t *frameData)> *onData) = 0;

        virtual void update() = 0;
    };

    class VideoOutput {
    public:
        virtual void initialiseVideo() = 0;

        virtual void videoFrameAvailable(uint32_t *image) = 0;

        virtual void display() = 0;
    private:
    };

    class AudioOutput {
    public:
        virtual void initialiseAudio() = 0;

        virtual void audioFrameAvailable(uint32_t *audio) = 0;

        virtual void render() = 0;
    private:
    };

    class Device {
    public:
        Device(Stream *stream, VideoOutput *videoOutput, AudioOutput *audioOutput);

        void initialise();

        void run();

    private:
        Stream *_stream;
        VideoOutput *_videoOutput;
        AudioOutput *_audioOutput;

        utils::FrameBuilder _frameBuilder;

        std::function<void(uint8_t *)> _onFrameData;

        void onFrameData(uint8_t *data);

        void produceVideoData(uint8_t *data);

        void produceAudioData(uint8_t *data);
    };

}

#endif
