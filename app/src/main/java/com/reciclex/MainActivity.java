package com.reciclex;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.reciclex.databinding.ActivityMainBinding;

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