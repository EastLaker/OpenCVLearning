#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<cv.h>
using namespace std;
using namespace cv;

void sharpen(const Mat &image, Mat &result) 
{
	// �ж��Ƿ���Ҫ����ͼ�����ݡ� �����Ҫ�� �ͷ���
	result.create(image.size(), image.type());
	int nchannels = image.channels(); // ���ͨ����
									  // ���������У����˵�һ�к����һ�У�
	for (int j = 1; j < image.rows - 1; j++) {
		const uchar* previous =
			image.ptr<const uchar>(j - 1); // ��һ��
		const uchar* current =
			image.ptr<const uchar>(j); // ��ǰ��
		const uchar* next =
			image.ptr<const uchar>(j + 1); // ��һ��
		uchar* output = result.ptr<uchar>(j); // �����
		for (int i = nchannels; i < (image.cols - 1)*nchannels; i++) {
			*output++ = cv::saturate_cast<uchar>(5 * current[i] - 1 * current[i - nchannels] -
				1 * current[i + nchannels] - 1 * previous[i] - 1*next[i]);
		}  //������˹����
	} // ��δ�����������Ϊ0
	result.row(0).setTo(cv::Scalar(0));
	result.row(result.rows - 1).setTo(cv::Scalar(0));
	result.col(0).setTo(cv::Scalar(0));
	result.col(result.cols - 1).setTo(cv::Scalar(0));
}

void salt(cv::Mat image, int n) {
	int i, j;
	for (int k = 0; k<n; k++) {
		// rand()�������������
		i = std::rand() % image.cols;
		j = std::rand() % image.rows;
		if (image.type() == CV_8UC1) { // �Ҷ�ͼ��
			image.at<uchar>(j, i) = 255;
		}
		else if (image.type() == CV_8UC3) { // ��ɫͼ��
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
			*data &= mask; // ����
			*data++ += div >> 1; // ����div/2
								 //data[i] = data[i] / div*div + div / 2;
		}
	}
}

void wave(const Mat &image, Mat &result) {
	// ӳ�����
	Mat srcX(image.rows, image.cols, CV_32F);
	Mat srcY(image.rows, image.cols, CV_32F);
	// ����ӳ�����
	for (int i = 0; i<image.rows; i++) {
		for (int j = 0; j<image.cols; j++) {
			// (i,j)���ص���λ��
			srcX.at<float>(i, j) = j; // ������ͬһ��
									  // ԭ���ڵ�i�е����أ� ���ڸ���һ�����������ƶ�
			srcY.at<float>(i, j) = i + 5 * sin(j / 10.0);
		}
	}
	// Ӧ��ӳ�����
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
	cap.open(1);
	Mat output;
	Mat ori, res;
	//cap.set(CV_CAP_PROP_FRAME_WIDTH, 900);//��� 
	//cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1600);//�߶�
	//cap.set(CV_CAP_PROP_BRIGHTNESS, 10);	//���� 1
	//cap.set(CV_CAP_PROP_EXPOSURE,-6);
	//cap.set(CV_CAP_PROP_FPS, 25);
	//cap.set(CV_CAP_PROP_SATURATION,70);
	while (1)
	{
		
		cap.read(ori);	//�ȼ���cap.read(frame);
       // Canny(frame, frame, 30, 100);//canny��Ե��⣬ȥ����һ�о��Ǵ���Ķ�ȡ����ͷ��
	    //cvtColor(frame, frame, CV_BGR2HSV);//BGR�ռ�תΪHSV��ɫ�ռ䣬ע�⣬���߲���ͬʱ��ͬһ��ͼƬ���ڴ�Ϊframe�����д������򱨴�
		//if (ori.empty())
			//cout << "Empty" << endl; break;
		//cout << cap.get(CV_CAP_PROP_EXPOSURE) << endl;
		//cout << cap.get(CV_CAP_PROP_BRIGHTNESS) <<endl;
		
		//cout << cap.get(CV_CAP_PROP_SATURATION) << endl;
		FrameProcess(ori, output);
		imshow("video", output);
		if (waitKey(20)>0)//����������˳�����ͷ��������Ի������죬�еĵ��Կ��ܻ����һ�����������
			  break;
	}
	
	cap.release();
	destroyAllWindows();//�ر����д���
	//waitKey(30);
	return 0;
}