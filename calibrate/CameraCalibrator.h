/*------------------------------------------------------------------------------------------*\
   This file contains material supporting chapter 9 of the cookbook:  
   Computer Vision Programming using the OpenCV Library. 
   by Robert Laganiere, Packt Publishing, 2011.

   This program is free software; permission is hereby granted to use, copy, modify, 
   and distribute this source code, or portions thereof, for any purpose, without fee, 
   subject to the restriction that the copyright notice may not be removed 
   or altered from any source or altered source distribution. 
   The software is released on an as-is basis and without any warranties of any kind. 
   In particular, the software is not guaranteed to be fault-tolerant or free from failure. 
   The author disclaims all warranties with regard to this software, any use, 
   and any consequent failure, is purely the responsibility of the user.
 
   Copyright (C) 2010-2011 Robert Laganiere, www.laganiere.name
\*------------------------------------------------------------------------------------------*/

#ifndef CAMERACALIBRATOR_H
#define CAMERACALIBRATOR_H

#include <vector>
#include <iostream>

#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class CameraCalibrator {

	// input points�����
    std::vector<std::vector<cv::Point3f>> objectPoints;			//��������ϵ�µĵ�
    std::vector<std::vector<cv::Point2f>> imagePoints;			//��������ϵ�µĵ�
    // output Matrices�������
    cv::Mat cameraMatrix;										//������ڲ�������
    cv::Mat distCoeffs;											//͸������ϵ������
	// flag to specify how calibration is done�궨��ʽ
	int flag;
	// used in image undistortion ����ͼ��ȥ����
    cv::Mat map1,map2; 
	bool mustInitUndistort;

  public:
	//Output rotations and translations
    std::vector<cv::Mat> rvecs, tvecs;
	CameraCalibrator() : flag(0), mustInitUndistort(true) {};

	// Open the chessboard images and extract corner points����궨ͼƬ��ȡ�ǵ�
	int addChessboardPoints(const std::vector<std::string>& filelist, cv::Size & boardSize);
	// Add scene points and corresponding image points��ӳ��������Ӧ��ͼ���
    void addPoints(const std::vector<cv::Point2f>& imageCorners, const std::vector<cv::Point3f>& objectCorners);
	// Calibrate the camera�궨���
	double calibrate(cv::Size &imageSize);
    // Set the calibration flag���ñ궨��ʽ
    void setCalibrationFlag(bool radial8CoeffEnabled=false, bool tangentialParamEnabled=false);
	// Remove distortion in an image (after calibration)����͸������(�궨֮�������Ч)
	cv::Mat CameraCalibrator::remap(const cv::Mat &image);

    // Getters��ȡ����
    cv::Mat getCameraMatrix() { return cameraMatrix; }
    cv::Mat getDistCoeffs()   { return distCoeffs; }
};

#endif // CAMERACALIBRATOR_H
