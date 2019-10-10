#include <jni.h>
#include <string>
#include <android/log.h>

#include <unistd.h>


#include "com_aisaka_ffmpegandroid_FFmpegUtil.h"

extern "C" {
#include <libavutil/imgutils.h>
#include <libavutil/audio_fifo.h>
#include "libswresample/swresample.h"
#include "libswscale/swscale.h"
#include "libavformat/avformat.h"
#include "libavutil/log.h"
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <android/native_window.h>
#include <libyuv.h>
}

#define LOGV(TAG, ...) __android_log_print(ANDROID_LOG_VERBOSE,TAG, __VA_ARGS__);
#define LOGD(TAG, ...) __android_log_print(ANDROID_LOG_DEBUG,TAG, __VA_ARGS__);
#define LOGI(TAG, ...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__);
#define LOGW(TAG, ...) __android_log_print(ANDROID_LOG_WARN,TAG, __VA_ARGS__);
#define LOGE(TAG, ...) __android_log_print(ANDROID_LOG_ERROR,TAG, __VA_ARGS__);

#define AUDIO_INBUF_SIZE 40960
#define AUDIO_REFILL_THRESH 4096
#define MAX_AUDIO_FRAME_SIZE 192000
const char *NATIVE_TAG = "NATIVE_TAG";

extern "C" JNIEXPORT jstring JNICALL
Java_com_aisaka_ffmpegandroid_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

static void log_callback_test2(void *ptr, int level, const char *fmt, va_list vl) {
    va_list vl2;
    char *line = (char *) malloc(128 * sizeof(char));
    static int print_prefix = 1;
    va_copy(vl2, vl);
    av_log_format_line(ptr, level, fmt, vl2, line, 128, &print_prefix);
    va_end(vl2);
    line[127] = '\0';
    LOGE(NATIVE_TAG, "%s", line);
    free(line);
}

JNIEXPORT void JNICALL Java_com_aisaka_ffmpegandroid_FFmpegUtil__1dumpFormat
        (JNIEnv *env, jobject jthis, jstring sfilepath) {


    const char *filepath = env->GetStringUTFChars(sfilepath, 0);


    int result;

    LOGE(NATIVE_TAG, "%s", filepath);

    FILE *pcmFile = fopen("/storage/emulated/0/1.pcm", "wb+");
    AVFormatContext *formatContext = NULL;
    AVStream *audioStream = NULL;
    int audioStreamIndex;
    AVCodecContext *codecContext = NULL;
    AVCodecParserContext *parserContext = NULL;
    AVCodec *codec = NULL;


//音频重采样
    struct SwrContext *swrCtx = NULL;


    av_log_set_callback(log_callback_test2);

    formatContext = avformat_alloc_context();

    result = avformat_open_input(&formatContext, filepath, NULL, NULL);
    LOGE(NATIVE_TAG, "avformat_open_input %s result %d", filepath, result);
//    assert(result);
    if (result < 0) {
        return;
    }


    result = avformat_find_stream_info(formatContext, NULL);
    LOGE(NATIVE_TAG, "avformat_find_stream_info result %d", result);
//    assert(result);

    av_dump_format(formatContext, -1, filepath, 0);


    result = av_find_best_stream(formatContext, AVMEDIA_TYPE_AUDIO, -1, -1, &codec, 0);
    LOGE(NATIVE_TAG, "av_find_best_stream result %d", result);
//    assert(result);


    if (result < 0) {
        avformat_close_input(&formatContext);
        return;
    }


    audioStreamIndex = result;
    audioStream = formatContext->streams[audioStreamIndex];

    codec = avcodec_find_decoder(audioStream->codecpar->codec_id);


    if (!codec) {
        LOGE(NATIVE_TAG, "avcodec_find_decoder not found codecid %d",
             audioStream->codecpar->codec_id);

        avformat_close_input(&formatContext);
        return;
    }

    parserContext = av_parser_init(codec->id);

    if (!parserContext) {
        LOGE(NATIVE_TAG, "av_parser_init Parser not found %d",
             audioStream->codecpar->codec_id);

        avformat_close_input(&formatContext);
        return;
    }


    codecContext = avcodec_alloc_context3(codec);

    if (!codecContext) {
        LOGE(NATIVE_TAG, "avcodec_alloc_context3");
        avformat_close_input(&formatContext);
        return;
    }


    result = avcodec_parameters_to_context(codecContext, audioStream->codecpar);

    if (result < 0) {

        LOGE(NATIVE_TAG, "avcodec_parameters_to_context %s",
             av_err2str(result));

        avformat_close_input(&formatContext);
        avcodec_close(codecContext);
        return;
    }


    LOGE(NATIVE_TAG, "%d %d %d", codec->id, audioStream->codecpar->frame_size,
         audioStream->codecpar->codec_id);

    result = avcodec_open2(codecContext, codec, NULL);

    if (result < 0) {

        LOGE(NATIVE_TAG, "avcodec_open2 error %s", av_err2str(result));
        avformat_close_input(&formatContext);
        return;
    }

    AVFrame *frame = av_frame_alloc();


    AVPacket pkt = {.data = NULL, .size = 0};

    const AVCodecParameters *codecParameters = audioStream->codecpar;
    //Out Audio Param
    uint64_t out_channel_layout = codecParameters->channel_layout;
    //AAC:1024  MP3:1152
    int64_t out_nb_samples = codecParameters->frame_size;
    AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_S16;
    int out_sample_rate = codecParameters->sample_rate;
    int out_channels = codecParameters->channels;
    //Out Buffer Size
    int out_buffer_size = av_samples_get_buffer_size(NULL, out_channels, out_nb_samples,
                                                     out_sample_fmt, 1);

    uint8_t *out_buffer = (uint8_t *) av_malloc(out_buffer_size);


    LOGE(NATIVE_TAG, "out_channel_layout=%llu", out_channel_layout);
    LOGE(NATIVE_TAG, "out_nb_samples= %llu", out_nb_samples);
    LOGE(NATIVE_TAG, "out_sample_rate=%d", out_sample_rate);
    LOGE(NATIVE_TAG, " out_channels=%d", out_channels);
    LOGE(NATIVE_TAG, " out_buffer_size=%d", out_buffer_size);
    LOGE(NATIVE_TAG, "in_sample_fmt=%d", codecContext->sample_fmt);
    LOGE(NATIVE_TAG, "out_sample_fmt=%d", out_sample_fmt);

    uint64_t in_channel_layout = av_get_default_channel_layout(codecParameters->channels);
    LOGE(NATIVE_TAG, " in_channels=%d", codecParameters->channels);
    LOGE(NATIVE_TAG, " in_channel_layout= %llu", in_channel_layout);

    swrCtx = swr_alloc();
    swrCtx = swr_alloc_set_opts(swrCtx, out_channel_layout, out_sample_fmt, out_sample_rate,
                                in_channel_layout, codecContext->sample_fmt,
                                codecParameters->sample_rate, 0, NULL);

    if (!swrCtx) {
        LOGE(NATIVE_TAG, "swr_alloc_set_opts failed");
        return;
    }
    result = swr_init(swrCtx);

    if (result < 0) {
        LOGE(NATIVE_TAG, "Could not open resample context\n");
        swr_free(&swrCtx);
        return;
    }

    //JNI begin------------------
    //JasonPlayer
    jclass player_class = env->GetObjectClass(jthis);
//    jmethodID construct = env->GetMethodID(clazz, "<init>", "()V");
//    jobject ffmpegutil = env->NewObject(player_class, construct);
    jmethodID get_audio_track = env->GetMethodID(player_class, "getAudioTrack",
                                                 "(II)Landroid/media/AudioTrack;");
    jobject audiotrackobj = env->CallObjectMethod(jthis, get_audio_track, out_sample_rate,
                                                  out_channels);

    jclass audioclazz = env->GetObjectClass(audiotrackobj);

    jmethodID audio_track_play = env->GetMethodID(audioclazz, "play", "()V");

    env->CallVoidMethod(audiotrackobj, audio_track_play);

    jmethodID audio_track_write = env->GetMethodID(audioclazz, "write", "([BII)I");

    int size;
    while (av_read_frame(formatContext, &pkt) >= 0) {


        if (pkt.stream_index == audioStreamIndex) {
//            LOGE(NATIVE_TAG, "packet %d %d", pkt.stream_index, pkt.size);
            int result = avcodec_send_packet(codecContext, &pkt);
            if (result >= 0) {
                while (result >= 0) {
                    result = avcodec_receive_frame(codecContext, frame);
                    if (result == AVERROR(EAGAIN) || result == AVERROR_EOF)
                        break;
                    else if (result < 0) {
//                        fprintf(stderr, "Error during decoding\n");
                        LOGE(NATIVE_TAG, "Error during decoding\n");
                        break;
                    }


                    size = swr_convert(swrCtx, &out_buffer, out_buffer_size,
                                       (const uint8_t **) frame->data,
                                       audioStream->codecpar->frame_size);
                    size *= (out_channels * av_get_bytes_per_sample(out_sample_fmt));

                    LOGE(NATIVE_TAG, "size = %d out_buffer_size = %d", size, out_buffer_size);
                    jbyteArray bytearray = env->NewByteArray(out_buffer_size);
                    jbyte *byte = env->GetByteArrayElements(bytearray, 0);
                    memcpy(byte, out_buffer, out_buffer_size);

                    env->ReleaseByteArrayElements(bytearray, byte, 0);

                    env->CallIntMethod(audiotrackobj, audio_track_write, bytearray, 0,
                                       out_buffer_size);
                    env->DeleteLocalRef(bytearray);
                    fwrite(out_buffer, out_buffer_size, 1, pcmFile);
                    usleep(1000 * 16);

//                    LOGE(NATIVE_TAG, "playing");

                }
            } else {
                if (result != 0) {
                    char buff[256];
                    av_strerror(result, buff, 256);
                    LOGE(NATIVE_TAG, "avcodec_send_packet failed result %s", buff);
                    return;
                }
            }
        }
        av_packet_unref(&pkt);
    }

    swr_free(&swrCtx);
    avcodec_close(codecContext);
    avformat_close_input(&formatContext);
    LOGE(NATIVE_TAG, "end");
}

JNIEXPORT void JNICALL Java_com_aisaka_ffmpegandroid_FFmpegUtil__1playVideo
        (JNIEnv *env, jobject jthis, jstring filePath, jobject surface) {

    const char *filepath = env->GetStringUTFChars(filePath, 0);

    LOGE(NATIVE_TAG, "playVideo %s", filepath);
    AVFormatContext *formatContext;
    AVCodecContext *videoCodecContext;
    AVCodec *videoCodec;
    int videoStreamIndex;
    int ret;

    av_log_set_callback(log_callback_test2);

    formatContext = avformat_alloc_context();

    ret = avformat_open_input(&formatContext, filepath, NULL, NULL);

    if (ret < 0) {
        LOGE(NATIVE_TAG, "avformat_open_input failed %s", av_err2str(ret));
        return;
    }

    LOGE(NATIVE_TAG, "avformat_open_input ");

    ret = avformat_find_stream_info(formatContext, NULL);

    if (ret < 0) {
        LOGE(NATIVE_TAG, "avformat_find_stream_info failed %s", av_err2str(ret));
        return;
    }

    LOGE(NATIVE_TAG, "avformat_find_stream_info ");
    av_dump_format(formatContext, -1, filepath, 0);

    ret = av_find_best_stream(formatContext, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);

    if (ret < 0) {
        LOGE(NATIVE_TAG, "av_find_best_stream failed %s", av_err2str(ret));
        return;
    }

    LOGE(NATIVE_TAG, "av_find_best_stream ");
    videoStreamIndex = ret;

    videoCodec = avcodec_find_decoder(formatContext->streams[videoStreamIndex]->codecpar->codec_id);

    if (!videoCodec) {
        LOGE(NATIVE_TAG, "avcodec_find_decoder failed");
        return;
    }

    LOGE(NATIVE_TAG, "avcodec_find_decoder");

    videoCodecContext = avcodec_alloc_context3(videoCodec);

    if (!videoCodecContext) {
        LOGE(NATIVE_TAG, "avcodec_alloc_context3 failed");
        return;
    }

    LOGE(NATIVE_TAG, "avcodec_alloc_context3");

//    在某些情况下可能videoCodecContext并没有获取到需要解码的信息 所以需要做这一步的赋值。
    ret = avcodec_parameters_to_context(videoCodecContext,
                                        formatContext->streams[videoStreamIndex]->codecpar);

    if (ret < 0) {
        LOGE(NATIVE_TAG, "avcodec_parameters_to_context failed %s", av_err2str(ret));
        return;
    }

    ret = avcodec_open2(videoCodecContext, videoCodec, NULL);

    if (ret < 0) {
        LOGE(NATIVE_TAG, "avcodec_open2 failed %s", av_err2str(ret));
        return;
    }

    AVFrame *frame;
    AVFrame *rgbframe;
    AVPacket *pkt;

    frame = av_frame_alloc();
    rgbframe = av_frame_alloc();
    pkt = av_packet_alloc();

    ANativeWindow *nativeWindow = ANativeWindow_fromSurface(env, surface);

    if (!nativeWindow) {
        LOGE(NATIVE_TAG, "ANativeWindow_fromSurface failed %s", av_err2str(ret));
        return;
    }

    LOGE(NATIVE_TAG,"帧率 %d %d",videoCodecContext->framerate.den,videoCodecContext->framerate.num);

    LOGE(NATIVE_TAG,"video_delay %d",formatContext->streams[videoStreamIndex]->codecpar->video_delay);
    ANativeWindow_Buffer outbuffer;

    SwsContext *swsContext = sws_alloc_context();

    swsContext = sws_getContext(videoCodecContext->width, videoCodecContext->height,
                                videoCodecContext->pix_fmt, videoCodecContext->width,
                                videoCodecContext->height, AV_PIX_FMT_RGBA, SWS_BILINEAR, NULL,
                                NULL, NULL);

    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGBA, videoCodecContext->width,
                                            videoCodecContext->height, 1);
    uint8_t *buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));
    av_image_fill_arrays(rgbframe->data, rgbframe->linesize, buffer, AV_PIX_FMT_RGBA,
                         videoCodecContext->width, videoCodecContext->height, 1);


    int framecount = 0;

    LOGE(NATIVE_TAG, "开始解码")
    while (av_read_frame(formatContext, pkt) >= 0) {
        if (pkt->stream_index == videoStreamIndex) {
            int result = avcodec_send_packet(videoCodecContext, pkt);
            if (result >= 0) {
                while (result >= 0) {
                    result = avcodec_receive_frame(videoCodecContext, frame);
                    if (result == AVERROR(EAGAIN) || result == AVERROR_EOF)
                        break;
                    else if (result < 0) {
//                        fprintf(stderr, "Error during decoding\n");
                        LOGE(NATIVE_TAG, "Error during decoding\n");
                        break;
                    }

                    ANativeWindow_setBuffersGeometry(nativeWindow, videoCodecContext->width,
                                                     videoCodecContext->height,
                                                     WINDOW_FORMAT_RGBA_8888);

                    ANativeWindow_lock(nativeWindow, &outbuffer, NULL);

//                    // 格式转换
//                    sws_scale(swsContext, (uint8_t const *const *) frame->data,
//                              frame->linesize, 0, videoCodecContext->height,
//                              rgbframe->data, rgbframe->linesize);

                    //YUV->RGBA_8888
                    libyuv::I420ToARGB(frame->data[0], frame->linesize[0],
                                       frame->data[2], frame->linesize[2],
                                       frame->data[1], frame->linesize[1],
                                       rgbframe->data[0], rgbframe->linesize[0],
                                       videoCodecContext->width, videoCodecContext->height);

                    LOGE(NATIVE_TAG, "");

                    // 获取stride
                    uint8_t *dst = (uint8_t *) outbuffer.bits;
                    int dstStride = outbuffer.stride * 4;
                    uint8_t *src = (uint8_t *) (rgbframe->data[0]);
                    int srcStride = rgbframe->linesize[0];

                    // 由于window的stride和帧的stride不同,因此需要逐行复制
                    int h;
                    for (h = 0; h < videoCodecContext->height; h++) {
                        memcpy(dst + h * dstStride, src + h * srcStride, srcStride);
                    }

                    ANativeWindow_unlockAndPost(nativeWindow);

                    sleep(1.0/33);

                    framecount++;


                    LOGE(NATIVE_TAG, "当前帧数 = %d dts=%d pts=%d pkt.pts=%d pkt.dts=%d", framecount,frame->pkt_dts,frame->pts,pkt->pts,pkt->dts);

                }
            } else {
                if (result != 0) {
                    char buff[256];
                    av_strerror(result, buff, 256);
                    LOGE(NATIVE_TAG, "avcodec_send_packet failed result %s", buff);
                    return;
                }
            }
        }

        av_packet_unref(pkt);
    }

    ANativeWindow_release(nativeWindow);
    av_frame_free(&frame);
    avcodec_close(videoCodecContext);
    avformat_free_context(formatContext);

    (env)->ReleaseStringUTFChars(filePath, filepath);

    LOGE(NATIVE_TAG, "end");
}

