package alex.t_spline.t_spline;


import android.app.Activity;
import android.content.Intent;
import android.view.View;
import android.widget.Button;

import android.os.Bundle;
import android.widget.EditText;

import alex.t_spline.t_spline.R;
import alex.t_spline.t_spline.TsplineNativeActivity;


/**
 * Created by alex on 28.01.17.
 */

public class MainActivity extends Activity implements View.OnClickListener {


    EditText file_name_Edt;
    String name;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main_activity);


        final Button showBtn = (Button) findViewById(R.id.show_demo);
        showBtn.setOnClickListener(this);

        final Button loadModelBtn = (Button) findViewById(R.id.load_file);
        loadModelBtn.setOnClickListener(this);

        file_name_Edt = (EditText) findViewById(R.id.file_name_edt);

        name = file_name_Edt.getText().toString();


    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case (R.id.show_demo): {
                Intent myIntent = new Intent(v.getContext(), TsplineNativeActivity.class);
                startActivityForResult(myIntent, 0);
                finish();

            }
            break;
            case (R.id.load_file): {
                name = file_name_Edt.getText().toString();
                Intent myIntent = new Intent(v.getContext(), TsplineNativeActivity2.class);
                myIntent.putExtra("file_name", name);
                startActivityForResult(myIntent, 0);
                finish();
            }
            break;
        }
    }

}