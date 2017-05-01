package com.example.android_car_socket;

import java.io.IOException;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

public class MoveCarActivity extends Activity {

	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		
		setContentView(R.layout.move_car);//���ò�����r_and_l.xmlҳ��
		
		//�ѵ�ǰ����ࣨthis����ӽ��б�
		MyArrayList.list.add(this);
			
	}
	public void moveButton(View v) throws IOException
	{
		//�����ַ����ͻ�����
		String str;
		byte[] buffer;
		
		switch(v.getId())
		{
		case R.id.upButton://ǰ��
			//str�������������
			str = "Umww";
			//��str�ڵ��ַ���ת��Ϊbyte����
			buffer = str.getBytes();
			//���������out��������������
			MyArrayList.out.write(buffer, 0, buffer.length);
			//��˾��ӡ����ʾ�û����ͳɹ�
			Toast.makeText(MoveCarActivity.this, "ǰ���źŷ��ͳɹ�", Toast.LENGTH_SHORT).show();
			break;
		case R.id.stopButton://ֹͣ
			//str�������������
			str = "Umws";
			//��str�ڵ��ַ���ת��Ϊbyte����
			buffer = str.getBytes();
			//���������out��������������
			MyArrayList.out.write(buffer, 0, buffer.length);
			//��˾��ӡ����ʾ�û����ͳɹ�
			Toast.makeText(MoveCarActivity.this, "ֹͣ�źŷ��ͳɹ�", Toast.LENGTH_SHORT).show();
			break;
		case R.id.leftButton://��ת
			//str�������������
			str = "Umwa";
			//��str�ڵ��ַ���ת��Ϊbyte����
			buffer = str.getBytes();
			//���������out��������������
			MyArrayList.out.write(buffer, 0, buffer.length);
			//��˾��ӡ����ʾ�û����ͳɹ�
			Toast.makeText(MoveCarActivity.this, "��ת�źŷ��ͳɹ�", Toast.LENGTH_SHORT).show();
			break;
		case R.id.rightButton://��ת
			//str�������������
			str = "Umwd";
			//��str�ڵ��ַ���ת��Ϊbyte����
			buffer = str.getBytes();
			//���������out��������������
			MyArrayList.out.write(buffer, 0, buffer.length);
			//��˾��ӡ����ʾ�û����ͳɹ�
			Toast.makeText(MoveCarActivity.this, "��ת�źŷ��ͳɹ�", Toast.LENGTH_SHORT).show();
			break;
		case R.id.endButton://�˳�����
			//����MyArrayList.list�б�ر�ҳ��
			for (Activity activity : MyArrayList.list) {
				activity.finish();
			}
		default:
			break;
		}
	}
	
	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		
		//���ûҳ����б���ɾ��
		MyArrayList.list.remove(MyArrayList.list.size()-1);
	}
}
