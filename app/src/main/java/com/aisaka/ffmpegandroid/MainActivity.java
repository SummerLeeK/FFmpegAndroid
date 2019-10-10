package com.aisaka.ffmpegandroid;

import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Surface;
import android.view.View;
import android.widget.TextView;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

public class MainActivity extends AppCompatActivity {

    String path = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "1.mp3";

    String videoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "1.mp4";
    private VideoView videoView;
    private FFmpegUtil fFmpegUtil;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        fFmpegUtil = new FFmpegUtil();
        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        videoView = findViewById(R.id.videoview);

        tv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new Thread(new Runnable() {
                    @Override
                    public void run() {

                        fFmpegUtil.playBgm(path);
                    }
                }).start();
            }
        });


        findViewById(R.id.java_text).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int sampleRateInHz = 44100;
                //最小缓存区
                int bufferSizeInBytes = AudioTrack.getMinBufferSize(sampleRateInHz, AudioFormat.CHANNEL_OUT_MONO, AudioFormat.ENCODING_PCM_16BIT);
                //创建AudioTrack对象   依次传入 :流类型、采样率（与采集的要一致）、音频通道（采集是IN 播放时OUT）、量化位数、最小缓冲区、模式
                AudioTrack player = new AudioTrack(AudioManager.STREAM_MUSIC, sampleRateInHz, AudioFormat.CHANNEL_OUT_MONO, AudioFormat.ENCODING_PCM_16BIT, bufferSizeInBytes, AudioTrack.MODE_STREAM);

                byte[] buffers = new byte[bufferSizeInBytes];
                try {
                    DataInputStream dataInputStream = new DataInputStream(new BufferedInputStream(new FileInputStream(new File(Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "1.pcm"))));
                    player.play();
                    while (dataInputStream.available() > 0) {
                        int i = 0;
                        while (dataInputStream.available() > 0 && i < buffers.length) {
                            buffers[i] = dataInputStream.readByte();
                            i++;
                        }
                        player.write(buffers, 0, buffers.length);
                    }
                    player.stop();
                    dataInputStream.close();
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });


        findViewById(R.id.play_video).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Surface surface = videoView.getHolder().getSurface();
                fFmpegUtil.playVideo(videoPath,surface);
            }
        });


    }

}
