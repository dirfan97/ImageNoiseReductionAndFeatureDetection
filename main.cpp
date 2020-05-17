#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
using namespace std;
using namespace cv;

Mat RemoveNoise(Mat pic){
	int row = pic.rows;
	int col = pic.cols;
	for (int i=1 ; i<row-1 ; i++){
		for (int j=0 ; j<col-1 ; j++){
			if ((pic.at<unsigned char>(i-1,j)==0 && pic.at<unsigned char>(i+1,j)==0)&&
			(pic.at<unsigned char>(i,j-1)==0 && pic.at<unsigned char>(i,j+1)==0)&&
			(pic.at<unsigned char>(i-1,j-1)==0 && pic.at<unsigned char>(i+1,j+1)==0)&&
			(pic.at<unsigned char>(i+1,j-1)==0 && pic.at<unsigned char>(i-1,j+1)==0))
			{	
				pic.at<unsigned char>(i,j)=0; 	 
			}
		}
	}	
	return pic;
}

Mat RemoveNoise10(Mat pic){
	int row = pic.rows;
	int col = pic.cols;
	for (int i=1 ; i<row-10 ; i++){
		for (int j=0 ; j<col-10 ; j++){
			if ((pic.at<unsigned char>(i-10,j)==0 && pic.at<unsigned char>(i+10,j)==0)&&
			(pic.at<unsigned char>(i,j-10)==0 && pic.at<unsigned char>(i,j+10)==0)&&
			(pic.at<unsigned char>(i-10,j-10)==0 && pic.at<unsigned char>(i+10,j+10)==0)&&
			(pic.at<unsigned char>(i+10,j-10)==0 && pic.at<unsigned char>(i-10,j+10)==0))
			{	
				pic.at<unsigned char>(i,j)=0; 	 
			}
		}
	}	
	return pic;
}

Mat RemoveNoise5(Mat pic){
	int row = pic.rows;
	int col = pic.cols;
	for (int i=1 ; i<row-5 ; i++){
		for (int j=0 ; j<col-5 ; j++){
			if ((pic.at<unsigned char>(i-5,j)==0 && pic.at<unsigned char>(i+5,j)==0)&&
			(pic.at<unsigned char>(i,j-5)==0 && pic.at<unsigned char>(i,j+5)==0)&&
			(pic.at<unsigned char>(i-5,j-5)==0 && pic.at<unsigned char>(i+5,j+5)==0)&&
			(pic.at<unsigned char>(i+5,j-5)==0 && pic.at<unsigned char>(i-5,j+5)==0))
			{	
				pic.at<unsigned char>(i,j)=0; 	 
			}
		}
	}	
	return pic;
}

Mat RemoveNoise20(Mat pic){
	int row = pic.rows;
	int col = pic.cols;
	for (int i=1 ; i<row-20 ; i++){
		for (int j=0 ; j<col-20 ; j++){
			if ((pic.at<unsigned char>(i-20,j)==0 && pic.at<unsigned char>(i+20,j)==0)&&
			(pic.at<unsigned char>(i,j-20)==0 && pic.at<unsigned char>(i,j+20)==0)&&
			(pic.at<unsigned char>(i-20,j-20)==0 && pic.at<unsigned char>(i+20,j+20)==0)&&
			(pic.at<unsigned char>(i+20,j-20)==0 && pic.at<unsigned char>(i-20,j+20)==0))
			{	
				pic.at<unsigned char>(i,j)=0; 	 
			}
		}
	}	
	return pic;
}

Mat Threshed(Mat pic){
	int row = pic.rows;
	int col = pic.cols;
	for (int i=0 ; i<row ; i++){
		for (int j=0 ; j<col ; j++){
			if (pic.at<unsigned char>(i,j) > 115){
				pic.at<unsigned char>(i,j) = 0;
			}else{
				pic.at<unsigned char>(i,j) = 255;
			}
		}
	}
	return RemoveNoise20(RemoveNoise10(RemoveNoise(pic)));
}

int* RowWiseFrequency(Mat pic){
	const int row = pic.rows;
	const int col = pic.cols;
	
	cout<<"Row: "<<row<<" Cols: "<<col<<endl;
	int counter=0;
	int *arr2;
	
	arr2 = new int[row];
	for (int i=0 ; i<row-2 ; i+=2){
		for (int j=0 ; j<col-1 ; j++){
			if (pic.at<unsigned char>(i,j) == 0 && pic.at<unsigned char>(i,j+1) == 255){
				counter+=1;
			}
		}
		arr2[i] = counter;
		counter = 0;
		
	}	

	return arr2;
}

int* ColWiseFrequency(Mat pic){
	const int row = pic.rows;
	const int col = pic.cols;
	
	cout<<"Row: "<<row<<" Cols: "<<col<<endl;
	int counter=0;
	int *arr2;
	
	arr2 = new int[col];
	for (int i=0 ; i<row-1 ; i++){
		for (int j=0 ; j<col-2 ; j+=2){
			if (pic.at<unsigned char>(i,j) == 0 && pic.at<unsigned char>(i+1,j) == 255){
				counter+=1;
			}
		arr2[j] = counter;
		}
		
		counter = 0;
		
	}	

	return arr2;
}

int main(){	
	string fileName = "ZERO.jpg";
	Mat pic = imread(fileName);
	Mat img;
	//imshow("ORIG" , pic);
	cvtColor(pic, img, COLOR_BGR2GRAY);
	int row = img.rows;
	int col = img.cols;
    int x = row/2;
    
    vector<int> compression_params;
    compression_params.push_back(IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);
    
    if(img.empty())
    {
        cout << "Could not read the image: " << fileName << endl;
        return 1;
    }
    Mat threshedPic = Mat::zeros(img.rows, img.cols, CV_8UC1);
        //imshow("without thres", img);
       	threshedPic = Threshed(img);
        imshow("Display window 2", threshedPic);
        imwrite("ZEROBinWindow10,1,20.png", threshedPic,compression_params );
        waitKey(0);	
        
       int *row_wise = RowWiseFrequency(threshedPic);
       int *col_wise = ColWiseFrequency(threshedPic);
       for (int i=0 ; i<row-2 ; i+=2){
			cout<< i<<" row : " <<row_wise[i]<<endl;		
		}
		for (int i=0 ; i<col-2 ; i+=2){
			cout<< i<<" col : " <<col_wise[i]<<endl;		
		}
		
	return 0;
}
