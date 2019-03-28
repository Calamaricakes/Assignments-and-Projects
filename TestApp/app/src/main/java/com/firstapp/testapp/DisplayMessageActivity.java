package com.firstapp.testapp;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.EditText;
import android.widget.TextView;

public class DisplayMessageActivity extends AppCompatActivity {

    private static final String TAG = "DisplayMessageActivity: ";

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        // generated on create.
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_display_message);

        // retrieve the intent which invoked the activity
        Intent intent = getIntent();

        // retrieve the string from the intent using the TAG.
        String message = intent.getStringExtra(MainActivity.EXTRA_MESSAGE);

        // create a text view object
        TextView textView = findViewById(R.id.textView);

        // then display the text with textView.
        textView.setText(message);

    }
}
