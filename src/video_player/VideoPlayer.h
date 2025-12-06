#pragma once
#include "raylib.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
}

class VideoPlayer {
public:
    VideoPlayer(const char* filename);
    ~VideoPlayer();

    bool IsLoaded() const { return loaded; }
    bool Update();     // Decodes next frame (returns false if video ends)
    void Render(int x, int y);

private:
    bool loaded = false;

    // FFmpeg
    AVFormatContext* fmt = nullptr;
    AVCodecContext* ctx = nullptr;
    SwsContext* sws = nullptr;

    int videoStream = -1;

    AVFrame* frame = nullptr;
    AVFrame* rgb = nullptr;
    AVPacket* packet = nullptr;

    uint8_t* rgbBuffer = nullptr;

    // Raylib
    Texture2D tex{};
};
