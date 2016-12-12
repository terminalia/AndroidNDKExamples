package mistwork.com.ndkexample1_passingdata;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TextView tv = (TextView) findViewById(R.id.sample_text);

        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append(stringFromJNI());

        stringBuilder.append("\n");
        stringBuilder.append(floatFromJNI());

        stringBuilder.append("\n");
        float floatArray[] = floatArrayFromJNI();
        for (int i=0; i<floatArray.length; i++) {
            stringBuilder.append(floatArray[i] + "\n");
        }

        String stringArray[] = stringArrayFromJNI();
        for (int i=0; i<stringArray.length; i++) {
            stringBuilder.append(stringArray[i] + "\n");
        }
        tv.setText(stringBuilder.toString());

        stringFromJAVA("Hello from Native!");
        floatFromJAVA(33.44f);
        float values[] = {1.3f, 34.44f, 12.34f, 55.4f};
        floatArrayFromJAVA(values);
        String games[] = {"Final Fantasy XV", "The Last Guardian", "Dishonored 2"};
        stringArrayFromJAVA(games);
    }

    //JAVA to JNI
    public native void stringFromJAVA(String msg);
    public native void floatFromJAVA(float value);
    public native void floatArrayFromJAVA(float[] values);
    public native void stringArrayFromJAVA(String[] msgs);

    //JNI to JAVA
    public native String stringFromJNI();
    public native float floatFromJNI();
    public native float[] floatArrayFromJNI();
    public native String[] stringArrayFromJNI();
}
