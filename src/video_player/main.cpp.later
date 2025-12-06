extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>   // <-- add this
}

#include "raylib.h"
#include <iostream>

int main() {
    const char* filename = "video.mp4";

    // ----- FFmpeg init -----
    avformat_network_init();

    AVFormatContext* fmt = nullptr;
    if (avformat_open_input(&fmt, filename, NULL, NULL) != 0) {
        std::cerr << "Can't open video\n";
        return 1;
    }
    avformat_find_stream_info(fmt, NULL);

    int videoStream = av_find_best_stream(fmt, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    AVCodecParameters* params = fmt->streams[videoStream]->codecpar;
    const AVCodec* codec = avcodec_find_decoder(params->codec_id);

    AVCodecContext* ctx = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(ctx, params);
    avcodec_open2(ctx, codec, NULL);

    SwsContext* sws = sws_getContext(
        ctx->width, ctx->height, ctx->pix_fmt,
        ctx->width, ctx->height, AV_PIX_FMT_RGB24,
        SWS_BILINEAR, NULL, NULL, NULL
    );

    AVFrame* frame = av_frame_alloc();
    AVFrame* rgb = av_frame_alloc();
    int rgbSize = av_image_get_buffer_size(AV_PIX_FMT_RGB24, ctx->width, ctx->height, 1);
    uint8_t* rgbBuffer = (uint8_t*)av_malloc(rgbSize);
    av_image_fill_arrays(rgb->data, rgb->linesize, rgbBuffer,
                         AV_PIX_FMT_RGB24, ctx->width, ctx->height, 1);

    AVPacket* packet = av_packet_alloc();

    // ----- Raylib init -----
    InitWindow(800, 450, "Raylib Video Player");
    SetTargetFPS(60);

    Image img = {
        .data = rgbBuffer,
        .width = ctx->width,
        .height = ctx->height,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8
    };
    Texture2D tex = LoadTextureFromImage(img);

    // ----- Main loop -----
    while (!WindowShouldClose()) {
        if (av_read_frame(fmt, packet) >= 0) {
            if (packet->stream_index == videoStream) {
                avcodec_send_packet(ctx, packet);
                if (avcodec_receive_frame(ctx, frame) == 0) {
                    // Convert YUV → RGB
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
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(tex, 0, 0, WHITE);
        EndDrawing();
    }

    // ----- Cleanup -----
    UnloadTexture(tex);
    CloseWindow();

    av_free(rgbBuffer);
    av_frame_free(&frame);
    av_frame_free(&rgb);
    av_packet_free(&packet);
    avcodec_free_context(&ctx);
    avformat_close_input(&fmt);

    return 0;
}
