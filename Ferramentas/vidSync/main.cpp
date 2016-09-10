#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

int main(int argc, char** argv){
	if(argc<2){
		std::cout<<"Número insuficiente de argumentos"<<std::endl;
	}
	cv::VideoCapture cap(argv[1]);

	

	return 0;
}
