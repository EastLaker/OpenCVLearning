#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<cv.h>
using namespace std;
using namespace cv;

void sharpen(const Mat &image, Mat &result) 
{
	// 判断是否需要分配图像数据。 如果需要， 就分配
	result.create(image.size(), image.type());
	int nchannels = image.channels(); // 获得通道数
									  // 处理所有行（除了第一行和最后一行）
	for (int j = 1; j < image.rows - 1; j++) {
		const uchar* previous =
			image.ptr<const uchar>(j - 1); // 上一行
		const uchar* current =
			image.ptr<const uchar>(j); // 当前行
		const uchar* next =
			image.ptr<const uchar>(j + 1); // 下一行
		uchar* output = result.ptr<uchar>(j); // 输出行
		for (int i = nchannels; i < (image.cols - 1)*nchannels; i++) {
			*output++ = cv::saturate_cast<uchar>(5 * current[i] - 1 * current[i - nchannels] -
				1 * current[i + nchannels] - 1 * previous[i] - 1*next[i]);
		}  //拉普拉斯算子
	} // 把未处理的像素设为0
	result.row(0).setTo(cv::Scalar(0));
	result.row(result.rows - 1).setTo(cv::Scalar(0));
	result.col(0).setTo(cv::Scalar(0));
	result.col(result.cols - 1).setTo(cv::Scalar(0));
}

void salt(cv::Mat image, int n) {
	int i, j;
	for (int k = 0; k<n; k++) {
		// rand()是随机数生成器
		i = std::rand() % image.cols;
		j = std::rand() % image.rows;
		if (image.type() == CV_8UC1) { // 灰度图像
			image.at<uchar>(j, i) = 255;
		}
		else if (image.type() == CV_8UC3) { // 彩色图像
			image.at<cv::Vec3b>(j, i)[0] = 255;
			image.at<cv::Vec3b>(j, i)[1] = 255;
			image.at<cv::Vec3b>(j, i)[2] = 255;
		}
	}
}

void colorreduce1(Mat image, int n)
{
	int div = pow(2, n);
	int nl = image.rows;
	int nc = image.cols*image.channels();
	uchar mask = 0xFF << n;
	for (int j = 0; j < nl; j++)
	{
		uchar *data = image.ptr<uchar>(j);
		for (int i = 0; i < nc; i++)
		{
			*data &= mask; // 掩码
			*data++ += div >> 1; // 加上div/2
								 //data[i] = data[i] / div*div + div / 2;
		}
	}
}

void wave(const Mat &image, Mat &result) {
	// 映射参数
	Mat srcX(image.rows, image.cols, CV_32F);
	Mat srcY(image.rows, image.cols, CV_32F);
	// 创建映射参数
	for (int i = 0; i<image.rows; i++) {
		for (int j = 0; j<image.cols; j++) {
			// (i,j)像素的新位置
			srcX.at<float>(i, j) = j; // 保持在同一列
									  // 原来在第i行的像素， 现在根据一个正弦曲线移动
			srcY.at<float>(i, j) = i + 5 * sin(j / 10.0);
		}
	}
	// 应用映射参数
	remap(image, result, srcX, srcY, cv::INTER_LINEAR);
}


void FrameProcess(Mat ori, Mat &output)
{
	Mat temp;
	sharpen(ori,temp);
	wave(temp, output);
}


int main()
{
	VideoCapture cap;
	cap.open(1);  //open the USB camera(the second camera)
	Mat output;
	Mat ori, res;
	//cap.set(CV_CAP_PROP_FRAME_WIDTH, 900);//宽度 
	//cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1600);//高度
	//cap.set(CV_CAP_PROP_BRIGHTNESS, 10);	//亮度 1
	//cap.set(CV_CAP_PROP_EXPOSURE,-6);
	//cap.set(CV_CAP_PROP_FPS, 25);
	//cap.set(CV_CAP_PROP_SATURATION,70);
	while (1)
	{
		
		cap.read(ori);	//等价于cap.read(frame);
       // Canny(frame, frame, 30, 100);//canny边缘检测，去掉这一行就是纯粹的读取摄像头了
	    //cvtColor(frame, frame, CV_BGR2HSV);//BGR空间转为HSV颜色空间，注意，两者不能同时对同一张图片（在此为frame）进行处理，否则报错
		//if (ori.empty())
			//cout << "Empty" << endl; break;
		//cout << cap.get(CV_CAP_PROP_EXPOSURE) << endl;
		//cout << cap.get(CV_CAP_PROP_BRIGHTNESS) <<endl;
		
		//cout << cap.get(CV_CAP_PROP_SATURATION) << endl;
		FrameProcess(ori, output);
		imshow("video", output);
		if (waitKey(20)>0)//按下任意键退出摄像头　　因电脑环境而异，有的电脑可能会出现一闪而过的情况
			  break;
	}
	
	cap.release();
	destroyAllWindows();//关闭所有窗口
	//waitKey(30);
	return 0;
}
