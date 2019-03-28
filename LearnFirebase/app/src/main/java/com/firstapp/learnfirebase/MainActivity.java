package com.firstapp.learnfirebase;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;


public class MainActivity extends AppCompatActivity {

    FirebaseDatabase database = FirebaseDatabase.getInstance();
    DatabaseReference refDB = database.getReference("Object");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void onClick(View context){

        switch(context.getId()){

            case R.id.writeToDB:
                writeData();
                break;

            case R.id.readData:
                readData();
                break;
        }
    }

    private void writeData() {

        TextView message = findViewById(R.id.messageToSend1);
        TextView integer = findViewById(R.id.sendNumber);

        //TextView message2 = findViewById(R.id.messageToSend2);

        String stringMessage1 = message.getText().toString();
        float number = Float.parseFloat(integer.getText().toString());

        //String stringMessage2 = message2.getText().toString();

        DBObject object = new DBObject(stringMessage1, number);

        refDB.setValue(object);

    }


    private void readData(){

        refDB.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                getData(dataSnapshot);
            }

            @Override
            public void onCancelled(DatabaseError databaseError) {

            }
        });
    }



    private void getData(DataSnapshot dataSnapshot){

        //DataSnapshot ds = (DataSnapshot) dataSnapshot.getChildren();
        DBObject currentObject = new DBObject();
        currentObject.setStr(dataSnapshot.getValue(DBObject.class).getStr());
        currentObject.setNum(dataSnapshot.getValue(DBObject.class).getNum());

        String readString = currentObject.getStr();
        Float readNum = currentObject.getNum();

        TextView newString = findViewById(R.id.displayMessage);
        TextView newInt = findViewById(R.id.displayNumber);

        newString.setText(readString);
        newInt.setText(readNum.toString());
    }

}
