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
		
		setContentView(R.layout.move_car);//设置并启动r_and_l.xml页面
		
		//把当前这个类（this）添加进列表
		MyArrayList.list.add(this);
			
	}
	public void moveButton(View v) throws IOException
	{
		//定义字符串和缓冲区
		String str;
		byte[] buffer;
		
		switch(v.getId())
		{
		case R.id.upButton://前进
			//str对象来存放命令
			str = "Umww";
			//将str内的字符串转换为byte类型
			buffer = str.getBytes();
			//调用输出流out对象，来发送数据
			MyArrayList.out.write(buffer, 0, buffer.length);
			//吐司打印，提示用户发送成功
			Toast.makeText(MoveCarActivity.this, "前进信号发送成功", Toast.LENGTH_SHORT).show();
			break;
		case R.id.stopButton://停止
			//str对象来存放命令
			str = "Umws";
			//将str内的字符串转换为byte类型
			buffer = str.getBytes();
			//调用输出流out对象，来发送数据
			MyArrayList.out.write(buffer, 0, buffer.length);
			//吐司打印，提示用户发送成功
			Toast.makeText(MoveCarActivity.this, "停止信号发送成功", Toast.LENGTH_SHORT).show();
			break;
		case R.id.leftButton://左转
			//str对象来存放命令
			str = "Umwa";
			//将str内的字符串转换为byte类型
			buffer = str.getBytes();
			//调用输出流out对象，来发送数据
			MyArrayList.out.write(buffer, 0, buffer.length);
			//吐司打印，提示用户发送成功
			Toast.makeText(MoveCarActivity.this, "左转信号发送成功", Toast.LENGTH_SHORT).show();
			break;
		case R.id.rightButton://右转
			//str对象来存放命令
			str = "Umwd";
			//将str内的字符串转换为byte类型
			buffer = str.getBytes();
			//调用输出流out对象，来发送数据
			MyArrayList.out.write(buffer, 0, buffer.length);
			//吐司打印，提示用户发送成功
			Toast.makeText(MoveCarActivity.this, "右转信号发送成功", Toast.LENGTH_SHORT).show();
			break;
		case R.id.endButton://退出程序
			//根据MyArrayList.list列表关闭页面
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
		
		//将该活动页面从列表中删除
		MyArrayList.list.remove(MyArrayList.list.size()-1);
	}
}
