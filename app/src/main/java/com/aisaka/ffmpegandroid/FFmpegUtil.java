package com.aisaka.ffmpegandroid;

import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceView;

public class FFmpegUtil {

    // Used to load the 'native-lib' library on application startup.
    static {
//        System.loadLibrary("yuv");
        System.loadLibrary("avutil");
        System.loadLibrary("avdevice");
        System.loadLibrary("avformat");
        System.loadLibrary("avcodec");
        System.loadLibrary("swscale");
        System.loadLibrary("swresample");
        System.loadLibrary("avfilter");
        System.loadLibrary("native-lib");
    }

    public AudioTrack getAudioTrack(int sampleRateInHz, int channelConfig) {

        int mode;
        if (channelConfig == 1) {
            mode = AudioFormat.CHANNEL_OUT_MONO;
        } else {
            mode = AudioFormat.CHANNEL_OUT_STEREO;
        }
        int bufferSizeInBytes = AudioTrack.getMinBufferSize(sampleRateInHz, AudioFormat.CHANNEL_OUT_STEREO, AudioFormat.ENCODING_PCM_16BIT);
        Log.e("FFmpegUtil", sampleRateInHz + "\t" + channelConfig + "\t" + bufferSizeInBytes);
        AudioTrack track = new AudioTrack(AudioManager.STREAM_MUSIC, sampleRateInHz, AudioFormat.CHANNEL_OUT_STEREO, AudioFormat.ENCODING_PCM_16BIT, bufferSizeInBytes, AudioTrack.MODE_STREAM);

        return track;
    }


    private native void _dumpFormat(String filepath);

    private native void _playVideo(String filePath, Surface surface);

    public void playBgm(String filepath) {
        _dumpFormat(filepath);
    }

    public void playVideo(String filePath, Surface surface) {
        _playVideo(filePath, surface);
    }
}
