package tests.mistwork.ndkexample2_cppclass;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.opengl.Matrix;
import android.util.Log;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by prometheus on 14/12/16.
 */

public class ES20Renderer implements GLSurfaceView.Renderer {

    private static final String TAG = "ES20Renderer";
    private Context context;

    private float[] modelMatrix = new float[16];
    private float[] viewMatrix = new float[16];
    private float[] projectionMatrix = new float[16];
    private float[] mvpMatrix = new float[16];

    private final FloatBuffer vertexDataBuffer;
    private int mvpHandle;
    private int vertexPositionHandle;
    private int vertexColorHandle;

    public ES20Renderer(Context context) {
        this.context = context;

        final float[] vertexData = {
                // X, Y, Z
                0.0f, 0.5f, 0.0f,
                // R, G, B, A
                1.0f, 0.0f, 0.0f, 1.0f,

                // X, Y, Z
                -0.5f, -0.5f, 0.0f,
                // R, G, B, A
                0.0f, 0.0f, 1.0f, 1.0f,

                // X, Y, Z
                0.5f, -0.5f, 0.0f,
                // R, G, B, A
                0.0f, 1.0f, 0.0f, 1.0f
        };

        //Number of position values * 4 bytes per float
        ByteBuffer bb = ByteBuffer.allocateDirect(vertexData.length * 4);
        bb.order(ByteOrder.nativeOrder());
        vertexDataBuffer = bb.asFloatBuffer();
        vertexDataBuffer.put(vertexData);
        vertexDataBuffer.position(0);
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        GLES20.glClearColor(0.0f, 0.3f, 0.5f, 1.0f);
        loadShader(loadShaderSourceFromResources(R.raw.basic_vert), loadShaderSourceFromResources(R.raw.basic_frag));

        Matrix.setLookAtM(viewMatrix, 0,
                0.0f, 0.0f, 3.0f,
                0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f);

        mvpHandle = GLES20.glGetUniformLocation(getShaderProgramHandle(), "uMVP");
        vertexPositionHandle = GLES20.glGetAttribLocation(getShaderProgramHandle(), "aPosition");
        vertexColorHandle = GLES20.glGetAttribLocation(getShaderProgramHandle(), "aColor");
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        GLES20.glViewport(0, 0, width, height);
        final float ratio = (float) width / height;
        Matrix.perspectiveM(projectionMatrix, 0, 45.0f, ratio, 0.1f, 1000.0f);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT|GLES20.GL_DEPTH_BUFFER_BIT);
        Matrix.setIdentityM(modelMatrix, 0);
        GLES20.glUseProgram(getShaderProgramHandle());

        //POSITION
        vertexDataBuffer.position(0);
        GLES20.glVertexAttribPointer(vertexPositionHandle, 3, GLES20.GL_FLOAT, false, 7 * 4, vertexDataBuffer);
        GLES20.glEnableVertexAttribArray(vertexPositionHandle);

        //COLOR
        vertexDataBuffer.position(3);
        GLES20.glVertexAttribPointer(vertexColorHandle, 4, GLES20.GL_FLOAT, false, 7 * 4, vertexDataBuffer);
        GLES20.glEnableVertexAttribArray(vertexColorHandle);

        Matrix.multiplyMM(mvpMatrix, 0, viewMatrix, 0, modelMatrix, 0);
        Matrix.multiplyMM(mvpMatrix, 0, projectionMatrix, 0, mvpMatrix, 0);

        GLES20.glUniformMatrix4fv(mvpHandle, 1, false, mvpMatrix, 0);
        GLES20.glDrawArrays(GLES20.GL_TRIANGLES, 0, 3);
    }

    private String loadShaderSourceFromResources(int resource) {
        InputStream is = context.getResources().openRawResource(resource);
        BufferedReader br = new BufferedReader(new InputStreamReader(is));
        String line;
        StringBuilder result = new StringBuilder();

        try {

            while ((line = br.readLine()) != null) {
                result.append(line);
                result.append("\n");
            }
        }
        catch (IOException ex) {
            Log.e(TAG, "Failed loading shader source: " + ex.toString());
            return null;
        }

        return result.toString();
    }

    static {
        System.loadLibrary("ShaderProgram");
    }

    public native void loadShader(String vertexSource, String fragmentSource);
    public native int getShaderProgramHandle();
}
