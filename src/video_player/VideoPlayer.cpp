#include "VideoPlayer.h"
#include <iostream>

VideoPlayer::VideoPlayer(const char* filename) {
    avformat_network_init();

    if (avformat_open_input(&fmt, filename, NULL, NULL) != 0) {
        std::cerr << "Can't open video file\n";
        return;
    }
    avformat_find_stream_info(fmt, NULL);

    videoStream = av_find_best_stream(fmt, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    if (videoStream < 0) {
        std::cerr << "No video stream found\n";
        return;
    }

    AVCodecParameters* params = fmt->streams[videoStream]->codecpar;
    const AVCodec* codec = avcodec_find_decoder(params->codec_id);

    ctx = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(ctx, params);
    avcodec_open2(ctx, codec, NULL);

    sws = sws_getContext(
        ctx->width, ctx->height, ctx->pix_fmt,
        ctx->width, ctx->height, AV_PIX_FMT_RGB24,
        SWS_BILINEAR, NULL, NULL, NULL
    );

    frame = av_frame_alloc();
    rgb   = av_frame_alloc();
    packet = av_packet_alloc();

    int rgbSize = av_image_get_buffer_size(AV_PIX_FMT_RGB24, ctx->width, ctx->height, 1);
    rgbBuffer = (uint8_t*)av_malloc(rgbSize);

    av_image_fill_arrays(
        rgb->data, rgb->linesize, rgbBuffer,
        AV_PIX_FMT_RGB24, ctx->width, ctx->height, 1
    );

    // Create Raylib Texture
    Image img = {
        .data = rgbBuffer,
        .width = ctx->width,
        .height = ctx->height,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8
    };
    tex = LoadTextureFromImage(img);

    loaded = true;
}

VideoPlayer::~VideoPlayer() {
    if (loaded) {
        UnloadTexture(tex);
    }

    if (rgbBuffer) av_free(rgbBuffer);
    if (frame) av_frame_free(&frame);
    if (rgb) av_frame_free(&rgb);
    if (packet) av_packet_free(&packet);

    if (ctx) avcodec_free_context(&ctx);
    if (fmt) avformat_close_input(&fmt);

    if (sws) sws_freeContext(sws);
}

bool VideoPlayer::Update() {
    if (!loaded) return false;

    if (av_read_frame(fmt, packet) < 0)
        return false;   // No more frames

    if (packet->stream_index == videoStream) {
        avcodec_send_packet(ctx, packet);

        if (avcodec_receive_frame(ctx, frame) == 0) {
            sws_scale(
                sws,
                frame->data, frame->linesize,
                0, ctx->height,
                rgb->data, rgb->linesize
            );

            UpdateTexture(tex, rgbBuffer);
        }
    }

    av_packet_unref(packet);
    return true;
}

void VideoPlayer::Render(int x, int y) {
    if (loaded) {
        DrawTexture(tex, x, y, WHITE);
    }
}
