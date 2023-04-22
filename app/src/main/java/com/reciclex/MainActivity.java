package com.reciclex;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.provider.MediaStore;
import android.view.View;
import android.widget.TextView;

import com.reciclex.databinding.ActivityMainBinding;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'reciclex' library on application startup.
    static {
        System.loadLibrary("reciclex");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI());

        binding.sampleText2.setText(process());
        binding.button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                cam_tela_cheia();
            }
        });

        binding.buttonVr.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                cam_tela_dupla();
            }
        });

    }

    private void cam_tela_cheia() {
        Intent intent = new Intent(this, MainActivity2.class);

        startActivity(intent);
    }

    private void cam_tela_dupla() {
        Intent intent = new Intent(this, VRActivity.class);

        startActivity(intent);
    }

    private File createPhotoFile() {
        //String name
        return null;
    }

    public native String process();

    public String processInJava(){
        return "Processed in Java";
    }
    /**
     * A native method that is implemented by the 'reciclex' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}