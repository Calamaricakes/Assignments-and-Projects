package com.firstapp.testapp;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

public class FragmentActivity extends Fragment{

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle
            savedInstanceState){
        // inflate layout for the fragment
        return inflater.inflate(R.layout.fragment_layout, container, false);
    }

}
