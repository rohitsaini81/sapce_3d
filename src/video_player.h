#pragma once
#include <string>
#include "raylib.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
}



class VideoPlayer {
public:
    VideoPlayer(const std::string& path);
    ~VideoPlayer();

    bool IsValid() const { return valid; }
    void Update();
    void Draw(int x, int y);

private:
    bool valid = false;

    AVFormatContext* fmt = nullptr;
    AVCodecContext* codec = nullptr;
    AVFrame* frame = nullptr;
    AVFrame* rgbFrame = nullptr;
    AVPacket* packet = nullptr;
    SwsContext* sws = nullptr;
    int videoStream = -1;

    Texture2D tex;
    uint8_t* rgbBuffer = nullptr;
    double nextFrameTime = 0;
    double fps = 30.0;
};

