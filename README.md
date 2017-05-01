# Smart Little Car

## 1. 介绍
### 主要功能：
通过手机连接wifi远程控制小车。

### [计划]后续增加功能：
1. 网页远程视频监控(已实现)
2. 网页远程控制
3. 手机远程视频监控
4. 语音模块

### 硬件列表：

小车：

|序号|设备|组成|作用|
|----|----|----|----|
|   1|小车控制板|stm32最小系统 *1、315M模块 *1|控制电机的转速转向|
|   2|驱动模块|L298N模块 *1、直流电机 *2、轮子 *2、万向轮 *1|为小车提供动力|
|   3|路由器|wrtnode1 *1 或者 其它支持openwrt的路由器 *1|提供WiFi热点，实现手机和小车控制板的通信（也为后期增加功能做准备）|
|   4|供电模块|DC-DC稳压模块若干、航模锂电池 *1、充电器 *1|为小车提供电源|
|   5|小车底盘及固定装置|亚克力底盘架 *1、固定板 *1、螺栓螺母等零件*n、安装工具*n|小车机械结构|

手机：

Android系统手机一部

### 软件结构

Android ---(socket)---> openwrt ---(uart)---> stm32 ---(TTL)---> motor

#### 0.总体框架
![all](https://github.com/daoshuti/smart_little_car/blob/master/img/smart_car.jpg?raw=true)

#### 1. Android "./android_car_scoket"
![app](https://github.com/daoshuti/smart_little_car/blob/master/img/app.jpg?raw=trues://github.com/daoshuti/smart_little_car/blob/master/img/app.jpg?raw=true)

#### 2. openwrt "./openwrt_main"
![main](https://github.com/daoshuti/smart_little_car/blob/master/img/main.jpg?raw=true)

#### 3. stm32 "./stm32_car"
![stm32](https://github.com/daoshuti/smart_little_car/blob/master/img/stm32.jpg?raw=true)

#### 4. 上下位机协议
![car_up](https://github.com/daoshuti/smart_little_car/blob/master/img/car_up.jpg?raw=trues://github.com/daoshuti/smart_little_car/blob/master/img/car_up.jpg?raw=true)
![car_down](https://github.com/daoshuti/smart_little_car/blob/master/img/car_down.jpg?raw=trues://github.com/daoshuti/smart_little_car/blob/master/img/car_down.jpg?raw=true)

### 小车实物图

![car](https://github.com/daoshuti/smart_little_car/blob/master/img/car.jpg?raw=tru://github.com/daoshuti/smart_little_car/blob/master/img/car.jpg?raw=true)


