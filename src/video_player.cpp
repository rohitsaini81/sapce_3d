#include "video_player.h"
#include <iostream>

VideoPlayer::VideoPlayer(const std::string& path) {
    avformat_open_input(&fmt, path.c_str(), nullptr, nullptr);
    if (!fmt) return;

    avformat_find_stream_info(fmt, nullptr);

    // Find video stream
    for (unsigned i = 0; i < fmt->nb_streams; i++) {
        if (fmt->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStream = i;
            break;
        }
    }
    if (videoStream < 0) return;

    AVCodecParameters* params = fmt->streams[videoStream]->codecpar;
    const AVCodec* codecPtr = avcodec_find_decoder(params->codec_id);
    codec = avcodec_alloc_context3(codecPtr);
    avcodec_parameters_to_context(codec, params);
    avcodec_open2(codec, codecPtr, nullptr);

    frame = av_frame_alloc();
    rgbFrame = av_frame_alloc();
    packet = av_packet_alloc();

    // Allocate RGB buffer
    int rgbBufSize = av_image_get_buffer_size(AV_PIX_FMT_RGB24,
                                              codec->width,
                                              codec->height,
                                              1);
    rgbBuffer = (uint8_t*)av_malloc(rgbBufSize);
    av_image_fill_arrays(rgbFrame->data, rgbFrame->linesize, rgbBuffer,
                         AV_PIX_FMT_RGB24, codec->width, codec->height, 1);

    // Create swscale context
    sws = sws_getContext(codec->width, codec->height, codec->pix_fmt,
                         codec->width, codec->height, AV_PIX_FMT_RGB24,
                         SWS_BILINEAR, nullptr, nullptr, nullptr);

    // Create raylib texture

    Image img {};
img.data = buffer;
img.width = w;
img.height = h;
img.mipmaps = 1;
img.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8;



    tex = LoadTextureFromImage(img);

    fps = av_q2d(fmt->streams[videoStream]->r_frame_rate);
    nextFrameTime = GetTime();

    valid = true;
}

VideoPlayer::~VideoPlayer() {
    if (valid) UnloadTexture(tex);
    sws_freeContext(sws);
    av_free(rgbBuffer);
    av_frame_free(&frame);
    av_frame_free(&rgbFrame);
    av_packet_free(&packet);
    avcodec_free_context(&codec);
    avformat_close_input(&fmt);
}

void VideoPlayer::Update() {
    if (!valid) return;

    double t = GetTime();
    if (t < nextFrameTime) return;
    nextFrameTime += 1.0 / fps;

    // Read frames until we get a video frame
    while (av_read_frame(fmt, packet) >= 0) {
        if (packet->stream_index == videoStream) {
            avcodec_send_packet(codec, packet);
            if (avcodec_receive_frame(codec, frame) == 0) {

                // Convert YUV -> RGB
                sws_scale(sws,
                          frame->data, frame->linesize,
                          0, codec->height,
                          rgbFrame->data, rgbFrame->linesize);

                // Update GPU texture
                UpdateTexture(tex, rgbBuffer);
                break;
            }
        }
        av_packet_unref(packet);
    }
}

void VideoPlayer::Draw(int x, int y) {
    if (valid)
        DrawTexture(tex, x, y, WHITE);
}

