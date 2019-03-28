package com.firstapp.testapp;

import android.content.Intent;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "Start Log: \n";
    public static final String EXTRA_MESSAGE = "com.firstapp.testapp.MESSAGE";
    public static final String NEW_MESSAGE = "com.firstapp.testapp.NEW_MESSAGE";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        FragmentManager fragmentManager = getSupportFragmentManager();
        FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();

        FragmentActivity fragment = new FragmentActivity();
        fragmentTransaction.add(R.id.fragmentContainer, fragment);
        fragmentTransaction.commit();
    }

    public void sendMessage(View view){
        //something good, something bad
        Log.d(TAG, "sendMessage Button");

        // create an intent object, send the context MainActivity as 'this', with the class
        // that the intent is suppose to invoke
        Intent intent = new Intent(this, DisplayMessageActivity.class);

        // The objects that the intent carries is from the UI inputs.

        //EditText object obtains some text from the user. All UI interfaces has a particular ID.
        EditText editText = findViewById(R.id.editText);

        // Extract the text from editText then convert to string.
        String message = editText.getText().toString();

        // put the message into intent, and tag as EXTRA_MESSAGE;
        intent.putExtra(EXTRA_MESSAGE, message);

        // Then start the activity with the intent.
        startActivity(intent);
    }


}

