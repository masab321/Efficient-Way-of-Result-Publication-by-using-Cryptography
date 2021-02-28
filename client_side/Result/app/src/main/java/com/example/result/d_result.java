package com.example.result;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.List;

public class d_result extends AppCompatActivity {

    private RecyclerView recyclerView;
    private LinearLayout linearLayout;
    private TextView program, name, id, enrollment, batch, sgpa, semester;
    private List<Model> modelList;
    private List<Model> modelList2;
    private MyAdapter adapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_d_result);
        Intent intent = getIntent();
        String res = intent.getStringExtra("key");
        findSection();
        setData(res);
        recyclerView.setLayoutManager(new LinearLayoutManager(d_result.this));
        recyclerView.setHasFixedSize(true);
        System.out.println(res);
    }

    private String calculateSgpa(String res){
        String[] data = res.split(",");
        double credit = 0, total = 0;
        for(int i = 7; i < data.length - 1; i += 3){
            double temp = Double.parseDouble(data[i + 1]);
            credit += temp;
            temp *= Double.parseDouble(data[i + 2]);
            total += temp;
        }
        System.out.println(total);
        System.out.println(credit);
        System.out.println(total / credit);
        String ret = String.format("%.2f", total / credit);
        return ret;

    }

    private void setData(String res) {
        String[] data = res.split(",");

        program.setText(data[1]);
        name.setText(data[2]);
        id.setText(data[3]);
        enrollment.setText(data[4]);
        batch.setText(data[5]);
        semester.setText(data[6]);

        sgpa.setText(calculateSgpa(res));
        modelList= new ArrayList<>();
        for(int i = 7; i < data.length - 1; i += 3){
            modelList.add(new Model(data[i], data[i + 2], data[i + 1]));
        }

        linearLayout.setVisibility(View.VISIBLE);
        adapter= new MyAdapter(modelList);
        recyclerView.setAdapter(adapter);

    }


    private void findSection() {
        recyclerView=findViewById(R.id.recycleViewId);
        linearLayout= findViewById(R.id.bottomLinear);
        linearLayout.setVisibility(View.INVISIBLE);
        name = findViewById(R.id.nameTextView);
        id = findViewById(R.id.idTextView);
        program = findViewById(R.id.programTextView);
        sgpa = findViewById(R.id.sgpaTextView);
        batch = findViewById(R.id.batchTextView);
        enrollment = findViewById(R.id.enrollmentTextView);
        semester = findViewById(R.id.semesterTextView);
    }
}