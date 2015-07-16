package com.fiziico.trustzone;

import android.app.Activity;
import android.os.Bundle;
import android.os.IBinder;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import java.lang.reflect.Method;

public class MainActivity extends Activity implements
    View.OnClickListener {

    private static final String TAG = "TrustZoneClient";
    private static final String SERVICE_NAME = "com.fiziico.trustzone";

    private EditText mNumberA;
    private EditText mNumberB;
    private Button mAddButton;
    private EditText mNumberSum;
    private ITrustZoneService mService;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        mNumberA = (EditText)findViewById(R.id.number_a);
        mNumberB = (EditText)findViewById(R.id.number_b);
        mAddButton = (Button)findViewById(R.id.button);
        mAddButton.setOnClickListener(this);
        mNumberSum = (EditText)findViewById(R.id.number_sum);
    }

    @Override
    public void onClick(View v) {
        try {
            int a = Integer.parseInt(mNumberA.getText().toString());
            int b = Integer.parseInt(mNumberB.getText().toString());
            if (mService == null) {
                getTrustZoneService();
            }
            mNumberSum.setText(Integer.toString(mService.add(a, b)));
        } catch (Exception e) {
            Log.e(TAG, e.toString());
        }
    }

    private void getTrustZoneService() {
        IBinder binder = null;
        try {
            Method getService = Class.forName("android.os.ServiceManager")
                .getMethod("getService", String.class);
            binder = (IBinder)getService.invoke(null,
                    new Object[]{new String(SERVICE_NAME)});
        } catch (Exception e) {
            Log.e(TAG, e.toString());
        }
        if (binder == null) {
            Log.e(TAG, "Service not found");
        } else {
            Log.d(TAG, "Service found");
            mService = ITrustZoneService.Stub.asInterface(binder);
        }
    }
}
