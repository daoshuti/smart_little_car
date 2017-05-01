package com.example.android_car_socket;

import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

public class SecondActivity extends Activity {
	// �������ݿ���ر���
	private SQLiteDatabase db;
	private MySQLiteOpenHelper helper;
	// ����EditText��ر���
	private EditText nameEditText;
	private EditText passwdEditText;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);

		setContentView(R.layout.reg_and_login);// ���ò�����r_and_l.xmlҳ��

		// �ѵ�ǰ����ࣨthis����ӽ��б�
		MyArrayList.list.add(this);

		// ����һ��sqlite���������
		helper = new MySQLiteOpenHelper(SecondActivity.this, "register.db",
				null, 1);

		// ����EditText����
		nameEditText = (EditText) findViewById(R.id.nameEditText);
		passwdEditText = (EditText) findViewById(R.id.passwdEditText);

		// �����׽��ֶ��󣬿�ʼTCP����
		try {
			// �����׽��ֶ���
			MyArrayList.socket = new Socket(MyArrayList.ipAddress, 50000);
			// ���������ʼ��Ϊ������������������͵����ݵ�������
			MyArrayList.out = MyArrayList.socket.getOutputStream();
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void secondActivityButton(View v) throws IOException {
		Cursor cursor;

		switch (v.getId()) {
		case R.id.registerButton:
			// ***********************************************************//
			// **************************ȱʡ*****************************//
			// ***********************************************************//
			db = helper.getWritableDatabase();

			// rawQuery������ִ�в鿴books���������ݣ����ز鿴�������ݵ��α�
			cursor = db.rawQuery("select * from users where name=?;",
					new String[] { nameEditText.getText().toString() });

			// ���α��ƶ���books���һ��
			cursor.moveToFirst();

			if (cursor.getCount() == 0) {
				db.execSQL("insert into users(name,passwd) values(?,?)",
						new String[] { nameEditText.getText().toString(),
								passwdEditText.getText().toString() });
				// ��˾��ӡ
				Toast.makeText(SecondActivity.this, "ע��ɹ�", Toast.LENGTH_SHORT)
						.show();
			} else {
				// ��˾��ӡ
				Toast.makeText(SecondActivity.this, "�˻��Ѵ�������������",
						Toast.LENGTH_SHORT).show();
			}
			break;
		case R.id.loginButton:
			// ***********************************************************//
			// **************************ȱʡ*****************************//
			// ***********************************************************//
			db = helper.getWritableDatabase();

			// rawQuery������ִ�в鿴books���������ݣ����ز鿴�������ݵ��α�
			cursor = db.rawQuery(
					"select * from users where name=? and passwd=?;",
					new String[] { nameEditText.getText().toString(),
							passwdEditText.getText().toString() });

			// ���α��ƶ���books���һ��
			cursor.moveToFirst();

			if (cursor.getCount() == 1) {
				Intent intent = new Intent(SecondActivity.this,
						MoveCarActivity.class);
				startActivity(intent);
				// ��˾��ӡ
				Toast.makeText(SecondActivity.this, "�ɹ���¼", Toast.LENGTH_SHORT)
						.show();
			} else {
				Toast.makeText(SecondActivity.this, "��¼ʧ�ܣ��û������������",
						Toast.LENGTH_SHORT).show();
			}
			break;
		default:
			break;
		}
	}

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();

		// ���ûҳ����б���ɾ��
		MyArrayList.list.remove(MyArrayList.list.size() - 1);

		// �������ʱ���ر��׽���
		// ʹ����ϣ��ر������
		try {
			MyArrayList.socket.close();
			MyArrayList.out.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
