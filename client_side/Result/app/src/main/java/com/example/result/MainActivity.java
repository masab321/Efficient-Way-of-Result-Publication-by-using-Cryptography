package com.example.result;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.net.MailTo;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import org.w3c.dom.Text;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final Button button = findViewById(R.id.show_result);
        TextView idd = findViewById(R.id.student_id);
        TextView enc = findViewById(R.id.encrypted_result);
        TextView p = findViewById(R.id.decrypt_password);

        Intent intent = getIntent();
        String action = intent.getAction();
        String type = intent.getType();
        String data = intent.getStringExtra(Intent.EXTRA_TEXT);
        enc.setText(data);


        button.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                // Code here executes on main thread after user presses button
                String id = idd.getText().toString();
                String cipher = enc.getText().toString();
                String pass = p.getText().toString();
                if(cipher.isEmpty() || pass.isEmpty()){
                    return;
                }
                crypt cr = new crypt();
                String res = cr.decrypt(pass, cipher);

                Intent myIntent = new Intent(MainActivity.this, d_result.class);
                myIntent.putExtra("key", res); //Optional parameters
                MainActivity.this.startActivity(myIntent);
//                System.out.println(res);
            }
        });
    }
}