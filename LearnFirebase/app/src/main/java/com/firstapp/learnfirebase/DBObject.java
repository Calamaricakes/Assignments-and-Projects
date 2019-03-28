package com.firstapp.learnfirebase;

public class DBObject{

    private String str;
    private float num;

    public DBObject(){}

    public DBObject(String str, float num){
        this.str = str;
        this.num = num;
    }

    public String getStr(){
        return this.str;
    }

    public float getNum(){
        return this.num;
    }

    public void setStr(String str){
        this.str = str;
    }

    public void setNum(float num){
        this.num = num;
    }

}
